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
#include "starfield.h"
#include "centron.h"

using namespace Centron;

// Variable Declarations
const std::string Engine::VERSION_STR = "Centron 0.0.1a";
const std::string Engine::LOG_TAG = "ENG";
const std::string Engine::RES_PATH = "/res/";

std::string PATH;

SDL_Surface *screen = NULL;

SDL_Surface *message = NULL;

TTF_Font *font = NULL;

SDL_Color fontColor = {255, 255, 255};

int frame = 0;

bool cap = true;

Engine::Engine(const int argc, const char *argv[]){
  log.info("Bootstrap stage 2");
  main(argc, argv);
}

bool Engine::init(const int argc, const char *argv[]) {
  log.info("Initializing Engine "+VERSION_STR);
  log.info(argv[0]);
  res.setLaunchPath(argv[0]);

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
  //font = TTF_OpenFont(res.getFontPath("ttf-inconsolata.otf").c_str(), 10);
  font = TTF_OpenFont("/usr/share/fonts/TTF/arial.ttf", 10);
  if(font == NULL){
    log.err("Unable to load font \"Inconsolata\"");
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
  //Starfield
  Starfield starfield (SCREEN_WIDTH, SCREEN_HEIGHT, screen);
  starfield.next_state();
  
  gfx.apply_image(100, 100, message, screen);
  SDL_Flip(screen);
  log.info(SDL_GetError());
  log.info("In main loop.");
  
  bool quit = false;
  while(!quit){
    fps.start();
    starfield.next_state();
    gfx.apply_image(100, 100, message, screen);
    SDL_Flip(screen);  
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_KEYDOWN){
        SDL_Flip(screen);
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
    if((cap) && (fps.get_ticks() < 1000 / FPS_LIMIT)){
      SDL_Delay((1000/FPS_LIMIT)-fps.get_ticks());
    }
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
