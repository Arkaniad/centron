// System Includes
#include <string>
#include <cmath>

// External Includes
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// Internal Includes
#include "graphics.h"
#include "log.h"
#include "util.h"

using namespace Centron;

Graphics::Graphics(){
  log = Logger("GRAPHICS");
}

SDL_Surface *Graphics::load_image(std::string filename) {
  log.info("Loading image "+filename);
  SDL_Surface* loadedImage    = NULL;
  SDL_Surface* optimizedImage = NULL;
  loadedImage = IMG_Load(filename.c_str());
  if(loadedImage != NULL){
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
    log.info("Successfully loaded "+filename);
  }
  if(optimizedImage != NULL){
    Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
    SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
    return optimizedImage;
  }
  return optimizedImage;
}

void Graphics::apply_image(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip) {
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  if(SDL_BlitSurface(source, clip, dest, &offset) == -1){
    std::string err = SDL_GetError();
    log.err("Failed to blit surface: "+err);
  }
}

void Graphics::apply_pixel(SDL_Surface* surface, int x, int y, Uint32 pixel){
  if(util.in_bounds(0, 0, surface->w, surface->h, x, y)){
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp){
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
    case 4:
      *(Uint32 *)p = pixel;
      break;
    }     
  } else {
    // woops
  }
}

void Graphics::apply_line(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 color) {
  int dx = abs(x1-x0);
  int dy = abs(y1-y0);
  
  int sx;
  int sy;
  
  if(x0 < x1) {
    sx = 1;
  } else {
    sx = -1;
  }
  
  if(y0 < y1) {
    sy = 1;
  } else {
    sy = -1;
  }
  
  int err = dx-dy;
  
  bool drawing = false;
  while(drawing) {
    apply_pixel(surface, x0, y0, color);
    if(x0 == x1 and y0 == y1) {
      drawing = false;
      return;
    }
    
    int e2 = 2*err;
    if(e2 > -dy) {
      err = err -dy;
      x0 = x0 + sx;
    }
    
    if(e2 > dx) { 
      err = err + dx;
      y0 = y0 + sy;
    }
  }
}