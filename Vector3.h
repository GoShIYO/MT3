#pragma once
#include<cmath>

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	Vector3& operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
	}
    Vector3& operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    Vector3& operator*=(const float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    Vector3& operator/=(const float s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
    Vector3 operator+(const Vector3& v) const {
        return Vector3{ x + v.x, y + v.y, z + v.z };
    }
    Vector3 operator-(const Vector3& v) const {
        return Vector3{ x - v.x, y - v.y, z - v.z };
    }
    Vector3 operator*(const float s) const {
        return Vector3{ x * s, y * s, z * s };
    }
    Vector3 operator/(const float s) const {
        return Vector3{ x / s, y / s, z / s };
    }
	Vector3 operator-() const { 
        return Vector3{-x,-y,-z}; 
    }
    float Length() const {
        return sqrtf(x * x + y * y + z * z);
    }
    float LengthSq() const {
        return x * x + y * y + z * z;
    }
    float Dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    Vector3 Cross(const Vector3& v) const {
        return Vector3{
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        };
    }
    Vector3 Normalize() const {
        float length = Length();
        return Vector3{ x / length, y / length, z / length };
    }
};