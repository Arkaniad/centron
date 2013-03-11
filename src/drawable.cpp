// System Includes
#include <iostream>

// External Includes
#include "SDL/SDL.h"

// Internal Includes
#include "position.h"
#include "drawable.h"

using namespace Centron;

Drawable2D::Drawable2D(SDL_Surface *surface, int x, int y) {
  content = surface;
  pos = Pos2D {x, y};
}

Drawable2D::Drawable2D(SDL_Surface *surface, int x, int y, Uint32 idp) {
  content = surface;
  pos = Pos2D {x, y};
  id = idp;
}

SDL_Surface *Drawable2D::get_content() {
  return content;
}

Pos2D *Drawable2D::get_pos(){
  return &pos;
}
