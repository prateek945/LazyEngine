#pragma once
#include "../../Includes/LazyIncludes.h"
#include "../../Memory/Handle.h"
#include "../../Math/LEVector.h"
#include "../../LazyFiling/FileHandler.h"
#include "../../Utils/LArray.h"
#include <vector>
#include <string>
namespace LE {
	class VertexBufferCPU {
		Primitives::Int32 m_count;
		LArray<Primitives::Float32> m_data;
		std::string m_name;
	public:
		VertexBufferCPU(std::string name);
		
		void addData(Primitives::Float32 vert);
		//Function to get back a vector3 of x,y,z verts given an index into the m_data (Index should be mod 3) returns 0 otherwise
		Primitives::Float32 getVertAtIndex(Primitives::Int32 index);
		//Function to get number of vertices within this mesh
		Primitives::Int32  getNumVerts();
		//Function to get the mesh name
		std::string getMeshName();
		//Function to set mesh name return 1 if successful else 0
		Primitives::Int16 setMeshName(std::string name);
		//Get Full m_data
		LArray<Primitives::Float32> getData() { return m_data; }
		//Read Vertex Data From File.
		void ReadDataFromFile();

	};
};