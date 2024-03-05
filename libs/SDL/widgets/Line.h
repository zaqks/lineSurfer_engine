float getDistance(float x1, float y1, float x2, float y2) {
  return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
}

void drawLine(SDL_Renderer *renderer, float x1, float y1, float x2, float y2) {
  float a = (y2 - y1) / (float)(x2 - x1);

  if (x1 > x2) {
    float x3 = x2;
    float y3 = y2;

    x2 = x1;
    y2 = y1;
    x1 = x3;
    y1 = y3;
  }
  //printf("%f %f %f %f\n", x1, y1, x2, y2, a);

  float length = getDistance(x1, y1, x2, y2);
  while (length > 0) {
    SDL_RenderDrawPoint(renderer, x1, y1);
    x1 += 1;
    y1 += a;
    // length -= getDistance(0, 0, a, a);
    length -= 1.0;
  }
}