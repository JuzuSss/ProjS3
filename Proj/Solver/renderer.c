#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


SDL_Window *create_window(char *title, unsigned int width, unsigned int height)            //ceci est le tp SDL jusqu'a 
{                                                                                          //la ligne 71;;
	int sdl = SDL_Init(SDL_INIT_VIDEO);
	if(sdl != 0)
	{
		return NULL;
	}
	
	SDL_Window *creefe = SDL_CreateWindow
		(
		 title,
		 SDL_WINDOWPOS_CENTERED,
		 SDL_WINDOWPOS_CENTERED,
		 width,
		 height,
		 SDL_WINDOW_SHOWN
		);
	return creefe;
};
 

SDL_Renderer *create_renderer(SDL_Window *window)
{
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	return renderer;
};

void close_program(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_Quit();
};

int process_events()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			return 0;
		}
	}
	return 1;
};

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
};


void draw_rects(SDL_Renderer *renderer, int rects[][4], int colors[][3], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		SDL_SetRenderDrawColor(renderer, colors[i][0], colors[i][1], colors[i][2], 255);
		SDL_Rect rec = 
		{
			rects[i][0], rects[i][1], rects[i][2], rects[i][3]
		};
		SDL_RenderFillRect(renderer, &rec);
	};
}

	//////////////////////////////////////////////////////////////////////////////////////////////

void draw_matrice(SDL_Renderer *renderer,int rows,int cols)
{
		for(int i = 1; i < cols; i++)
		{
			draw_line(renderer,i*100,0,i*100,rows*100);
		}

		for(int i = 1; i < rows; i++)
		{
			draw_line(renderer,0,i*100,cols*100,i*100);
		}
}

	///////////////////////////////////////////////////////////////////////////////////////////////



void draw_letter_matrice(SDL_Renderer *renderer,char* matrice,int rows,int cols)
{
		for(int i = 1; i < cols; i++)
		{
			draw_line(renderer,i*100,0,i*100,rows*100);
		}



	
}

void draw_letter(SDL_Renderer *renderer, const char *letter, int x, int y, TTF_Font *font, SDL_Color color) 
{
    // Crée une surface avec le texte
    SDL_Surface *surface = TTF_RenderText_Solid(font, letter, color);
    if (surface == NULL) {
        printf("Erreur lors de la création de la surface texte : %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Erreur lors de la création de la texture texte : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Définir la position et la taille où le texte sera dessiné
    SDL_Rect dstrect = { x, y, surface->w, surface->h };

    // Copier la texture dans le renderer
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    // Libérer la surface et la texture
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


  
int main(int argc, char *argv[]) {
    // Exemple de matrice
    char *matrice[7] = {
        "ABCDE",
        "FGHIJ",
        "KLMNO",
        "PQRST",
        "UVWXY",
        "UVWXY",
        "UIWXY"
    };


    int rows = sizeof(matrice) / sizeof(matrice[0]);  // Nombre de lignes (5)
    int cols = strlen(matrice[0]);                    // Nombre de colonnes (5)

 		/////////////////////////////////////////////////////////////////////////////////////////
    
    SDL_Window *window = create_window("example", cols*100, rows*100);       //88 a 102 cree et fait apparaitre une fenetre de bonne taille

    if (!window)
        errx(EXIT_FAILURE, "Failed to create SDL window");

    SDL_Renderer *renderer = create_renderer(window);

    if (!renderer)
        errx(EXIT_FAILURE, "Failed to create SDL renderer");

    SDL_RenderPresent(renderer); // Make the window appear

    /////////////////////////////////////////////////////////////////////////////////////////

        // Initialisation de SDL
    // if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    // {
    //     printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
    //     return 1;
    // }

    // Initialisation de SDL_ttf
    // if (TTF_Init() == -1) 
    // {
    //     printf("Erreur d'initialisation de SDL_ttf: %s\n", TTF_GetError());
    //     SDL_Quit();
    //     return 1;
    // }

    // Charger la police (par exemple, Arial)
    // TTF_Font *font = TTF_OpenFont("Arial.ttf", 24);  // Assure-toi que le fichier Arial.ttf est dans le bon dossier
    // if (font == NULL) 
    // {
    //     printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
    //     SDL_DestroyRenderer(renderer);
    //     SDL_DestroyWindow(window);
    //     TTF_Quit();
    //     SDL_Quit();
    //     return 1;
    // }

    // SDL_Color white = {255, 255, 255, 255};

    ///////////////////////////////////////////////////////////////////////////////////////////

    int rects[][4] = {                                                       //102 a 120 cree un carre gris de fond
        { 0,0,cols*100,rows*100}};
    
    int colors[][3] = {
        { 200, 200, 200 }};
    
    int keep_alive = 1;
    while (keep_alive)
    {
        keep_alive = process_events();   
        draw_rects(renderer, rects, colors, 3); 
    //////////////////////////////////////////////////////////////////////////////////////////
				draw_matrice(renderer,rows,cols);
				// draw_letter(renderer, "A", 100, 100, font, white);
    		SDL_RenderPresent(renderer);
		}	
    close_program(window, renderer);
    return EXIT_SUCCESS;
    return 0;
}
