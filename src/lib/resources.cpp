#include "resources.h"
#include <string>
#include <iostream>
#include <iterator>
#include "logger.h"

namespace Centron {
  Resources::Resources(){
    log = Logger("RES");
    log.info("Initialized resource handler");
  }
  void Resources::buildResPath(){
    resPath = truncateExecFromPath(launchPath).append("res/");
    log.info("Built resPath: "+resPath);
  }
  std::string Resources::truncateExecFromPath(std::string in){
    return in.substr(0, in.rfind("/")+1);
  }
  void Resources::setLaunchPath(std::string path){
    launchPath = path;
  }
  std::string Resources::getLaunchPath(){
    return launchPath;
  }
  std::string Resources::getResPath(){
    return resPath;
  }
}

