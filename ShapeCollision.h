#pragma once
#include"Shape.h"

//球と球の当たり判定
bool IsCollision(const Sphere& a, const Sphere& b);
//球と平面の当たり判定
bool IsCollision(const Sphere& sphere, const Plane& plane);
//線分と平面の当たり判定
bool IsCollision(const Segment& segment, const Plane& plane);