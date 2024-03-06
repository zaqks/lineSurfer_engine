#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

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
  if(!trackPlay){
    playBg(beat);
    trackPlay = true;
  }
  //obs manage


  //
  if (counter >= CLK / REFRESHRATE) {
    animTerrain(terrain);
    moveObstacle(terrain, obs);
    counter = 0;
  }

  counter++;
  // drawing
  drawTerrain(renderer, terrain);
  drawPlayer(renderer, player);
  drawObstacle(renderer, obs);
  //
  SDL_RenderPresent(renderer);
}
