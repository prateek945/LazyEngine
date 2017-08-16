#pragma once
#ifndef LEVECTOR_H_
#define LEVECTOR_H_
#include "MathHelpers.h"
using namespace std;
namespace LE {
	
	struct LEVector3 {
	public:
		//So that an array of 3 values can be used directly as well
		union
		{
			Primitives::Float32 m_values[3];
			struct
			{
				Primitives::Float32 m_x, m_y, m_z;
			};
		};
		LEVector3() : m_x(0), m_y(0), m_z(0) {}
		LEVector3(Primitives::Float32 x, Primitives::Float32 y, Primitives::Float32 z) : m_x(x), m_y(y), m_z(z) {}
		LEVector3(const Primitives::Float32 &val) : m_x(val), m_y(val), m_z(val) {}
		LEVector3(const Primitives::Float32 val) : m_x(val), m_y(val), m_z(val) {}
		LEVector3(const LEVector3 &copy) : m_x(copy.m_x), m_y(copy.m_y), m_z(copy.m_z) {}
	
		//magnitude operations

		Primitives::Float32 length() { return (Primitives::Float32)sqrt(m_x*m_x + m_y*m_y + m_z*m_z); }

		Primitives::Float32 lengthSqrd() { return (Primitives::Float32)(m_x*m_x + m_y*m_y + m_z*m_z); }

		Primitives::Float32 dotProduct(const LEVector3 &v) {
			return (m_x*v.m_x + m_y*v.m_y + m_z*v.m_z);
		}
		void Normalize() {
			Primitives::Float32 lengthnorm = length();
			if (lengthnorm != 0.f) {
				m_x /= lengthnorm;
				m_y /= lengthnorm;
				m_z /= lengthnorm;
			}
		}
		void crossProduct(const LEVector3 &v) {
			Primitives::Float32 copyX, copyY, copyZ;
			copyX = (m_y*v.m_z - m_z*v.m_y);
			copyY = (m_z*v.m_x - m_x*v.m_z);
			copyZ = (m_x*v.m_y - m_y*v.m_x);
			m_x = copyX; m_y = copyY; m_z = copyZ;
		}
		void crossProduct(const LEVector3 &v1, const LEVector3 &v2) {
			Primitives::Float32 copyX, copyY, copyZ;
			copyX = (v1.m_y*v2.m_z - v1.m_z*v2.m_y);
			copyY = (v1.m_z*v2.m_x - v1.m_x*v2.m_z);
			copyZ = (v1.m_x*v2.m_y - v1.m_y*v2.m_x);
			m_x = copyX; m_y = copyY; m_z = copyZ;
		}
		//Vector operations =,+,-,/,*
		void operator += (const LEVector3 &v1) { m_x += v1.m_x; m_y += v1.m_y; m_z += v1.m_z; }
		void operator -= (const LEVector3 &v1) { m_x -= v1.m_x; m_y -= v1.m_y; m_z -= v1.m_z; }
		void operator *= (const Primitives::Float32 &val) { m_x *= val; m_y *= val; m_z *= val; }
		void operator *= (const LEVector3 &val) { m_x *= val.m_x; m_y *= val.m_y; m_z *= val.m_z; }
		void operator /= (const Primitives::Float32 &val) { 
			 
			m_x /= val; m_y /= val; m_z /= val; }

		friend ostream &operator << (ostream &output, LEVector3 &v) {
			output << "X : " << v.m_values[0] << ", Y : " << v.m_values[1] << ", Z : " << v.m_values[2] << "\n";
			return output;
		}
		
		
	};
	inline LEVector3 operator * (const Primitives::Float32 &val, const LEVector3 &v1) { return LEVector3(v1.m_x*val, v1.m_y*val, v1.m_z*val); }
	inline LEVector3 operator * (const LEVector3 &val, const LEVector3 &v1) { return LEVector3(v1.m_x*val.m_x, v1.m_y*val.m_y, v1.m_z*val.m_z); }

	inline LEVector3 operator / (const LEVector3 &v1, const Primitives::Float32 &val) { return LEVector3(v1.m_x / val, v1.m_y / val, v1.m_z / val); }

	inline LEVector3 operator + (const LEVector3 &v1, const LEVector3 &v2)
	{
		return LEVector3(v1.m_x + v2.m_x,
			v1.m_y + v2.m_y,
			v1.m_z + v2.m_z);
	}

	inline LEVector3 operator - (const LEVector3 &v1, const LEVector3 &v2)
	{
		return LEVector3(v1.m_x - v2.m_x,
			v1.m_y - v2.m_y,
			v1.m_z - v2.m_z);
	}
	//bool operations == , > , <

	inline bool operator == (const LEVector3 &v1, const LEVector3 &v2)
	{
		return (compareVals(v1.m_x, v2.m_x)
			&& compareVals(v1.m_y, v2.m_y)
			&& compareVals(v1.m_z, v2.m_z)
			);
	}

	inline LEVector3 operator - (const LEVector3 &v) {
		return (LEVector3(-v.m_values[0], -v.m_values[1], -v.m_values[2]));
	}

	inline bool operator > (const LEVector3 &v1, const LEVector3 &v2) {
		return ((v1.m_x > v2.m_x)
			&& (v1.m_y > v2.m_y)
			&& (v1.m_z > v2.m_z));
	}

	inline bool operator < (const LEVector3 &v1, const LEVector3 &v2) {
		return ((v1.m_x < v2.m_x)
			&& (v1.m_y < v2.m_y)
			&& (v1.m_z < v2.m_z));
	}
};
#endif // File Guard