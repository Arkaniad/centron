#ifndef RESOURCES_H
#define RESOURCES_H
#include <string>
#include "logger.h"
/**
 * A simple class that handles the configuration of the resources directory
 */
namespace Centron {
  class Resources {
    Logger log;
    std::string resPath;
    std::string launchPath;
    std::string truncateExecFromPath(std::string);
    public:
    Resources();
    void buildResPath();
    void setLaunchPath(std::string path);
    std::string getResPath();
    std::string getLaunchPath();
  };
  
};

#endif // RESOURCES_H
