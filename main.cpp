#include <Novice.h>
#include"Shape.h"
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
	// デバッグカメラ
	Vector3 cameraPosition = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	DebugCamera debugCamera;
	debugCamera.Initialize(cameraPosition);
	// カメラ
	Camera* camera = debugCamera.GetCamera();
	camera->SetRotate(cameraRotate);
	// 線分
	Segment segment = { {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point = { -1.5f,0.6f,0.6f };
	// 点が線分での投影と最近接点
	Vector3 project = Project(point - segment.origin, segment.diff);
	Vector3 closestPoint = ClosestPoint(point, segment);
	// 最近接点を小さい球で描画
	Sphere pointSphere = { point,0.01f };
	Sphere closestPointSphere = { closestPoint,0.01f };

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

		debugCamera.Update(keys, isUseCameraMotion);
		ImGui::DragFloat3("Point", &pointSphere.center.x, 0.01f);
		ImGui::DragFloat3("Segment origin", &segment.origin.x, 0.01f);
        ImGui::DragFloat3("Segment diff", &segment.diff.x, 0.01f);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::Checkbox("Use Camera Motion", &isUseCameraMotion);
		// 最近接点を更新
		closestPointSphere.center = ClosestPoint(point, segment);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(camera);
		segment.Draw(camera, WHITE);
		pointSphere.Draw(camera, RED);
        closestPointSphere.Draw(camera, BLACK);

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
