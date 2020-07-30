#include "my_gui.h"

#include <string>

static unsigned currSel = 0;
static unsigned currSubSel = 0;
static unsigned vol = 64;
static unsigned titleX = 60;
static unsigned titleY = 30;
static unsigned menuX = 55, menuY = 115;
static unsigned subX = 411, subY = 88;

SDL_Color convertColor(unsigned col) {
	SDL_Color c;
	c.r = ((col >> 24) & 0xFF);
	c.g = ((col >> 16) & 0xFF);
	c.b = ((col >> 8) & 0xFF);
	c.a = (col & 0xFF);
	return c;
}

UI::UI(std::string title,const unsigned SCREEN_WIDTH, const unsigned SCREEN_HEIGHT)
{
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
		printf("sdl_ttf初始化成功\n");
	SDL_Init(SDL_INIT_EVERYTHING);
	quit = false;
	gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//获取渲染层
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL)
		{
			printf("渲染层失败\n");

		}
		else
		{
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
		}
	}
	printf("渲染成功\n");

}
bool UI::setFont_Color()
{
	gfont = TTF_OpenFont("./data/lazy.ttf", 28);
	if (gfont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	return true;
}
unsigned clock_count = 0;
void UI::handle_gui()
{
	renderMenu();

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		if (clock_count == 1000)
		{
			renderMenu();
			clock_count = 0;
		}
		printf("%d\n" , clock_count);
		clock_count++;
		//SDL_SetRenderDrawColor(gRenderer,0xff,0xff,0xff,0xff);

		//Update screen

		//Update the surface
		//SDL_UpdateWindowSurface(gWindow);
	}
}
void UI::renderMenu()
{
	time_t now = time(0);
	char buff[40];
	memset(buff, '\0', sizeof(buff));
	ctime_s(buff, sizeof(buff), &now);

	SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, image_Texture, NULL, NULL);
	//Mainmenu  text
	drawText(60, 30, color_red, "tian sofeware", gfont); //titulo
	drawText(1150, 30, color_red, "v1.3", gfont);//vercion HB
	drawText(500, 30, color_red, buff, gfont);//time
	drawText(1150, 100, color_red, "v 3.4", gfont);//vercion HB
	drawText(100, 100, color_red, u8"nihao a 你好", gfont);


	drawRect(menuX-10, menuY-10, 210 + 20, 25 + 20, convertColor(GREY), 5, convertColor(LIGHTBLUE));

	SDL_RenderPresent(gRenderer);
	//drawRect(menuX - 10, oy - 10, 210 + 20, 25 + 20, mThemes->butCol, 5, mThemes->butBorderCol);

}
void UI::drawRect(int x, int y, int w, int h, SDL_Color scolor, unsigned border, SDL_Color bcolor)
{
	drawRect(x-border, y-border, w+border, h+border, bcolor);
	drawRect(x,y,w-border,h-border,scolor);
}
void UI::drawRect(int x, int y, int w, int h, SDL_Color scolor)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(gRenderer, scolor.r, scolor.g, scolor.b, scolor.a);
	SDL_RenderFillRect(gRenderer, &rect);
}
bool UI::render(SDL_Texture* mTexture, const int x,const int y)
{
	if (!SDL_RenderCopy(gRenderer, mTexture, NULL, NULL))
	{
		printf("render fail\n");
		return false;
	}
	return true;
}
bool UI::loadMedia(const string path)//加载图片
{
	
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//将render渲染成texture纹理
		image_Texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (image_Texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		//释放surface ；
		//使用texture
	}
	return true;
}
void UI::drawText(int x, int y, const SDL_Color scolor, const string text,  TTF_Font *font)
{

	SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), scolor);
	if (!textSurface) {
		printf("显示文字失败\n");
	}
	//设置透明度
	//SDL_SetSurfaceAlphaMod(surface, 0x4F);
	this->text_Texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	if (this->text_Texture)
	{
		SDL_Rect position;
		position.x = x;
		position.y = y;
		position.w = textSurface->w;
		position.h = textSurface->h;
		//将文字纹理嵌入到渲染器中
		SDL_RenderCopy(gRenderer, this->text_Texture, NULL, &position);
		//释放文字纹理
		SDL_DestroyTexture(this->text_Texture);
	}
	else
		printf("渲染文字失败\n");
	SDL_FreeSurface(textSurface);
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
