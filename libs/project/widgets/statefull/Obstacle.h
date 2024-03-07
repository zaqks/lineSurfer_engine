typedef struct {
  SDL_Texture *texture;
  SDL_Rect *rect;
} Obstacle;

int randomNum(int min, int max) { return (rand() % (max - min)) + min; }

Obstacle *initObstacle() {
  Obstacle *widget = (Obstacle *)malloc(sizeof(Obstacle));

  // texture
  SDL_Surface *img = IMG_Load("assets/images/maps/map3/entities/trees/1.png");
  widget->texture = (SDL_Texture *)SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(Obstacle));
  rect->w = RENDER_HEIGHT / 5;
  rect->h = RENDER_HEIGHT / 5;

  // lzm t3rf la v/h oumba3 u chose a random val ou cbn
  if (randomNum(0, 10) > 5) // get if v
  {
    rect->x = RENDER_WIDTH;
    rect->y = randomNum(rect->h, RENDER_HEIGHT);
    // rect->y = randomNum(1, TRACKS) * (RENDER_HEIGHT / TRACKS);
  } else {
    rect->y = RENDER_HEIGHT;
    rect->w = randomNum(rect->w, RENDER_WIDTH);
    // rect->x = randomNum(1, TRACKS) * (RENDER_WIDTH / TRACKS);
  }

  widget->rect = rect;

  return widget;
}

void destroyObstacle(Obstacle *widget) {
  SDL_DestroyTexture(widget->texture);
  free(widget->rect);
  free(widget);
}

bool moveObstacle(Terrain *terrain, Obstacle *obs) {

  obs->rect->x -= terrain->ax * terrain->speed;
  obs->rect->y -= terrain->ay * terrain->speed;

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

// obstacles
void moveObstacles(Terrain *terrain, Array *obstacles) {
  ArrayNode current;
  Obstacle *obs;

  for (int i = 0; i < obstacles->length; i++) {
    current = obstacles->arr[i];
    obs = current.val;

    if (!moveObstacle(terrain, obs)) {
      destroyObstacle(obs);
      delArrayNode(obstacles, i);
      i--;
    }
  }
}

void drawObstacles(SDL_Renderer *renderer, Array *obstacles) {
  ArrayNode current;
  Obstacle *obs;

  for (int i = 0; i < obstacles->length; i++) {
    current = obstacles->arr[i];
    obs = current.val;
    drawObstacle(renderer, obs);
  }
}