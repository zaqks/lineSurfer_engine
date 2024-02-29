void eventFunc(SDL_Event e) {}

#define CLK 0
int counter = CLK / REFRESHRATE;

void loopFunc(Window *win) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  //
  if (counter >= CLK / REFRESHRATE) {
    animLanscape(landscape);
    counter = 0;
  }

  counter++;
  // draw the landscape
  drawLandscape(renderer, landscape);
  //
  SDL_RenderPresent(renderer);
}
