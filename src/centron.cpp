#include "centron.h"

int Centron::centron() {
  Surf_Display = NULL;
  Running = true;
}

int Centron::OnExecute() {
  if(OnInit() == false) {
    return -1;
  }
  SDL_Event Event;

  while(Running) {
    while(SDL_PollEvent(&Event)) {
      OnEvent(&Event);
    }
    
    OnLoop();
    OnRender();
  }
  OnCleanup();
  return 0;
}

int main(int argc, const char *argv[]) {
  Centron app;
  return app.OnExecute();
}
