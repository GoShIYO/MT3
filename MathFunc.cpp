#include "MathFunc.h"
#include<Novice.h>
#include<cmath>
#include<cassert>

Matrix3x3 MakeOrthoGraphicMatrix(float left, float top, float right, float bottom)
{
	Matrix3x3 result = {
		{
			2.0f / (right - left),0.0f,0.0f,
			0.0f,2.0f / (top - bottom),0.0f,
			(left + right) / (left - right),(top + bottom) / (bottom - top),1.0f
		}

	};
	return result;
}

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height)
{
	Matrix3x3 result = {
		{
			width / 2.0f,0.0f,0.0f,
			0.0f,-height / 2.0f,0.0f,
			left + width / 2.0f,top + height / 2.0f,1.0f
		}
	};
	return result;
}

Matrix3x3 Invers(Matrix3x3 matrix)
{
	float a =
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];
	assert(a != 0.0f);
	float inversA = 1 / a;

	Matrix3x3 result{};
	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) * inversA;
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) * inversA;
	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) * inversA;

	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) * inversA;
	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) * inversA;
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) * inversA;

	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * inversA;
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) * inversA;
	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) * inversA;

	return result;
}

Matrix3x3 MakeAffineMatrix(const Vector2& scale, float theta, const Vector2& translate)
{
	Matrix3x3 affineMatrix = {
		{
			{ scale.x * cos(theta),  sin(theta), 0.0f },
			{ -sin(theta), scale.y * cos(theta), 0.0f},
			{ translate.x, translate.y, 1.0f}
		}
	};

	return affineMatrix;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result = {
		{
			1.0f / (aspectRatio * tan(fovY * 0.5f)), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tan(fovY * 0.5f), 0.0f, 0.0f,
			0.0f, 0.0f, farClip / (farClip - nearClip), 1.0f,
			0.0f, 0.0f, -farClip * nearClip / (farClip - nearClip), 0.0f
		}
	};
	return result;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result = {
		{
			2 / (right - left), 0.0f, 0.0f, 0.0f,
			0.0f, 2 / (top - bottom), 0.0f, 0.0f,
			0.0f, 0.0f, 1 / (farClip - nearClip), 0.0f,
			(left + right) / (left - right), (top + bottom) / (bottom - top), nearClip / (nearClip - farClip), 1.0f
		}
	};

	return result;

}
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minD, float maxD)
{
	Matrix4x4 result = {
		{
			width / 2.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -height / 2.0f, 0.0f, 0.0f,
			0.0f,0.0f,maxD - minD,0.0f,
			left + width / 2.0f, top + height / 2.0f, minD, 1.0f
		}
	};
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 result = MakeScaleMatrix(scale) * MakeRotateMatrix(rotate) * MakeTranslateMatrix(translate);

	return result;
}

