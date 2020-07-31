#pragma once
#include <string>
#include "MenuObj.h"
#include <functional>
using namespace std;
class MenuOption :public MenuObj
{
public:
	MenuOption(string Name, string Desc,function<void()> Call) {
		name = Name;
		desc = Desc;
		callback = Call;
	}
	string getDesc() {
		return desc;
	}
	vector<MenuOption> subMenu;
protected:
	string desc;
	function<void()> callback;

};
