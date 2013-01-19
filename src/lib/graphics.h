#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "logger.h"

namespace Centron {
  /**
  * @brief A simple graphics utility class to seperate some code.
  */
  class Graphics {
    Logger log;
    public:
      Graphics();
      
      /**
      * @brief SDL abstraction helpers
      */
      SDL_Surface *load_image(std::string filename);
      
      /**
      * @brief Basic graphics functions
      */
      void apply_image(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip = NULL);
  };
};
#endif // GRAPHICS_H
