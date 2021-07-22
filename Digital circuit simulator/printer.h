#pragma once
#include <graphics.h>
#include <unordered_map>
#include "widget.h"
using namespace std;
class printer//绘图器
{
protected:
	IMAGE andimg, orimg, notimg, inputimg, outputimg, andfimg, orfimg, notfimg, inputfimg, outputfimg;
public:
	printer();
	void print_ui();//绘制组件框
	void print_widgets(unordered_map<int, widget*> &widgets);//绘制组件
	void print_and(int x, int y);//绘制与门
	void print_not(int x, int y);//绘制非门
	void print_or(int x, int y);//绘制或门
	void print_input(int x, int y);//绘制输入端
	void print_output(int x, int y);//绘制输出端
	void print_andf(int x, int y);//绘制被选中状态的与门
	void print_notf(int x, int y);//绘制被选中状态的非门
	void print_orf(int x, int y);//绘制被选中状态的或门
	void print_inputf(int x, int y);//绘制被选中状态的输入端
	void print_outputf(int x, int y);//绘制被选中状态的输出端
	void print_lines(unordered_map<int, widget*>& widgets);//绘制所有连线
	void print_line(int x1, int y1, int x2, int y2);//绘制两个组件间的一条连线
	void print_outputvalue(unordered_map<int, widget*>& widgets);//绘制每个组件的输出值
};