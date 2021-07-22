#include <graphics.h>
#include <conio.h>
#include <unordered_map>
#include "printer.h"
#include "mouse.h"
#include "widget.h"
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
	BeginBatchDraw();//使用批量绘图，以解决闪烁问题
	while (!_kbhit())
	{
		cleardevice();//清屏
		printer.print_ui();//绘制组件框
		printer.print_widgets(widgets);//绘制组件
		printer.print_outputvalue(widgets);//绘制每个组件的输出值
		printer.print_lines(widgets);//绘制连线
		mouse.check(widgets);//检查鼠标事件
		FlushBatchDraw();//执行未完成的绘制任务
	}
	EndBatchDraw();//结束批量绘图
	closegraph();//关闭绘图窗口
}