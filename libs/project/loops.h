/*
  aya doka srx HDRA ta3 rjal

  rn u have a refresh each REFRESHRATE

  for the anims:
  each t (ms)
  dok ya l boubou w3lah dir CLK<REFRSHRATE
  jml ou ma y dirhach ya tchini
  */

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

#define CLK 66 //>REFRESHRATE

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
