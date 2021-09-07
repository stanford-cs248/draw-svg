#ifndef CS248_RENDERER_UTILS
#define CS248_RENDERER_UTILS

#include "vector2D.h"

using namespace CS248;

namespace utils
{
    int upperBound(float a, float b, float c);
    int lowerBound(float a, float b, float c);

    bool isOnLeft(const Vector2D &start, const Vector2D &end, int x, int y);

    class Triangle
    {
    public:
        Triangle(float x0, float y0, float x1, float y1, float x2, float y2) : vertexA(x0, y0), vertexB(x1, y1), vertexC(x2, y2) {}

        void makeCounterClockwise();

        int getMinX() const;
        int getMaxX() const;
        int getMinY() const;
        int getMaxY() const;

        bool isInside(int sx, int sy, size_t w, size_t h);

    private:
        bool isCounterClockwise();
        Vector2D vertexA;
        Vector2D vertexB;
        Vector2D vertexC;
    };
}

#endif