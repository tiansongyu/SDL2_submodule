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
#include <thread>
using namespace std;
void print_test_thread();
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
		void print() { while (1)printf("test\n"); }
		//lambda���ʽ���߳�����
		/*void printf_test() 
		{
			 for(int i = 0; i < 4; ++i) {
				thread t([i] {
					while(1)printf("%d test\n", i);
				});
				t.detach();
			}
		}*/
		void printf_test()
		{
			for (int i = 0; i < 4; ++i) {
				thread t(print_test_thread);
				t.detach();
			}
		}
		bool inSubMenu;
		void deinit(); //�ͷ��ڴ�
private:
	Render mRender;
	Themes *mThemes;

};