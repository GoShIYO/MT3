#include <Novice.h>
#include"Shape.h"
#include<memory>
#include"DebugCamera.h"
#define USE_IMGUI
#include"2d/ImGuiManager.h"

const char kWindowTitle[] = "LE2A_20_リショウコウ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	// カメラの初期状態
	Vector3 cameraPosition = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	// デバッグカメラ
	DebugCamera debugCamera;
	debugCamera.Initialize(cameraPosition);
	// カメラの取得
	Camera* camera = debugCamera.GetCamera();
	camera->SetRotate(cameraRotate);

	Sphere sphere = {
		{ 0.0f,0.0f,0.0f},
		1.0f
	};
	//DebugCameraを更新するかどうかを切り替えるフラグ
	bool isUseCameraMotion = false;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.01f);
        ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
        ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f,0.1f,10.0f);
        ImGui::Checkbox("UseCameraMotion", &isUseCameraMotion);
		if (!isUseCameraMotion) {
			camera->SetCameraPosition(cameraPosition);
			camera->SetRotate(cameraRotate);
		}
		debugCamera.Update(keys,isUseCameraMotion);
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(camera);
		sphere.Draw(camera, 0xffffffff);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
