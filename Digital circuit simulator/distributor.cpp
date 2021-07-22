#include "distributor.h"

distributor::distributor()
{
	i = 0;//��Ŵ�0��ʼ
}

int distributor::get_i()
{
	return i;
}

void distributor::set_i(int _i)
{
	i = _i;
}

void distributor::fresh_i(unordered_map<int, widget*> &widgets)//ˢ��i����i����Ϊ��i����δ��ʹ�õ���Сi
{
	while (widgets.find(i)!=widgets.end())
	{
		i++;
	}
}

void distributor::new_and(unordered_map<int, widget*> &widgets,int x,int y)//��������
{
	AND* t = new AND;//�����ڴ�ռ�
	t->set_id(get_i());
	t->set_x(x);
	t->set_y(y);
	widgets[get_i()] = t;//��ӵ�widgets������
	fresh_i(widgets);//ˢ��i
}

void distributor::new_or(unordered_map<int, widget*>& widgets, int x, int y)
{
	OR* t = new OR;
	t->set_id(get_i());
	t->set_x(x);
	t->set_y(y);
	widgets[get_i()] = t;
	fresh_i(widgets);
}

void distributor::new_not(unordered_map<int, widget*>& widgets, int x, int y)
{
	NOT* t = new NOT;
	t->set_id(get_i());
	t->set_x(x);
	t->set_y(y);
	widgets[get_i()] = t;
	fresh_i(widgets);
}

void distributor::new_input(unordered_map<int, widget*>& widgets, int x, int y)
{
	input *t=new input;
	t->set_id(get_i());
	t->set_x(x);
	t->set_y(y);
	widgets[get_i()] = t;
	fresh_i(widgets);
}

void distributor::new_output(unordered_map<int, widget*>& widgets, int x, int y)
{
	output *t=new output;
	t->set_id(get_i());
	t->set_x(x);
	t->set_y(y);
	widgets[get_i()] = t;
	fresh_i(widgets);
}