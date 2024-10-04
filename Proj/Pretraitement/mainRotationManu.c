#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "Rotation.c"


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Rotation Manuelle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* surface = IMG_Load("test.jpg");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    int Running = 1;
    double angle = 0.0;

    while (Running) {
        RotationManuelle(&Running, &angle);

        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, texture, NULL, NULL, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
	SDL_Delay(16);
    }

    SDL_Surface* rotatedSurface = SDL_CreateRGBSurfaceWithFormat(0, 800, 600, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_Texture* targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 800, 600);
    SDL_SetRenderTarget(renderer, targetTexture);
    SDL_RenderCopyEx(renderer, texture, NULL, NULL, angle, NULL, SDL_FLIP_NONE);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA32, rotatedSurface->pixels, rotatedSurface->pitch);
    IMG_SavePNG(rotatedSurface, "test.jpg");
    SDL_FreeSurface(rotatedSurface);
    SDL_DestroyTexture(targetTexture);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

