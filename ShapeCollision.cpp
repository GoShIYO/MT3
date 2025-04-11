#include "ShapeCollision.h"
#include"MathFunc.h"

bool IsCollision(const Sphere& a, const Sphere& b)
{
    float lengthSq = LengthSq(Subtract(a.center, b.center));
    float radiusSum = a.radius + b.radius;

    return lengthSq < radiusSum * radiusSum;
}
