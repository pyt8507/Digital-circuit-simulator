#include "widget.h"
#pragma once
class NOT :public widget
{
private:
	int n = 1;

public:
	NOT();
	int getOutputValue(unordered_map<int, widget*>& widgets);
	void setValue(int v);
	int inputUnderMouse(int x, int y);
	int getN();
};