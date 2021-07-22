#include "or.h"

OR::OR()
{
	type = 2;
	size_x = 86;
	size_y = 64;
	input_x[0] = 0;
	input_y[0] = 16;
	input_x[1] = 0;
	input_y[1] = 47;
	output_x = 85;
	output_y = 32;
	for (int i = 0; i < n; i++)
		pre[i] = -1;
}

int OR::getOutputValue(unordered_map<int, widget*>& widgets)
{
	if (pre[0] != -1 && pre[1] != -1)
		return (widgets[pre[0]]->getOutputValue(widgets) || widgets[pre[1]]->getOutputValue(widgets));
	else
		return -1;
}

void OR::setValue(int v)
{

}

int OR::inputUnderMouse(int _x, int _y)
{
	int in1x = x + input_x[0];
	int in1y = y + input_y[0];
	int in2x = x + input_x[1];
	int in2y = y + input_y[1];
	if ((_x - in1x) * (_x - in1x) + (_y - in1y) * (_y - in1y) <= 25)
		return 1;
	else if ((_x - in2x) * (_x - in2x) + (_y - in2y) * (_y - in2y) <= 25)
		return 2;
	else
		return 0;
}

int OR::getN()
{
	return n;
}