#include "widget.h"
#pragma once
class output :public widget
{
private:
	int n = 1;

public:
	output();
	int getOutputValue(unordered_map<int, widget*>& widgets);
	void setValue(int v);
	int inputUnderMouse(int x, int y);
	int getN();
};