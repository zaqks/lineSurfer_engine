#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#define SPEED 20

typedef struct {
  // int a;

  SDL_Texture *texture;

  SDL_Rect *rect1;
  SDL_Rect *rect2;
  SDL_Rect *rect3;
  SDL_Rect *rect4;

  int ax;
  int ay;

} Terrain;

Terrain *initTerrain(SDL_Renderer *renderer) {
  Terrain *widget = (Terrain *)malloc(sizeof(Terrain));

  // vals
  widget->ax = (RENDER_WIDTH / (float)(RENDER_HEIGHT)) * (float)SPEED;
  widget->ay = SPEED;

  // texture
  char *paths[5] = {
      "assets/images/maps/map3/5.jpg", // texture
      "assets/images/maps/map3/4.jpg", // lines bg
      "assets/images/maps/map3/3.png", // clr bg
      "assets/images/maps/map3/2.png", // clr sections
      "assets/images/maps/map3/1.jpg"  // real bg
  };

  SDL_Surface *img = IMG_Load(paths[0]);

  widget->texture = (SDL_Texture *)SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  /// rects
  widget->rect1 = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  widget->rect2 = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  widget->rect3 = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  widget->rect4 = (SDL_Rect *)malloc(sizeof(SDL_Rect));

  SDL_Rect *rects[4] = {
      widget->rect1,
      widget->rect2,
      widget->rect3,
      widget->rect4,
  };

  for (int i = 0; i < 4; i++) {
    rects[i]->w = RENDER_WIDTH;
    rects[i]->h = RENDER_HEIGHT;

    rects[i]->x = (i % 2) ? (int)(RENDER_WIDTH) : 0;
    rects[i]->y = (i < 2) ? 0 : (int)(RENDER_HEIGHT);

    // printf("%d %d\n", rects[i]->w, rects[i]->h);
  };

  return widget;
}

void animTerrain(Terrain *widget) {

  SDL_Rect *rects[4] = {
      widget->rect1,
      widget->rect2,
      widget->rect3,
      widget->rect4,
  };

  for (int i = 0; i < 4; i++) {
    if (widget->rect1->x <= -RENDER_WIDTH) {
      for (i = 0; i < 4; i++) {
        rects[i]->w = RENDER_WIDTH;
        rects[i]->h = RENDER_HEIGHT;

        rects[i]->x = (i % 2) ? (int)(RENDER_WIDTH) : 0;
        rects[i]->y = (i < 2) ? 0 : (int)(RENDER_HEIGHT);
      }

      break;
    } else {

      rects[i]->y -= widget->ay;
      rects[i]->x -= widget->ax;

      // rects[i]->y -= (float)(tan(M_PI * widget->a / 180)) * SPEED;
    }
  }
}

void drawTerrain(SDL_Renderer *renderer, Terrain *widget) {
  SDL_Rect *rects[4] = {
      widget->rect1,
      widget->rect2,
      widget->rect3,
      widget->rect4,
  };

  for (int i = 0; i < 4; i++) {
    SDL_RenderCopy(renderer, widget->texture, NULL, rects[i]);
  }
}