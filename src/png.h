#ifndef CS248_PNG_H
#define CS248_PNG_H

#include <map>
#include <vector>

#include "color.h"
#include "vector2D.h"
#include "tinyxml2.h"

namespace CS248 {

struct PNG {
  int width;
  int height;
  std::vector<unsigned char> pixels;
}; // class PNG

class PNGParser {
 public:
  static int load( const unsigned char* buffer, size_t size, PNG& png );
  static int load( const char* filename, PNG& png );
  static int save( const char* filename, const PNG& png );
}; // class PNGParser

} // namespace CS248

#endif // CS248_PNG_H
