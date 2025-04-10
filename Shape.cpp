#include"Camera.h"
#include<Novice.h>
#include "Shape.h"
#include "MathFunc.h"
#include<algorithm>

Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f };
	}

	return { 0.0f, -vector.z, vector.y };
}

Matrix4x4 MakeOBBWorldMatrix(const OBB& obb)
{
	Matrix4x4 result = {
		{
			obb.orientations[0].x, obb.orientations[0].y, obb.orientations[0].z, 0.0f,
			obb.orientations[1].x, obb.orientations[1].y, obb.orientations[1].z, 0.0f,
			obb.orientations[2].x, obb.orientations[2].y, obb.orientations[2].z, 0.0f,
			obb.center.x,obb.center.y,obb.center.z, 1.0f
		}
	};
	return result;
}

void DrawGrid(Camera* camera, uint32_t subdvision) {
	const float kGridHalfWidth = 2.0f;										//Gridの半分の幅
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(subdvision);	//1つ分の長さ

	for (uint32_t xIndex = 0; xIndex <= subdvision; ++xIndex) {

		float pos_x = -kGridHalfWidth + xIndex * kGridEvery;
		Vector3 startPos = { pos_x,0,-kGridHalfWidth };
		Vector3 endPos = { pos_x,0,kGridHalfWidth };



		Vector3 screenStartPos = camera->TransformVertex(startPos);

		Vector3 screenEndPos = camera->TransformVertex(endPos);

		unsigned int color = (xIndex == subdvision / 2) ? 0x111111ff : 0xaaaaaaff;

		Novice::DrawLine(
			static_cast<int>(screenStartPos.x),
			static_cast<int>(screenStartPos.y),
			static_cast<int>(screenEndPos.x),
			static_cast<int>(screenEndPos.y),
			color);
	}

	for (uint32_t zIndex = 0; zIndex <= subdvision; ++zIndex) {

		float pos_z = -kGridHalfWidth + zIndex * kGridEvery;
		Vector3 startPos = { -kGridHalfWidth ,0,pos_z };
		Vector3 endPos = { kGridHalfWidth ,0,pos_z };


		Vector3 screenStartPos = camera->TransformVertex({ 0,0,0 }, startPos);

		Vector3 screenEndPos = camera->TransformVertex({ 0,0,0 }, endPos);
		unsigned int color = (zIndex == subdvision / 2) ? 0x111111ff : 0xaaaaaaff;

		Novice::DrawLine(
			static_cast<int>(screenStartPos.x),
			static_cast<int>(screenStartPos.y),
			static_cast<int>(screenEndPos.x),
			static_cast<int>(screenEndPos.y),
			color);

	}
}

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	float t = Dot(v1, v2) / Dot(v2,v2);
	Vector3 result = v2 * t;

	return result;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	// 点を直線での投影
    Vector3 distance = point - segment.origin;
	Vector3 project = Project(distance, segment.diff);
	
	float t = Dot(distance, segment.diff) / Dot(segment.diff, segment.diff);
	// tの範囲を線分に収める
	t = std::clamp(t, 0.0f, 1.0f);

	Vector3 result = segment.origin + segment.diff * t;

	return result;
}

void Plane::Draw(Camera* camera, uint32_t color) {
	Vector3 center = normal * distance;
	Vector3 perpendiculars[4]{};

	perpendiculars[0] = Normalize(Perpendicular(normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = Cross(normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int i = 0; i < 4; ++i) {
		Vector3 extend = perpendiculars[i] * 2.0f;
		points[i] = camera->TransformVertex({ 0,0,0 }, center + extend);
	}
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), color);
}

void Sphere::Draw(Camera* camera, uint32_t color) {
	const uint32_t kSubdivision = 16;
	const float kLonEvery = (2 * pi) / float(kSubdivision);
	const float kLatEvery = pi / float(kSubdivision);

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			Vector3 a, b, c;
			a = {
				cos(lat) * cos(lon),
				sin(lat),
				cos(lat) * sin(lon)
			};
			b = {
				cos(lat + kLatEvery) * cos(lon),
				sin(lat + kLatEvery),
				cos(lat + kLatEvery) * sin(lon)
			};
			c = {
				cos(lat) * cos(lon + kLonEvery),
				sin(lat),
				cos(lat) * sin(lon + kLonEvery)
			};
			a = center + a * radius;
			b = center + b * radius;
			c = center + c * radius;

			Vector3 screenAPos = camera->TransformVertex({ 0,0,0 }, a);
			Vector3 screenBPos = camera->TransformVertex({ 0,0,0 }, b);
			Vector3 screenCPos = camera->TransformVertex({ 0,0,0 }, c);

			Novice::DrawLine(
				static_cast<int>(screenAPos.x),
				static_cast<int>(screenAPos.y),
				static_cast<int>(screenBPos.x),
				static_cast<int>(screenBPos.y),
				color);
			Novice::DrawLine(
				static_cast<int>(screenAPos.x),
				static_cast<int>(screenAPos.y),
				static_cast<int>(screenCPos.x),
				static_cast<int>(screenCPos.y),
				color);
		}
	}
}

