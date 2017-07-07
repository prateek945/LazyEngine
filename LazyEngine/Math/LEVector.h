#pragma once
#ifndef LEVECTOR_H_
#define LEVECTOR_H_
#include "MathHelpers.h"
using namespace std;
namespace LE {
	template <class T = Primitives::Float32>
	class LEVector3 {
	public:
		//So that an array of 3 values can be used directly as well
		union
		{
			T m_values[3];
			struct
			{
				T m_x, m_y, m_z;
			};
		};
		LEVector3<T>() : m_x(0), m_y(0), m_z(0) {}
		LEVector3<T>(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}
		LEVector3<T>(const T &val) : m_x(*val), m_y(*val), m_z(*val) {}
		LEVector3<T>(const T val) : m_x(val), m_y(val), m_z(val) {}
		LEVector3<T>(const LEVector3<T> &copy) : m_x(copy.m_x), m_y(copy.m_y), m_z(copy.m_z) {}

		//magnitude operations

		T length() { return (T)sqrt(m_x*m_x + m_y*m_y + m_z*m_z); }

		T lengthSqrd() { return (T)(m_x*m_x + m_y*m_y + m_z*m_z); }

		T dotProduct(const LEVector3<T> &v) {
			return (m_x*v.m_x + m_y*v.m_y + m_z*v.m_z);
		}
		void crossProduct(const LEVector3<T> &v) {
			Primitives::Float32 copyX, copyY, copyZ;
			copyX = (m_y*v.m_z - m_z*v.m_y);
			copyY = (m_z*v.m_x - m_x*v.m_z);
			copyZ = (m_x*v.m_y - m_y*v.m_x);
			m_x = copyX; m_y = copyY; m_z = copyZ;
		}
		//Vector operations =,+,-,/,*
		void operator += (const LEVector3<T> &v1) { m_x += v1.m_x; m_y += v1.m_y; m_z += v1.m_z; }
		void operator -= (const LEVector3<T> &v1) { m_x -= v1.m_x; m_y -= v1.m_y; m_z -= v1.m_z; }
		void operator *= (const T &val) { m_x *= val; m_y *= val; m_z *= val; }
		void operator /= (const T &val) { LAZYASSERT((val != 0)) m_x /= val; m_y /= val; m_z /= val; }

		friend ostream &operator << (ostream &output, LEVector3<T> &v) {
			output << "X : " << v.m_values[0] << ", Y : " << v.m_values[1] << ", Z : " << v.m_values[2] << "\n";
			return output;
		}

	};
	template <typename T>
	inline LEVector3<T> operator * (const T &val, const LEVector3<T> &v1) { return LEVector3<T>(v1.m_x*val, v1.m_y*val, v1.m_z*val); }
	template <typename T>
	inline LEVector3<T> operator / (const LEVector3<> &v1, const T &val) { return LEVector3<>(v1.m_x / val, v1.m_y / val, v1.m_z / val); }
	template <typename T>
	inline LEVector3<T> operator + (const LEVector3<T> &v1, const LEVector3<T> &v2)
	{
		return LEVector3<T>(v1.m_x + v2.m_x,
			v1.m_y + v2.m_y,
			v1.m_z + v2.m_z);
	}
	template <typename T>
	inline LEVector3<T> operator - (const LEVector3<T> &v1, const LEVector3<T> &v2)
	{
		return LEVector3<T>(v1.m_x - v2.m_x,
			v1.m_y - v2.m_y,
			v1.m_z - v2.m_z);
	}
	//bool operations == , > , <
	template <typename T>
	inline bool operator == (const LEVector3<T> &v1, const LEVector3<T> &v2)
	{
		return (compareVals(v1.m_x, v2.m_x)
			&& compareVals(v1.m_y, v2.m_y)
			&& compareVals(v1.m_z, v2.m_z)
			);
	}
	template <typename T>
	inline LEVector3<T> operator - (const LEVector3<T> &v) {
		return (LEVector3<T>(-v.m_values[0], -v.m_values[1], -v.m_values[2]));
	}
	template <typename T>
	inline bool operator > (const LEVector3<T> &v1, const LEVector3<T> &v2) {
		return ((v1.m_x > v2.m_x)
			&& (v1.m_y > v2.m_y)
			&& (v1.m_z > v2.m_z));
	}
	template <typename T>
	inline bool operator < (const LEVector3<T> &v1, const LEVector3<T> &v2) {
		return ((v1.m_x < v2.m_x)
			&& (v1.m_y < v2.m_y)
			&& (v1.m_z < v2.m_z));
	}
};
#endif // File Guard