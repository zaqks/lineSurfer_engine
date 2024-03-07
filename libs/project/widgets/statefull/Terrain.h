#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#define SPEED 2 // 20

typedef struct {
  int speed;
  int ax;
  int ay;

  SDL_Texture *texture;

  SDL_Rect *rect1;
  SDL_Rect *rect2;
  SDL_Rect *rect3;
  SDL_Rect *rect4;

} Terrain;

Terrain *initTerrain(SDL_Renderer *renderer, int imgIndx) {
  Terrain *widget = (Terrain *)malloc(sizeof(Terrain));

  // vals
  widget->speed = SPEED;

  widget->ax = (RENDER_WIDTH / (float)(RENDER_HEIGHT)) * (float)widget->speed;
  widget->ay = widget->speed;

  // texture
  char *paths[7] = {
      "assets/images/maps/map3/particles.png",
      "assets/images/maps/map3/6.jpg", // texture dark
      "assets/images/maps/map3/5.jpg", // texture
      "assets/images/maps/map3/4.jpg", // lines bg
      "assets/images/maps/map3/3.png", // clr bg
      "assets/images/maps/map3/2.png", // clr sections
      "assets/images/maps/map3/1.jpg"  // real bg
  };

  SDL_Surface *img = IMG_Load(paths[imgIndx]);

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

      rects[i]->y -= widget->ay * widget->speed;
      rects[i]->x -= widget->ax * widget->speed;

      // rects[i]->y -= (float)(tan(M_PI * widget->a / 180)) * widget->speed;
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
  /*
  // draw trajectories
  if (WIRES) {

    float x1, y1, x2, y2, ax, ay;
    ax = RENDER_WIDTH / (float)widget->tracks;
    ay = RENDER_HEIGHT / (float)widget->tracks;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // v x1++ y2--
    x1 = 0;
    y1 = 0;
    x2 = RENDER_WIDTH;
    y2 = RENDER_HEIGHT;

    for (int i = 0; i < widget->tracks; i++) {
      drawLine(renderer, x1, y1, x2, y2);
      x1 += ax;
      y2 -= ay;
    }

    // h x2-- y1++
    x1 = 0;
    y1 = 0;
    x2 = RENDER_WIDTH;
    y2 = RENDER_HEIGHT;

    for (int i = 0; i < widget->tracks; i++) {
      drawLine(renderer, x1, y1, x2, y2);
      x2 -= ax;
      y1 += ay;
    }
  }*/
}