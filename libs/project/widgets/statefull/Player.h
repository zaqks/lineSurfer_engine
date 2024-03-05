#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

typedef struct {
  SDL_Texture *texture;
  SDL_Rect *rect;

  int ax;
  int ay;

} Player;

Player *initPlayer(SDL_Renderer *renderer) {
  Player *rslt = (Player *)malloc(sizeof(Player));

  // vals
  rslt->ax = 1;
  rslt->ay = 1;

  // texture
  SDL_Surface *img = IMG_Load("assets/images/players/player1/1.png");
  rslt->texture = (SDL_Texture *)SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  // rect
  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

  rect->w = RENDER_HEIGHT / 10;
  rect->h = RENDER_HEIGHT / 10;

  rect->x = (RENDER_WIDTH - rect->w) / 2;
  rect->y = (RENDER_HEIGHT - rect->h) / 2;

  rslt->rect = rect;

  return rslt;
}

void drawPlayer(SDL_Renderer *renderer, Player *widget) {
  SDL_RenderCopy(renderer, widget->texture, NULL, widget->rect);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect(renderer, widget->rect);
}