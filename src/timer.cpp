// System Includes

// Internal Includes
#include "log.h"
#include "timer.h"

// External Includes
#include "SDL/SDL.h"

using namespace Centron;

Timer::Timer(){
  log.setTag("TMR");
  log.info("Creating a timer.");
  stop();
}

void Timer::start(){
  log.info("Starting timer.");
  started = true;
  paused = false;
  startTicks = SDL_GetTicks();
}

void Timer::stop(){
  log.info("Stopping timer.");
  paused = false;
  started = false;
  pausedTicks = 0;
  startTicks = 0;
}

void Timer::pause(){
  if(started && !paused){
    paused = true;
    pausedTicks = SDL_GetTicks() - startTicks;
  }
}

void Timer::unpause(){
  if(paused){
    paused = false;
    startTicks = SDL_GetTicks() - pausedTicks;
    pausedTicks = 0;
  }
}

int Timer::get_time(){
  return get_ticks() / 1000;
}

int Timer::get_ticks(){
  if(started){
    if(paused){
      return pausedTicks;
    } else {
      return SDL_GetTicks() - startTicks;
    }
  }
  return 0;
}

bool Timer::is_paused(){
  return paused;
}

bool Timer::is_started(){
  return started;
}
