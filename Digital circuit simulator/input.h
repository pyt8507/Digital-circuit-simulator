#include "widget.h"
#pragma once
class input :public widget
{
private:
	int n = 0;
	int value = 0;

public:
	input();
	int getOutputValue(unordered_map<int, widget*>& widgets);
	void setValue(int v);
	int inputUnderMouse(int x, int y);
	int getN();
};
