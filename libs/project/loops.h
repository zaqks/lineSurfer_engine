/*
  aya doka srx HDRA ta3 rjal

  rn u have a refresh each REFRESHRATE

  for the anims:
  each t (ms)
  dok ya l boubou w3lah dir CLK<REFRSHRATE
  jml ou ma y dirhach ya tchini


  for the obs check
  bpm : beats/min
  BPS = BPM/60 -> beats/second
  tsma BPS checks per second
  tsma 1 beat each 1/BPS
  dont 1 check each 1/BPS seconds
  that leads us to run 1 check each 1000/BPS ms
  li hya
  1000 * 1/(BPM/60)
  ou li hya enfin
  1000 * 60 /BPM <=> 60K/BPM



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

bool trackPlay = false;

int counter = REFRESHRATE / REFRESHRATE;

void loopFunc(Window *win) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  //
  if (trackPlay) {
    if (clockTick(clk2)) {
      if (getMoment(beat)) {
        generateObstacle(obstacles);
        printf("obs\n");
      }
    }
  }

  if (!trackPlay) {
    playBg(beat);
    trackPlay = true;
  }

  //

  if (clockTick(clk1)) {
    animTerrain(terrain);
    moveObstacles(terrain, obstacles);
  }

  // drawing
  drawTerrain(renderer, terrain);
  drawPlayer(renderer, player);

  //
  SDL_RenderPresent(renderer);
}
