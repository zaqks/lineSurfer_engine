typedef struct {
  SDL_Texture *texture;
  SDL_Rect *rect;
} Landscape;

Landscape *initLandscape(SDL_Renderer *renderer) {
  Landscape *rslt = (Landscape *)malloc(sizeof(Landscape));

  // texture
  SDL_Surface *img = IMG_Load("assets/images/maps/map1/bg.jpg");
  rslt->texture = (SDL_Texture *)SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  // rect

  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
  rect->x = 0;
  rect->y = 0;
  rect->w = SCREEN_WIDTH;
  rect->h = SCREEN_HEIGHT;

  rslt->rect = rect;

  return rslt;
}

void drawLandscape(SDL_Renderer *renderer, Landscape *widget) {
  SDL_RenderCopy(renderer, widget->texture, NULL, widget->rect);
}

void animLanscape() {}