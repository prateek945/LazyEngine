#pragma once
#ifndef MATRIX3X3_H_

#include "MathHelpers.h"
#include "LEVector.h"
#include <iostream>
//using namespace std;
namespace LE {
	using namespace std;
	enum RotateAxis {
		XAxis = 0,
		YAxis,
		ZAxis
	};
	enum RotationOrder {
		XYZ = 0,
		ZYX

	};
	
	struct Matrix3X3 {
	public:
		union
		{
			Primitives::Float32 m_values[3][3];
			Primitives::Float32 m09[9];
		};

		Matrix3X3() {
			m_values[0][0] = m_values[0][1] = m_values[0][2] = (Primitives::Float32) 0.f;
			m_values[1][0] = m_values[1][1] = m_values[1][2] = (Primitives::Float32) 0.f;
			m_values[2][0] = m_values[2][1] = m_values[2][2] = (Primitives::Float32) 0.f;
		}

		Matrix3X3(const Matrix3X3 &copy) {
			memcpy(this, &copy, sizeof(Matrix3X3));
		}
		Matrix3X3(RotateAxis axis, float angle) {
			float sintheta = sinf(angle);
			float costheta = cosf(angle);
			Matrix3X3();
			switch (axis){
				case XAxis: m_values[1][1] = costheta;
					m_values[1][2] = sintheta;
					m_values[2][1] = -sintheta;
					m_values[2][2] = costheta;
					break;
				case YAxis: m_values[0][0] = costheta;
					m_values[0][2] = -sintheta;
					m_values[2][0] = sintheta;
					m_values[2][2] = costheta;
					break;
				case ZAxis: m_values[0][0] = costheta;
					m_values[0][1] = sintheta;
					m_values[1][0] = -sintheta;
					m_values[1][1] = costheta;
					break;
			}
		}

		Matrix3X3(const LEVector3& angles, RotationOrder rotOrder = XYZ) {
			Matrix3X3 xRotate, yRotate, zRotate;
			xRotate = Matrix3X3(XAxis, angles.m_x);
			yRotate = Matrix3X3(YAxis, angles.m_y);
			zRotate = Matrix3X3(ZAxis, angles.m_z);
			switch (rotOrder) {
			case XYZ: *this = xRotate*yRotate*zRotate;
				break;
			case ZYX: *this = zRotate*yRotate*xRotate;
				break;
			}
		}

		Matrix3X3(LEVector3 u, LEVector3 v, LEVector3 n) {
			//XAxis
			m_values[0][0] = u.m_x;
			m_values[0][1] = u.m_y;
			m_values[0][2] = u.m_z;
			//YAxis
			m_values[1][0] = v.m_x;
			m_values[1][1] = v.m_y;
			m_values[1][2] = v.m_z;
			//ZAxis
			m_values[2][0] = n.m_x;
			m_values[2][1] = n.m_y;
			m_values[2][2] = n.m_z;

		}

		Matrix3X3(const Primitives::Float32 m00, Primitives::Float32 m01, const Primitives::Float32 m02,
			const Primitives::Float32 m10, const Primitives::Float32 m11, const Primitives::Float32 m12,
			const Primitives::Float32 m20, const Primitives::Float32 m21, const Primitives::Float32 m22) {

			m_values[0][0] = m00;
			m_values[0][1] = m01;
			m_values[0][2] = m02;
			m_values[1][0] = m10;
			m_values[1][1] = m11;
			m_values[1][2] = m12;
			m_values[2][0] = m20;
			m_values[2][1] = m21;
			m_values[2][2] = m22;

		}

		friend Matrix3X3 operator * (Matrix3X3 &m0, Matrix3X3 &m1) {
			Matrix3X3 returnMat = Matrix3X3();
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						returnMat.m_values[i][k] += m0.m_values[i][j] * m1.m_values[j][k];
			return returnMat;
		}
		friend LEVector3 operator * (LEVector3 &v, Matrix3X3 &m) {
			LEVector3 retVector;

			retVector.m_values[0] = v.m_x * (m.m_values[0][0]) + v.m_y * (m.m_values[1][0]) + v.m_z * (m.m_values[2][0]);
			retVector.m_values[1] = v.m_x * (m.m_values[0][1]) + v.m_y * (m.m_values[1][1]) + v.m_z * (m.m_values[2][1]);
			retVector.m_values[2] = v.m_x * (m.m_values[0][2]) + v.m_y * (m.m_values[1][2]) + v.m_z * (m.m_values[2][2]);
			return retVector;

		}
		friend ostream &operator << (ostream &output, const Matrix3X3 &m) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					output << m.m_values[i][j] << "\Primitives::Float32";
				}
				output << "\n";
			}
			return output;
		}
		void clearMatrix() {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					m_values[i][j] = 0.f;
				}
			}
		}

		void identityMatrix() {
			clearMatrix();
			m_values[0][0] = m_values[1][1] = m_values[2][2] = 1.f;
		}

		LEVector3 getU() {
			LEVector3 u = LEVector3(m_values[0][0], m_values[1][0], m_values[2][0]);
			return u;
		}

		LEVector3 getV() {
			LEVector3 v = LEVector3(m_values[0][1], m_values[1][1], m_values[2][1]);
			return v;
		}

		LEVector3 getN() {
			LEVector3 n = LEVector3(m_values[0][2], m_values[1][2], m_values[2][2]);
			return n;
		}

		Primitives::Float32 det() {

			Primitives::Float32 retValue;
			retValue = m_values[0][0] * ((m_values[1][1] * m_values[2][2]) - (m_values[1][2] * m_values[2][1]))
				- m_values[0][1] * ((m_values[1][0] * m_values[2][2]) - (m_values[1][2] * m_values[2][0]))
				+ m_values[0][2] * ((m_values[1][0] * m_values[2][1]) - (m_values[1][1] * m_values[2][0]));
			return retValue;

		}





	};
};
#endif // !MATIX3X3_H_