#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

// Déclaration de la fonction readImage
unsigned char* readImage(const char* filename, int* width, int* height, int* channels);

unsigned char* readImage(const char* filename, int* width, int* height, int* channels) {
    unsigned char* data = stbi_load(filename, width, height, channels, 0);
    if (data == NULL) {
        printf("Erreur lors de la lecture de l'image: %s\n", stbi_failure_reason());
    }
    return data;
}

void median_filter(unsigned char *input, unsigned char *output, int width, int height, int channels) {
    int window_size = 3;
    int half_window = window_size / 2;
    int window_area = window_size * window_size;
    unsigned char window[window_area * channels];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int count = 0;
            for (int wy = -half_window; wy <= half_window; wy++) {
                for (int wx = -half_window; wx <= half_window; wx++) {
                    int iy = y + wy;
                    int ix = x + wx;
                    if (iy >= 0 && iy < height && ix >= 0 && ix < width) {
                        for (int c = 0; c < channels; c++) {
                            window[count * channels + c] = input[(iy * width + ix) * channels + c];
                        }
                        count++;
                    }
                }
            }

            for (int c = 0; c < channels; c++) {
                for (int i = 0; i < count - 1; i++) {
                    for (int j = i + 1; j < count; j++) {
                        if (window[i * channels + c] > window[j * channels + c]) {
                            unsigned char temp = window[i * channels + c];
                            window[i * channels + c] = window[j * channels + c];
                            window[j * channels + c] = temp;
                        }
                    }
                }
                output[(y * width + x) * channels + c] = window[count / 2 * channels + c];
            }
        }
    }
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

    unsigned char *filteredData = (unsigned char *)malloc(width * height * channels);
    median_filter(imageData, filteredData, width, height, channels);

    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        stbi_image_free(imageData);
        free(filteredData);
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Image filtrée", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_Quit();
        stbi_image_free(imageData);
        free(filteredData);
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        stbi_image_free(imageData);
        free(filteredData);
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);
    if (!texture) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        stbi_image_free(imageData);
        free(filteredData);
        return 1;
    }

    SDL_UpdateTexture(texture, NULL, filteredData, width * channels);

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
    free(filteredData);

    printf("L'image a été filtrée et affichée.\n");

    return 0;
}

