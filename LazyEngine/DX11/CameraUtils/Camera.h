#pragma once
#include "../../Includes/LazyIncludes.h"
#include "../../Math/Matrix4X4.h"
namespace LE {
	class Camera {
	private:
		LEVector3 eye;
		LEVector3 lookAt,up;
		Matrix4X4 worldMatrix,viewMatrix;
		Matrix4X4 projectionMatrix;
		Primitives::Float32 FOV,AspectRatio,NearClip,FarClip;
		Primitives::Bool bIsActiveCamera;
	public:
		Camera();
		Camera(const LEVector3& eye,const LEVector3& lookAt,const LEVector3& up,
			const Primitives::Float32& fov, const Primitives::Float32& aspectRatio, const Primitives::Float32& near, const Primitives::Float32& far);
		void TurnLeft(const Primitives::Float32& rad);
		void TurnRight(const Primitives::Float32& rad);
		void TurnUp(const Primitives::Float32& rad);
		void TurnDown(const Primitives::Float32& rad);
		void MoveLeft(const Primitives::Float32& distance);
		void MoveRight(const Primitives::Float32& distance);
		void MoveUp(const Primitives::Float32& distance);
		void MoveDown(const Primitives::Float32& distance);
		void Reset();
		void CreateWorldViewMatrix();
		void CreateProjectionMatrix();
		Matrix4X4 getViewMatrix();
		Matrix4X4 getProjectionMatrix();
		void ReCalculateView();
		void ReCalculateProjection();
		
	};
};