#include "distributor.h"

distributor::distributor()
{
	i = 0;//编号从0开始
}

int distributor::get_i()
{
	return i;
}

void distributor::set_i(int _i)
{
	i = _i;
}

void distributor::fresh_i(unordered_map<int, widget*> &widgets)//刷新i，将i更新为比i大且未被使用的最小i
{
	while (widgets.find(i)!=widgets.end())
	{
		i++;
	}
}

void distributor::new_and(unordered_map<int, widget*> &widgets,int x,int y)//创建与门
{
	AND* t = new AND;//分配内存空间
	t->set_id(get_i());
	t->set_x(x);
	t->set_y(y);
	widgets[get_i()] = t;//添加到widgets容器中
	fresh_i(widgets);//刷新i
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