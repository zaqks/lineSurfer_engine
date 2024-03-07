typedef struct {
  Mix_Chunk *bg;
  int bpm;
  int measures;
  char *beats;

  int len;  // bits num
  int indx; // keeps track of the current bit
} Beat;

void initSound() {
  SDL_Init(SDL_INIT_AUDIO);
  Mix_Init(MIX_INIT_MP3);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // open the device
}

Beat *initBeat() {
  Beat *beat = (Beat *)malloc(sizeof(Beat));

  // load the mp3
  char *bgPath =
      "data/levels/level1/sounds/track/TwoStepsFromHellArchangel.mp3";
  beat->bg = Mix_LoadWAV(bgPath);

  // load the beats file
  char *btsPath = "data/levels/level1/sounds/track/beats3.txt";
  FILE *btsFile;

  size_t len = 0;
  char *line = NULL;
  __ssize_t read;

  btsFile = fopen(btsPath, "r");
  for (int i = 0; (read = getline(&line, &len, btsFile)) != -1; i++) {

    if (!i || i == 1) {
      if (!i) {
        beat->measures = atoi(line);
      } else {
        beat->bpm = atoi(line);
      }

    } else {
      beat->beats = line;
      break;
    }
  }
  fclose(btsFile);
  //

  beat->indx = 0;
  beat->len = strlen(beat->beats);

  return beat;
}
/*
int getMoment(Beat *beat) {
  if (beat->indx < beat->len) {

    char *current;
    current = beat->beats + beat->indx;

    if (*current != '|' &
        beat->indx != beat->len - 1) // check if !(ure at the end & char is '|')
    {

      if (*current == '|') // skip the division
      {
        beat->indx += 1;
        current += 1;
      }
      beat->indx += 1;

      if (*current != '0') {
        return 1;
      }
    }
  }

  return 0;
}
*/

int getMoment(Beat *beat) {
  if (beat->indx < beat->len) {

    char *current;
    current = beat->beats + beat->indx;
    beat->indx ++;

    return *current != '0';
  }
  return 0;
}

void playBg(Beat *beat) {
  Mix_PlayChannel(-1, beat->bg, 0);
}