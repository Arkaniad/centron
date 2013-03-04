// System Includes
#include <string>
#include <iostream>
#include <iterator>

// Internal Includes
#include "resources.h"
#include "log.h"

using namespace Centron;

Resources::Resources(){
  log = Logger("RES");
  log.info("Initialized resource factory");
}
Resources::Resources(std::string theLaunchPath){
  launchPath = theLaunchPath;
  log = Logger("RES");
  log.info("Initialized resource factory with launch path.");
  buildResPath();
}
std::string Resources::truncateExecFromPath(std::string in){
  return in.substr(0, in.rfind("/")+1);
}
void Resources::setLaunchPath(std::string path){
  launchPath = path;
  buildResPath();
}
std::string Resources::getLaunchPath(){
  return launchPath;
}
std::string Resources::getResPath(){
  return resPath;
}
std::string Resources::getFontPath(std::string font = ""){
  if(font == ""){
    log.info(getResPath().append("font/"));
    return getResPath().append("font/");
  } else {
    log.info(getFontPath().append(font));
    return getFontPath().append(font);
  }
}
void Resources::buildResPath(){
  resPath = truncateExecFromPath(launchPath).append("res/");
  log.info("Built resPath: "+resPath);
}

