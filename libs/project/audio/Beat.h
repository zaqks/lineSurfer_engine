typedef struct {
  Mix_Chunk *bg;
  int bpm;
  char *beats;

  int tick;//keeps track of the current bit
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

  // load the beats
  char *btsPath = "data/levels/level1/sounds/track/beats2.txt";
  FILE *btsFile;

  size_t len = 0;
  char *line = NULL;
  __ssize_t read;

  btsFile = fopen(btsPath, "r");
  for (int i = 0; (read = getline(&line, &len, btsFile)) != -1; i++) {
    if (!i) {
      beat->bpm = atoi(line);
    } else {
      beat->beats = line;
      break;
    }
  }
  fclose(btsFile);

  return beat;
}

int getMoment(Beat *beat) {

}

void playBg(Beat *beat) {
  Mix_PlayChannel(-1, beat->bg, 0);
  // Mix_PlayMusic(sounds[soundId], 0);
}