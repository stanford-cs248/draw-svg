#include "viewport.h"

#include "CS248.h"

namespace CS248 {

void ViewportImp::set_viewbox( float x, float y, float span ) {

  // Task 3 (part 2): 
  // Set svg to normalized device coordinate transformation. 
  // Your input arguments are defined as SVG canvas coordinates.

  this->x = x;
  this->y = y;
  this->span = span; 

  Matrix3x3 viewbox_transform;
  viewbox_transform(0, 0) = (double)(1 / (2 * span));
  viewbox_transform(0, 1) = (double)0;
  viewbox_transform(0, 2) = (double)((span - x) / (2 * span));
  viewbox_transform(1, 0) = (double)0;
  viewbox_transform(1, 1) = (double)(1 / (2 * span));
  viewbox_transform(1, 2) = (double)((span - y) / (2 * span));
  viewbox_transform(2, 0) = (double)0;
  viewbox_transform(2, 1) = (double)0;
  viewbox_transform(2, 2) = (double)1;
  set_canvas_to_norm(viewbox_transform);
}

void ViewportImp::update_viewbox( float dx, float dy, float scale ) { 
  
  this->x -= dx;
  this->y -= dy;
  this->span *= scale;
  set_viewbox( x, y, span );
}

} // namespace CS248
