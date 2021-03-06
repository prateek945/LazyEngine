#include "LevelLoader.h"

namespace LE {

	void LevelLoader::storeGPUVertDataForObj(Handle m_hMesh) {
		
		//Check Key exists and add to gpu buffer
//TODO(Prateek) : Make changes so that only refernces to buffers are stored within the Gameobject & not a copy
		MeshCPU* mesh = m_hMesh.getObject<MeshCPU>();
		std::string key = mesh->m_name;
		VertexBufferCPU* verts = mesh->m_hVertexBufferCPU.getObject<VertexBufferCPU>();
		m_GPUIndices[key] = make_pair(gpubuffer.m_vertices.size(), gpubuffer.m_indices.size());
		IndexBufferCPU* indices = mesh->m_hIndexBufferCPU.getObject<IndexBufferCPU>();
		TextureCoordBufferCPU* texCoords = mesh->m_hTextureCoordBufferCPU.getObject<TextureCoordBufferCPU>();
		MaterialBufferCPU* material = mesh->m_hMaterialCPU.getObject<MaterialBufferCPU>();
		NormalBufferCPU* normals = mesh->m_hNormalBufferCPU.getObject<NormalBufferCPU>();
		NormalBufferCPU* tangents = nullptr;
		if (material->isDetailedMesh()) {
			tangents = mesh->m_hTangentBufferCPU.getObject<NormalBufferCPU>();
		}
		if (m_instances.find(key) == m_instances.end()) {
			std::string vertexshader; 
			std::string pixelshader;
			
			
			
			char progBase[256] = PROJPATH;
			string s = string(progBase);
			for (int i = 0; i < s.length(); i++) {
				if (progBase[i] == '\\') {
					progBase[i] = '/';
				}
			}
			
			strcat(progBase,"Meshes/GPUPrograms//");
			EffectManager* _EffectManager = EffectManager::getInstance();
			Handle h = Handle(sizeof(Effect));
			if (material->isDetailedMesh()) {
				char effectName[256] = "Detailed";
				if (!_EffectManager->getEffect(progBase,effectName,h)){
					_EffectManager->addEffect(progBase, effectName,ShaderID::DetialedShader);
				}
				for (unsigned int j = 0; j < verts->getNumVerts(); j++) {
					gpubuffer.m_vertices.push_back(verts->getVertAtIndex(3*j)); gpubuffer.m_vertices.push_back(verts->getVertAtIndex(3*j+1)); gpubuffer.m_vertices.push_back(verts->getVertAtIndex(3*j+2));
					gpubuffer.m_vertices.push_back(texCoords->getVertAtIndex(2*j)); gpubuffer.m_vertices.push_back(texCoords->getVertAtIndex(2*j+1));
					gpubuffer.m_vertices.push_back(normals->getVertAtIndex(3 * j)); gpubuffer.m_vertices.push_back(normals->getVertAtIndex(3 * j + 1)); gpubuffer.m_vertices.push_back(normals->getVertAtIndex(3 * j + 2));
					gpubuffer.m_vertices.push_back(tangents->getVertAtIndex(3 * j)); gpubuffer.m_vertices.push_back(tangents->getVertAtIndex(3 * j + 1)); gpubuffer.m_vertices.push_back(tangents->getVertAtIndex(3 * j + 2));

				}
			}
			else {
				char effectName[256] = "Simple";

				if (!_EffectManager->getEffect(progBase, effectName, h)) {
					_EffectManager->addEffect(progBase, effectName,ShaderID::StandardShader);
				}
				for (unsigned int j = 0; j < verts->getNumVerts(); j++) {
					gpubuffer.m_vertices.push_back(verts->getVertAtIndex(3 * j)); gpubuffer.m_vertices.push_back(verts->getVertAtIndex(3 * j + 1)); gpubuffer.m_vertices.push_back(verts->getVertAtIndex(3 * j + 2));
					gpubuffer.m_vertices.push_back(texCoords->getVertAtIndex(2 * j)); gpubuffer.m_vertices.push_back(texCoords->getVertAtIndex(2 * j + 1));
					gpubuffer.m_vertices.push_back(normals->getVertAtIndex(3 * j)); gpubuffer.m_vertices.push_back(normals->getVertAtIndex(3 * j + 1)); gpubuffer.m_vertices.push_back(normals->getVertAtIndex(3 * j + 2));
					gpubuffer.m_vertices.push_back(0.0f); gpubuffer.m_vertices.push_back(0.0f); gpubuffer.m_vertices.push_back(0.0f);
				}
			}
			for (unsigned int j = 0; j < indices->getNumVerts()*3; j++) {
				gpubuffer.m_indices.push_back(indices->getVertAtIndex(j));
			}
			
		}
	}
	bool LevelLoader::loadLevelGameObjs(ID3D11Device* device, ID3D11DeviceContext* context) {
		char base[1024];

		char progBase[256] = PROJPATH;
		string s = string(progBase);
		for (int i = 0; i < s.length(); i++) {
			if (progBase[i] == '\\') {
				progBase[i] = '/';
			}
		}
		strcat(progBase, "Meshes/GPUPrograms//");
		char effectName[256] = "Detailed_LightPass";
		Handle h = Handle(sizeof(Effect));
		EffectManager* _EffectManager = EffectManager::getInstance();
		
		if (!_EffectManager->getEffect(progBase, effectName, h)) {
			_EffectManager->addEffect(progBase, effectName, ShaderID::LightPass);
		}
		strcpy(base, "..\\LazyEngine\\levels\\");
		//sprintf_s(base, 1000, "%s%s", base, "C:\\LazyEngine\\LazyEngine\\LazyEngine\\levels\\");
		strcat(base, getLevelName());
		//sprintf_s(base, 1000, "%s%s", base, getLevelName());
		FileReader fr(base);
		
		fr.readNextUInt(num_gameObjs);
		char nextLine[256];
		
		for (int i = 0; i < num_gameObjs; i++) {
			GameObject g;
			g.setObjId((Primitives::UInt16)(i));
			g.hasCollider = true;

			fr.readNextNonEmptyLine(nextLine, 256);

			while (strcmp(nextLine, "EndObject") != 0) {
				if (strcmp(nextLine, "BeginObject") == 0) {
					fr.readNextNonEmptyLine(nextLine, 256);
				}
				else if (strcmp(nextLine, "Name") == 0) {
					fr.readNextNonEmptyLine(nextLine, 256);
					strcpy(g.objectName, nextLine);
					if (m_instances.find(g.objectName) == m_instances.end()) {
						Handle h = Handle(sizeof(MeshCPU));
						MeshCPU* newMesh = new(h.getAddress()) MeshCPU(device, context, g.objectName);
						
						storeGPUVertDataForObj(h);
						m_instances[g.objectName] = h;
						g.m_hMeshCPU = h;
					}
					else {
						g.m_hMeshCPU = m_instances[g.objectName];
					}
				
					fr.readNextNonEmptyLine(nextLine, 256);
				}
				else if (strcmp(nextLine, "Matrix") == 0) {
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							fr.readNextFloat(g.objMatrix.m_values[i][j]);
						}
					}
					fr.readNextNonEmptyLine(nextLine, 256);
				}
				else if (strcmp(nextLine, "isVisible") == 0) {
					Primitives::Int32 ph;
					fr.readNextInt(ph);
					g.isVisible = (Primitives::Bool)ph;
					fr.readNextNonEmptyLine(nextLine, 256);
				}
				else if (strcmp(nextLine, "Color") == 0) {
					Primitives::Float32 ph;

					fr.readNextFloat(ph);
					g.diffuseColor.m_x = ph;
					fr.readNextFloat(ph);
					g.diffuseColor.m_y = ph;
					fr.readNextFloat(ph);
					g.diffuseColor.m_z = ph;
					fr.readNextFloat(ph);
					g.alpha = ph;
					fr.readNextNonEmptyLine(nextLine, 256);
					
				}
				else if (strcmp(nextLine, "BeginObjectPhysics") == 0) {
					fr.readNextNonEmptyLine(nextLine, 256);
					std::shared_ptr<Colliders::Collider> col,col2;
					while (strcmp(nextLine, "EndObjectPhysics") != 0) {
						Colliders::ColliderMeta m = {};
						if (strcmp(nextLine, "Collider") == 0) {
							fr.readNextNonEmptyLine(nextLine, 256);
							MeshCPU* mesh = g.m_hMeshCPU.getObject<MeshCPU>();
							if (strcmp(nextLine, "Cube") == 0) {
								col = std::make_shared<Colliders::Cube>(m);
								col.get()->generateValuesFromBuffer(mesh->m_hVertexBufferCPU.getObject<VertexBufferCPU>()->getData());
								col2 = std::make_shared<Colliders::Cube>(m);
								col2.get()->generateValuesFromBuffer(mesh->m_hVertexBufferCPU.getObject<VertexBufferCPU>()->getData());
							}
							else if (strcmp(nextLine, "Sphere") == 0) {
								col = std::make_shared<Colliders::Sphere>(m); 
								col.get()->generateValuesFromBuffer(mesh->m_hVertexBufferCPU.getObject<VertexBufferCPU>()->getData());
								col2 = std::make_shared<Colliders::Sphere>(m);
								col2.get()->generateValuesFromBuffer(mesh->m_hVertexBufferCPU.getObject<VertexBufferCPU>()->getData());
							}
							col->metaData.ObjId = i;
							col->metaData.objMat = g.objMatrix;
							col2->metaData.ObjId = i;
							col2->metaData.objMat = g.objMatrix;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						if (strcmp(nextLine, "IsMovable") == 0) {
							Primitives::Int32 ph;
							fr.readNextInt(ph);
							col->metaData.bisMovable = (Primitives::Bool) ph;
							col2->metaData.bisMovable = (Primitives::Bool) ph;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						if (strcmp(nextLine, "Momentum") == 0) {
							Primitives::Int32 ph;
							fr.readNextInt(ph);
							col->metaData.bhasMomentum = (Primitives::Bool) ph;
							col2->metaData.bhasMomentum = (Primitives::Bool) ph;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						else if (strcmp(nextLine, "Gravity") == 0) {
							Primitives::Int32 ph;
							fr.readNextInt(ph);
							col->metaData.Gravity = (Primitives::Bool) ph;
							col2->metaData.Gravity = (Primitives::Bool) ph;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						else if (strcmp(nextLine, "Mass") == 0) {
							Primitives::Float32 ph;
							fr.readNextFloat(ph);
							col->metaData.mass = ph;
							col2->metaData.mass = ph;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						else if (strcmp(nextLine, "Velocity") == 0) {
							Primitives::Float32 ph;

							fr.readNextFloat(ph);
							col->metaData.Velocity.m_x = ph;
							col2->metaData.Velocity.m_x = ph;
							fr.readNextFloat(ph);
							col->metaData.Velocity.m_y = ph;
							col2->metaData.Velocity.m_y = ph;
							fr.readNextFloat(ph);
							col->metaData.Velocity.m_z = ph;
							col2->metaData.Velocity.m_z = ph;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
					}
					fr.readNextNonEmptyLine(nextLine, 256);
					col->metaData.Energy = 5.0f;
					col2->metaData.Energy = 5.0f;
					PhysicsManager::getInstance()->get()->objects[0].push_back(col);
					PhysicsManager::getInstance()->get()->objects[1].push_back(col2);
				}

				
			}
			g_gameObjs.push_back(g);
		}
		fr.readNextNonEmptyLine(nextLine, 256);
		
			if (strcmp(nextLine, "BeginLights") == 0) {
				fr.readNextUInt(num_lights);

				for (int i = 0; i < num_lights; i++) {
					LightObject newLight;
					fr.readNextNonEmptyLine(nextLine,256);
					while (strcmp(nextLine, "EndLight") != 0) {
						if (strcmp(nextLine, "BeginLight") == 0) {
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						else if (strcmp(nextLine, "Type") == 0) {
							fr.readNextNonEmptyLine(nextLine, 256);
							if (strcmp(nextLine, "Directional") == 0) {
								fr.readNextNonEmptyLine(nextLine, 256);
								newLight.type = LightType::Directional;
								newLight.position = LEVector3();
							}
						}
						else if (strcmp(nextLine, "PointingAt") == 0) {
							float num;
							fr.readNextFloat(num);
							newLight.direction.m_x = num;
							fr.readNextFloat(num);
							newLight.direction.m_y = num;
							fr.readNextFloat(num);
							newLight.direction.m_z = num;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						else if (strcmp(nextLine, "Color") == 0) {
							float num;
							fr.readNextFloat(num);
							newLight.color.m_x = num;
							fr.readNextFloat(num);
							newLight.color.m_y = num;
							fr.readNextFloat(num);
							newLight.color.m_z = num;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
					}
				}
		}
		fr.readNextNonEmptyLine(nextLine, 256);
		if (strcmp(nextLine, "BeginGlobalPhysics") == 0) {
			fr.readNextNonEmptyLine(nextLine, 256);
			while (strcmp(nextLine, "EndGlobalPhysics") != 0) {
				if (strcmp(nextLine, "Gravity") == 0) {
					Primitives::Float32 ph;
					fr.readNextFloat(ph);
					PhysicsManager::getInstance()->get()->gravity.magnitude = ph;
					fr.readNextFloat(ph);
					PhysicsManager::getInstance()->get()->gravity.direction.m_x = ph;
					fr.readNextFloat(ph);
					PhysicsManager::getInstance()->get()->gravity.direction.m_y = ph;
					fr.readNextFloat(ph);
					PhysicsManager::getInstance()->get()->gravity.direction.m_z = ph;
					fr.readNextNonEmptyLine(nextLine, 256);
				}		
			}
		}		
		return true;
	}		
};