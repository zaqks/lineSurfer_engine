#include "libs/project/imports.h"
#define FONT_SIZE 24 // Adjust the font size as needed
#define MESSAGE_BOX_PADDING_X 10 // Padding for message box (left and right)
#define MESSAGE_BOX_PADDING_Y 10  // Padding for message box (top and bottom)
#define MESSAGE_BOX_COLOR {255, 0, 0, 255} // Red color for the message box
// Function to draw a rounded rectangle
void drawFilledCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for(int i = 0; i <= radius * 2; i++) {
        for(int j = 0; j <= radius * 2; j++) {
            int dx = radius - i; // horizontal offset
            int dy = radius - j; // vertical offset
            if(sqrt(dx * dx + dy * dy) <= radius) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void drawRoundedRect(SDL_Renderer *renderer, SDL_Rect rect, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int w = rect.w;
    int h = rect.h;

    // Draw filled rounded rectangle
    SDL_Rect innerRect = { rect.x + radius, rect.y, rect.w - 2 * radius, rect.h };
    SDL_RenderFillRect(renderer, &innerRect);
    SDL_Rect topRect = { rect.x + radius, rect.y, rect.w - 2 * radius, radius };
    SDL_RenderFillRect(renderer, &topRect);
    SDL_Rect bottomRect = { rect.x + radius, rect.y + rect.h - radius, rect.w - 2 * radius, radius };
    SDL_RenderFillRect(renderer, &bottomRect);
    SDL_Rect leftRect = { rect.x, rect.y + radius, radius, rect.h - 2 * radius };
    SDL_RenderFillRect(renderer, &leftRect);
    SDL_Rect rightRect = { rect.x + rect.w - radius, rect.y + radius, radius, rect.h - 2 * radius };
    SDL_RenderFillRect(renderer, &rightRect);

    // Draw filled circles at corners
    drawFilledCircle(renderer, rect.x + radius, rect.y + radius, radius, color);
    drawFilledCircle(renderer, rect.x + w - radius, rect.y + radius, radius, color);
    drawFilledCircle(renderer, rect.x + radius, rect.y + h - radius, radius, color);
    drawFilledCircle(renderer, rect.x + w - radius, rect.y + h - radius, radius, color);
}



void drawMessageBox(SDL_Renderer *renderer, const char* fontPath, int fontSize, const char* message, float x, float y, int maxWidth) {
    if (TTF_Init() == -1) { // Initialize SDL_ttf
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        TTF_Quit();
        return;
    }

    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Color messageBoxColor = MESSAGE_BOX_COLOR;

    int lineHeight = TTF_FontLineSkip(font);

    const char* start = message;
    const char* end = message;

    // Calculate text dimensions
    int textWidth = 0, textHeight = 0;
    while (*end) {
        // Find the end of the line
        while (*end && *end != '\n') {
            ++end;
        }

        // Render the line
        SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, start, textColor, maxWidth);
        if (textSurface == NULL) {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            TTF_CloseFont(font);
            TTF_Quit();
            return;
        }

        // Update text dimensions
        if (textSurface->w > textWidth) {
            textWidth = textSurface->w;
        }
        textHeight += textSurface->h;

        SDL_FreeSurface(textSurface);

        // Move to the next line
        start = end;
        while (*start == '\n' || *start == ' ') {
            ++start;
        }
        end = start;
    }

    // Draw message box with rounded corners
    SDL_Rect messageRect = { x - MESSAGE_BOX_PADDING_X/3, y - MESSAGE_BOX_PADDING_Y/2, textWidth + 2* MESSAGE_BOX_PADDING_X, textHeight + 3 * MESSAGE_BOX_PADDING_Y };
    drawRoundedRect(renderer, messageRect, 24, messageBoxColor);

    // Render text
    start = message;
    end = message;
    int textY = y;
    while (*end) {
        // Find the end of the line
        while (*end && *end != '\n') {
            ++end;
        }

        // Render the line
        SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, start, textColor, maxWidth);
        if (textSurface == NULL) {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            TTF_CloseFont(font);
            TTF_Quit();
            return;
        }

        // Render text surface to texture
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == NULL) {
            printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
            SDL_FreeSurface(textSurface);
            TTF_CloseFont(font);
            TTF_Quit();
            return;
        }

        // Render text texture
        SDL_Rect textRect = { x + MESSAGE_BOX_PADDING_X, textY + MESSAGE_BOX_PADDING_Y, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Clean up
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);

        // Move to the next line
        textY += lineHeight;

        start = end;
        while (*start == '\n' || *start == ' ') {
            ++start;
        }
        end = start;
    }

    TTF_CloseFont(font); // Close the font
    TTF_Quit(); // Quit SDL_ttf
}
void LoopFunc(Window *win) {
    // Your rendering code here
    SDL_SetRenderDrawColor(win->renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(win->renderer);
    // Render message box
    drawMessageBox(win->renderer, "/usr/share/fonts/TTF/Hack-Regular.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box This is a message box", 50, 100, 100);
    drawMessageBox(win->renderer, "/usr/share/fonts/TTF/Hack-Bold.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box This is a message box", 600, 150, 200);
    drawMessageBox(win->renderer, "/usr/share/fonts/TTF/Hack-BoldItalic.ttf", FONT_SIZE, "This is a message box This is a message box This is a message box This is a message box", 1000, 150, 300);
    // Present renderer
    SDL_RenderPresent(win->renderer);
}

int main() {
    Window *win = initWin("DOOM");

    mainLoop(win, NULL, LoopFunc); //drt null for eventFunc

    return 0;
}
