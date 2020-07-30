#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
class UI
{
	public:

		static UI* mInstance;
		static UI* getInstance();
		UI(string title,const unsigned SCREEN_WIDTH,const unsigned SCREEN_HEIGHT);
		void deinit();
		SDL_Surface* loadMedia(string path);//º”‘ÿÕº∆¨
		bool loadMedia(vector<string> path);
		bool display_background();
		void handle_gui();
private:
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//Screen dimension constant
	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface* gHelloWorld = NULL;
	SDL_Surface* gXOut = NULL;
	SDL_Event e;

	//º¸≈Ã ‰»Î
	enum KeyPressSurfaces
	{
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN,
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_TOTAL
	};
	//The images that correspond to a keypress
	SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	//Current displayed image
	SDL_Surface* gCurrentSurface = NULL;
	bool quit;
};