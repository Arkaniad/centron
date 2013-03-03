#ifndef CENTRON_UTIL_H
#define CENTRON_UTIL_H

// System Includes
#include <string>
#include <sstream>

namespace Centron {
  /**
   * This is a simple utility class.
   */
  class Utility {
  public:
    // General utility functions
    std::string int2string(int in);
    int rand_int_range(int low, int high);

    // Geometry functions (amenable to separate later)
    bool in_bounds(int top_x, int top_y, int bottom_x, int bottom_y, int x, int y);
    
    // Constructor
    Utility();
  };
}
#endif
