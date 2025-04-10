#pragma once
#include<cmath>

/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4]{};

	Matrix4x4 operator+(const Matrix4x4& other) const {
		Matrix4x4 result{};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = m[i][j] + other.m[i][j];
			}
		}
		return result;
	}

	Matrix4x4 operator-(const Matrix4x4& other) const {
		Matrix4x4 result{};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = m[i][j] - other.m[i][j];
			}
		}
		return result;
	}

	Matrix4x4 operator*(const Matrix4x4& other) const {
		Matrix4x4 result{};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					result.m[i][j] += m[i][k] * other.m[k][j];
				}
			}
		}
		return result;
	}

	Matrix4x4 operator*(const float& scalar) const {
		Matrix4x4 result{};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = m[i][j] * scalar;
			}
		}
		return result;
	}

	Matrix4x4 operator/(const float& scalar) const {
		Matrix4x4 result{};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = m[i][j] / scalar;
			}
		}
		return result;
	}
	/// <summary>
	/// 行列の転置
	/// </summary>
	/// <returns></returns>
	Matrix4x4 Transpose() const {
		Matrix4x4 result{};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = m[j][i];
			}
		}
		return result;
	}
};
