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

	Sphere sphereA = {
		{0.0f,0.0f,0.0f},
		1.0f
	};

	Sphere sphereB = {
		{0.8f,0.0f,1.0f},
		0.5f
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

		ImGui::DragFloat3("SphereA.center", &sphereA.center.x, 0.01f);
		ImGui::DragFloat("SphereA.radius", &sphereA.radius, 0.01f);
		ImGui::DragFloat3("SphereB.center", &sphereB.center.x, 0.01f);
        ImGui::DragFloat("SphereB.radius", &sphereB.radius, 0.01f);
		ImGui::Checkbox("isUseCameraMotion", &isUseCameraMotion);

		bool isCollision = IsCollision(sphereA, sphereB);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(camera);
		sphereA.Draw(camera, isCollision ? RED : WHITE);
		sphereB.Draw(camera, WHITE);

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
