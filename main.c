#include "libs/project/imports.h"

int main() {
  srand(time(NULL));

  win = initWin("lineSurfer");
  initSound();
  renderer = win->renderer;

  // init vars
  terrain = initTerrain(renderer);
  player = initPlayer(renderer);

  obs = initObstacle();
  beat = initBeat();

  mainLoop(win, eventFunc, loopFunc);

  return 0;
}
