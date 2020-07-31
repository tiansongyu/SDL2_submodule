#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "type.h"
#include <stdio.h>
#include "Render.h"
class Themes
{
public:
	Themes(Render mRender);
	void init_fc(Render mRender);

	TTF_Font* gfont;
	SDL_Color TextColor;
	SDL_Color ButtonBorderColor;
	SDL_Color ButtonColor;
	SDL_Surface *bgs;
	SDL_Texture *bgt;
	Theme default_theme();
};