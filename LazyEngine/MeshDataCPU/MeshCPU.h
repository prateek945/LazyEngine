#ifndef MESHCPU_H_
#define MESHCPU_H_
#include "../Includes/LazyIncludes.h"
#include "../Memory/Handle.h"
#include "../Math/LEVector.h"
namespace LE {
	class MeshCPU {
		Handle* m_hVertexBufferCPU,m_hNormalBufferCPU,m_hTangentBufferCPU;

	};
};

#endif