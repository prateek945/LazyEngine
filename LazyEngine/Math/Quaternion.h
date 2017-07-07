#pragma once
#ifndef QUATERNION_H_
#define QUATERNION_H_
#include "../Includes/LazyIncludes.h"
#include "../Math/LEVector.h"
using namespace std;
namespace LE {
	class Quaternion {
	public:
		//constructors
		//Null Quaternion
		Quaternion():w(0.f),x(0.f),y(0.f),z(0.f) {}
		//Copy Constructor
		Quaternion(const Quaternion &q): w(q.getW()),x(q.getX()),y(q.getY()),z(q.getZ()){}
		//From 4 floats (w,x,y,z). General form
		Quaternion(Primitives::Float32 w, Primitives::Float32 x
			, Primitives::Float32 y, Primitives::Float32 z) :w(w), x(x), y(y), z(z) {}
		//Pure Quaternion from LEVector3
		Quaternion(const LEVector3<> &v) {
			w = 0.f;
			x = v.m_x;
			y = v.m_y;
			z = v.m_z;
		}
		//Real Quaternion from w
		Quaternion(const Primitives::Float32 w) {
			(*this).w = w;
			x = y = z = 0.f;
		}
		// Quaternion given axis angle
		Quaternion(const LEVector3<> &v, const Primitives::Float32 rad) {
			Primitives::Float32 halfangle = rad / 2.f;
			Primitives::Float32 sinehalfangle = sinf(halfangle);
			w = cosf(halfangle);
			x = v.m_x * sinehalfangle;
			y = v.m_y * sinehalfangle;
			z = v.m_z * sinehalfangle;
		}
		
		//Get coeffs.
		Primitives::Float32 getW() const { return w; }
		Primitives::Float32 getX() const { return x; }
		Primitives::Float32 getY() const { return y; }
		Primitives::Float32 getZ() const { return z; }

		LEVector3<> getVector() {
			return LEVector3<>(getX(),getY(),getZ());
		}
		void setVector(LEVector3<> &v){
			x = v.m_values[0]; y = v.m_values[1]; z = v.m_values[2];
		}
		//operator overlaods
		void setVector(const LEVector3<> &v) {
			x = v.m_x;
			y = v.m_y;
			z = v.m_z;
		}
		Quaternion fromEuler(LEVector3<> Eulerangles) {
			Quaternion ret;
			Primitives::Float32 halfPitch = Eulerangles.m_values[0] / 2.f;
			Primitives::Float32 halfYaw = Eulerangles.m_values[1] / 2.f;
			Primitives::Float32 halfRoll = Eulerangles.m_values[2] / 2.f;
			Primitives::Float32 cP, cY, cR, sP, sY, sR;
			cP = cosf(halfPitch); sP = sinf(halfPitch);
			cY = cosf(halfYaw); sY = sinf(halfYaw);
			cR = cosf(halfRoll); sR = sinf(halfRoll);
			/*	
				w = c1 c2 c3 - s1 s2 s3
				x = s1 s2 c3 +c1 c2 s3
				y = s1 c2 c3 + c1 s2 s3
				z = c1 s2 c3 - s1 c2 s3
			*/
			ret.w = cP*cY*cR - sP*sY*sR;
			ret.x = sP*sY*cR + cP*cY*sR;
			ret.y = sP*cY*cR + cP*sY*sR;
			ret.z = cP*sY*cR - sP*cY*sR;

			return ret;
		}

		friend Quaternion operator * ( Quaternion &q1,  Quaternion &q2) {
			
			LEVector3<> copyvector(LEVector3<>(q1.getX(),q1.getY(),q1.getZ()));
			Primitives::Float32 dotProduct = copyvector.dotProduct(q2.getVector());
			Quaternion ret = Quaternion();
			ret.w = q1.getW() + q2.getW() + dotProduct;
			copyvector.crossProduct(q2.getVector());
			
			copyvector += ((q2.getW()*q1.getVector()) + (q1.getW()*q2.getVector()));
			ret.setVector(copyvector);
			return ret;
		}
		friend Quaternion operator *(Quaternion &q1) {
			return q1.inverse();
		}
		friend Quaternion operator + (const Quaternion &q1, const Quaternion &q2) {
			return Quaternion(q1.getW() + q2.getW(),
				q1.getX() + q2.getX(),
				q1.getY() + q2.getY(),
				q1.getZ() + q2.getZ());

		}

		friend Quaternion operator - (const Quaternion &q1, const Quaternion &q2) {
			return Quaternion(q1.getW() - q2.getW(),
				q1.getX() - q2.getX(),
				q1.getY() - q2.getY(),
				q1.getZ() - q2.getZ());

		}
		inline void operator /= (Primitives::Float32 f) {
			w /= f; x /= f; y /= f; z /= f;
		}
		void normalise() {
			Primitives::Float32 length = sqrtf(w*w + x*x + y*y + z*z);
			
			*this /= length;
			
		}
		Quaternion conjugate() {
			Quaternion ret(*this);
			LEVector3<> v = -ret.getVector();
			ret.setVector(v);
			return ret;
		}
		Quaternion inverse() {
			Quaternion ret = Quaternion(*this);
			ret = ret.conjugate();
			ret.normalise();
			return ret;
		}
		friend ostream &operator << (ostream &output, Quaternion &q) {

			output << "W : " << q.getW() << ", " << q.getVector();
			return output;

		}

		LEVector3<> rotateCCW(Quaternion &q, LEVector3<> &v) {
			Quaternion pure(v), axis(q);
			Quaternion ret;
			ret = (axis * pure)*(*axis);
			return ret.getVector();
		}

		LEVector3<> rotateCW(Quaternion &q, LEVector3<> &v) {
			Quaternion pure(v), axis(q);
			axis.normalise();
			pure = ((*axis) * pure)*(axis);
			return pure.getVector();
		}
	private: 

		Primitives::Float32 w, x, y, z;


	};
};

#endif

