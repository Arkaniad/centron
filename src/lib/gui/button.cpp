#include "button.h"
#include "buttonstates.h"
#include "../graphics.h"
#include "../logger.h"

using namespace Centron::GUI;

Button::Button(SDL_Surface *sheet, int x, int y, int w, int h, bool vis){
 log = Centron::Logger("BUTTN");
 image = sheet;
 box.x = x;
 box.y = y;
 box.w = w;
 box.h = h;
 
 visible = vis;
 
 setClips();
 log.info("Setting the current clip.");
 clip = &clips[CLIP_MOUSEOUT];
 log.info("Set the current clip.");
}

Button::~Button()
{

}
void Button::show(){
  visible = true;
}
void Button::hide(){
  visible = false;
}
bool Button::isVisible(){
  return visible;
}
void Button::handleEvents(SDL_Event *event){
  int x = 0; int y = 0;
  if(event->type == SDL_MOUSEMOTION){
    x = event->motion.x;
    y = event->motion.y;
    if((x>box.x)&&(x<box.x+box.w)&&(y>box.y)&&(y<box.y+box.h)){
      clip = &clips[CLIP_MOUSEOVER];
    } else {
      clip = &clips[CLIP_MOUSEOUT];
    }
  }
}
void Button::setClips(){
  log.info("Setting clips...");
  clips[CLIP_MOUSEOVER].x = 0;
  clips[CLIP_MOUSEOVER].y = 0;
  clips[CLIP_MOUSEOVER].w = 200;
  clips[CLIP_MOUSEOVER].h = 40;
  
  clips[CLIP_MOUSEOUT].x = 200;
  clips[CLIP_MOUSEOUT].y = 0;
  clips[CLIP_MOUSEOUT].w = 200;
  clips[CLIP_MOUSEOUT].h = 40;
  
  clips[CLIP_MOUSEDOWN].x = 0;
  clips[CLIP_MOUSEDOWN].y = 40;
  clips[CLIP_MOUSEDOWN].w = 200;
  clips[CLIP_MOUSEDOWN].h = 40;
  
  clips[CLIP_MOUSEUP].x = 200;
  clips[CLIP_MOUSEUP].y = 40;
  clips[CLIP_MOUSEUP].w = 200;
  clips[CLIP_MOUSEUP].h = 40;
  log.info("Done setting clips.");
}
SDL_Rect *Button::getClips(){
  return clips;
}
SDL_Surface *Button::getSurface(){
  return image;
}

int Button::getX(){
  return box.x;
}

int Button::getY(){
  return box.y;
}