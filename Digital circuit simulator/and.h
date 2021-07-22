#pragma once
#include "widget.h"
class AND :public widget
{
private:
	int n = 2;

public:
	AND();
	int getOutputValue(unordered_map<int, widget*>& widgets);
	void setValue(int v);
	int inputUnderMouse(int x, int y);
	int getN();
};