Matrix4x4 Inverse(const Matrix4x4& matrix)
{
	float a = {
		1 /
		((matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) +
		(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) +
		(matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2])

		- (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) -
			(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) -
			(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2])

		- (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) -
			(matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]) -
			(matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2])

		+ (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2])

		+ (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1]) + (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2])

		- (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2])

		- (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0])

		+ (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0])
			)
	};

	Matrix4x4 inverseMatrix = { 0 };
	inverseMatrix.m[0][0] = (
		(matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) + (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2])
		- (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) - (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2])
		);
	inverseMatrix.m[0][1] = (
		-(matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1]) - (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2])
		+ (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1]) + (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2])
		);
	inverseMatrix.m[0][2] = (
		(matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1]) + (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2])
		- (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1]) - (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2])
		);

	inverseMatrix.m[0][3] = (
		-(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1]) - (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2])
		+ (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1]) + (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2])
		);


	inverseMatrix.m[1][0] = (
		-(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2])
		+ (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2])
		);

	inverseMatrix.m[1][1] = (
		(matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2])
		- (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2])
		);

	inverseMatrix.m[1][2] = (
		-(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2])
		+ (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2])
		);

	inverseMatrix.m[1][3] = (
		(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2])
		- (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2])
		);


	inverseMatrix.m[2][0] = (
		(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1])
		- (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1])
		);

	inverseMatrix.m[2][1] = (
		-(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1])
		+ (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1])
		);

	inverseMatrix.m[2][2] = (
		(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1])
		- (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0]) - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1])
		);

	inverseMatrix.m[2][3] = (
		-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0]) - (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1])
		+ (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3]) + (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1])
		);


	inverseMatrix.m[3][0] = (
		-(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]) - (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1])
		+ (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]) + (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1])
		);

	inverseMatrix.m[3][1] = (
		(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2]) + (matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1])
		- (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1])
		);

	inverseMatrix.m[3][2] = (
		-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2]) - (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1])
		+ (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2]) + (matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1])
		);

	inverseMatrix.m[3][3] = (
		(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) + (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1])
		- (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) - (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1])
		);


	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = a * inverseMatrix.m[i][j];
		}
	}

	return result;
}

Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}

	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result = {
		{
			scale.x,0.0f,0.0f,0.0f,
			0.0f,scale.y,0.0f,0.0f,
			0.0f,0.0f,scale.z,0.0f,
			0.0f,0.0f,0.0f,1.0f
		}
	};
	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	Matrix4x4 result = {
		{1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, cosTheta, sinTheta, 0.0f,
		 0.0f, -sinTheta, cosTheta, 0.0f,
		  0.0f, 0.0f, 0.0f, 1.0f
		}
	};
	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	Matrix4x4 result = {
		{ 
		  cosTheta, 0.0f, -sinTheta, 0.0f,
		  0.0f, 1.0f, 0.0f, 0.0f,
		  sinTheta, 0.0f, cosTheta, 0.0f,
		  0.0f, 0.0f, 0.0f, 1.0f
		}
	};
	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	Matrix4x4 result = {
		{
		   cosTheta, sinTheta, 0.0f, 0.0f,
		  -sinTheta, cosTheta, 0.0f, 0.0f,
		  0.0f, 0.0f, 1.0f, 0.0f,
		  0.0f, 0.0f, 0.0f, 1.0f
		}
	};
	return result;
}

Matrix4x4 MakeRotateMatrix(const Vector3& axis)
{
	Matrix4x4 rotateX = MakeRotateXMatrix(axis.x);
    Matrix4x4 rotateY = MakeRotateYMatrix(axis.y);
    Matrix4x4 rotateZ = MakeRotateZMatrix(axis.z);
	return Multiply(rotateX, Multiply(rotateY, rotateZ));
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result = {
		{
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
            0.0f,0.0f,1.0f,0.0f,
			translate.x,translate.y,translate.z,1.0f
		}
	};
	return result;
}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
	return result;
}

Vector2 Transform(const Vector2& vector, Matrix3x3& matrix)
{
	Vector2 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Vector2 Normalize(const Vector2& v)
{
	float length = std::sqrt(v.x * v.x + v.y * v.y);
	return v / length;
}

float Cross(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

float Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

Matrix4x4 MakeIdentity4x4()
{
	Matrix4x4 result = {
		{
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f
		}
	};
	return result;
}

Vector3 Transform(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{};
	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	assert(w != 0);
	result /= w;

	return result;
}

Vector3 Normalize(const Vector3& v)
{
	float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return v / length;
}

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	return v1 + v2;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
    return v1 - v2;
}

Vector3 Multiply(float s, const Vector3& v1)
{
    return v1 * s;
}

float Length(const Vector3& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    return Vector3{ x, y, z };
}

float Dot(const Vector3& v1, const Vector3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector4 Transform(const Vector4& v, const Matrix4x4& m)
{
	Vector4 result;
	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w * m.m[3][0];
    result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w * m.m[3][1];
    result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w * m.m[3][2];
    result.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

	return result;
}

void NoviceUtility::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
    Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void NoviceUtility::MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix,const char* label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			Novice::ScreenPrintf(x + col * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f", matrix.m[row][col]);
		}
	}
}
