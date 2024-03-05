#include "libs/project/imports.h"

int main() {
  win = initWin("lineSurfer");
  renderer = win->renderer;


  //
  terrain = initTerrain(renderer);


  mainLoop(win, eventFunc, loopFunc);

  return 0;
}
