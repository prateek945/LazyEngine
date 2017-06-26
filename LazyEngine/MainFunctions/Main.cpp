#include "Main.h"
using namespace std;
int main(int argc, char* argv[]) {
	cout << "Hello";
	LEVector3<Primitives::Float32> V1;
	V1 += LEVector3<>(1.0f, 2.0f, 3.0f);
	LEVector3<> V2(5.0, 6.0, 7.0);
	cout << "Vector ops:\n" << (V1 + V2).m_x << "\n" << ((Primitives::Float32)3.0f *V1).m_x << "\n";
	cout << V1.m_values[0]<<"\nlength : "<<V1.length()<<"\nlength squared : "<<V1.lengthSqrd();
	cout << "\n\n";
	LEVector3<Primitives::Int32> VI1(1,2,3), VI2(4,5,6),VI3(1,2,3);
	cout << (VI1 == VI2) << "\t" << (VI1 < VI2) << "\t" << (VI1 == VI3) << "\n";
	while (true) {
		continue;
	}
	return 0;
}