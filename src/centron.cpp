//Include SDL functions
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "lib/logger.h"
#include <string>
#include <iostream>

//Use the namespace
using namespace Centron;

//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

SDL_Surface *image  = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

Logger log;

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
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* dest){
    log.info("Blitting surface");
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, NULL, dest, &offset);
}
bool init(){
  log = Logger(tag);
  log.info("Initializing Engine");
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
  
  SDL_WM_SetCaption("Centron", NULL);
  return true;
}
bool load_files(){
  log.info("Loading content");
  image = load_image("x.png");
  if(image == NULL){
    return false;
  }
  return true;
}
void clean_up(){
  log.info("Cleaning up");
  SDL_FreeSurface(image);
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
  apply_surface(0,0,image,screen);
  if(SDL_Flip(screen)==-1){
    return 1;
  }
  
  while(quit ==false){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        quit = true;
      }
    }
  }
  clean_up();
  return 0;
}