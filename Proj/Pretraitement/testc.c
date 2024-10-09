#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../stb-master/stb-master/stb_image.h"
#include "../../stb-master/stb-master/stb_image_write.h"

typedef struct {
    unsigned char r, g, b;
} Pixel;

Pixel** loadImage(const char *filename, int *width, int *height) {
    int channels;
    unsigned char *data = stbi_load(filename, width, height, &channels, 3);
    if (data == NULL) {
        fprintf(stderr, "Error loading image: %s\n", stbi_failure_reason());
        return NULL;
    }

    Pixel **image = malloc(*height * sizeof(Pixel *));
    for (int i = 0; i < *height; i++) {
        image[i] = malloc(*width * sizeof(Pixel));
        for (int j = 0; j < *width; j++) {
            int index = (i * (*width) + j) * 3;
            image[i][j].r = data[index];
            image[i][j].g = data[index + 1];
            image[i][j].b = data[index + 2];
        }
    }

    stbi_image_free(data);
    return image;
}

void saveImage(const char *filename, Pixel **image, int width, int height) {
    unsigned char *data = malloc(width * height * 3);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = (i * width + j) * 3;
            data[index] = image[i][j].r;
            data[index + 1] = image[i][j].g;
            data[index + 2] = image[i][j].b;
        }
    }

    stbi_write_bmp(filename, width, height, 3, data);
    free(data);
}

void convertToBlackAndWhite(Pixel **image, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Pixel *p = &image[i][j];
            unsigned char gray = (p->r + p->g + p->b) / 3;
            if (p->r < 100 && p->g < 100 && p->b > 200) {
                p->r = p->g = p->b = 255;
            } else {
                p->r = p->g = p->b = gray;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv);
        return 1;
    }

    int width, height;
    Pixel **image = loadImage(argv[0], &width, &height);

    convertToBlackAndWhite(image, width, height);

    saveImage("output_image.bmp", image, width, height);

    for (int i = 0; i < height; i++) {
        free(image[i]);
    }
    free(image);

    return 0;
}

