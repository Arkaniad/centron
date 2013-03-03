// System includes
#include <ctime>
#include <cstdlib>

// Internal includes
#include "log.h"
#include "graphics.h"
#include "util.h"
#include "starfield.h"

// External includes
#include "SDL/SDL.h"

using namespace Centron;

Starfield::Starfield(int width, int height, SDL_Surface *surface){
  log.setTag("STRFLD");
  log.info("Initializing starfield");
  srand(time(0));

  screen = surface;

  color = SDL_MapRGB(screen->format, 255, 255, 255);
  blank = SDL_MapRGB(screen->format, 0,   0,   0  );

  log.info("Loading stars");
  for(int i = 0; i < star_count; i++){
    log.info("Loading star "+util.int2string(i));
    star_x[i] = util.rand_int_range(-500, 500);
    star_y[i] = util.rand_int_range(-500, 500);
    star_z[i] = util.rand_int_range(100, 1000);
    log.info("Star position: "+util.int2string(star_x[i])+","\
             + util.int2string(star_y[i]) + "," \
             + util.int2string(star_z[i]));
  }

  log.info("Calculating screen width");
  center_x = width / 2;
  center_y = height / 2;

  screen_x = width;
  screen_y = height;
  log.info("Done initializing starfield");
}

void Starfield::next_state(){
  log.info("Advancing starfield state...");
  for(int i = 0; i < star_count; i++){
    log.info("Applying pixel for star "+util.int2string(i));
    log.info("X: "+util.int2string(star_screenx[i]));
    log.info("Y: "+util.int2string(star_screeny[i]));
    gfx.apply_pixel(screen, star_screenx[i], star_screeny[i], blank);
    log.info("Applied pixel.");
    
    star_z[i] = star_z[i] - 5;

    star_screenx[i] = ((star_x[i] / star_z[i]) * 100) + center_x;
    star_screeny[i] = ((star_y[i] / star_z[i]) * 100) + center_y;
    
    if((!util.in_bounds(0, 0, screen_x, screen_y, star_screenx[i], star_screeny[i])) | (star_z[i] < 1)){
      star_x[i] = util.rand_int_range(-500, 500);
      star_y[i] = util.rand_int_range(-500, 500);
      star_z[i] = util.rand_int_range(100, 1000);
    }

    gfx.apply_pixel(screen, star_screenx[i], star_screeny[i], color);
  }
}
