#include "viewport.h"

#include "CS248.h"

namespace CS248 {

void ViewportImp::set_viewbox( float x, float y, float span ) {

  // Task 3 (part 2): 
  // Set svg to normalized device coordinate transformation. Your input
  // arguments are defined as SVG canvans coordinates.

  this->x = x;
  this->y = y;
  this->span = span;

  float x0 = x - span, y0 = y - span;
  float x1 = x + span, y1 = y + span;

  double translate[] = {
    1, 0, -x0,
    0, 1, -y0,
    0, 0, 1
  };
  double scale[] = {
    1.0 / (x1 - x0), 0, 0,
    0, 1.0 / (y1 - y0), 0,
    0, 0, 1
  };

  set_canvas_to_norm(Matrix3x3(scale) * Matrix3x3(translate));
}

void ViewportImp::update_viewbox( float dx, float dy, float scale ) { 
  
  this->x -= dx;
  this->y -= dy;
  this->span *= scale;
  set_viewbox( x, y, span );
}

} // namespace CS248
