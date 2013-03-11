#ifndef CENTRON_DRAWABLE_H
#define CENTRON_DRAWABLE_H

#include <string>

namespace Centron {
  class Drawable {
    Uint32 id;
    boolean flatspace;
    int x;
    int y;
    int z;
    SDL_Surface *content;
  public:
    Drawable(SDL_Surface *surface, int x, int y, int z = 0);
    Drawable(SDL_Surface *surface, int x, int y, int z = 0, Uint32 id);
  }
}
