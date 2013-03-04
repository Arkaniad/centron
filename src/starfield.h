#ifndef CENTRON_STARFIELD_H
#define CENTRON_STARFIELD_H

// Internal includes
#include "log.h"
#include "graphics.h"
#include "util.h"

// External includes
#include "SDL/SDL.h"

namespace Centron {
  class Starfield {
    /**
     * Class that allows for a nice starfield to be drawn.
     */
  private:
    Graphics gfx;
    Utility util;
    
    SDL_Surface *screen;
    
    const static int star_count = 64;
    
    int star_x[64];
    int star_y[64];
    int star_z[64];

    int star_screenx[64];
    int star_screeny[64];

    int screen_x;
    int screen_y;
    
    int center_x;
    int center_y;

    int state;

    Uint32 color;
    Uint32 blank;
    
    Logger log;
  public:
    Starfield(int width, int height, SDL_Surface *surface);
    void next_state();
    int get_new_axial_position(int axis, int z, int center);
  };
}

#endif
