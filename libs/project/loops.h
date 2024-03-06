void eventFunc(SDL_Event e) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_RIGHT:
      movePlayer(player, 1);
      break;
    case SDLK_LEFT:
      movePlayer(player, -1);
      break;

    default:
      break;
    }
  }
}

#define CLK 10
int counter = CLK / REFRESHRATE;
bool trackPlay = false;

void loopFunc(Window *win) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  //
  if (!trackPlay) {
    playBg(beat);
    trackPlay = true;
  }
  // obs manage

  /*
  rn u have a refresh each CLK
  */

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
