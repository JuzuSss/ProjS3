#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "Rotation.c"
#include <time.h>


int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Test Rotation Automatique",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int Running = 1;
    double angle = 0.0;

    
    srand(time(NULL));

    angle = (double)(rand() % 360);

    printf("Angle initial aléatoire: %f\n", angle);

    RotationAutomatique(&Running, &angle);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
