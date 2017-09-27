#pragma once

#include "../../Includes/LazyIncludes.h"
#include "../../Memory/Handle.h"
#include "../../Math/LEVector.h"
#include "../../LazyFiling/FileHandler.h"
#include <vector>
#include <string>
namespace LE {
	class IndexBufferCPU {
		Primitives::Int32 m_count;
		std::vector<Primitives::Float32> m_data;
		std::string m_name;
	public:
		IndexBufferCPU(std::string name);

		void addData(Primitives::Float32 vert);
		//Function to get back a vector3 of x,y,z verts given an index into the m_data (Index should be mod 3) returns 0 otherwise
		Primitives::Int16 getVertAtIndex(Primitives::Int32 index, LEVector3& vert);
		//Function to get number of vertices within this mesh
		Primitives::Int32  getNumVerts();
		//Function to get the mesh name
		std::string getMeshName();
		//Function to set mesh name return 1 if successful else 0
		Primitives::Int16 setMeshName(std::string name);
		void ReadDataFromFile();

	};
};
