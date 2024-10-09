#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../stb-master/stb-master/stb_image.h"
#include "../../stb-master/stb-master/stb_image_write.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>



void medianFilter(unsigned char *input, unsigned char *output, int width, int height, int channels, int windowSize) {
    int halfWindowSize = windowSize / 2;
    int windowArea = windowSize * windowSize;
    int *window = (int *)malloc(windowArea * sizeof(int));
    int k, l, m, n, temp;

    for (int i = halfWindowSize; i < height - halfWindowSize; i++) {
        for (int j = halfWindowSize; j < width - halfWindowSize; j++) {
            for (int c = 0; c < channels; c++) {
                k = 0;
                for (m = -halfWindowSize; m <= halfWindowSize; m++) {
                    for (n = -halfWindowSize; n <= halfWindowSize; n++) {
                        window[k++] = input[((i + m) * width + (j + n)) * channels + c];
                    }
                }

                // Trier le tableau window
                for (m = 0; m < windowArea; m++) {
                    for (n = m + 1; n < windowArea; n++) {
                        if (window[m] > window[n]) {
                            temp = window[m];
                            window[m] = window[n];
                            window[n] = temp;
                        }
                    }
                }

                // Assigner la valeur médiane au pixel de sortie
                output[(i * width + j) * channels + c] = window[windowArea / 2];
            }
        }
    }

    free(window);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_image> <window_size>\n", argv);
        return 1;
    }

    int windowSize = atoi(argv);
    if (windowSize % 2 == 0 || windowSize < 3) {
        printf("La taille de la fenêtre doit être un entier impair supérieur ou égal à 3\n");
        return 1;
    }

    int width, height, channels;
    unsigned char *img = stbi_load(argv, &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Erreur lors du chargement de l'image\n");
        return 1;
    }
    printf("Image chargée : largeur = %d, hauteur = %d, canaux = %d\n", width, height, channels);

    // Allouer dynamiquement la mémoire pour le tableau de sortie
    unsigned char *output = (unsigned char *)malloc(width * height * channels);

    medianFilter(img, output, width, height, channels, windowSize);
    printf("Filtre médian appliqué\n");

    if (!stbi_write_jpg("output.jpg", width, height, channels, output, 100)) {
        printf("Erreur lors de la sauvegarde de l'image\n");
        free(output);
        stbi_image_free(img);
        return 1;
    }
    printf("output.jpg\n");

    // Libérer la mémoire allouée
    free(output);
    stbi_image_free(img);
    printf("Mémoire libérée\n");

    return 0;
}
