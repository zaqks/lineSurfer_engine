#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#define SCALE 1

void eventFunc(SDL_Event e) {}

void loopFunc(Window *win) {
  //
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  //

  // get the image and convert it to a texture
  SDL_Surface *img = IMG_Load("assets/images/maps/map1/bg.jpg");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  // dst rect
  SDL_Rect dst;
  dst.x = 0;
  dst.y = 0;
  dst.w = win->width * SCALE;
  dst.h = win->height * SCALE;

  // scale

  // texture render
  SDL_RenderCopy(renderer, texture, NULL, &dst);

  //
  SDL_RenderPresent(renderer);
}
