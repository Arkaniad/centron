//Include SDL functions
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>

//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

//Loading Function
SDL_Surface *load_image(std::string filename){
  //Temporarily store image
  SDL_Surface* loadedImage    = NULL;
  //Optimized image
  SDL_Surface* optimizedImage = NULL;
  
  //Load the image!
  loadedImage = IMG_Load(filename.c_str());
  
  //Check image and optimize
  if(loadedImage != NULL){
    //Optimize
    optimizedImage = SDL_DisplayFormat(loadedImage);
    //Free the old image
    SDL_FreeSurface(loadedImage);
  }
  
  //Return the good stuff!
  return optimizedImage;
}

//Blitting function
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* dest){
    //Make a temporary rect to hold the offset;
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
    //Go forth and blit
    SDL_BlitSurface(source, NULL, dest, &offset);
}

int main(int argc, const char* args[]){
  SDL_Surface *screen;
  SDL_Surface *message;
  SDL_Surface *background;
  
  //Initialize all SDL subsystems
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
    return 1;
  }
  
  //Set up screen
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if(screen == NULL){
    return 1;
  }
  
  SDL_WM_SetCaption("Centron", NULL);
  
  //Load images
  message     = load_image("hello.bmp");
  background  = load_image("background.bmp");
  
  //Apply background
  apply_surface(0, 0, background, screen);
  apply_surface(320, 0, background, screen);
  apply_surface(0, 240, background, screen);
  apply_surface(320, 240, background, screen);
  
  apply_surface(180, 140, message, screen);
  
  //Update screen
  if(SDL_Flip(screen) == -1){
    return 1;
  }
  
  
  //Wait
  SDL_Delay(2000);
  
  //Loop and move silly ways
  int x_move = 180;
  int y_move = 140;
  bool loop = true;
  do {
    apply_surface(0, 0, background, screen);
    apply_surface(320, 0, background, screen);
    apply_surface(0, 240, background, screen);
    apply_surface(320, 240, background, screen);
    x_move++;
    y_move++;
    apply_surface(x_move, y_move, message, screen);
    if(SDL_Flip(screen) == -1){
      return 1;
    }
    SDL_Delay(10);
    
  } while(loop);
  
  //Free
  SDL_FreeSurface(message);
  SDL_FreeSurface(background);
  
  //Quit
  SDL_Quit();
  
  //Return
  return 0;
}