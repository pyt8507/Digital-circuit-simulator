#pragma once
#include <graphics.h>
#include "printer.h"
#include "distributor.h"
#include <unordered_map>
#include "widget.h"
#include "and.h"
#include "x_scroll_bar.h"
#include "y_scroll_bar.h"

class mouse//����¼�������
{
protected:
	HWND hwnd = GetHWnd();
	MOUSEMSG mm;
	printer printer;
	distributor distributor;//�����������𴴽�����ͷ�����
public:
	void check(unordered_map<int, widget*>& widgets, x_scroll_bar& xs, y_scroll_bar& ys);//�������¼�
	int getMouseX();//��ȡ����ڴ����еĺ�����
	int getMouseY();//��ȡ����ڴ����е�������
	void clearFocus(unordered_map<int, widget*>& widgets);//��������������ѡ��
};