

typedef struct {
  SDL_Texture *texture;
  SDL_Rect *rect;
} Vignette;

Vignette *initVignette() {
  Vignette *rslt = (Vignette *)malloc(sizeof(Vignette));

  // rect
  rslt->rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  rslt->rect->x = 0;
  rslt->rect->y = 0;
  rslt->rect->w = RENDER_WIDTH;
  rslt->rect->h = RENDER_HEIGHT;

  // texture
  SDL_Surface *img = IMG_Load("assets/images/maps/map3/vignette2.png");
  rslt->texture = (SDL_Texture *)SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  return rslt;
}

void drawVignette(SDL_Renderer *renderer, Vignette *widget) {
  SDL_RenderCopy(renderer, widget->texture, NULL, widget->rect);
}