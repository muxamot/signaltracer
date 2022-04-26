#pragma once

#include "matrix.hpp"
#include "vector.hpp"

namespace math
{
	class Pipeline
	{
	public:

		Pipeline()
		{
			m_scale = Vector3f(1.0f, 1.0f, 1.0f);
			m_worldPos = Vector3f(0.0f, 0.0f, 0.0f);
			m_rotateInfo = Vector3f(0.0f, 0.0f, 0.0f);
		}

		void Scale(float ScaleX, float ScaleY, float ScaleZ)
		{
			m_scale.x = ScaleX;
			m_scale.y = ScaleY;
			m_scale.z = ScaleZ;
		}

		void WorldPos(float x, float y, float z)
		{
			m_worldPos.x = x;
			m_worldPos.y = y;
			m_worldPos.z = z;
		}

		void Rotate(float RotateX, float RotateY, float RotateZ)
		{
			m_rotateInfo.x = RotateX;
			m_rotateInfo.y = RotateY;
			m_rotateInfo.z = RotateZ;
		}

		void SetPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar)
		{
			m_persProj.FOV = FOV;
			m_persProj.Width = Width;
			m_persProj.Height = Height;
			m_persProj.zNear = zNear;
			m_persProj.zFar = zFar;
		}

		void SetCamera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
		{
			m_camera.Pos = Pos;
			m_camera.Target = Target;
			m_camera.Up = Up;
		}

		const Matrix4f& GetWorldCameraTrans()
		{
			GetWorldTrans();
			Matrix4f CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

			CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
			CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
			PersProjTrans.InitPersProjTransform(m_persProj.FOV, m_persProj.Width, m_persProj.Height, m_persProj.zNear, m_persProj.zFar);

			m_WVPtransformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * m_WorldTransformation;
			return m_WVPtransformation;
		}

		const Matrix4f& GetWorldTrans() {
			Matrix4f ScaleTrans, RotateTrans, TranslationTrans;

			ScaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
			RotateTrans.InitRotateTransform(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
			TranslationTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);

			m_WorldTransformation = TranslationTrans * RotateTrans * ScaleTrans;

			return m_WorldTransformation;
		}

	private:

		Vector3f m_scale;
		Vector3f m_worldPos;
		Vector3f m_rotateInfo;

		struct
		{
			float FOV;
			float Width;
			float Height;
			float zNear;
			float zFar;
		} m_persProj;

		struct
		{
			Vector3f Pos;
			Vector3f Target;
			Vector3f Up;
		} m_camera;

		Matrix4f m_WVPtransformation;
		Matrix4f m_WorldTransformation;

	};
}