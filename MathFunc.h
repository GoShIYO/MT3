#pragma once
#include"Matrix3x3.h"
#include"Matrix4x4.h"
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"

static const float pi = 3.14159265358979323846f;
namespace NoviceUtility {
	static const int kColumnWidth = 60;
	static const int kRowHeight = 20;
	//ベクトルを画面に表示する関数
	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);
	//マトリックスを画面に表示する関数
	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);
}

//
// --2D
//
/// <summary>
/// 正射影行列作る関数
/// </summary>
/// <param name="left">左</param>
/// <param name="top">上</param>
/// <param name="right">右</param>
/// <param name="bottom">下</param>
/// <returns>正射影行列</returns>
Matrix3x3 MakeOrthoGraphicMatrix(float left, float top, float right, float bottom);
/// <summary>
/// ビューポート(変換)関数
/// </summary>
/// <param name="left">左</param>
/// <param name="top">上</param>
/// <param name="width">幅</param>
/// <param name="height">高</param>
/// <returns>変換した行列</returns>
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

Matrix3x3 Invers(Matrix3x3 matrix);

Matrix3x3 MakeAffineMatrix(const Vector2& scale, float theta, const Vector2& translate);
Vector2 Transform(const Vector2& vector, Matrix3x3& m);
Vector2 Normalize(const Vector2& v);
float Cross(const Vector2& v1, const Vector2& v2);
float Dot(const Vector2& v1, const Vector2& v2);
//
// --3D
//

/// <summary>
/// 透視投影行列作る関数
/// </summary>
/// <param name="fovY">fov</param>
/// <param name="aspectRatio"></param>
/// <param name="nearClip"></param>
/// <param name="farClip"></param>
/// <returns>透視投影行列</returns>
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip = 0.1f, float farClip = 100.0f);
/// <summary>
/// 正射影行列作る関数
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="right"></param>
/// <param name="bottom"></param>
/// <param name="nearClip"></param>
/// <param name="farClip"></param>
/// <returns></returns>
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
/// <summary>
/// ビューポート(変換)関数
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="minD">深度min</param>
/// <param name="maxD">深度max</param>
/// <returns></returns>
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height,float minD = 0.0f,float maxD = 1.0f);
/// <summary>
/// 4x4アフィン行列作る関数
/// </summary>
/// <param name="scale"></param>
/// <param name="rotate"></param>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
/// <summary>
/// スケール行列作る関数
/// </summary>
/// <param name="scale">スケール</param>
/// <returns>スケール行列</returns>
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
/// <summary>
/// オーラ角回転行列作る関数（X軸）
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRotateXMatrix(float radian);
/// <summary>
/// オーラ角回転行列作る関数（Y軸）
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRotateYMatrix(float radian);
/// <summary>
/// オーラ角回転行列作る関数（Z軸）
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRotateZMatrix(float radian);
/// <summary>
/// 回転行列作る関数
/// </summary>
/// <param name="axis">軸回転角度</param>
/// <returns>回転行列</returns>
Matrix4x4 MakeRotateMatrix(const Vector3& axis);
/// <summary>
/// 移動行列作る関数
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
/// <summary>
/// 行列の加法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
/// <summary>
/// 行列の減法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
/// <summary>
/// 行列の積
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
/// <summary>
/// 逆行列
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix4x4 Inverse(const Matrix4x4& matrix);
/// <summary>
/// 転置行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Transpose(const Matrix4x4& m);
/// <summary>
/// 単位行列作る
/// </summary>
/// <returns></returns>
Matrix4x4 MakeIdentity4x4();
/// <summary>
/// 4x4行列の変換
/// </summary>
Vector3 Transform(const Vector3& v, const Matrix4x4& m);
//正規化
Vector3 Normalize(const Vector3& v);
//加法
Vector3 Add(const Vector3& v1, const Vector3& v2);
//減法
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
//乗算
Vector3 Multiply(float s,const Vector3& v1);
//長さ
float Length(const Vector3& v);
//外積
Vector3 Cross(const Vector3& v1, const Vector3& v2);
//内積
float Dot(const Vector3& v1, const Vector3& v2);

//4次元ベクトル変換
Vector4 Transform(const Vector4& v, const Matrix4x4& m);
constexpr float ConvertToRadians(float degrees) noexcept { return degrees * (pi / 180.0f); }
constexpr float ConvertToDegrees(float radians) noexcept { return radians * (180.0f / pi); }