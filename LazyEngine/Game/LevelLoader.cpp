#include "LevelLoader.h"

namespace LE {

	bool LevelLoader::loadLevelGameObjs() {
		char base[1024];
		strcpy(base, "C:\\LazyEngine\\LazyEngine\\LazyEngine\\levels\\");
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
			
			while (strcmp(nextLine, "EndObject")!=0) {
				if (strcmp(nextLine, "BeginObject")==0) {
					fr.readNextNonEmptyLine(nextLine, 256);
				}	
				else if (strcmp(nextLine, "Name") == 0) {
					fr.readNextNonEmptyLine(nextLine, 256);
					
					strcpy(g.objectName, nextLine);
					fr.readNextNonEmptyLine(nextLine, 256);
				}
				else if(strcmp(nextLine,"Matrix")==0){
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							fr.readNextFloat(g.objMatrix.m_values[i][j]);
						}
					}
					fr.readNextNonEmptyLine(nextLine, 256);
				}
				else if (strcmp(nextLine, "BeginObjectPhysics")==0) {
					fr.readNextNonEmptyLine(nextLine, 256);
					std::shared_ptr<Colliders::Collider> col;
					Colliders::ColliderMeta m = {};
					if (strcmp(g.objectName, "Cube") == 0) { 
						PrimitiveShapes::Point p(g.objMatrix.getTranslation());
						
						col = std::make_shared<Colliders::Cube>(m); }
					else if (strcmp(g.objectName, "Sphere") == 0) col = std::make_shared<Colliders::Sphere>(m);
					col->metaData.ObjId = i;
					col->metaData.objMat = g.objMatrix;
					while (strcmp(nextLine, "EndObjectPhysics")!=0) {
						if (strcmp(nextLine, "IsMovable") == 0) {
							Primitives::Int32 ph;
							fr.readNextInt(ph);
							col->metaData.bisMovable = (Primitives::Bool) ph;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						else if (strcmp(nextLine, "Gravity")==0) {
							Primitives::Int32 ph;
							fr.readNextInt(ph);
							col->metaData.Gravity = (Primitives::Bool) ph;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
						else if (strcmp(nextLine, "Mass") == 0) {
							Primitives::Float32 ph;
							fr.readNextFloat(ph);
							col->metaData.mass = ph;
						    fr.readNextNonEmptyLine(nextLine, 256);
						}
						else if (strcmp(nextLine, "Velocity") == 0) {
							Primitives::Float32 ph;
							fr.readNextFloat(ph);
							col->metaData.velocityMagnitude = ph;
							fr.readNextFloat(ph);
							col->metaData.velocityDir.m_x = ph;
							fr.readNextFloat(ph);
							col->metaData.velocityDir.m_y = ph;
							fr.readNextFloat(ph);
							col->metaData.velocityDir.m_z = ph;
							fr.readNextNonEmptyLine(nextLine, 256);
						}
					}
					fr.readNextNonEmptyLine(nextLine, 256);
					PhysicsManager::getInstance()->get()->objects[0].push_back(col);
					PhysicsManager::getInstance()->get()->objects[1].push_back(col);
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
			string key(g.objectName);
			
			
			
			//Check Key exists and add to gpu buffer
			
			if (m_instances.find(key) == m_instances.end()) {
				char base2[1024];
				strcpy(base, "C:\\LazyEngine\\LazyEngine\\LazyEngine\\meshes\\VertexBuffer\\");
				strcat(base, g.objectName);
				strcat(base, ".vb");
				FileReader fr2(base);
				vector<Primitives::Float32> m_vertices;
				vector<Primitives::Float32> m_color;
				vector<Primitives::UInt32> m_indices;
				
				fr2.readNextUInt(g.num_verts);
				for (unsigned int j = 0; j < g.num_verts * 3; j++) {
					Primitives::Float32 temp;
					fr2.readNextFloat(temp);
					m_vertices.push_back(temp);
				}
				strcpy(base, "C:\\LazyEngine\\LazyEngine\\LazyEngine\\meshes\\ColorBuffer\\");
				strcat(base, g.objectName);
				strcat(base, ".cb");
				FileReader fr3(base);
				fr3.readNextUInt(g.num_verts);
				for (int j = 0; j < g.num_verts * 3; j++) {
					Primitives::Float32 temp;
					fr3.readNextFloat(temp);
					m_color.push_back(temp);
				}
				strcpy(base, "C:\\LazyEngine\\LazyEngine\\LazyEngine\\meshes\\IndexBuffer\\");
				strcat(base, g.objectName);
				strcat(base, ".ib");
				FileReader fr4(base);
			
				fr4.readNextUInt(g.num_indices);
				for (int j = 0; j < g.num_indices * 3; j++) {
					Primitives::Int32 temp;
					fr4.readNextInt(temp);
					m_indices.push_back(temp);
				}
				
				m_instances[key] = make_pair(gpubuffer.m_vertices.size() , gpubuffer.m_indices.size());
				for (unsigned int j = 0; j < g.num_verts; j++) {
					gpubuffer.m_vertices.push_back(m_vertices[3* j]); gpubuffer.m_vertices.push_back(m_vertices[3* j +1]); gpubuffer.m_vertices.push_back(m_vertices[3* j +2]);
					gpubuffer.m_vertices.push_back(m_color[3 * j]); gpubuffer.m_vertices.push_back(m_color[3 * j + 1]); gpubuffer.m_vertices.push_back(m_color[3 * j + 2]);
				}
				for (unsigned int j = 0; j < g.num_indices*3; j++) {
					gpubuffer.m_indices.push_back(m_indices[j]);
				}
				
				
			}
			g_gameObjs.push_back(g);
			
		}
		
		return true;
	}
};