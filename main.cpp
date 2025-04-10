#include <Novice.h>
#include"MathFunc.h"
#include<array>

const char kWindowTitle[] = "LE2A_20_リショウコウ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

using namespace NoviceUtility;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 v1 = { 1.2f,-3.9f,2.5f };
	Vector3 v2 = { 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };

	Vector3 cameraPosition = { 0.0f,0.0f,-3.0f };
	float speed = 0.1f;

	const Vector3 kLocalVertices[3] = {
		{-0.5f,-0.5f,0.0f},
		{0.0f,0.5f,0.0f},
		{0.5f,-0.5f,0.0f}
	};
	std::array<Vector3, 3> screenVertices{};

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
		if (keys[DIK_W]) {
			translate.z += speed;
		}
		if (keys[DIK_S]) {
			translate.z -= speed;
		}
		if (keys[DIK_A]) {
			translate.x -= speed;
		}
		if (keys[DIK_D]) {
			translate.x += speed;
		}
		rotate.y += 0.01f;

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, (float)kWindowWidth / (float)kWindowHeight, 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, (float)kWindowWidth, (float)kWindowHeight, 0.0f, 1.0f);

		for (int i = 0; i < 3; i++) {
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y),
			0xcc0000ff, kFillModeSolid
		);
		VectorScreenPrintf(0, 0, cross, "cross");
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
