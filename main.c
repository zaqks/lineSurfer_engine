#include "libs/project/imports.h"

int main() {
  srand(time(NULL));

  win = initWin("lineSurfer");
  initSound();
  renderer = win->renderer;

  // init vars
  terrain = initTerrain(renderer);
  player = initPlayer(renderer);

  beat = initBeat();

  // init clocks
  clk1 = initClock(REFRESHRATE, REFRESHRATE);
  clk2 = initClock(REFRESHRATE, 60000 / (float)(beat->bpm));

  mainLoop(win, eventFunc, loopFunc);

  return 0;
}
