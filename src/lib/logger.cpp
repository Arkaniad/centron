#include "logger.h"
#include <iostream>

using namespace Centron;

Logger::Logger()
{
  tag = "LOG";
  info("Logger initialized.");
}
Logger::Logger(std::string newtag){
  tag = newtag;
  info("Logger initialized.");
}
Logger::~Logger()
{
}
void Logger::info(std::string message){
  std::cout << "[" << tag << "] " << message << std::endl;
}
void Logger::info(std::string suptag, std::string message){
  std::cout << "[" << suptag << "] " << message << std::endl;
}
void Logger::warn(std::string message){
  std::cout << "[" << tag << " WARN] " << message << std::endl;
}
void Logger::warn(std::string suptag, std::string message){
  std::cout << "[" << suptag << " WARN] " << message << std::endl;
}
void Logger::err(std::string message){
  std::cout << "[" << tag << "] ERROR" << message << std::endl;
}
void Logger::err(std::string suptag, std::string message){
  std::cout << "[" << suptag << "] ERROR" << message << std::endl;
}
void Logger::setTag(std::string newtag){
  tag = newtag;
}
