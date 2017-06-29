#pragma once
#ifndef MATRIX3X3_H_
#define MATRIX3X3_H_
#include "MathHelpers.h"
#include "LEVector.h"
#include <iostream>
//using namespace std;
enum RotateAxis {
	XAxis = 0,
	YAxis,
	ZAxis
};
enum RotationOrder {
	XYZ = 0,
	ZYX
	
};
template <class T = Primitives::Float32>
class Matrix3X3 {
public:
	union 
	{
		T m_values[3][3];
		T m09[9];
	};
	
	Matrix3X3<T>() {
		m_values[0][0] = m_values[0][1] = m_values[0][2] = (T) 0.f;
		m_values[1][0] = m_values[1][1] = m_values[1][2] = (T) 0.f;
		m_values[2][0] = m_values[2][1] = m_values[2][2] = (T) 0.f;
	}

	Matrix3X3<T>(const Matrix3X3<T> &copy) {
		memcpy(this, &copy, sizeof(Matrix3X3<T>));
	}
	Matrix3X3<T>(RotateAxis axis, float angle) {
		float sintheta = sinf(angle);
		float costheta = cosf(angle);
		Matrix3X3<T>();
		switch axis{
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

	Matrix3X3<T>(const LEVector3<T>& angles, RotationOrder rotOrder = XYZ) {
		Matrix3X3<T> xRotate, yRotate, zRotate;
		xRotate = Matrix3X3<T>(XAxis, angle.m_x);
		yRotate = Matrix3X3<T>(YAxis, angle.m_y);
		zRotate = Matrix3X3<T>(ZAxis, angle.m_z);
		switch (rotOrder) {
		case XYZ: *this = xRotate*yRotate*zRotate;
			break;
		case ZYX: *this = zRotate*yRotate*xRotate;
			break;
		}
	}

	Matrix3X3<T>(LEVector3<T> u, LEVector3<T> v, LEVector3<T> n) {
		//XAxis
		m_values[0][0] = u.m_x;
		m_values[0][1] = v.m_x;
		m_values[0][2] = n.m_x;
		//YAxis
		m_values[1][0] = u.m_y;
		m_values[1][1] = v.m_y;
		m_values[1][2] = n.m_y;
		//ZAxis
		m_values[2][0] = u.m_z;
		m_values[2][1] = v.m_z;
		m_values[2][2] = n.m_z;

	}

	Matrix3X3<T>(const T m00,T m01, const T m02,
		const T m10, const T m11, const T m12,
		const T m20, const T m21, const T m22 ) {

		m_values[0][0] = m00;
		m_values[1][0] = m01;
		m_values[2][0] = m02;
		m_values[0][1] = m10;
		m_values[1][1] = m11;
		m_values[2][1] = m12;
		m_values[0][2] = m20;
		m_values[1][2] = m21;
		m_values[2][2] = m22;
		
	}

	friend Matrix3X3<T> operator * (Matrix3X3<T> &m0, Matrix3X3<T> &m1) {
		Matrix3X3<T> returnMat = Matrix3X3<T>();
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					returnMat.m_values[i][k] += m0.m_values[i][j] * m1.m_values[j][k];
		return returnMat;
	}
	friend LEVector3<T> operator * (LEVector3<T> v, Matrix3X3<T> m) {
		LEVector3<T> retVector;

		retVector.m_values[0] = v.m_x * (m.m_values[0][0]) + v.m_y * (m.m_values[1][0]) + v.m_z * (m.m_values[2][0]);
		retVector.m_values[1] = v.m_x * (m.m_values[0][1]) + v.m_y * (m.m_values[1][1]) + v.m_z * (m.m_values[2][1]);
		retVector.m_values[2] = v.m_x * (m.m_values[0][2]) + v.m_y * (m.m_values[1][2]) + v.m_z * (m.m_values[2][2]);
		return retVector;

	}
	friend ostream &operator << (ostream &output,const Matrix3X3<T> &m) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				output << m.m_values[i][j] << "\t";
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

	LEVector3<T> getU() {
		LEVector3<T> u = LEVector3(m_values[0][0],m_values[1][0],m_values[2][0]);
		return u;
	}

	LEVector3<T> getV() {
		LEVector3<T> v = LEVector3<T>(m_values[0][1], m_values[1][1], m_values[2][1]);
		return v;
	}

	LEVector3<T> getN() {
		LEVector3<T> n = LEVector3(m_values[0][2], m_values[1][2], m_values[2][2]);
		return n;
	}

	T det() {

		T retValue;
		retValue = m_values[0][0] * ((m_values[1][1] * m_values[2][2]) - (m_values[1][2] * m_values[2][1]))
			+ m_values[0][1] * ((m_values[1][0] * m_values[2][2]) - (m_values[1][2] * m_values[2][0]))
			+ m_values[0][2] * ((m_values[1][0] * m_values[2][1]) - (m_values[1][1] * m_values[2][0]));
		return retValue;

	}
	
	



};
#endif // !MATIX3X3_H_