#ifndef CENTRON_GRAPHICS_H
#define CENTRON_GRAPHICS_H

// External Includes
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// Internal Includes
#include "log.h"
#include "util.h"

namespace Centron {
  /**
   * This class is a graphics utility class.
   */
  class Graphics {
    Logger log;
    Utility util;
  public:
    Graphics();

    SDL_Surface *load_image(std::string filename);
    void apply_image(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip = NULL);
    void apply_pixel(SDL_Surface *screen, int x, int y, Uint32 color);
  };
}
#endif
