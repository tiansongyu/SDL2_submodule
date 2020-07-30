#include "my_gui.h"

#include <string>

UI * UI::mInstance = 0;

UI::UI(std::string title,const unsigned SCREEN_WIDTH, const unsigned SCREEN_HEIGHT)
{
	quit = false;
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//ªÒ»°‰÷»æ≤„
		gScreenSurface = SDL_GetWindowSurface(gWindow);
	}
}
bool UI::display_background()
{
	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
	//Wait two seconds
	SDL_Delay(2000);
	return true;
}
void UI::handle_gui()
{
	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

	//Handle events on queue
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;
				case SDLK_DOWN:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;
				case SDLK_LEFT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;
				case SDLK_RIGHT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;
				default:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
		}


		//Apply the image
		SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
	}
}

SDL_Surface* UI::loadMedia(string path)//º”‘ÿÕº∆¨
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gXOut = SDL_LoadBMP(path.c_str());

	return gXOut;
}
bool UI::loadMedia(vector<string> path)
{
	unsigned int tmp = 0;
	for (auto x = path.begin(); x != path.end(); x++)
	{
		gKeyPressSurfaces[tmp++] = loadMedia(*x);
		if (gKeyPressSurfaces[tmp - 1] == NULL)
		{
			printf("Failed to load image!\n");
			return false;
		}
	}
	return true;
}

void UI::deinit()
{
	//Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
