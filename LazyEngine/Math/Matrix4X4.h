#pragma once
#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include "../Includes/LazyIncludes.h"
#include "LEVector.h"
#include "Matrix3X3.h"
#include "Quaternion.h"
using namespace std;
namespace LE {
	template <class T = Primitives::Float32>
	class Matrix4X4 {
		union {
			struct {
				T m00, m01, m02, m03, 
					m10, m11, m12, m13, 
					m20, m21, m22, m23, 
					m30, m31, m32, m33;
			};
			T m_values[4][4];
		};
		
		
	public:
		//set zero
		Matrix4X4<T>() {
			memset(m_values, 0, 16 * sizeof(T));
		}
		//copy constructor
		Matrix4X4<T>(Matrix4X4<T> &m) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					m_values[i][j] = m.m_values[i][j];
				}
			}
		}
		//from values
		Matrix4X4<T>(T m00, T m01, T m02, T m03,
			T m10, T m11, T m12, T m13,
			T m20, T m21, T m22, T m23,
			T m30, T m31, T m32, T m33) {

			m_values[0][0] = m00; m_values[0][1] = m01; m_values[0][2] = m02; m_values[0][3] = m03;
			m_values[1][0] = m10; m_values[1][1] = m11; m_values[1][2] = m12; m_values[1][3] = m13;
			m_values[2][0] = m20; m_values[2][1] = m21; m_values[2][2] = m22; m_values[2][3] = m23;
			m_values[3][0] = m30; m_values[3][1] = m31; m_values[3][2] = m32; m_values[3][3] = m33;
			
		}

		Matrix4X4<T>(const Matrix3X3<T> &sr,const LEVector3<T> &t) {

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					m_values[i][j] = sr.m_values[i][j];

			m_values[3][0] = t.m_values[0]; m_values[3][1] = t.m_values[1]; m_values[3][2] = t.m_values[2];
			m_values[0][3] = m_values[1][3] = m_values[2][3] = (T)0;
			m_values[3][3] = (T)1;

		}

		Matrix4X4<T>(T &s, Quaternion &q, LEVector3<T> &t) {
			this = Matrix4X4<T>(q, t);
			m_values[0][0] *= s; m_values[1][1] *= s; m_values[2][2] *= s;

		}
		Matrix4X4<T>(LEVector3<T> &s, Quaternion &q, LEVector3<T> &t) {
			this = Matrix4X4<T>(q, t);
			m_values[0][0] *= s.m_x; m_values[1][1] *= s.m_y; m_values[2][2] *= s.m_z;
		}
		Matrix4X4<T>(Quaternion &q, LEVector3<T> &translation) {
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


		friend Matrix4X4<T> operator * (const Matrix4X4<T> &m1, const Matrix4X4<T> &m2) {

			Matrix4X4<T> ret();
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						ret.m_values[i][k] += m1.m_values[i][j] * m2.m_values[j][k];
					}
				}
			}
			return ret;
		}
		friend Matrix4X4<T> operator * (const Matrix4X4<T> &m1, const T val) {

			Matrix4X4<T> ret = Matrix4X4<T> ();
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					ret.m_values[i][j] = m1.m_values[i][j] * val;
				}
			}
			return ret;
		}
		friend Matrix4X4<T> operator / (const Matrix4X4<T> &m1, const T val) {

			Matrix4X4<T> ret = Matrix4X4<T>();
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					ret.m_values[i][j] = m1.m_values[i][j] / val;
				}
			}
			return ret;
		}
		friend Matrix4X4<T> operator + (const Matrix4X4<T> &m1, const Matrix4X4<T> &m2) {
			Matrix4X4<T> ret();
			for (int i = 0; i < 4; i++) 
				for (int j = 0; j < 4; j++) 
					ret.m_values[i][j] = m1.m_values[i][j] + m2.m_values[i][j];
				
			return ret;
		}

		friend Matrix4X4<T> operator - (const Matrix4X4<T> &m1, const Matrix4X4<T> &m2) {
			Matrix4X4<T> ret();
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					ret.m_values[i][j] = m1.m_values[i][j] - m2.m_values[i][j];

			return ret;
		}

		inline void operator *= (T val) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_values[i][j] *= val;
		}

		inline void operator /= (T val) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_values[i][j] /= val;
		}

		inline void operator += (Matrix4X4<T> &m) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_values[i][j] += m.m_values[i][j];
		}

		inline void operator -= (Matrix4X4<T> &m) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_values[i][j] -= m.m_values[i][j];
		}

		friend ostream &operator << (ostream &output,const Matrix4X4<T> &m) {
			output << "Matrix4X4 : ";
			for (int i = 0; i < 4; i++) {
				output << "\n";
				for (int j = 0; j < 4; j++)
					output << m.m_values[i][j] << "\t";
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
		Matrix3X3<T> getMinorMat(Primitives::Int16 x, Primitives::Int16 y) {
			Primitives::Int16 i,j;
			Matrix3X3<T> ret;
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
		T det() {
			Matrix3X3<T> detMat00 = getMinorMat(0, 0);
			Matrix3X3<T> detMat01 = getMinorMat(0, 1);
			Matrix3X3<T> detMat02 = getMinorMat(0, 2);
			Matrix3X3<T> detMat03 = getMinorMat(0, 3);
			
			return (m00*(detMat00.det()) - m01*(detMat01.det()) + m02*(detMat02.det()) - m03*(detMat03.det()));
		}
		Matrix4X4<T> getTranspose() {
			Matrix4X4<T> ret = Matrix4X4<T> ();
			Primitives::Int16 i, j;
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					ret.m_values[i][j] = m_values[j][i];
				}
			}
			return ret;
		}
		Matrix4X4<T> furfiller() {
			Matrix4X4<T> ret = Matrix4X4<T>();
			Primitives::Int16 i, j;
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					T minordet = getMinorMat(i, j).det();
					ret.m_values[i][j] = minordet * powf(-1.f, (float)i + (float)j);
				}
			}
			return ret;
		}
		Matrix4X4<T> inverse() {
			Matrix4X4<T> ret = Matrix4X4<T>();
			Matrix4X4<T> transpose = getTranspose();
			T matDet = det();
			if(!(matDet ==(T)0)){
				ret = transpose.furfiller()*(1.f/ matDet);
			}
		
			return ret;
		}
	};

};
#endif
