#include "widget.h"

int widget::get_id()
{
	return id;
}
void widget::set_id(int _id)
{
	id = _id;
}

int widget::get_x()
{
	return x;
}
void widget::set_x(int _x)
{
	x = _x;
}

int widget::get_y()
{
	return y;
}

void widget::set_y(int _y)
{
	y = _y;
}

int widget::get_size_x()
{
	return size_x;
}

int widget::get_size_y()
{
	return size_y;
}

int widget::get_type()
{
	return type;
}

bool widget::underMouse(int _x, int _y)//����Ƿ�������£�_x,_yΪ�������
{
	if (_x >= x && _x <= x + size_x && _y >= y && _y <= y + size_y)
		return true;
	else
		return false;
}

bool widget::outputUnderMouse(int _x, int _y)//���������Ƿ�������£�_x,_yΪ�������
{
	int outx = x + output_x;
	int outy = y + output_y;
	if ((_x - outx) * (_x - outx) + (_y - outy) * (_y - outy) <= 25)
		return true;
	else
		return false;
}

void widget::setFocused()
{
	focused = true;
}

void widget::setUnfocused()
{
	focused = false;
}

bool widget::isFocused()
{
	return focused;
}

void widget::setPre(int i, int preid)//��¼���i������ܽ�����������ı��preid
{
	pre[i-1] = preid;
}

int widget::getPre(int i)//��ȡ���i������ܽ�����������ı��
{
	return pre[i];
}

int widget::getInputX(int i)//��ȡ��i������ܽ��ڴ����еĺ�����
{
	return x+input_x[i];
}

int widget::getInputY(int i)//��ȡ��i������ܽ��ڴ����е�������
{
	return y+input_y[i];
}

int widget::getOutputX()//��ȡ����ܽ��ڴ����еĺ�����
{
	return x+output_x;
}

int widget::getOutputY()//��ȡ����ܽ��ڴ����е�������
{
	return y+output_y;
}

widget::~widget()
{
	delete[]pre;
	delete[]input_x;
	delete[]input_y;
}