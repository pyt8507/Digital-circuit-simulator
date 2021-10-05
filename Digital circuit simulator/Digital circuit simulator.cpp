#include <graphics.h>
#include <conio.h>
#include <unordered_map>
#include "printer.h"
#include "mouse.h"
#include "widget.h"
#include "x_scroll_bar.h"
#include "y_scroll_bar.h"
#include <iostream>

using namespace std;

unordered_map<int, widget*> widgets;//用于存放与或非门、输入端、输出端

int WINDOW_X = 960;//窗口宽度
int WINDOW_Y = 720;//窗口高度

// 主函数
int main()
{
	initgraph(WINDOW_X, WINDOW_Y);//创建绘图窗口
	printer printer;//绘图器
	mouse mouse;//鼠标事件处理器
	x_scroll_bar xs(0,620,20,940,1920,960);//横向滚动条
	y_scroll_bar ys(940,0,20,620,1440,720);//纵向滚动条
	BeginBatchDraw();//使用批量绘图，以解决闪烁问题
	while (!_kbhit())
	{
		cleardevice();//清屏
		printer.print_widgets(widgets,xs,ys);//绘制组件
		printer.print_outputvalue(widgets, xs, ys);//绘制每个组件的输出值
		printer.print_lines(widgets, xs, ys);//绘制连线
		printer.print_ui();//绘制组件框
		xs.print();//绘制横向滚动条
		ys.print();//绘制纵向滚动条
		mouse.check(widgets,xs,ys);//检查鼠标事件
		FlushBatchDraw();//执行未完成的绘制任务
	}
	EndBatchDraw();//结束批量绘图
	closegraph();//关闭绘图窗口
}