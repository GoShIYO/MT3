#pragma once
#include"Shape.h"

//球と球の当たり判定
bool IsCollision(const Sphere& a, const Sphere& b);
//球と平面の当たり判定
bool IsCollision(const Sphere& a, const Plane& b);
