#ifndef CENTRON_DRAWABLE_H
#define CENTRON_DRAWABLE_H

// System Includes
#include <string>

// External Includes
#include "SDL/SDL.h"

// Internal Includes
#include "position.h"

namespace Centron {
  class Drawable2D {
    Uint32 id;
    Pos2D pos;
    SDL_Surface *content;
  public:
    Drawable2D(SDL_Surface *surface, int x, int y);
    Drawable2D(SDL_Surface *surface, int x, int y, Uint32 idp);
    SDL_Surface *get_content();
    Pos2D *get_pos();
  };
}

#endif
