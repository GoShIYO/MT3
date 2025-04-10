#include "Camera.h"
#define USE_IMGUI
#include<2d/ImGuiManager.h>

//using namespace KamataEngine;

void Camera::Initialize(
	const Vector3& position,
	float fovY,
	float viewportWidth, float viewportHeight)
{
	m_position = position;
	m_fovY = fovY;
	m_viewportWidth = viewportWidth;
	m_viewportHeight = viewportHeight;
	m_viewportMatrix = MakeViewportMatrix(0, 0, m_viewportWidth, m_viewportHeight, 0.0f, 1.0f);

}
void Camera::Walk(float distance)
{
	Vector3 v = m_lookat * distance;
    m_position += v;
	m_isNeendUpdate = true;
}
void Camera::Strafe(float distance)
{
	Vector3 v = m_right * distance;
    m_position += v;
    m_isNeendUpdate = true;
}
void Camera::RotateX(float angle)
{
	//基底ベクトルをワールドのX軸を中心に回転させる。
	Matrix4x4 rotate = MakeRotateXMatrix(angle);
	m_up = Transform(Normalize(m_up), rotate);
	m_right = Transform(Normalize(m_right), rotate);
	m_lookat = Transform(Normalize(m_lookat), rotate);
    m_isNeendUpdate = true;
}
void Camera::RotateY(float angle)
{
	//基底ベクトルをワールドのY軸を中心に回転させる。
	Matrix4x4 rotate = MakeRotateYMatrix(angle);
	m_right = Transform(Normalize(m_right), rotate);
	m_up = Transform(Normalize(m_up), rotate);
	m_lookat = Transform(Normalize(m_lookat), rotate);
    m_isNeendUpdate = true;
}
void Camera::SetRotate(const Vector3& rotate)
{
	//ベクトルを回転行列を作る
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate);
	//軸に分けて各軸のベクトルに変換する
    m_right = Transform(Vector3{1.0f,0.0f,0.0f}, rotateMatrix);
    m_up = Transform(Vector3{ 0.0f,1.0f,0.0f }, rotateMatrix);
    m_lookat = Transform(Vector3{ 0.0f,0.0f,1.0f }, rotateMatrix);
	m_isNeendUpdate = true;
}
void Camera::SetLookAt(const Vector3& lookat) {
	m_lookat = lookat; 
	m_isNeendUpdate = true;
}
void Camera::Update()
{
	if (m_isNeendUpdate) {
		//カメラの軸を互いに直交させ、正規化する
		m_lookat = Normalize(m_lookat);
		m_right = Normalize(Cross(m_up, m_lookat));
		m_up = Normalize(Cross(m_lookat, m_right));
		//ビュー行列の項目を埋める。
		float x = -Dot(m_right, m_position);
		float y = -Dot(m_up, m_position);
		float z = -Dot(m_lookat, m_position);

		m_viewMatrix = {
			m_right.x,  m_up.x,  m_lookat.x, 0,
			m_right.y,  m_up.y,  m_lookat.y, 0,
			m_right.z,  m_up.z,  m_lookat.z, 0,
				 x,        y,         z,     1
		};

		m_isNeendUpdate = false;
	}
	m_projectionMatrix = MakePerspectiveFovMatrix(m_fovY, m_viewportWidth / m_viewportHeight, 0.1f, 100.0f);
	m_orthographicMatrix = MakeOrthographicMatrix(0.0f, 0.0f, m_viewportWidth, m_viewportHeight, 0.0f, 100.0f);
	m_viewProjectionMatrix = Multiply(m_viewMatrix, m_projectionMatrix);
}

void Camera::SetCameraPosition(const Vector3& position) {
	m_position = position; 
	m_isNeendUpdate = true;
}

Vector3 Camera::TransformVertex(const Vector3& vertex, const Vector3& local, const Vector3& scale, const Vector3& rotate)const
{

	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, vertex);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, m_viewProjectionMatrix);
	Vector3 ndcVertex = Transform(local, worldViewProjectionMatrix);

	return Transform(ndcVertex, m_viewportMatrix);
}
Matrix4x4 Camera::GetWorldViewProjectionMatrix(const Matrix4x4& worldMatrix)
{
	return Multiply(worldMatrix, m_viewProjectionMatrix);
}

Matrix4x4 Camera::GetOrthographicMatrix(const Matrix4x4& worldMatrix)
{
	return Multiply(worldMatrix,m_orthographicMatrix);
}

Matrix4x4 Camera::GetWorldViewOrthographicMatrix(const Matrix4x4& worldMatrix)
{
	return Multiply(worldMatrix, Multiply(m_viewMatrix, m_orthographicMatrix));
}

#ifdef _DEBUG
void Camera::ImGuiDebug()
{
	// カメラ情報
	ImGui::Begin("CameraInfo");
	ImGui::Text("position.x = %.3f", m_position.x);
	ImGui::Text("position.y = %.3f", m_position.y);
	ImGui::Text("position.z = %.3f", m_position.z);
    ImGui::Text("fovY = %.3f", m_fovY);
	ImGui::End();

	ImGui::Begin("CameraPosition");
	ImGui::DragFloat3("position", &m_position.x, 0.01f);
	ImGui::End();

	ImGui::Begin("CameraRotate");
	ImGui::DragFloat3("right", &m_right.x, 0.01f);
	ImGui::DragFloat3("up", &m_up.x, 0.01f);
	ImGui::DragFloat3("lookat", &m_lookat.x, 0.01f);
	ImGui::End();

    ImGui::Begin("CameraFovY");
    ImGui::DragFloat("fovY", &m_fovY, 0.01f,0.1f,3.14f);
    ImGui::End();


}
#endif // _DEBUG