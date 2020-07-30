/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "my_gui.h"
#include <string>
#include <vector>
#include <SDL_ttf.h>
const unsigned SCREEN_WIDTH = 1280;
const unsigned SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	TTF_Font* gfont = TTF_OpenFont("./data/lazy.ttf", 28);

	UI ui("tian",SCREEN_WIDTH,SCREEN_HEIGHT);//初始化窗口
	string path = "./data/tian.png";
	if (!ui.loadMedia(path))
		printf("加载图片失败\n");
	else
		printf("图片加载成功\n");
	ui.setFont_Color();	
	ui.handle_gui();
	ui.deinit();
	return 0;
}