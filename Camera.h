#pragma once
#include"MathFunc.h"

class Camera
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="fovY">fov</param>
	/// <param name="viewportWidth">幅</param>
	/// <param name="viewportHeight">高さ</param>
	void Initialize(
		const Vector3& position = { 0.0f,0.0f,-10.0f },
		float fovY = 0.45f,
		float viewportWidth = 1280.0f, float viewportHeight = 720.0f);
	/// <summary>
	/// 移動(前後)
	/// </summary>
	/// <param name="distance">距離</param>
	void Walk(float distance);
	/// <summary>
	/// 移動(左右)
	/// </summary>
	/// <param name="distance">距離</param>
	void Strafe(float distance);
	/// <summary>
	/// 回転(X)
	/// </summary>
	/// <param name="angle">角度</param>
	void RotateX(float angle);
	/// <summary>
	/// 回転(Y)
	/// </summary>
	/// <param name="angle">角度</param>
	void RotateY(float angle);
	void SetRotate(const Vector3& rotate);
	void SetLookAt(const Vector3& lookat);
	void Update();
	void SetCameraPosition(const Vector3& position);

	Vector3 TransformVertex(
		const Vector3& vertex,
		const Vector3& local = { 0.0f,0.0f,0.0f },
		const Vector3& scale = { 1.0f,1.0f,1.0f },
		const Vector3& rotate = { 0.0f,0.0f,0.0f })const;
	Matrix4x4 GetWorldViewProjectionMatrix(const Matrix4x4& worldMatrix);
	Matrix4x4 GetOrthographicMatrix(const Matrix4x4& worldMatrix);
	Matrix4x4 GetWorldViewOrthographicMatrix(const Matrix4x4& worldMatrix);
	void SetFov(float fov) { m_fovY = fov; }
#ifdef _DEBUG
	void ImGuiDebug();
#endif // _DEBUG

private:
	Matrix4x4 m_viewMatrix{};
	Matrix4x4 m_projectionMatrix{};
	Matrix4x4 m_orthographicMatrix{};
	Matrix4x4 m_viewProjectionMatrix{};
	Matrix4x4 m_viewportMatrix{};

	Vector3 m_position{};
	float m_fovY;
	float m_viewportWidth;
	float m_viewportHeight;

	Vector3 m_right =	{ 1.0f,0.0f,0.0f };		//右方向
	Vector3 m_up =		{ 0.0f,1.0f,0.0f };		//上方向
	Vector3 m_lookat =  { 0.0f,0.0f,1.0f };		//見ている向き

	bool m_isNeendUpdate = true;
};

