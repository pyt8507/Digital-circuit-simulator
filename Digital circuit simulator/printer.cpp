#include "printer.h"

printer::printer()//���캯������ȡ���������ͼ��
{
	loadimage(&andimg, _T("src\\and.png"));//ʹ�ÿ⺯������ȡ�����ͼ��
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

void printer::print_ui()//���������
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

void printer::print_widgets(unordered_map<int, widget*> &widgets, x_scroll_bar& xs, y_scroll_bar& ys)//�������
{
	unordered_map<int, widget*>::iterator it;
	for (it = widgets.begin(); it != widgets.end(); it++)//�����������
	{
		int aaa = it->second->get_type();//��ȡ���������
		switch (it->second->get_type())//����������͵Ĳ�ͬ���Ʋ�ͬ��ͼ��
		{
		case 1:
			if (it->second->isFocused())//���������ڱ�ѡ��״̬
				print_andf(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());//���Ʊ�ѡ��״̬��ͼ��
			else
				print_and(it->second->get_x() - xs.get_delta_x(), it->second->get_y() - ys.get_delta_y());//���򣬻���δ��ѡ��״̬��ͼ��
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

void printer::print_and(int x, int y)//��������
{
	putimage(x, y, &andimg);//���ÿ��еĺ���
}

void printer::print_not(int x, int y)//���Ʒ���
{
	putimage(x, y, &notimg);
}

void printer::print_or(int x, int y)//���ƻ���
{
	putimage(x, y, &orimg);
}

void printer::print_input(int x, int y)//���������
{
	putimage(x, y, &inputimg);
}

void printer::print_output(int x, int y)//���������
{
	putimage(x, y, &outputimg);
}

void printer::print_andf(int x, int y)//���Ʊ�ѡ��״̬������
{
	putimage(x, y, &andfimg);
}

void printer::print_notf(int x, int y)//���Ʊ�ѡ��״̬�ķ���
{
	putimage(x, y, &notfimg);
}

void printer::print_orf(int x, int y)//���Ʊ�ѡ��״̬�Ļ���
{
	putimage(x, y, &orfimg);
}

void printer::print_inputf(int x, int y)//���Ʊ�ѡ��״̬�������
{
	putimage(x, y, &inputfimg);
}

void printer::print_outputf(int x, int y)//���Ʊ�ѡ��״̬�������
{
	putimage(x, y, &outputfimg);
}

void printer::print_lines(unordered_map<int, widget*>& widgets, x_scroll_bar& xs, y_scroll_bar& ys)//��������
{
	unordered_map<int, widget*>::iterator it;
	for (it = widgets.begin(); it != widgets.end(); it++)//����ÿ�����
	{
		for (int i = 0; i < it->second->getN(); i++)//���ڸ������ÿ������ܽ�
		{
			if(it->second->getPre(i)!=-1)//��������Ӷ���
				print_line(widgets[it->second->getPre(i)]->getOutputX() - xs.get_delta_x(), widgets[it->second->getPre(i)]->getOutputY() - ys.get_delta_y(), it->second->getInputX(i) - xs.get_delta_x(), it->second->getInputY(i) - ys.get_delta_y());//��������
		}
	}
}

void printer::print_line(int x1, int y1, int x2, int y2)//������������������ʱ����ֱ�ӻ�ֱ�ߣ����ǻ����ߣ����������߼���·�Ļ�ͼҪ��
{
	int t;
	if(x2>x1)
		t = x1 + abs(x2 - x1) * abs(y2 - y1) / 720;
	else
		t = x1 - abs(x2 - x1) * abs(y2 - y1) / 720;
	line(x1, y1, t, y1);//���ÿ��еĺ�����ֱ��
	line(t, y1, t, y2);
	line(t, y2, x2, y2);
}

void printer::print_outputvalue(unordered_map<int, widget*>& widgets, x_scroll_bar& xs, y_scroll_bar& ys)//����ÿ����������ֵ
{
	unordered_map<int, widget*>::iterator it;
	for (it = widgets.begin(); it != widgets.end(); it++)//����ÿ�����
	{
		int s = widgets.size();
		if (it->second->getOutputValue(widgets) != -1)//���������������ֵ
		{
			char v = it->second->getOutputValue(widgets) + '0';//���ֵתΪchar����
			outtextxy(it->second->getOutputX() - xs.get_delta_x(), it->second->getOutputY() - 20 - ys.get_delta_y(), v);//���ÿ�ĺ������������ֵ
		}
		else
			outtextxy(it->second->getOutputX() - xs.get_delta_x(), it->second->getOutputY() - 20 - ys.get_delta_y(), '-');//û�����ֵ�����ÿ�ĺ�������һ����-����
	}
}