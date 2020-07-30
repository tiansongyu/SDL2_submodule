/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "my_gui.h"
#include <string>
#include <vector>
const unsigned SCREEN_WIDTH = 640;
const unsigned SCREEN_HEIGHT = 480;
int main(int argc, char* args[])
{
	UI ui("tian",SCREEN_WIDTH,SCREEN_HEIGHT);//≥ı ºªØ¥∞ø⁄
	vector<string> path = { 
		"./data/press.bmp",
		"./data/up.bmp",
		"./data/down.bmp",
		"./data/left.bmp",
		"./data/right.bmp"
	};
	if (ui.loadMedia(path) == false)
		printf("º”‘ÿÕº∆¨ ß∞‹\n");
	ui.handle_gui();
	ui.deinit();
	return 0;
}