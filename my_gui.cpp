#include "my_gui.h"

#include <string>

static unsigned currSel = 0;
static unsigned currSubSel = 0;
static unsigned vol = 64;
static unsigned titleX = 60;
static unsigned titleY = 30;
static unsigned menuX = 55, menuY = 115;
static unsigned subX = 411, subY = 88;

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
	mRender._window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mRender._window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//获取渲染层
		mRender._renderer = SDL_CreateRenderer(mRender._window, -1, SDL_RENDERER_ACCELERATED);
		if (mRender._renderer == NULL)
		{
			printf("渲染层失败\n");

		}
		else
		{
			SDL_SetRenderDrawColor(mRender._renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
		}
	}
	mThemes = new Themes(mRender);
	printf("渲染成功\n");

}
unsigned clock_count = 0;
void UI::handle_gui()
{
	SDL_Event e;
	bool quit =false ;
	//绘制菜单；
	renderMenu();
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
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
		//SDL_SetRenderDrawColor(mRender._renderer,0xff,0xff,0xff,0xff);
		//SDL_UpdateWindowSurface(gWindow);
	}
}
void UI::renderMenu()
{
	time_t now = time(0);
	char buff[40];
	memset(buff, '\0', sizeof(buff));
	ctime_s(buff, sizeof(buff), &now);
	//开始渲染背景图片和文字
	SDL_RenderClear(mRender._renderer); //清除界面
	SDL_RenderCopy(mRender._renderer, mThemes->bgt, NULL, NULL); //设置背景
	//Mainmenu  text
	drawText(60, 30, mThemes->TextColor, "tian sofeware", mThemes->gfont); //titulo
	drawText(1150, 30, mThemes->TextColor, "v1.3", mThemes->gfont);//vercion HB
	drawText(500, 30, mThemes->TextColor, buff, mThemes->gfont);//time
	drawText(1150, 100, mThemes->TextColor, "v 3.4", mThemes->gfont);//vercion HB
	drawText(100, 100, mThemes->TextColor, u8"nihao a 你好", mThemes->gfont);


	drawRect(menuX-10, menuY-10, 210 + 20, 25 + 20, mThemes->ButtonColor, 5, mThemes->ButtonBorderColor);

	SDL_RenderPresent(mRender._renderer);
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
	SDL_SetRenderDrawColor(mRender._renderer, scolor.r, scolor.g, scolor.b, scolor.a);
	SDL_RenderFillRect(mRender._renderer, &rect);
}
bool UI::render(SDL_Texture* mTexture, const int x,const int y)
{
	if (!SDL_RenderCopy(mRender._renderer, mTexture, NULL, NULL))
	{
		printf("render fail\n");
		return false;
	}
	return true;
}
bool UI::loadMedia(const string path)//加载图片
{
	
	/*SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//将render渲染成texture纹理
		image_Texture = SDL_CreateTextureFromSurface(mRender._renderer, loadedSurface);
		if (image_Texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		//释放surface ；
		//使用texture
	}*/
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
	SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(mRender._renderer, textSurface);
	if (text_Texture)
	{
		SDL_Rect position;
		position.x = x;
		position.y = y;
		position.w = textSurface->w;
		position.h = textSurface->h;
		//将文字纹理嵌入到渲染器中
		SDL_RenderCopy(mRender._renderer, text_Texture, NULL, &position);
		//释放文字纹理
		SDL_DestroyTexture(text_Texture);
	}
	else
		printf("渲染文字失败\n");
	SDL_FreeSurface(textSurface);
}

void UI::deinit()
{
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(mRender._renderer);
	SDL_FreeSurface(mRender._surface);
	SDL_DestroyWindow(mRender._window);
	SDL_Quit();
}
