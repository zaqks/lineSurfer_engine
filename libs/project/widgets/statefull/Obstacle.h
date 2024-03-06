#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

typedef struct {
  bool anim;

  SDL_Texture *texture;
  SDL_Rect *rect;
} Obstacle;

Obstacle *initObstacle() {
  Obstacle *widget = (Obstacle *)malloc(sizeof(Obstacle));
  widget->anim = true;

  // texture
  SDL_Surface *img = IMG_Load("assets/images/maps/map3/entities/trees/1.png");
  widget->texture = (SDL_Texture *)SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  // lzm t3rf la v/h oumba3 u chose a random val ou cbn
  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(Obstacle));
  rect->x = 300;
  rect->y = 300;
  rect->w = RENDER_HEIGHT / 5;
  rect->h = RENDER_HEIGHT / 5;

  widget->rect = rect;

  return widget;
}

void destroyObstacle(Obstacle *widget) {
  SDL_DestroyTexture(widget->texture);
  free(widget->rect);
  free(widget);
}

void moveObstacle(Terrain *terrain, Obstacle *obs) {
  if (obs->anim) {
    obs->rect->x -= terrain->ax;
    obs->rect->y -= terrain->ay;

    if (obs->rect->x + obs->rect->w < 0 || obs->rect->y + obs->rect->h < 0) {
      obs->anim = false;
    }
  }
}

void drawObstacle(SDL_Renderer *renderer, Obstacle *widget) {
  SDL_RenderCopy(renderer, widget->texture, NULL, widget->rect);
}
