#ifndef CENTRON_GUI_BUTTON_H
#define CENTRON_GUI_BUTTON_H
#include "SDL/SDL.h"
#include "../logger.h"


namespace Centron {
  namespace GUI {
    class Button {
      bool visible;
      SDL_Surface *image;
      SDL_Rect box;
      SDL_Rect *clip;
      SDL_Rect clips[4];
      
      Logger log;
      
      public:
        Button(SDL_Surface *sheet, int x, int y, int w, int h, bool vis = true);
        void handleEvents(SDL_Event *event);
        void show();
        void hide();
        bool isVisible();
        virtual ~Button();
        SDL_Rect *getClips();
        void setClips();
        SDL_Surface *getSurface();
        
        int getX();
        int getY();
    };
  }
}

#endif // CENTRON_GUI_BUTTON_H
