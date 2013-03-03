// System Includes
#include <string>
#include <sstream>

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

