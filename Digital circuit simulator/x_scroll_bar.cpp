#include "x_scroll_bar.h"

x_scroll_bar::x_scroll_bar(int WINDOW_X, int WINDOW_Y, int _width, int _total_w)
{
	x = 0;
	y = WINDOW_Y - _width;
	width = _width;
	length = WINDOW_X - width;
	total_w = _total_w;
	show_w = WINDOW_X;
	block_length = length * show_w / total_w;
	b_x = 0;
	b_y = y;
	hwnd = GetHWnd();
}

x_scroll_bar::x_scroll_bar(int _x, int _y, int _width, int _length, int _total_w, int _show_w)
{
	x = _x;
	y = _y;
	width = _width;
	length = _length;
	total_w = _total_w;
	show_w = _show_w;
	block_length = length * show_w / total_w;
	b_x = x;
	b_y = y;
	hwnd = GetHWnd();
}

void x_scroll_bar::print()
{
	rectangle(x, y, x + length - 1, y + width - 1);
	fillrectangle(b_x + 2, b_y + 2, b_x + block_length - 3, b_y + width - 3);
}

int x_scroll_bar::getMouseX()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	return point.x;
}

int x_scroll_bar::getMouseY()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	return point.y;
}

void x_scroll_bar::mouse_check()
{
	int m_x = getMouseX() - b_x;//记录点击鼠标的相对位置
	while (true)//进入循环，以实现鼠标拖动滑块的效果
	{
		b_x = getMouseX() - m_x;
		if (b_x < 0)
			b_x = 0;
		else if (b_x + block_length > length)
			b_x = length - block_length;
		delta_x = double(b_x) * total_w / length;
		cleardevice();//清屏
		print();
		FlushBatchDraw();//执行绘制任务
		mm = GetMouseMsg();//获取最新的鼠标事件
		if (mm.uMsg == WM_LBUTTONUP)//检测到鼠标左键松开
			break;
	}
}

int x_scroll_bar::get_delta_x()
{
	return delta_x;
}

int x_scroll_bar::get_b_x()
{
	return b_x;
}

void x_scroll_bar::set_b_x(int x)
{
	b_x = x;
}

int x_scroll_bar::get_block_length()
{
	return block_length;
}

int x_scroll_bar::get_y()
{
	return y;
}

int x_scroll_bar::get_width()
{
	return width;
}

int x_scroll_bar::get_length()
{
	return length;
}

int x_scroll_bar::get_total_w()
{
	return total_w;
}

void x_scroll_bar::set_delta_x(int x)
{
	delta_x = x;
}
