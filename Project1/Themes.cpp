#include "Themes.h"

SDL_Color convertColor(unsigned col) {
	SDL_Color c;
	c.r = ((col >> 24) & 0xFF);
	c.g = ((col >> 16) & 0xFF);
	c.b = ((col >> 8) & 0xFF);
	c.a = (col & 0xFF);
	return c;
}

Themes::Themes(Render mRender)
{
	init_fc(mRender);
}
void Themes::init_fc(Render mRender)
{
	//初始化字体
	Theme th = default_theme();
	gfont = TTF_OpenFont("./data/lazy.ttf", 28);
	if (gfont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	//初始化颜色
	TextColor = convertColor(th.TextColor);
	ButtonBorderColor = convertColor(th.ButtonBorderColor);
	ButtonColor = convertColor(th.ButtonColor);
	//初始化表面和纹理
	bgs = IMG_Load(th.BackgroundPath.c_str());
	if (bgs) {
		Uint32 colorkey = SDL_MapRGB(bgs->format, 0, 0, 0);
		SDL_SetColorKey(bgs, SDL_TRUE, colorkey);
	}
	bgt = SDL_CreateTextureFromSurface(mRender._renderer, bgs);
}
Theme Themes::default_theme()
{
	Theme th;
	th.TextColor = GREEN;
	th.ButtonBorderColor = LIGHTBLUE;
	th.ButtonColor = GREY;
	th.BackgroundPath = "./data/tian.png";
	return th;
}