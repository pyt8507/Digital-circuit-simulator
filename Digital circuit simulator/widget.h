#pragma once
#include <unordered_map>
using namespace std;
class widget
{
protected:
	int id;//编号
	int type;//组件类型 1:与门 2:或门 3:非门 4:输入端 5:输出端
	int x;//位置横坐标
	int y;//位置纵坐标
	int size_x;//宽度
	int size_y;//高度
	int n;//输入管脚个数
	int* pre = new int[n];//存放与输入端相连的组件的id
	int* input_x = new int[n];//输入管脚在组件中的横坐标
	int* input_y = new int[n];//输入管脚在组件中的纵坐标
	int output_x;//输出管脚在组件中的横坐标
	int output_y;//输出管脚在组件中的纵坐标
	bool focused = false;//被选中的标记

public:
	int get_id();
	void set_id(int _id);
	int get_x();
	void set_x(int _x);
	int get_y();
	void set_y(int _y);
	int get_size_x();
	int get_size_y();
	int get_type();
	virtual int getOutputValue(unordered_map<int, widget*>& widgets) = 0;//获取输出值
	virtual void setValue(int v) = 0;//设置输入端的值
	bool underMouse(int x,int y);//是否在鼠标下
	virtual int inputUnderMouse(int x, int y) = 0;//输入管脚是否在鼠标下
	bool outputUnderMouse(int x, int y);//输出管脚是否在鼠标下
	void setFocused();//设为被选中
	void setUnfocused();//设为未被选中
	bool isFocused();//是否为选中状态
	void setPre(int i,int preid);//记录与第i个输入管脚相连的组件的编号
	int getPre(int i);//获取与第i个输入管脚相连的组件的编号
	int getInputX(int i);//获取第i个输入管脚在窗口中的横坐标
	int getInputY(int i);//获取第i个输入管脚在窗口中的纵坐标
	int getOutputX();//获取输出管脚在窗口中的横坐标
	int getOutputY();//获取输入管脚在窗口中的纵坐标
	virtual int getN() = 0;
	~widget();
};