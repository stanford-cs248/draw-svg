#include "renderer_utils.h"
#include "vector2D.h"

#include <iostream>
#include <cmath>

using namespace CS248;

namespace utils
{
    int upperBound(float a, float b, float c)
    {
        float max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
        return (int)std::ceil(max);
    }
    int lowerBound(float a, float b, float c)
    {
        float min = (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
        return (int)std::floor(min);
    }

    bool isOnLeft(const Vector2D &start, const Vector2D &end, float x, float y)
    {
        auto edge = end - start;
        auto point = Vector2D(x, y) - start;
        return cross(point, edge) <= 0;
    }

    bool Triangle::isCounterClockwise()
    {
        auto edgeAB = vertexB - vertexA;
        auto edgeAC = vertexC - vertexA;
        return cross(edgeAB, edgeAC) >= 0;
    }

    void Triangle::makeCounterClockwise()
    {
        if (isCounterClockwise())
            return;

        std::swap(vertexB, vertexC);
    }
    int Triangle::getMaxX() const
    {

        return upperBound(vertexA.x, vertexB.x, vertexC.x);
    }
    int Triangle::getMinX() const
    {

        return lowerBound(vertexA.x, vertexB.x, vertexC.x);
    }
    int Triangle::getMaxY() const
    {

        return upperBound(vertexA.y, vertexB.y, vertexC.y);
    }

    int Triangle::getMinY() const
    {

        return lowerBound(vertexA.y, vertexB.y, vertexC.y);
    }

    bool Triangle::isInside(int sx, int sy, size_t w, size_t h)
    {
        float x = (float)sx + 0.5;
        float y = (float)sy + 0.5;
        if (sx < 0 || sx >= w)
            return false;

        if (sy < 0 || sy >= h)
            return false;
        auto ab = isOnLeft(vertexA, vertexB, x, y);
        auto bc = isOnLeft(vertexB, vertexC, x, y);
        auto ca = isOnLeft(vertexC, vertexA, x, y);

        return ab && bc && ca;
    }
}