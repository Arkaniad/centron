//Include SDL functions
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "lib/logger.h"
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

SDL_Surface *message_dn = NULL;
SDL_Surface *message_rt = NULL;
SDL_Surface *message_lt = NULL;
SDL_Surface *message_up = NULL;

SDL_Surface *message_keyboard = NULL;

SDL_Event event;

Logger log;

TTF_Font *font = NULL;
SDL_Color text_color = { 255, 255, 255};

std::string tag = "ENGINE";


SDL_Surface *load_image(std::string filename){
  log.info("Loading image "+filename);
  SDL_Surface* loadedImage    = NULL;
  SDL_Surface* optimizedImage = NULL;
  loadedImage = IMG_Load(filename.c_str());
  if(loadedImage != NULL){
    log.info("Successfully loaded "+filename);
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  if(optimizedImage != NULL){
    Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
    SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
    return optimizedImage;
  }
  return optimizedImage;
}
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip = NULL){
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, dest, &offset);
}
bool init(){
  log = Logger(tag);
  log.info("Initializing Engine "+version_str);
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
    return false;
  }
  SDL_WM_SetCaption(version_str.c_str(), NULL);
  return true;
}
bool load_files(){
  log.info("Loading content");
  background = load_image("background.bmp");
  font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 28);
  if(font == NULL){
    return false;
  } else {
    message = TTF_RenderText_Solid(font, version_str.c_str(), text_color);
    message_up = TTF_RenderText_Solid(font, "Key: UP", text_color);
    message_dn = TTF_RenderText_Solid(font, "Key: DN", text_color);
    message_lt = TTF_RenderText_Solid(font, "Key: LT", text_color);
    message_rt = TTF_RenderText_Solid(font, "Key: RT", text_color);
  }
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

int main(int argc, const char* args[]){
  bool quit = false;
  if(!init()){
    return 1;
  }
  if(load_files() == false){
    return 1;
  }  
  

  apply_surface(0,0,background,screen);
  apply_surface(10,10,message,screen);
  if(SDL_Flip(screen)==-1){
    return 1;
  }
  
  while(quit ==false){
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
          apply_surface(0,0,background,screen);
          apply_surface(10,10,message,screen);
          apply_surface((SCREEN_WIDTH - message_keyboard->w) / 2, (SCREEN_HEIGHT - message_keyboard->h)/2, message_keyboard, screen);
          message_keyboard = NULL;
        }
        if(SDL_Flip(screen)==-1){
          return 1;
        }
      }
      if(event.type == SDL_QUIT){
        quit = true;
      }
    }
  }
  clean_up();
  return 0;
}