// System Includes
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

// Internal Includes
#include "util.h"

using namespace Centron;

Utility::Utility(){
  
}

std::string Utility::int2string(int in){
  std::ostringstream stream;
  stream << in;
  return stream.str();
}

int Utility::rand_int_range(int low, int high){
  return ((rand() % high) + 1) + low;
}

bool Utility::in_bounds(int top_x, int top_y, int bottom_x, int bottom_y, int x, int y){
  return (x < bottom_x) && (x > top_y) && (y < bottom_y) && (y > top_y);
}

