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



void RotationAutomatique(int* Running, double* angle)
{
	SDL_Event event;
	Uint32 start_time = SDL_GetTicks();

	while(*Running)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				*Running = 0;
			}
		}
		Uint32 time = SDL_GetTicks();
		*angle += (time - start_time) * 0.01;
		start_time = time;


		if (*angle >= 360.0)
        	{
       		    *angle -= 360.0;
       		}
        	else if (*angle < 0.0)
        	{
        	    *angle += 360.0;
        	}
	}

}



