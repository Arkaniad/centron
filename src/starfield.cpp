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

Starfield::Starfield(int w, int h, SDL_Surface *surface){
  srand(time(0));
  log.setTag("STRFLD");
  log.info("Initializing starfield");

  screen = surface;

  color = SDL_MapRGB(screen->format, 255, 255, 255);
  blank = SDL_MapRGB(screen->format, 0,   0,   0  );

  screen_x = w;
  screen_y = h;
  
  
  log.info("Calculating screen width");
  center_x = w / 2;
  center_y = h / 2;
  
  
  log.info("Loading stars");
  for(int i = 0; i < star_count; i++){
    star_x[i] = util.rand_int_range(-500, 500);
    star_y[i] = util.rand_int_range(-500, 500);
    star_z[i] = util.rand_int_range(0, 927);
    
    star_screenx[i] = get_new_axial_position(star_x[i], star_z[i], center_x);
    star_screeny[i] = get_new_axial_position(star_y[i], star_z[i], center_y);
    
  }

  log.info("Done initializing starfield");
}

void Starfield::next_state(){
  for(int i = 0; i < star_count; i++){
    gfx.apply_pixel(screen, star_screenx[i], star_screeny[i], blank);
    
    star_z[i] = star_z[i] + 5;

    star_screenx[i] = get_new_axial_position(star_x[i], star_z[i], center_x);
    star_screeny[i] = get_new_axial_position(star_y[i], star_z[i], center_y);

    if((!util.in_bounds(0, 0, screen_x, screen_y, star_screenx[i], star_screeny[i])) | (star_z[i] > 927)){
      star_x[i] = util.rand_int_range(-500, 500);
      star_y[i] = util.rand_int_range(-500, 500);
      star_z[i] = util.rand_int_range(100, 1000);
    }

    gfx.apply_pixel(screen, star_screenx[i], star_screeny[i], color);
  }
}

int Starfield::get_new_axial_position(int axis, int z, int center){
  return (axis * (.000000001 * ((z*z*z)-3)) + center);
}
