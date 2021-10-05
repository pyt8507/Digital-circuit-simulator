#pragma once
#include <graphics.h>

class x_scroll_bar
{
private:
	int x;
	int y;
	int length;
	int width;
	double total_w;
	double show_w;
	int block_length;
	int b_x;
	int b_y;
	MOUSEMSG mm;
	HWND hwnd;
	int delta_x;
public:
	x_scroll_bar(int WINDOW_X, int WINDOW_Y, int _width, int _total_w);
	x_scroll_bar(int _x, int _y, int _width, int _length, int _total_w, int _show_w);
	void print();
	int getMouseX();
	int getMouseY();
	void mouse_check();
	int get_delta_x();
	int get_b_x();
	void set_b_x(int x);
	int get_block_length();
	int get_y();
	int get_width();
	int get_length();
	int get_total_w();
	void set_delta_x(int x);
};

