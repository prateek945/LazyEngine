#include "Main.h"
#include <time.h>
using namespace std;
int main(int argc, char* argv) {

	cout << "Hello\n";
	gLogManager.startUp();
	LAZYASSERT(gLogManager.get())
	LEVector3<Primitives::Float32> V1;
	V1 += LEVector3<>(1.f, 2.f, 3.f);
	LEVector3<> V2(4.f, 5.f, 6.f);
	LEVector3<> V3(7.f, 8.f, 9.f);
	
	Matrix3X3<> M1(V1, V2, V3);
	Matrix3X3<> M2(M1);
	LEVector3<> V4 = V1 * M1;
	cout << "Multipplication Matrix : " << V4.m_x << " " << V4.m_y << " " << V4.m_z << "\n";
	Matrix3X3<> Mult = M1*M2;
	cout << Mult;
	gLogManager.get()->Log("%0.2f", V1.length());


	while (true) {
		continue;
	}
	return 0;
}