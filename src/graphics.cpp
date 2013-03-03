// System Includes
#include <string>

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
    log.warn("Pixel out of range.");
  }
}

