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

	

		Quaternion q1, q2;
		q1 = Quaternion(1, 1, 1, 1);
		q2 = Quaternion(2, 2, 2, 2);
		Quaternion q3 = q1*q2;
		Quaternion q4(q3);
		q4.normalise();
		cout << q3;
		cout << q4 <<*q4;
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
