#include "DebugCamera.h"
#include<Novice.h>

void DebugCamera::Initialize(const Vector3& position) {
	m_camera = std::make_unique<Camera>();
	if (m_camera) {
		m_camera->Initialize(position, 0.45f);
	}
}

void DebugCamera::Update(char* keys, bool isUseMotion) {
	if (isUseMotion) {
		if (keys[DIK_W]) {
			m_camera->Walk(m_moveSpeed);
		}
		if (keys[DIK_S]) {
			m_camera->Walk(-m_moveSpeed);
		}
		if (keys[DIK_A]) {
			m_camera->Strafe(-m_moveSpeed);
		}
		if (keys[DIK_D]) {
			m_camera->Strafe(m_moveSpeed);
		}
		Novice::GetMousePosition((int*)&m_currMousePos.x, (int*)&m_currMousePos.y);

		if (Novice::IsTriggerMouse(0)) {
			m_prevMousePos = m_currMousePos;
		}
		if (Novice::IsPressMouse(0)) {
			float dx = ConvertToRadians(0.025f * (m_currMousePos.x - m_prevMousePos.x));
			float dy = ConvertToRadians(0.025f * (m_currMousePos.y - m_prevMousePos.y));

			m_camera->RotateX(dy);
			m_camera->RotateY(dx);
		}
		m_prevMousePos = m_currMousePos;
		m_prevMousePos = m_currMousePos;
	}

	m_camera->Update();
}
