#ifndef CS248_TRIANGULATION_H
#define CS248_TRIANGULATION_H

#include "svg.h"

namespace CS248 {

// triangulates a polygon and save the result as a triangle list
void triangulate(const Polygon& polygon, std::vector<Vector2D>& triangles );

} // namespace CS248

#endif // CS248_TRIANGULATION_H

