#include "input.h"

input::input()
{
	type = 4;
	size_x = 111;
	size_y = 17;
	output_x = 110;
	output_y = 8;
	for (int i = 0; i < n; i++)
		pre[i] = -1;
}

int input::getOutputValue(unordered_map<int, widget*>& widgets)
{
	return value;
}

void input::setValue(int v)
{
	value = v;
}

int input::inputUnderMouse(int _x, int _y)
{
	return 0;
}

int input::getN()
{
	return n;
}