void Line::Draw(Camera* camera, uint32_t color)
{
	Vector3 screenStartPos = camera->TransformVertex(origin);
	Vector3 screenEndPos = camera->TransformVertex(origin + diff);
	Novice::DrawLine(
		static_cast<int>(screenStartPos.x),
		static_cast<int>(screenStartPos.y),
		static_cast<int>(screenEndPos.x),
		static_cast<int>(screenEndPos.y),
		color);
}

void Ray::Draw(Camera* camera, uint32_t color)
{
	Vector3 screenStartPos = camera->TransformVertex(origin);
	Vector3 screenEndPos = camera->TransformVertex(origin + diff);
	Novice::DrawLine(
		static_cast<int>(screenStartPos.x),
		static_cast<int>(screenStartPos.y),
		static_cast<int>(screenEndPos.x),
		static_cast<int>(screenEndPos.y),
		color);
}

void Segment::Draw(Camera* camera, uint32_t color)
{
	Vector3 screenStartPos = camera->TransformVertex(origin);
	Vector3 screenEndPos = camera->TransformVertex(origin + diff);
	Novice::DrawLine(
		static_cast<int>(screenStartPos.x),
		static_cast<int>(screenStartPos.y),
		static_cast<int>(screenEndPos.x),
		static_cast<int>(screenEndPos.y),
		color);
}

void Triangle::Draw(Camera* camera, uint32_t color)
{
	Vector3 screenAPos = camera->TransformVertex(vertices[0]);
	Vector3 screenBPos = camera->TransformVertex(vertices[1]);
	Vector3 screenCPos = camera->TransformVertex(vertices[2]);
	Novice::DrawTriangle(
		static_cast<int>(screenAPos.x), static_cast<int>(screenAPos.y),
		static_cast<int>(screenBPos.x), static_cast<int>(screenBPos.y),
		static_cast<int>(screenCPos.x), static_cast<int>(screenCPos.y),
		color, kFillModeWireFrame);
}

void AABB::Draw(Camera* camera, uint32_t color)
{
	//各頂点のインデックス
	const int aabbIndex[12][2]{
		{0, 1}, {1, 3}, {3, 2}, {2, 0}, // 前
		{4, 5}, {5, 7}, {7, 6}, {6, 4}, // 後ろ
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  // 左右
	};

	Vector3 screenPos[8];
	for (uint32_t i = 0; i < 8; ++i) {
		// 各頂点の座標を計算する
		Vector3 vertex{
			(i & 0b0100) == 0 ? min.x : max.x,
			(i & 0b0010) == 0 ? min.y : max.y,
			(i & 0b0001) == 0 ? min.z : max.z
		};
		screenPos[i] = camera->TransformVertex(vertex);
	}
	// 頂点の座標を順番に接続して描画
	for (uint32_t i = 0; i < 12; ++i) {
		int index0 = aabbIndex[i][0];
		int index1 = aabbIndex[i][1];

		Novice::DrawLine(
			static_cast<int>(screenPos[index0].x),
			static_cast<int>(screenPos[index0].y),
			static_cast<int>(screenPos[index1].x),
			static_cast<int>(screenPos[index1].y),
			color);
	}
}

void AABB::Clamp()
{
	min.x = std::min(min.x, max.x);
	max.x = std::max(min.x, max.x);

	min.y = std::min(min.y, max.y);
	max.y = std::max(min.y, max.y);

	min.z = std::min(min.z, max.z);
	max.z = std::max(min.z, max.z);
}

void OBB::SetRotation(const Vector3& axis)
{
	Matrix4x4 rotateMatrix = MakeRotateMatrix(axis);
	orientations[0] = Transform(Vector3(1.0f, 0.0f, 0.0f), rotateMatrix);
	orientations[1] = Transform(Vector3(0.0f, 1.0f, 0.0f), rotateMatrix);
	orientations[2] = Transform(Vector3(0.0f, 0.0f, 1.0f), rotateMatrix);
}

void OBB::Draw(Camera* camera, uint32_t color)
{
	Vector3 halfSize = size * 0.5f;
	const int aabbIndex[12][2]{
		{0, 1}, {1, 3}, {3, 2}, {2, 0}, // 前
		{4, 5}, {5, 7}, {7, 6}, {6, 4}, // 後ろ
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  // 左右
	};
	Vector3 vertices[8];
	for (uint32_t i = 0; i < 8; ++i) {
		vertices[i] = {
            (i & 0b0100) == 0 ? -halfSize.x : halfSize.x,
            (i & 0b0010) == 0 ? -halfSize.y : halfSize.y,
            (i & 0b0001) == 0 ? -halfSize.z : halfSize.z
        };
	}
	Matrix4x4 worldMatrix = MakeOBBWorldMatrix(*this);

	for (auto& vertex : vertices) {
		vertex = Transform(vertex,worldMatrix);
	}
	Vector3 screenVertices[8];
	for (int i = 0; i < 8; i++) {
		screenVertices[i] = camera->TransformVertex(vertices[i]);
	}

	// 頂点の座標を順番に接続して描画
	for (uint32_t i = 0; i < 12; ++i) {
		int index0 = aabbIndex[i][0];
		int index1 = aabbIndex[i][1];

		Novice::DrawLine(
			static_cast<int>(screenVertices[index0].x),
			static_cast<int>(screenVertices[index0].y),
			static_cast<int>(screenVertices[index1].x),
			static_cast<int>(screenVertices[index1].y),
			color);
	}
}
