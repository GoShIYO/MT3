#pragma once
#include"Camera.h"
#include<memory>
#include<windows.h>

//class Input;
class DebugCamera {
public:
    DebugCamera() = default;
    ~DebugCamera() = default;

    void Initialize(const Vector3& position = {0.0f,1.9f,-6.49f});

    void Update(char* keys,bool isUseMotion);
    Camera* GetCamera()const { return m_camera.get(); }
private:
    //Input* m_input = nullptr;
    std::unique_ptr<Camera> m_camera = nullptr;

    float m_moveSpeed = 0.05f;

    POINT m_currMousePos = { 0,0 };
    POINT m_prevMousePos = { 0,0 };
};