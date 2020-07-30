#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>

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
		void deinit(); //�ͷ��ڴ�
		bool loadMedia(const string path);//����ͼƬ
		/*bool loadMedia(vector<string> path);*/
		void handle_gui();    //��������������� ѭ�� 
		bool setFont_Color();  //�趨����
		void drawText(int x, int y, const SDL_Color scolor, const string text,  TTF_Font *font);//��ʾ����
		void drawRect(int x, int y, int w, int h, SDL_Color scolor, unsigned border, SDL_Color bcolor);
		void drawRect(int x, int y, int w, int h, SDL_Color scolor);

		bool render(SDL_Texture* mTexture, const int x, const int y);
		void renderMenu();//���Ʋ˵�
		inline  TTF_Font* getFont() { return this->gfont; };
		inline  SDL_Color* getTextColor() { return this->gtextColor; };
private:
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//Screen dimension constant
	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface* gHelloWorld = NULL;
	SDL_Surface* gXOut = NULL;
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* image_Texture = NULL;

	SDL_Texture* text_Texture = NULL;
	SDL_Event e;
	//��������
	SDL_Color color_red = { 0x11,0x11,0x11,0xFF };

	TTF_Font* gfont = NULL;
	SDL_Color* gtextColor =NULL ;
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