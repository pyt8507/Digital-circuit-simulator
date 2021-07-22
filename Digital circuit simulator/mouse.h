#pragma once
#include <graphics.h>
#include "printer.h"
#include "distributor.h"
#include <unordered_map>
#include "widget.h"
#include "and.h"

class mouse//鼠标事件处理器
{
protected:
	HWND hwnd = GetHWnd();
	MOUSEMSG mm;
	printer printer;
	distributor distributor;//分配器，负责创建组件和分配编号
public:
	void check(unordered_map<int, widget*> &widgets);//检查鼠标事件
	int getMouseX();//获取鼠标在窗口中的横坐标
	int getMouseY();//获取鼠标在窗口中的纵坐标
	void clearFocus(unordered_map<int, widget*>& widgets);//清除对所有组件的选中
};