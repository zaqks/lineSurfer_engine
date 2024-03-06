typedef struct {
  float clk;
  int counter;
} Clock;

Clock *initClock(float refreshRate, float clk) {
  // koulch bl ms
  Clock *rslt = (Clock *)malloc(sizeof(Clock));
  
  rslt->clk = clk / refreshRate;
  rslt->counter = rslt->clk;


  return rslt;
}

bool clockTick(Clock *clk) {
  if (clk->counter >= clk->clk) {
    clk->counter = 0;
    return true;
  } else {
    clk->counter++;
    return false;
  }
}
