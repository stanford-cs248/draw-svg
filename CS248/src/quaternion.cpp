#include "quaternion.h"

namespace CS248 {

  std::ostream& operator<<( std::ostream& os, const Quaternion& v ) {
    os << "{ " << v.x << "i, " << v.y << "j, " << v.z << "k, " << v.w << " }";
    return os;
  }

} // namespace CS248
