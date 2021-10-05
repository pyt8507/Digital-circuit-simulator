#include "y_scroll_bar.h"

y_scroll_bar::y_scroll_bar(int WINDOW_X, int WINDOW_Y, int _width, int _total_h)
{
	x = WINDOW_X - _width;
	y = 0;
	width = _width;
	length = WINDOW_Y - width;
	total_h = _total_h;
	show_h = WINDOW_Y;
	block_length = length * show_h / total_h;
	b_x = x;
	b_y = 0;
	hwnd = GetHWnd();
}

y_scroll_bar::y_scroll_bar(int _x, int _y, int _width, int _length, int _total_h, int _show_h)
{
	x = _x;
	y = _y;
	width = _width;
	length = _length;
	total_h = _total_h;
	show_h = _show_h;
	block_length = length * show_h / total_h;
	b_x = x;
	b_y = y;
	hwnd = GetHWnd();
}

void y_scroll_bar::print()
{
	rectangle(x, y, x + width - 1, y + length - 1);
	fillrectangle(b_x + 2, b_y + 2, b_x + width - 3, b_y + block_length - 3);
}

int y_scroll_bar::getMouseX()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	return point.x;
}

int y_scroll_bar::getMouseY()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	return point.y;
}

void y_scroll_bar::mouse_check()
{
	int m_y = getMouseY() - b_y;//��¼����������λ��
	while (true)//����ѭ������ʵ������϶������Ч��
	{
		b_y = getMouseY() - m_y;
		if (b_y < 0)
			b_y = 0;
		else if (b_y + block_length > length)
			b_y = length - block_length;
		delta_y = double(b_y) * total_h / length;
		cleardevice();//����
		print();
		FlushBatchDraw();//ִ�л�������
		mm = GetMouseMsg();//��ȡ���µ�����¼�
		if (mm.uMsg == WM_LBUTTONUP)//��⵽�������ɿ�
			break;
	}
}

int y_scroll_bar::get_delta_y()
{
	return delta_y;
}

int y_scroll_bar::get_b_y()
{
	return b_y;
}

void y_scroll_bar::set_b_y(int x)
{
	b_y = x;
}

int y_scroll_bar::get_block_length()
{
	return block_length;
}

int y_scroll_bar::get_x()
{
	return x;
}

int y_scroll_bar::get_width()
{
	return width;
}

int y_scroll_bar::get_length()
{
	return length;
}

int y_scroll_bar::get_total_h()
{
	return total_h;
}

void y_scroll_bar::set_delta_y(int x)
{
	delta_y = x;
}
