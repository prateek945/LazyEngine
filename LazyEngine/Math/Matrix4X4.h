#pragma once
#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include "../Includes/LazyIncludes.h"
#include "LEVector.h"
#include "Matrix3X3.h"
#include "Quaternion.h"
using namespace std;
namespace LE {
	
	struct Matrix4X4 {
	public:
		union {
			struct {
				Primitives::Float32 m00, m01, m02, m03,
					m10, m11, m12, m13,
					m20, m21, m22, m23,
					m30, m31, m32, m33;
			};
			Primitives::Float32 m_values[4][4];
		};
		//set zero
		Matrix4X4() {
			memset(m_values, 0, 16 * sizeof(Primitives::Float32));
		}
		//copy constructor
		Matrix4X4(Matrix4X4 &m) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					m_values[i][j] = m.m_values[i][j];
				}
			}
		}
		//from values
		Matrix4X4(Primitives::Float32 m00, Primitives::Float32 m01, Primitives::Float32 m02, Primitives::Float32 m03,
			Primitives::Float32 m10, Primitives::Float32 m11, Primitives::Float32 m12, Primitives::Float32 m13,
			Primitives::Float32 m20, Primitives::Float32 m21, Primitives::Float32 m22, Primitives::Float32 m23,
			Primitives::Float32 m30, Primitives::Float32 m31, Primitives::Float32 m32, Primitives::Float32 m33) {

			m_values[0][0] = m00; m_values[0][1] = m01; m_values[0][2] = m02; m_values[0][3] = m03;
			m_values[1][0] = m10; m_values[1][1] = m11; m_values[1][2] = m12; m_values[1][3] = m13;
			m_values[2][0] = m20; m_values[2][1] = m21; m_values[2][2] = m22; m_values[2][3] = m23;
			m_values[3][0] = m30; m_values[3][1] = m31; m_values[3][2] = m32; m_values[3][3] = m33;
			
		}

		Matrix4X4(const Matrix3X3 &sr,const LEVector3 &t) {

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					m_values[i][j] = sr.m_values[i][j];

			m_values[3][0] = t.m_values[0]; m_values[3][1] = t.m_values[1]; m_values[3][2] = t.m_values[2];
			m_values[0][3] = m_values[1][3] = m_values[2][3] = (Primitives::Float32)0;
			m_values[3][3] = (Primitives::Float32)1;

		}

		Matrix4X4(Primitives::Float32 &s, Quaternion &q, LEVector3 &t) {
			*this = Matrix4X4(q, t);
			m_values[0][0] *= s; m_values[1][1] *= s; m_values[2][2] *= s;

		}
		Matrix4X4(LEVector3 &s, Quaternion &q, LEVector3 &t) {
			*this = Matrix4X4(q, t);
			m_values[0][0] *= s.m_x; m_values[1][1] *= s.m_y; m_values[2][2] *= s.m_z;
		}
		Matrix4X4(Quaternion &q, LEVector3 &translation) {
			/*
			1 - 2*qy2 - 2*qz2	2*qx*qy - 2*qz*qw	2*qx*qz + 2*qy*qw
			2*qx*qy + 2*qz*qw	1 - 2*qx2 - 2*qz2	2*qy*qz - 2*qx*qw
			2*qx*qz - 2*qy*qw	2*qy*qz + 2*qx*qw	1 - 2*qx2 - 2*qy2
			*/
			m_values[0][0] = 1.f-(2.f*q.y*q.y)-(2.f*q.z*q.z); 
			m_values[0][1] = (2.f*q.x*q.y)+(2.f*q.z*q.w); 
			m_values[0][2] = (2.f*q.x*q.z)-(2.f*q.y*q.z);
			m_values[0][3] = 0.f;
			m_values[1][0] = (2.f*q.x*q.y) - (2.f*q.z*q.w);
			m_values[1][1] = 1.f - (2.f*q.x*q.x) - (2.f*q.z*q.z);
			m_values[1][2] = (2.f*q.y*q.z) + (2.f*q.x*q.w);
			m_values[1][3] = 0.f;
			m_values[2][0] = (2 * q.x*q.z) + (2 * q.y*q.w);
			m_values[2][1] = (2 * q.y*q.z) - (2.f*q.x*q.w);
			m_values[2][2] = 1.f - (2 * q.x*q.x) - (2 * q.y*q.y);
			m_values[2][3] = 0.f;
			m_values[3][0] = translation.m_x;
			m_values[3][1] = translation.m_y;
			m_values[3][2] = translation.m_z;
			m_values[3][3] = 1.f;
		}

		LEVector3 getU() {
			LEVector3 retVec = LEVector3(m_values[0][0], m_values[0][1], m_values[0][2]);
			//retVec.Normalize();
			return retVec;
		}
		LEVector3 getV() {
			LEVector3 retVec = LEVector3(m_values[1][0], m_values[1][1], m_values[1][2]);
			//retVec.Normalize();
			return retVec;
		}
		LEVector3 getN() {
			LEVector3 retVec = LEVector3(m_values[2][0], m_values[2][1], m_values[2][2]);
			//retVec.Normalize();
			return retVec;
		}
		LEVector3 getTranslation() {
			return LEVector3(m_values[0][3], m_values[1][3], m_values[2][3]);
		}
		LEVector3 getScale() {
			Primitives::Float32 sX, sY, sZ;
			sX = getU().length();
			sY = getV().length();
			sZ = getN().length();
			return LEVector3(sX, sY, sZ);
		}
		void setRotation(Matrix3X3 &m) {
			
		}
		void setTranslation(LEVector3 t) {
			m_values[0][3] = t.m_x;
			m_values[1][3] = t.m_y;
			m_values[2][3] = t.m_z;
		}

		friend ostream &operator << (ostream &output,const Matrix4X4 &m) {
			output << "Matrix4X4 : ";
			for (int i = 0; i < 4; i++) {
				output << "\n";
				for (int j = 0; j < 4; j++)
					output << m.m_values[i][j] << "\Primitives::Float32";
			}
			output << "\n";
			return output;
		}

		Quaternion getQuaternionRotation() {
			Quaternion ret = Quaternion();
			/*√(1 + m00 + m11 + m22) / 2
				qx = (m21 - m12) / (4 * qw)
				qy = (m02 - m20) / (4 * qw)
				qz = (m10 - m01) / (4 * qw)
				*/
			Primitives::Float32 trace = 1 + m_values[0][0] + m_values[1][1] + m_values[2][2];
			if (trace > 0) {
				ret.w = sqrtf(trace) * 0.5f;
				Primitives::Float32 S = 4.0f * ret.w;
				ret.x = (m_values[2][1] - m_values[1][2]) / (S);
				ret.y = (m_values[0][2] - m_values[2][0]) / (S);
				ret.z = (m_values[1][0] - m_values[0][1]) / (S);
			}
			else if ((m_values[0][0] > m_values[1][1]) && (m_values[0][0] > m_values[2][2])) {
				ret.x = sqrt(1 + m_values[0][0] - m_values[1][1] - m_values[2][2]) * 0.5f;
				Primitives::Float32 S = 4.f * ret.x;
				ret.w = (m_values[2][1] - m_values[1][2]) / (S);
				ret.y = (m_values[1][0] + m_values[0][1]) / (S);
				ret.z = (m_values[0][2] + m_values[2][0]) / (S);
			}
			else if (m_values[1][1] > m_values[2][2]) {
				ret.y = sqrt(1 + m_values[1][1] - m_values[0][0] - m_values[2][2]) * 0.5f;
				Primitives::Float32 S = 4.f * ret.y;
				ret.w = (m_values[0][2] - m_values[2][0]) / (S);
				ret.x = (m_values[1][0] + m_values[0][1]) / (S);
				ret.z = (m_values[2][1] + m_values[1][2]) / (S);
			}
			else {
				ret.z = sqrt(1 + m_values[2][2] - m_values[0][0] - m_values[1][1]) * 0.5f;
				Primitives::Float32 S = 4.f * ret.z;
				ret.w = (m_values[2][1] - m_values[1][2]) / (S);
				ret.x = (m_values[2][0] + m_values[0][2]) / (S);
				ret.z = (m_values[0][1] + m_values[1][0]) / (S);
			}
			
			return ret;
		}
		Matrix3X3 getMinorMat(Primitives::Int16 x, Primitives::Int16 y) {
			Primitives::Int16 i,j;
			Matrix3X3 ret;
			Primitives::Int16 retX = 0, retY = 0;
			ret.clearMatrix();
			for (i = 0; i < 4; i++) {
				if (i != x) {
					for (j = 0; j < 4; j++) {
						if (j != y) {
							ret.m_values[retX][retY] = m_values[i][j];
							retY++;
						}
					}
					retY = 0;
					retX++;
				}
			}
			return ret;
		}
		Primitives::Float32 det() {
			Matrix3X3 detMat00 = getMinorMat(0, 0);
			Matrix3X3 detMat01 = getMinorMat(0, 1);
			Matrix3X3 detMat02 = getMinorMat(0, 2);
			Matrix3X3 detMat03 = getMinorMat(0, 3);
			
			return (m00*(detMat00.det()) - m01*(detMat01.det()) + m02*(detMat02.det()) - m03*(detMat03.det()));
		}
		Matrix4X4 getTranspose() {
			Matrix4X4 ret = Matrix4X4 ();
			Primitives::Int16 i, j;
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					ret.m_values[i][j] = m_values[j][i];
				}
			}
			return ret;
		}
		Matrix4X4 furfiller() {
			Matrix4X4 ret = Matrix4X4();
			Primitives::Int16 i, j;
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					Primitives::Float32 minordet = getMinorMat(i, j).det();
					ret.m_values[i][j] = minordet * powf(-1.f, (float)i + (float)j);
				}
			}
			return ret;
		}
		Matrix4X4 inverse() {
			Matrix4X4 ret = Matrix4X4();
			Matrix4X4 transpose = getTranspose();
			Primitives::Float32 matDet = det();
			if(!(matDet ==(Primitives::Float32)0)){
				Primitives::Float32 frac = 1.f / matDet;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						ret.m_values[i][j] = transpose.furfiller().m_values[i][j] * frac;
					}
				}
			}
		
			return ret;
		}

		inline void operator *= (Primitives::Float32 val) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_values[i][j] *= val;
		}

		inline void operator /= (Primitives::Float32 val) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_values[i][j] /= val;
		}

		inline void operator += (Matrix4X4 &m) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_values[i][j] += m.m_values[i][j];
		}

		inline void operator -= (Matrix4X4 &m) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_values[i][j] -= m.m_values[i][j];
		}
		
	};
	inline Matrix4X4 operator *(const Matrix4X4 &m0, const float &f)
	{
		Matrix4X4 res = Matrix4X4();
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				res.m_values[i][j] = m0.m_values[i][j] * f;

			}
		}
		return res;
	}
	inline Matrix4X4 operator / (const Matrix4X4 &m1, const Primitives::Float32 val) {

		Matrix4X4 ret = Matrix4X4();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret.m_values[i][j] = m1.m_values[i][j] / val;
			}
		}
		return ret;
	}
	inline Matrix4X4 operator + (const Matrix4X4 &m1, const Matrix4X4 &m2) {
		Matrix4X4 ret = Matrix4X4();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.m_values[i][j] = m1.m_values[i][j] + m2.m_values[i][j];

		return ret;
	}

	inline Matrix4X4 operator - (const Matrix4X4 &m1, const Matrix4X4 &m2) {
		Matrix4X4 ret = Matrix4X4();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.m_values[i][j] = m1.m_values[i][j] - m2.m_values[i][j];

		return ret;
	}

	inline LEVector3 operator * (const LEVector3 &v, const Matrix4X4 &m) {
		LEVector3 ret;
		ret.m_values[0] = v.m_x * m.m00 + v.m_y * m.m01 + v.m_z * m.m02 + m.m03;
		ret.m_values[1] = v.m_x * m.m10 + v.m_y * m.m11 + v.m_z * m.m12 + m.m13;
		ret.m_values[2] = v.m_x * m.m20 + v.m_y * m.m21 + v.m_z * m.m22 + m.m23;

		return ret;

	}


	inline Matrix4X4 operator * (const Matrix4X4 &m1, const Matrix4X4 &m2) {

		Matrix4X4 ret = Matrix4X4();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					ret.m_values[i][k] += m1.m_values[i][j] * m2.m_values[j][k];
				}
			}
		}
		return ret;
	}

	

};
#endif
