#include "libs/project/imports.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FONT_SIZE 24
#define MAX_LINE_WIDTH 300

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow("Box Message", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    gFont = TTF_OpenFont("/usr/share/fonts/TTF/Hack-Regular.ttf", FONT_SIZE);
    if (gFont == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

void close() {
    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    TTF_Quit();
    SDL_Quit();
}

void drawMessageBox(const char* message, float x, float y) {
    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, message, textColor, MAX_LINE_WIDTH);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (textTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
            SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect); // Render text texture
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

int main() {
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    // Main loop
    while (1) {
        // Event handling
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                close();
                return 0;
            }
        }

        // Rendering
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // White color
        SDL_RenderClear(gRenderer);
        drawMessageBox("This is a long text that should wrap around to fit within the specified maximum line width.", 100, 100);
        SDL_RenderPresent(gRenderer);

        // Delay to avoid excessive CPU usage
        SDL_Delay(100); // Adjust as needed
    }

    return 0;
}
