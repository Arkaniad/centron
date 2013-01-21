//Include SDL functions
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "lib/logger.h"
#include "lib/graphics.h"
#include "lib/gui/button.h"
#include <string>
#include <iostream>

#define DEBUG

const std::string version_str = "Centron Engine 0.0.1a";

//Use the namespace
using namespace Centron;

//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

SDL_Surface *sprite  = NULL;

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Surface *button_sheet = NULL;

SDL_Surface *message_dn = NULL;
SDL_Surface *message_rt = NULL;
SDL_Surface *message_lt = NULL;
SDL_Surface *message_up = NULL;

SDL_Surface *message_keyboard = NULL;

SDL_Event event;

Logger log;
Graphics gfx;

TTF_Font *font = NULL;
SDL_Color text_color = { 255, 255, 255};

GUI::Button *button = NULL;


std::string tag = "ENGINE";
std::string path = "";
std::string respath = "/res/";

//Engine Functions
bool init(const int argc, const char *argv[]){
  log = Logger(tag);
  log.info("Initializing Engine "+version_str);
  log.info(argv[0]);
  path = argv[0];
  //Initialize all SDL subsystems
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
    log.info("Failed to init SDL.");
    return false;
  }
  
  //Set up screen
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if(screen == NULL){
    log.info("Failed to init screen.");
    return false;
  }
  
  if(TTF_Init() == -1){
    log.err("Could not init font.");
    return false;
  }
  SDL_WM_SetCaption(version_str.c_str(), NULL);
  return true;
}
bool load_files(){
  log.info("Loading content");
  
  log.info("Loading images.");
  background = gfx.load_image(path+respath+"background.bmp");
  button_sheet = gfx.load_image(path+respath+"button.png");
  
  log.info("Loading fonts.");
  font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 28);
  if(font == NULL){
    log.err("Couldn't load fonts.");
    return false;
  } else {
    log.info("Loading messages.");
    message = TTF_RenderText_Solid(font, version_str.c_str(), text_color);
    message_up = TTF_RenderText_Solid(font, "Key: UP", text_color);
    message_dn = TTF_RenderText_Solid(font, "Key: DN", text_color);
    message_lt = TTF_RenderText_Solid(font, "Key: LT", text_color);
    message_rt = TTF_RenderText_Solid(font, "Key: RT", text_color);
  }
  GUI::Button tmp_button = GUI::Button(button_sheet, 50, 50, 200, 40, true);
  button = &tmp_button;
  return true;
}
void clean_up(){
  log.info("Cleaning up");
  SDL_FreeSurface(sprite);
  SDL_FreeSurface(background);
  SDL_FreeSurface(message);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

//Game loop
bool loop(){
  log.info("In main loop.");
  bool quit = false;
  while(quit == false){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
          case SDLK_UP: message_keyboard = message_up;
          log.info("Key: UP");
          break;
          case SDLK_DOWN: message_keyboard = message_dn;
                   log.info("Key: DN");
          break;
          case SDLK_LEFT: message_keyboard = message_lt;
          log.info("Key: LT");
          break;
          case SDLK_RIGHT: message_keyboard = message_rt;
                   log.info("Key: RT");
          break;
          default:
            break;
        }
        if(message_keyboard != NULL){
          button->show();
          if(button->isVisible()){
            log.info("Drawing button!");
            gfx.apply_image(button->getX(), button->getY(),button->getSurface(),screen, button->getClips());
          }
          gfx.apply_image(0,0,background,screen);
          gfx.apply_image(10,10,message,screen);
          gfx.apply_image((SCREEN_WIDTH - message_keyboard->w) / 2, (SCREEN_HEIGHT - message_keyboard->h)/2, message_keyboard, screen);
          message_keyboard = NULL;
        }
        if(SDL_Flip(screen)==-1){
          log.err("Couldn't flip screen (In main loop.)");
          return false;
        }
      }
      if(event.type == SDL_QUIT){
        log.info("Received quit event.");
        quit = true;
      }
    }
  } return true;
}

//Main code
int main(const int argc, const char *argv[]){
  if(!init(argc, argv)){
    log.err("Couldn't init.");
    return 1;
  }
  if(load_files() == false){
    log.err("Didn't load files.");
    return 1;
  }  
  
  log.info("Setting up the engine view.");
  gfx.apply_image(0,0,background,screen);
  gfx.apply_image(10,10,message,screen);
  
  log.info("Flipping screen.");
  if(SDL_Flip(screen)==-1){
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