#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

typedef struct {
  SDL_Texture *texture;
  SDL_Rect *rect;
} Obstacle;

Obstacle *initObstacle() {
  Obstacle *widget = (Obstacle *)malloc(sizeof(Obstacle));

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

bool moveObstacle(Terrain *terrain, Obstacle *obs) {

  obs->rect->x -= terrain->ax;
  obs->rect->y -= terrain->ay;

  if (obs->rect->x + obs->rect->w < 0 || obs->rect->y + obs->rect->h < 0) {
    return false;
  }
  return true;
}

void drawObstacle(SDL_Renderer *renderer, Obstacle *widget) {
  SDL_RenderCopy(renderer, widget->texture, NULL, widget->rect);
}

void generateObstacle(Array *obstacles) {
  pushArrayNode(obstacles, initObstacle());
}

void moveObstacles(Terrain *terrain, Array *obstacles) {
  ArrayNode current;
  for (int i = 0; i < obstacles->length; i++) {
    current = obstacles->arr[i];
  }
}
