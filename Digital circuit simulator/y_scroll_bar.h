#pragma once
#include <graphics.h>

class y_scroll_bar
{
private:
	int x;
	int y;
	int length;
	int width;
	double total_h;
	double show_h;
	int block_length;
	int b_x;
	int b_y;
	MOUSEMSG mm;
	HWND hwnd;
	int delta_y;
public:
	y_scroll_bar(int WINDOW_X, int WINDOW_Y, int _width, int _total_h);
	y_scroll_bar(int _x, int _y, int _width, int _length, int _total_h, int _show_h);
	void print();
	int getMouseX();
	int getMouseY();
	void mouse_check();
	int get_delta_y();
	int get_b_y();
	void set_b_y(int x);
	int get_block_length();
	int get_x();
	int get_width();
	int get_length();
	int get_total_h();
	void set_delta_y(int x);
};

