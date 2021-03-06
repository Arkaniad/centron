// System Includes
#include <string>
#include <sstream>

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
#include "starfield.h"
#include "core.h"

using namespace Centron;

// Variable Declarations
const std::string Engine::VERSION_STR = "Centron 0.0.9a";
const std::string Engine::LOG_TAG = "ENG";
const std::string Engine::RES_PATH = "/res/";

std::string PATH;

SDL_Surface *screen = NULL;
SDL_Surface *stars = NULL;
SDL_Surface *message = NULL;

TTF_Font *font = NULL;

Engine::Engine(const int argc, const char *argv[]){
  log.info("Bootstrap stage 2");
  main(argc, argv);
}

bool Engine::init(const int argc, const char *argv[]) {
  log.info("Initializing Engine "+VERSION_STR);
  log.info(argv[0]);
  res.setLaunchPath(argv[0]);

  status = "Running...";
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    log.info("Failed to initialize SDL.");
    return false;
  }
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if(screen == NULL) {
    log.err("Failed to initialize screen.");
    log.err(SDL_GetError());
    return false;
  }

  stars = get_star_surface();

  if(TTF_Init() == -1) {
    log.err("Could not initialize font.");
    return false;
  }

  SDL_WM_SetCaption(VERSION_STR.c_str(), NULL);
  return true;
}

bool Engine::load_files(){
  log.info("Loading content");

  log.info("Loading images.");
  
  log.info("Loading fonts.");
  console_font = TTF_OpenFont(res.getFontPath("ttf-inconsolata.otf").c_str(), 16);
  font = TTF_OpenFont(res.getFontPath("ttf-droidsans.ttf").c_str(), 12);
  if(font == NULL){
    log.err("Unable to load fonts");
    return false;
  } else {
    message = TTF_RenderText_Solid(font, VERSION_STR.c_str(), fontColor);
    if(message == NULL){
      log.err("Unable to load version tag");
      return false;
    }
  }
  return true;
}

void Engine::clean_up(){
  log.info("Cleaning up");

  SDL_FreeSurface(message);

  TTF_CloseFont(font);
  
  TTF_Quit();
  SDL_Quit();
}

bool Engine::loop(){
  // Clear rect
  SDL_Rect clear_rect {SCREEN_WIDTH, SCREEN_HEIGHT};
  
  // Starfield
  Starfield starfield (SCREEN_WIDTH, SCREEN_HEIGHT, stars);
  starfield.next_state();

  //Framerate Utilities
  int frame = 0;
  int framerate = 0;
  bool cap_frame = true;
  update.start();
  
  log.info("In main loop.");
  bool quit = false;
  while(!quit){
    fps.start();

    //Clear Rect
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    
    // Starfield
    starfield.next_state();
    gfx.apply_image(0, 0, stars, screen);
    
    // FPS Display
    std::stringstream buf;
    buf << VERSION_STR.c_str() << " | " << status << " | FPS: " << framerate;
    message = TTF_RenderText_Solid(font, buf.str().c_str(), fontColor);
    gfx.apply_image(0, SCREEN_HEIGHT-message->h, message, screen);

    // Event Handling
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
        case SDLK_UP: //message_keyboard = message_up;
            log.info("Key: UP");
            break;
        case SDLK_DOWN: //message_keyboard = message_dn;
            log.info("Key: DN");
            break;
        case SDLK_LEFT: //message_keyboard = message_lt;
            log.info("Key: LT");
            break;
        case SDLK_RIGHT: //message_keyboard = message_rt;
            log.info("Key: RT");
            break;
          default:
            break;
        }
      }
      if(event.type == SDL_QUIT){
        log.info("Received quit event.");
        quit = true;
      }
    }

    if((cap_frame) && (fps.get_ticks() < 1000 / FPS_LIMIT)){
      int ticks = fps.get_ticks();
      SDL_Delay((1000/FPS_LIMIT)-ticks);
    }
    
    if(update.get_ticks() > 1000) {
      framerate = frame;
      frame = 0;
      
      update.start();
    }
    
    if(SDL_Flip(screen) == -1){
      return 1;
    }
    
    frame++;
    
  }
  return true;
}

int Engine::main(const int argc, const char *argv[]){
  log.setTag(LOG_TAG);
  if(!init(argc, argv)){
    log.err("Could not initialize.");
    return 1;
  }
  if(load_files() == false){
    log.err("Could not load files.");
    return 1;
  }

  log.info("Setting up engine view.");

  log.info("Flipping screen.");
  if(SDL_Flip(screen) == -1){
    log.err("Could not flip screen.");
    return 1;
  }

  log.info("Entering main loop.");
  if(loop() == false){
    return 1;
  }

  clean_up();
  return 0;
}

SDL_Surface *Engine::get_star_surface() {
  Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif
  return SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, rmask, gmask, bmask, amask);
}
