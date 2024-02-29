#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
typedef struct {
  SDL_Texture *texture;
  SDL_Rect *rect1;
  SDL_Rect *rect2;

  int offset;
  float speed;
} Landscape;

Landscape *initLandscape(SDL_Renderer *renderer) {
  Landscape *rslt = (Landscape *)malloc(sizeof(Landscape));

  // texture
  SDL_Surface *img = IMG_Load("assets/images/maps/map2/1.jpg");
  rslt->texture = (SDL_Texture *)SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  // rects

  SDL_Rect *rect1 = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  SDL_Rect *rect2 = (SDL_Rect *)malloc(sizeof(SDL_Rect));

  SDL_Rect *rects[2] = {rect1, rect2};

  for (int i = 0; i < 2; i++) {

    rects[i]->y = 0;
    rects[i]->w = SCREEN_WIDTH;
    rects[i]->h = SCREEN_HEIGHT;
  }

  rect1->x = 0;
  rect2->x = SCREEN_WIDTH;

  rslt->rect1 = rect1;
  rslt->rect2 = rect2;

  // offset + fact
  rslt->offset = 0;
  rslt->speed = 5;

  return rslt;
}

void drawLandscape(SDL_Renderer *renderer, Landscape *widget) {
  SDL_RenderCopy(renderer, widget->texture, NULL, widget->rect1);
  SDL_RenderCopy(renderer, widget->texture, NULL, widget->rect2);
}

void animLanscape(Landscape *widget) {
  float speed = widget->speed;

  widget->offset += speed;
  int offset = widget->offset;
  if (offset >= SCREEN_WIDTH) {
    widget->offset = 0;
    offset = 0;
  }

  widget->rect1->x = (offset) ? widget->rect1->x - speed : 0;
  widget->rect2->x = (offset) ? widget->rect2->x - speed : SCREEN_WIDTH;
}