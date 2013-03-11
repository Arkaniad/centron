#ifndef CENTRON_ENGINE_H
#define CENTRON_ENGINE_H

// System Includes
#include <string>

// External Includes
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"

// Internal Includes
#include "log.h"
#include "graphics.h"
#include "resources.h"
#include "util.h"
#include "timer.h"


namespace Centron {
  /**
   * This is the main engine class. It's what makes the whole thing tick.
   */
  class Engine {

  private:
    // String Constants
    const static std::string VERSION_STR;
    const static std::string LOG_TAG;
    const static std::string RES_PATH;

    std::string PATH;        
    
    // Settings (later changeable at runtime)
    const static int SCREEN_WIDTH   = 800;
    const static int SCREEN_HEIGHT  = 600;
    const static int SCREEN_BPP     = 32;

    const static int FPS_LIMIT      = 60;
    
    // Internal Variables
    Logger    log;
    Graphics  gfx;
    Resources res;
    Utility   util;
    Timer     fps;
    Timer     update;
    
    // Resource Variables
    // - Surfaces
    SDL_Surface *message;

    // - Fonts
    TTF_Font *font;
    TTF_Font *console_font;
    
    // - Colors
    SDL_Color fontColor = {255, 255, 255};
    
    // - Transient Variables
    SDL_Event event;
    SDL_Surface *screen;

    int frame;
    bool cap;

  public:
    Engine(const int argc, const char *argv[]);
    float get_fps();
    bool init(const int argc, const char *argv[]);
    bool load_files();
    void clean_up();
    bool loop();
    int main(const int argc, const char *argv[]);
  };
}
#endif
    
