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
#include "MenuOption.hpp"
#include "type.h"
using namespace std;
class UI
{
public:
		UI(string title,const unsigned SCREEN_WIDTH,const unsigned SCREEN_HEIGHT);
		void handle_gui();    //��������������� ѭ�� 
		void drawText(int x, int y, const SDL_Color scolor, const string text,  TTF_Font *font);//��ʾ����
		void drawRect(int x, int y, int w, int h, SDL_Color scolor, unsigned border, SDL_Color bcolor);
		void drawRect(int x, int y, int w, int h, SDL_Color scolor);
		void renderMenu();//���Ʋ˵�
		void PaintMenu();

		void Menuup();
		void Menudown();
		void subMenuup();
		void subMenudown();
		void Menuright();
		void Menuleft();

		bool inSubMenu;
		void deinit(); //�ͷ��ڴ�
private:
	Render mRender;
	Themes *mThemes;

};