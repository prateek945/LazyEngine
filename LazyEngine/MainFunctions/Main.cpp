#include "Main.h"
#include <time.h>
namespace LE {
	int MainWrapper() {
		cout << "Hello\n";

		LogManager *gLogManager = LogManager::getInstance();
		gLogManager->startUp();
		LAZYASSERT(gLogManager->get(), "Log Manager Not Set")
			
		MemoryManager *gMemoryManager = MemoryManager::getInstance();
		gMemoryManager->startUp();
		LAZYASSERT(gMemoryManager->get(), "Memory Manager Not Set")

		gLogManager->get()->Log("%u\n%u\n",sizeof(Matrix3X3<>),sizeof(LEVector3<>));
		for (int i = 0; i < 100000; i++) {
			LEVector3<>* vecPtr = (LEVector3<>*) gMemoryManager->get()->getStackAllocator()->Alloc(sizeof(LEVector3<>));
			Matrix3X3<>* matPtr = (Matrix3X3<>*) gMemoryManager->get()->getStackAllocator()->Alloc(sizeof(Matrix3X3<>));
		}
		gLogManager->get()->Log("Done");
		//matPtr->identityMatrix();
		//cout << *matPtr;
		
		/*LEVector3<Primitives::Float32> V1;
		V1 += LEVector3<>(1.f, 2.f, 3.f);
		LEVector3<> V2(4.f, 5.f, 6.f);
		LEVector3<> V3(7.f, 8.f, 9.f);

		Matrix3X3<> M1(V1, V2, V3);
		Matrix3X3<> M2(M1);
		LEVector3<> V4 = V1 * M1;
		cout << "Multipplication Matrix : " << V4.m_x << " " << V4.m_y << " " << V4.m_z << "\n";
		Matrix3X3<> Mult = M1*M2;
		cout << Mult;*/
//		gLogManager->get()->Log("%0.2f", V1.length());


		while (true) {
			continue;
		}
		return 0;
	}
};

using namespace std;
int main(int argc, char* argv) {

	LE::MainWrapper();
}
