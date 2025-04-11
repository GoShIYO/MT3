#include "ShapeCollision.h"
#include"MathFunc.h"

bool IsCollision(const Sphere& a, const Sphere& b)
{
    float lengthSq = LengthSq(Subtract(a.center, b.center));
    float radiusSum = a.radius + b.radius;

    return lengthSq < radiusSum * radiusSum;
}

bool IsCollision(const Sphere& sphere, const Plane& plane)
{
    float distance = std::fabs(Dot(sphere.center, plane.normal) - plane.distance);

    return distance <= sphere.radius;
}

bool IsCollision(const Segment& segment, const Plane& plane)
{
    if (Dot(plane.normal, segment.diff) == 0) {
        return false;
    }
    // t = d - o・n / b・n
    float t = (plane.distance - Dot(segment.origin,plane.normal)) / Dot(segment.diff,plane.normal);

    return t >= 0.0f && t <= 1.0f;
}
