#ifndef CENTRON_RESOURCES_H
#define CENTRON_RESOURCES_H

// System Includes
#include <string>

// Internal Includes
#include "log.h"

namespace Centron {
  class Resources {
  private:
    Logger log;
    std::string resPath;
    std::string launchPath;
    std::string truncateExecFromPath(std::string in);
    void buildResPath();
    
  public:
    Resources();
    Resources(std::string theLaunchPath);

    void setLaunchPath(std::string path);
    std::string getResPath();
    std::string getLaunchPath();
    std::string getFontPath(std::string font);
  };
}

#endif 
