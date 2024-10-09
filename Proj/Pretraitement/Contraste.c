#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>



unsigned char* readImage(const char* filename, int* width, int* height, int* channels) {
    *width = 640;
    *height = 480;
    *channels = 3;
    unsigned char* data = (unsigned char*)malloc((*width) * (*height) * (*channels));
    return data;
}



void writeImage(const char* filename, unsigned char* data, int width, int height, int channels) {

}

void convertToGrayscale(unsigned char *input, unsigned char *output, int width, int height, int channels) {
    if (channels < 3) {
        printf("L'image doit etre RGB.\n");
        return;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = (i * width + j) * channels;
            unsigned char r = input[index];
            unsigned char g = input[index + 1];
            unsigned char b = input[index + 2];
            unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
            output[index] = gray;
            output[index + 1] = gray;
            output[index + 2] = gray;
            if (channels == 4) {
                output[index + 3] = input[index + 3];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_filename>\n", argv[0]);
        return 1;
    }

    const char *inputFilename = argv[0];
    const char *outputFilename = "output.jpg"; // Chemin absolu

    int width, height, channels;
    unsigned char *input = readImage(inputFilename, &width, &height, &channels);
    if (input == NULL) {
        printf("Erreur lors de la lecture de l'image.\n");
        return 1;
    }

    unsigned char *output = (unsigned char *)malloc(width * height * channels * sizeof(unsigned char));

    // Convertir l'image en niveaux de gris
    convertToGrayscale(input, output, width, height, channels);

    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        free(input);
        free(output);
        return 1;
    }

    // Créer une fenêtre SDL
    SDL_Window *window = SDL_CreateWindow("Image en niveaux de gris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_Quit();
        free(input);
        free(output);
        return 1;
    }

    // Créer un renderer SDL
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        free(input);
        free(output);
        return 1;
    }

    // Créer une texture SDL
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);
    if (!texture) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        free(input);
        free(output);
        return 1;
    }

    // Mettre à jour la texture avec les données de l'image
    SDL_UpdateTexture(texture, NULL, output, width * channels);

    // Afficher l'image
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Attendre que l'utilisateur ferme la fenêtre
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Sauvegarder l'image de sortie
    writeImage(outputFilename, output, width, height, channels);

    // Libérer les ressources SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Libérer la mémoire allouée
    free(input);
    free(output);

    printf("L'image a été convertie en niveaux de gris et sauvegardée sous le nom %s\n", outputFilename);

    return 0;
}
