#pragma once
#include"Vector3.h"
#include"Matrix4x4.h"
#undef max
#undef min

class Camera;
struct Shape
{
	virtual void Draw(Camera* camera, uint32_t color) = 0;
};

struct Plane : public Shape
{
	Plane(const Vector3& normal, float distance) : normal(normal), distance(distance) {}
	Vector3 normal;
	float distance;
	void Draw(Camera* camera, uint32_t color)override;
};

struct Sphere : public Shape
{
	Sphere(const Vector3& center, float radius) : center(center), radius(radius) {}
	Vector3 center;
	float radius;
	void Draw(Camera* camera, uint32_t color)override;
};

struct Line : public Shape
{
	Line(const Vector3& start, const Vector3& diff) : origin(start), diff(diff) {}
	Vector3 origin;
	Vector3 diff;
	void Draw(Camera* camera, uint32_t color)override;
};

struct Ray : public Shape
{
	Ray(const Vector3& start, const Vector3& diff) : origin(start), diff(diff) {}
	Vector3 origin;
	Vector3 diff;
	void Draw(Camera* camera, uint32_t color)override;
};

struct Segment : public Shape
{
	Segment(const Vector3& start, const Vector3& diff) : origin(start), diff(diff) {}
	Vector3 origin;
	Vector3 diff;
	void Draw(Camera* camera, uint32_t color)override;
};

struct Triangle : public Shape
{
	Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3) : vertices{ v1,v2,v3 } {}
	Vector3 vertices[3];
	void Draw(Camera* camera, uint32_t color)override;
};

struct AABB : public Shape
{
	AABB(const Vector3& min, const Vector3& max) : min(min), max(max) {}
	Vector3 min;
	Vector3 max;
	void Draw(Camera* camera, uint32_t color)override;
	void Clamp();
};

struct OBB : public Shape
{
	OBB(const Vector3& center, const Vector3& size) : center(center), size(size) {
		orientations[0] = { 1, 0, 0 };
		orientations[1] = { 0, 1, 0 };
		orientations[2] = { 0, 0, 1 };
	}
	Vector3 center;
	Vector3 size;
	Vector3 orientations[3];
	void SetRotation(const Vector3& axis);
	void Draw(Camera* camera, uint32_t color)override;

};
/// <summary>
/// グリッドを描画
/// </summary>
/// <param name="camera">カメラポインター</param>
/// <param name="subdvision">分割数</param>
void DrawGrid(Camera* camera, uint32_t subdvision = 10);
/// <summary>
/// ベクトルの投影
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
Vector3 Project(const Vector3& v1, const Vector3& v2);
/// <summary>
/// ベクトルの最も近い点を取得
/// </summary>
/// <param name="point"></param>
/// <param name="segment"></param>
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
/// <summary>
/// ベクトルの垂直ベクトルを取得
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
Vector3 Perpendicular(const Vector3& vector);
/// <summary>
/// OBBのワールド行列を取得
/// </summary>
/// <param name="obb"></param>
/// <returns></returns>
Matrix4x4 MakeOBBWorldMatrix(const OBB& obb);

