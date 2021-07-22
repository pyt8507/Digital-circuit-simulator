#include "output.h"

output::output()
{
	type = 5;
	size_x = 111;
	size_y = 17;
	input_x[0] = 0;
	input_y[0] = 8;
	for (int i = 0; i < n; i++)
		pre[i] = -1;
}

int output::getOutputValue(unordered_map<int, widget*>& widgets)
{
	if (pre[0] != -1)
		return widgets[pre[0]]->getOutputValue(widgets);
	else
		return -1;
}

void output::setValue(int v)
{

}

int output::inputUnderMouse(int _x, int _y)
{
	int in1x = x + input_x[0];
	int in1y = y + input_y[0];
	if ((_x - in1x) * (_x - in1x) + (_y - in1y) * (_y - in1y) <= 25)
		return 1;
	else
		return 0;
}

int output::getN()
{
	return n;
}