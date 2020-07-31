#pragma once
#include <string>
using namespace std;
#define WHITE 0xFFFFFFFF
#define BLACK 0xFF
#define GREY 0x4C4C4CFF
#define LIGHTGREY 0x8C8C8CFF
#define RED 0xFF0000FF
#define BLUE 0xFFFF
#define TEAL 0xFFCEFF
#define LIGHTBLUE 0x44C0DAFF
#define GREEN 0xFF00FF

typedef struct
{
	string BackgroundPath;
	string FontPath;
	unsigned TextColor;
	unsigned SelectedTextColor;
	unsigned ButtonColor;
	unsigned ButtonBorderColor;
	unsigned BGColor;
	unsigned PopCol1;
	unsigned PopCol2;
} Theme;