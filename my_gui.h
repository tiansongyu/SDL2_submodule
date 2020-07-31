#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>
#include "Render.h"
#include "Themes.h"
#define WHITE 0xFFFFFFFF
#define BLACK 0xFF
#define GREY 0x4C4C4CFF
#define LIGHTGREY 0x8C8C8CFF
#define RED 0xFF0000FF
#define BLUE 0xFFFF
#define TEAL 0xFFCEFF
#define LIGHTBLUE 0x44C0DAFF
#define GREEN 0xFF00FF


using namespace std;
class UI
{
public:
		UI(string title,const unsigned SCREEN_WIDTH,const unsigned SCREEN_HEIGHT);
		bool loadMedia(const string path);//加载图片
		void handle_gui();    //处理键盘鼠标控制器 循环 
		void drawText(int x, int y, const SDL_Color scolor, const string text,  TTF_Font *font);//显示文字
		void drawRect(int x, int y, int w, int h, SDL_Color scolor, unsigned border, SDL_Color bcolor);
		void drawRect(int x, int y, int w, int h, SDL_Color scolor);
		bool render(SDL_Texture* mTexture, const int x, const int y);
		void renderMenu();//绘制菜单

		void deinit(); //释放内存
private:
	Render mRender;
	Themes *mThemes;
};