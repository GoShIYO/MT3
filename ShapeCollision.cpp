#include "ShapeCollision.h"
#include"MathFunc.h"

bool IsCollision(const Sphere& a, const Sphere& b)
{
    float lengthSq = LengthSq(Subtract(a.center, b.center));
    float radiusSum = a.radius + b.radius;

    return lengthSq < radiusSum * radiusSum;
}

bool IsCollision(const Sphere& a, const Plane& b)
{
    float distance = std::fabs(Dot(a.center, b.normal) - b.distance);

    return distance <= a.radius;
}
