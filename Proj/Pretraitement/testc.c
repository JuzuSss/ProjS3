#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

// Déclaration de la fonction readImage
unsigned char* readImage(const char* filename, int* width, int* height, int* channels);

void convert_to_black_and_white(JSAMPROW buffer, int width, int height, int channels) {
    for (int i = 0; i < width * height * channels; i += channels) {
        int gray = (int)(0.299 * buffer[i] + 0.587 * buffer[i + 1] + 0.114 * buffer[i + 2]);
        buffer[i] = buffer[i + 1] = buffer[i + 2] = (gray > 128) ? 255 : 0;
    }
}

unsigned char* readImage(const char* filename, int* width, int* height, int* channels) {
    unsigned char* data = stbi_load(filename, width, height, channels, 0);
    if (data == NULL) {
        printf("Erreur lors de la lecture de l'image: %s\n", stbi_failure_reason());
    }
    return data;
}



int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_filename>\n", *argv);
        return 1;
    }

    const char *inputFilename = argv[1];
    int width, height, channels;
    unsigned char *imageData = readImage(inputFilename, &width, &height, &channels);
    if (imageData == NULL) {
        return 1;
    }

    printf("Image dimensions: %d x %d\n", width, height);
    printf("Number of channels: %d\n", channels);

    convert_to_black_and_white(imageData, width, height, channels);

    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        stbi_image_free(imageData);
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Image en noir et blanc", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_Quit();
        stbi_image_free(imageData);
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        stbi_image_free(imageData);
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);
    if (!texture) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        stbi_image_free(imageData);
        return 1;
    }

    SDL_UpdateTexture(texture, NULL, imageData, width * channels);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    stbi_image_free(imageData);

    printf("L'image a été convertie en niveaux de gris et affichée.\n");

    return 0;
}
