#include <SDL2/SDL.h>   
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>  



void RotationManuelle(int* Running, double* angle)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			*Running = 0;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					*angle -= 1.0;
					break;
				case SDLK_RIGHT:
					*angle += 1.0;
					break;
			}
		}
	}
}
