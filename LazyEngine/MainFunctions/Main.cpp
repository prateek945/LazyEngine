#include "Main.h"
using namespace std;
int main(int argc, char* argv) {

	cout << "Hello";
	gLogManager.startUp();
	LAZYASSERT(gLogManager.get())
	LEVector3<Primitives::Float32> V1;
	V1 += LEVector3<>(1.f, 2.f, 3.f);
	LEVector3<> V2(5.f, 6.f, 7.f);
	LEVector3<> V3(7.f, 8.f, 9.f);
	
	Matrix3X3<> M1(V1, V2, V3);
	cout << "Matrix : " << M1.m_values[1][1];

	gLogManager.get()->Log("%0.2f", V1.length());


	while (true) {
		continue;
	}
	return 0;
}