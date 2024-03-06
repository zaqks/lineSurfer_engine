#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include "chemso.h"
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
  //chemso
  //render tiles box
   drawtilesBox(win->renderer, "/usr/share/fonts/TTF/Hack-Regular.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box", 50, 330, 40,700);
    drawtilesBox(win->renderer, "/usr/share/fonts/TTF/Hack-Bold.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box", 50, 400, 40,700);
    drawtilesBox(win->renderer, "/usr/share/fonts/TTF/Hack-BoldItalic.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box", 50, 470,40, 700);
    // Render message box
    drawMessageBox(win->renderer, "/usr/share/fonts/TTF/Hack-Regular.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box", 20, 20, 400);
    drawMessageBox(win->renderer, "/usr/share/fonts/TTF/Hack-Bold.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box", 20, 90, 400);
    drawMessageBox(win->renderer, "/usr/share/fonts/TTF/Hack-BoldItalic.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box", 20, 160, 400);
  //
  SDL_RenderPresent(renderer);
}
