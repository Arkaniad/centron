#ifndef _CAPP_H_
  #define _CAPP_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Centron {
  private: 
    bool  Running;
    SDL_Surface* Surf_Display;

  public:
    int centron();
    int OnExecute();

  public:
    bool OnInit();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif
