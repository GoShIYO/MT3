#include <Novice.h>
#include"Shape.h"
#include"DebugCamera.h"
#define USE_IMGUI
#include"2d/ImGuiManager.h"
#include"MathFunc.h"
#include"ShapeCollision.h"

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
	// デバッグカメラ
	Vector3 cameraPosition = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	DebugCamera debugCamera;
	debugCamera.Initialize(cameraPosition);
	// カメラ
	Camera* camera = debugCamera.GetCamera();
	camera->SetRotate(cameraRotate);
	
	bool isUseCameraMotion = false;

	Sphere sphere = {
		{0.0f,0.0f,0.0f},
		0.6f
	};
	
	Plane plane = {
		{0.0f,1.0f,0.0f},
		1.0f
	};
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
		debugCamera.Update(keys,isUseCameraMotion);

		ImGui::DragFloat3("SphereA.center", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereA.radius", &sphere.radius, 0.01f);
		ImGui::DragFloat3("Plane.normal", &plane.normal.x, 0.01f);
        ImGui::DragFloat("Plane.distance", &plane.distance, 0.01f);
		ImGui::Checkbox("isUseCameraMotion", &isUseCameraMotion);
		plane.normal = Normalize(plane.normal);

		bool isCollision = IsCollision(sphere, plane);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(camera);
		sphere.Draw(camera, isCollision ? RED : WHITE);
		plane.Draw(camera, WHITE);

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
