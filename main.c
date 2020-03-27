#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <SDL/SDL.h>
#include <emscripten.h>
#include <pthread.h>

SDL_Surface *screen;

typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} _RGB;

_RGB dark = {53, 63, 76};
_RGB lines = {230, 230, 250};
_RGB Light = {220, 220, 240};

// 813 * 429
#define screenX 660
#define screenY 340
#define PixelSize 4
#define Offset 10

uint8_t screenEmu[128 * 64];
Uint32 screenBuff[screenX * screenY];

int touched = 0;

void PutFakePixel(_RGB c, int x, int y) {
    int lx, ly;
    long xp = (x * (PixelSize + 1)) + Offset;
    long yp = (y * (PixelSize + 1)) + Offset;

    for (lx = xp; lx < xp + PixelSize; lx++) {
        for (ly = yp; ly < yp + PixelSize; ly++) {
            screenBuff[(ly * screenX) + lx] = SDL_MapRGBA(screen->format, c.R, c.G, c.B, 255);
        }
    }
}

void drawScreen(void) {

    int x, y;
    for (x = 0; x < screenX * screenY; x++) {
        screenBuff[x] = SDL_MapRGBA(screen->format, lines.R, lines.G, lines.B, 255);
    }
    for (x = 0; x < 128; x++) {
        for (y = 0; y < 64; y++) {
            if (screenEmu[y * 128 + x]) {
                PutFakePixel(dark, x, y);
            } else {
                PutFakePixel(Light, x, y);
            }
        }
    }
    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
    memcpy(screen->pixels, screenBuff, sizeof (screenBuff));
    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
    SDL_Flip(screen);
}

int mark = 0;

void doSomething(void) {
    memset(screenEmu, 0, 8192);
    touched = EM_ASM_INT(return getPressedButton());
    if (touched) {
        screenEmu[5 * 128 + 64 + touched] = 1;
    }
    drawScreen();
}

int main(int argc, char** argv) {
    printf("hello, world!\n");

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(screenX, screenY, 32, SDL_SWSURFACE);
    memset(screenEmu, 0, 8192);
    emscripten_set_main_loop(doSomething, 30, 1);
    SDL_Quit();

    return 0;
}


