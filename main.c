#include "libs/project/imports.h"

int main() {
  srand(time(NULL));

  win = initWin("lineSurfer");
  initSound();
  renderer = win->renderer;

  // init vars
  beat = initBeat();

  terrain = initTerrain(renderer);
  player = initPlayer(renderer);
  obstacles = initArray();

  // init clocks
  clk1 = initClock(REFRESHRATE, REFRESHRATE);
  clk2 =
      initClock(REFRESHRATE, 60 * 1000 / (float)(beat->bpm * beat->measures));

  mainLoop(win, eventFunc, loopFunc);

  return 0;
}
