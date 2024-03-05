void eventFunc(SDL_Event e) {}

#define CLK 10
int counter = CLK / REFRESHRATE;

void loopFunc(Window *win) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  //
  if (counter >= CLK / REFRESHRATE) {
    animTerrain(terrain);
    counter = 0;
  }

  counter++;
  // drawing
  drawTerrain(renderer, terrain);
  drawPlayer(renderer, player);
  //
  SDL_RenderPresent(renderer);
}
