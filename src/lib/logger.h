#ifndef CENTRON_LOGGER_H
#define CENTRON_LOGGER_H

#include <iostream>

namespace Centron {

class Logger
{
  std::string tag;
  public:
    Logger();
    Logger(std::string newtag);
    virtual ~Logger();
    
    //Reams and reams of logging functions
    void info(std::string message);
    void info(std::string suptag, std::string message);
    void warn(std::string message);
    void warn(std::string suptag, std::string message);
    void err(std::string message);
    void err(std::string suptag, std::string message);
    
    void setTag(std::string newTag);
  };
    
}

#endif // CENTRON_LOGGER_H
