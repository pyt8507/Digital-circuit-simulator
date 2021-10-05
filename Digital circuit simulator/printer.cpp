#include "printer.h"

printer::printer()//构造函数，读取所有组件的图像
{
	loadimage(&andimg, _T("src\\and.png"));//使用库函数，读取组件的图像
	loadimage(&andfimg, _T("src\\and_focused.png"));
	loadimage(&orimg, _T("src\\or.png"));
	loadimage(&orfimg, _T("src\\or_focused.png"));
	loadimage(&notimg, _T("src\\not.png"));
	loadimage(&notfimg, _T("src\\not_focused.png"));
	loadimage(&inputimg, _T("src\\input.png"));
	loadimage(&inputfimg, _T("src\\input_focused.png"));
	loadimage(&outputimg, _T("src\\output.png"));
	loadimage(&outputfimg, _T("src\\output_focused.png"));
}

void printer::print_ui()//绘制组件框
{
	line(0, 640, 960, 640);
	line(190, 640, 190, 720);
	line(380, 640, 380, 720);
	line(570, 640, 570, 720);
	line(760, 640, 760, 720);
	putimage(40, 650, &andimg);
	putimage(230, 650, &orimg);
	putimage(420, 650, &notimg);
	putimage(610, 675, &inputimg);
	putimage(800, 675, &outputimg);
}

void printer::print_widgets(unordered_map<int, widget*> &widgets, x_scroll_bar& xs, y_scroll_bar& ys)//绘制组件
{
	unordered_map<int, widget*>::iterator it;
	for (it = widgets.begin(); it != widgets.end(); it++)//遍历所有组件
	{
		int aaa = it->second->get_type();//读取组件的类型
		switch (it->second->get_type())//根据组件类型的不同绘制不同的图像
		{
		case 1:
			if (it->second->isFocused())//如果组件处于被选中状态
				print_andf(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());//绘制被选中状态的图像
			else
				print_and(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());//否则，绘制未被选中状态的图像
			break;
		case 2:
			if (it->second->isFocused())
				print_orf(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());
			else
				print_or(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());
			break;
		case 3:
			if (it->second->isFocused())
				print_notf(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());
			else
				print_not(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());
			break;
		case 4:
			if (it->second->isFocused())
				print_inputf(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());
			else
				print_input(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());
			break;
		case 5:
			if (it->second->isFocused())
				print_outputf(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());
			else
				print_output(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());
			break;
		default:
			break;
		}
	}
}

void printer::print_and(int x, int y)//绘制与门
{
	putimage(x, y, &andimg);//调用库中的函数
}

void printer::print_not(int x, int y)//绘制非门
{
	putimage(x, y, &notimg);
}

void printer::print_or(int x, int y)//绘制或门
{
	putimage(x, y, &orimg);
}

void printer::print_input(int x, int y)//绘制输入端
{
	putimage(x, y, &inputimg);
}

void printer::print_output(int x, int y)//绘制输出端
{
	putimage(x, y, &outputimg);
}

void printer::print_andf(int x, int y)//绘制被选中状态的与门
{
	putimage(x, y, &andfimg);
}

void printer::print_notf(int x, int y)//绘制被选中状态的非门
{
	putimage(x, y, &notfimg);
}

void printer::print_orf(int x, int y)//绘制被选中状态的或门
{
	putimage(x, y, &orfimg);
}

void printer::print_inputf(int x, int y)//绘制被选中状态的输入端
{
	putimage(x, y, &inputfimg);
}

void printer::print_outputf(int x, int y)//绘制被选中状态的输出端
{
	putimage(x, y, &outputfimg);
}

void printer::print_lines(unordered_map<int, widget*>& widgets, x_scroll_bar& xs, y_scroll_bar& ys)//绘制连线
{
	unordered_map<int, widget*>::iterator it;
	for (it = widgets.begin(); it != widgets.end(); it++)//遍历每个组件
	{
		for (int i = 0; i < it->second->getN(); i++)//对于该组件的每个输入管脚
		{
			if(it->second->getPre(i)!=-1)//如果有连接东西
				print_line(widgets[it->second->getPre(i)]->getOutputX() - xs.get_delta_x(), widgets[it->second->getPre(i)]->getOutputY() - ys.get_delta_y(), it->second->getInputX(i) - xs.get_delta_x(), it->second->getInputY(i) - ys.get_delta_y());//绘制连线
		}
	}
}

void printer::print_line(int x1, int y1, int x2, int y2)//绘制两个组件间的连线时，不直接画直线，而是画折线，符合数字逻辑电路的绘图要求
{
	int t;
	if(x2>x1)
		t = x1 + abs(x2 - x1) * abs(y2 - y1) / 720;
	else
		t = x1 - abs(x2 - x1) * abs(y2 - y1) / 720;
	line(x1, y1, t, y1);//调用库中的函数画直线
	line(t, y1, t, y2);
	line(t, y2, x2, y2);
}

void printer::print_outputvalue(unordered_map<int, widget*>& widgets, x_scroll_bar& xs, y_scroll_bar& ys)//绘制每个组件的输出值
{
	unordered_map<int, widget*>::iterator it;
	for (it = widgets.begin(); it != widgets.end(); it++)//遍历每个组件
	{
		int s = widgets.size();
		if (it->second->getOutputValue(widgets) != -1)//如果该组件的有输出值
		{
			char v = it->second->getOutputValue(widgets) + '0';//输出值转为char类型
			outtextxy(it->second->getOutputX() - xs.get_delta_x(), it->second->getOutputY() - 20 - ys.get_delta_y(), v);//调用库的函数，绘制输出值
		}
		else
			outtextxy(it->second->getOutputX() - xs.get_delta_x(), it->second->getOutputY() - 20 - ys.get_delta_y(), '-');//没有输出值，调用库的函数绘制一个“-”号
	}
}