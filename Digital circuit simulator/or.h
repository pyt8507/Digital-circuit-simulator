#include "widget.h"
#pragma once
class OR :public widget
{
private:
	int n = 2;

public:
	OR();
	int getOutputValue(unordered_map<int, widget*>& widgets);
	void setValue(int v);
	int inputUnderMouse(int x, int y);
	int getN();
};
