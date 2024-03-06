typedef struct {
  float clk;
  int counter;
} Clock;

Clock *initClock(float parentCLK, float childCLK) {
  // koulch bl ms
  Clock *rslt = (Clock *)malloc(sizeof(Clock));

  rslt->clk = childCLK / (float)parentCLK;
  rslt->counter = rslt->clk;

  return rslt;
}

bool clockTick(Clock *clk) {
  if (clk->counter >= clk->clk) {
    clk->counter = 1;
    return true;
  }

  clk->counter++;
  return false;
}
