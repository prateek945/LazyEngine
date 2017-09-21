#include "Camera.h"

namespace LE {

	Camera::Camera() : eye(LEVector3(0,0,0)),lookAt(LEVector3(1,0,0)),up(LEVector3(0,1,0)),FOV(90.0f),NearClip(0.01f), FarClip(100.0f) {
		CreateWorldViewMatrix();
		CreateProjectionMatrix();
	}

	Camera::Camera(const LEVector3& eye, const LEVector3& lookAt, const LEVector3& up, const Primitives::Float32& fov,
		const Primitives::Float32& aspectRatio,const Primitives::Float32& near, const Primitives::Float32& far) : eye(eye),
		lookAt(lookAt), up(up),
		FOV(fov), NearClip(near), FarClip(far), AspectRatio(aspectRatio) {
		CreateWorldViewMatrix();
		CreateProjectionMatrix();
	}

	void Camera::CreateWorldViewMatrix() {
		//Create the world Matrix for Camera.
		LEVector3 Z = lookAt - eye;
		Z.Normalize();
		LEVector3 X,Y;
		X.crossProduct(up, Z);
		X.Normalize();
		Y.crossProduct(Z, X);
		
		worldMatrix.setIdentity();
		worldMatrix.setU(X); worldMatrix.setV(Y); worldMatrix.setN(Z);
		worldMatrix.setTranslation(eye);
		//Create the viewMatrix from the worldMatrix.
		viewMatrix.setIdentity();
		viewMatrix.m00 = worldMatrix.m00; viewMatrix.m11 = worldMatrix.m11; viewMatrix.m22 = worldMatrix.m22;
		viewMatrix.m01 = worldMatrix.m10; viewMatrix.m02 = worldMatrix.m20; viewMatrix.m10 = worldMatrix.m01;
		viewMatrix.m12 = worldMatrix.m21; viewMatrix.m20 = worldMatrix.m02; viewMatrix.m21 = worldMatrix.m12;
		viewMatrix.m30 = -(worldMatrix.getU().dotProduct(eye));
		viewMatrix.m31 = -(worldMatrix.getV().dotProduct(eye));
		viewMatrix.m32 = -(worldMatrix.getN().dotProduct(eye));
	}

	void Camera::CreateProjectionMatrix() {

		Primitives::Float32 ScaleX, ScaleY;
		ScaleY = 1 / (tanf(DEGTORAD(FOV) / 2.f));
		ScaleX = ScaleY / AspectRatio;
		projectionMatrix.setIdentity();
		projectionMatrix.m00 = ScaleX;
		projectionMatrix.m11 = ScaleY;
		projectionMatrix.m22 = FarClip / (FarClip - NearClip);
		projectionMatrix.m23 = 1.f;
		projectionMatrix.m32 = -(NearClip * FarClip) / (FarClip - NearClip);
		projectionMatrix.m33 = 0.f;

	}

	Matrix4X4 Camera::getViewMatrix() {
		return viewMatrix;
	}
	Matrix4X4 Camera::getProjectionMatrix() {
		return projectionMatrix;
	}

	void Camera::TurnLeft(const Primitives::Float32& rad) {
		worldMatrix.turnLeft(rad);
	}
	void Camera::TurnRight(const Primitives::Float32& rad) {
		worldMatrix.turnRight(rad);
	}
	void Camera::TurnUp(const Primitives::Float32& rad) {
		worldMatrix.turnUp(rad);
	}
	void Camera::TurnDown(const Primitives::Float32& rad) {
		worldMatrix.turnDown(rad);
	}

	void Camera::MoveLeft(const Primitives::Float32& distance){
		worldMatrix.setTranslation(worldMatrix.getTranslation() - distance*worldMatrix.getU());
	}

	void Camera::MoveRight(const Primitives::Float32& distance){
		worldMatrix.setTranslation(worldMatrix.getTranslation() + distance*worldMatrix.getU());
	}

	void Camera::MoveUp(const Primitives::Float32& distance){
		worldMatrix.setTranslation(worldMatrix.getTranslation() + distance*worldMatrix.getN());
	}
	void Camera::MoveDown(const Primitives::Float32& distance){
		worldMatrix.setTranslation(worldMatrix.getTranslation() - distance*worldMatrix.getN());
	}

	void Camera::Reset() {
		LEVector3 Z = lookAt - eye;
		Z.Normalize();
		LEVector3 X, Y;
		X.crossProduct(up, Z);
		X.Normalize();
		Y.crossProduct(Z, X);

		worldMatrix.setIdentity();
		worldMatrix.setU(X); worldMatrix.setV(Y); worldMatrix.setN(Z);
		worldMatrix.setTranslation(eye);
	}
	void Camera::ReCalculateView() {
		viewMatrix.setIdentity();
		viewMatrix.m00 = worldMatrix.m00; viewMatrix.m11 = worldMatrix.m11; viewMatrix.m22 = worldMatrix.m22;
		viewMatrix.m01 = worldMatrix.m10; viewMatrix.m02 = worldMatrix.m20; viewMatrix.m10 = worldMatrix.m01;
		viewMatrix.m12 = worldMatrix.m21; viewMatrix.m20 = worldMatrix.m02; viewMatrix.m21 = worldMatrix.m12;
		viewMatrix.m30 = -(worldMatrix.getU().dotProduct(worldMatrix.getTranslation()));
		viewMatrix.m31 = -(worldMatrix.getV().dotProduct(worldMatrix.getTranslation()));
		viewMatrix.m32 = -(worldMatrix.getN().dotProduct(worldMatrix.getTranslation()));
	}
	void Camera::ReCalculateProjection() {
		Primitives::Float32 ScaleX, ScaleY;
		ScaleY = 1 / (tanf(DEGTORAD(FOV) / 2.f));
		ScaleX = ScaleY / AspectRatio;
		projectionMatrix.setIdentity();
		projectionMatrix.m00 = ScaleX;
		projectionMatrix.m11 = ScaleY;
		projectionMatrix.m22 = FarClip / (FarClip - NearClip);
		projectionMatrix.m23 = 1.f;
		projectionMatrix.m32 = -(NearClip * FarClip) / (FarClip - NearClip);
		projectionMatrix.m33 = 0.f;
	}
};