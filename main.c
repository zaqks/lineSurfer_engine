#include "libs/project/imports.h"

int main() {
  win = initWin("lineSurfer");
  renderer = win->renderer;


  //init
  terrain = initTerrain(renderer);
  player = initPlayer(renderer);

  mainLoop(win, eventFunc, loopFunc);

  return 0;
}
