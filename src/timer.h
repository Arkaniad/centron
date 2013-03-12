#ifndef CENTRON_TIMER_H
#define CENTRON_TIMER_H

// System Includes

// Internal Includes
#include "log.h"

// External Includes
#include "SDL/SDL.h"

namespace Centron {
  class Timer {
  private:
    bool started;
    bool paused;

    int startTicks;
    int pausedTicks;
    
    Logger log;
  public:
    Timer();
    void stop();
    void start();
    void pause();
    void unpause();
    
    int get_time();
    int get_ticks();

    bool is_paused();
    bool is_started();
  };
};

#endif
