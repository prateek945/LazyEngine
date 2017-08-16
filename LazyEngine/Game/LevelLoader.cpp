#include "LevelLoader.h"

namespace LE {

	void LevelLoader::storeCPUVertDataForObj(GameObject &g) {
		string key(g.objectName);
		//Check Key exists and add to gpu buffer
//TODO(Prateek) : Make changes so that only refernces to buffers are stored within the Gameobject & not a copy
		char base[1024];
		strcpy(base, "..\\LazyEngine\\meshes\\VertexBuffer\\");
		strcat(base, g.objectName);
		strcat(base, ".vb");
		FileReader fr2(base);
			

		fr2.readNextUInt(g.num_verts);
		for (unsigned int j = 0; j < g.num_verts * 3; j++) {
			Primitives::Float32 temp;
			fr2.readNextFloat(temp);
			g.m_vertices.push_back(temp);
		}
		strcpy(base, "..\\LazyEngine\\meshes\\ColorBuffer\\");
		strcat(base, g.objectName);
		strcat(base, ".cb");
		FileReader fr3(base);
		fr3.readNextUInt(g.num_verts);
		for (int j = 0; j < g.num_verts * 3; j++) {
			Primitives::Float32 temp;
			fr3.readNextFloat(temp);
			g.m_color.push_back(temp);
		}
		strcpy(base, "..\\LazyEngine\\meshes\\NormalBuffer\\");
		strcat(base, g.objectName);
		strcat(base, ".nb");
		FileReader fr5(base);
		fr5.readNextUInt(g.num_verts);
		for (int j = 0; j < g.num_verts * 3; j++) {
			Primitives::Float32 temp;
			fr5.readNextFloat(temp);
			g.m_normals.push_back(temp);
		}
		strcpy(base, "..\\LazyEngine\\meshes\\IndexBuffer\\");
		strcat(base, g.objectName);
		strcat(base, ".ib");
		FileReader fr4(base);

		fr4.readNextUInt(g.num_indices);
		for (int j = 0; j < g.num_indices * 3; j++) {
			Primitives::Int32 temp;
			fr4.readNextInt(temp);
			g.m_indices.push_back(temp);
		}
		if (m_instances.find(key) == m_instances.end()) {
			m_instances[key] = make_pair(gpubuffer.m_vertices.size(), gpubuffer.m_indices.size());
			for (unsigned int j = 0; j < g.num_verts; j++) {
				gpubuffer.m_vertices.push_back(g.m_vertices[3 * j]); gpubuffer.m_vertices.push_back(g.m_vertices[3 * j + 1]); gpubuffer.m_vertices.push_back(g.m_vertices[3 * j + 2]);
				gpubuffer.m_vertices.push_back(g.m_color[3 * j]); gpubuffer.m_vertices.push_back(g.m_color[3 * j + 1]); gpubuffer.m_vertices.push_back(g.m_color[3 * j + 2]);
				gpubuffer.m_vertices.push_back(g.m_normals[3 * j]); gpubuffer.m_vertices.push_back(g.m_normals[3 * j + 1]); gpubuffer.m_vertices.push_back(g.m_normals[3 * j + 2]);
				
			}
			for (unsigned int j = 0; j < g.num_indices * 3; j++) {
				gpubuffer.m_indices.push_back(g.m_indices[j]);
			}
		}
	}
	bool LevelLoader::loadLevelGameObjs() {
		char base[1024];
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
					storeCPUVertDataForObj(g);
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
							if (strcmp(nextLine, "Cube") == 0) {
								col = std::make_shared<Colliders::Cube>(m);
								col.get()->generateValuesFromBuffer(g.m_vertices);
								col2 = std::make_shared<Colliders::Cube>(m);
								col2.get()->generateValuesFromBuffer(g.m_vertices);
							}
							else if (strcmp(nextLine, "Sphere") == 0) {
								col = std::make_shared<Colliders::Sphere>(m); 
								col.get()->generateValuesFromBuffer(g.m_vertices);
								col2 = std::make_shared<Colliders::Sphere>(m);
								col2.get()->generateValuesFromBuffer(g.m_vertices);
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