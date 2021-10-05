#include "mouse.h"

int mouse::getMouseX()//��ȡ����ڴ����еĺ�����
{
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(hwnd, &point);
    return point.x;
}

int mouse::getMouseY()//��ȡ����ڴ����е�������
{
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(hwnd, &point);
    return point.y;
}

void mouse::check(unordered_map<int, widget*> &widgets, x_scroll_bar& xs, y_scroll_bar& ys)//�������¼�
{
    if (MouseHit())//��ǰ�������Ϣ
    {
        mm = GetMouseMsg();//���������¼�
        if (mm.uMsg == WM_LBUTTONDOWN)//����¼�Ϊ������������
        {
            if (getMouseX() >= xs.get_b_x() && getMouseX() <= xs.get_b_x() + xs.get_block_length() && getMouseY() >= xs.get_y() && getMouseY() <= xs.get_y() + xs.get_width())
            {
                int m_x = getMouseX() - xs.get_b_x();//��¼����������λ��
                while (true)//����ѭ������ʵ������϶������Ч��
                {
                    xs.set_b_x(getMouseX() - m_x);
                    if (xs.get_b_x() < 0)
                        xs.set_b_x(0);
                    else if (xs.get_b_x() + xs.get_block_length() > xs.get_length())
                        xs.set_b_x(xs.get_length() - xs.get_block_length());
                    xs.set_delta_x(double(xs.get_b_x()) * xs.get_total_w() / xs.get_length());
                    cleardevice();//����
                    printer.print_widgets(widgets, xs, ys);//�������
                    printer.print_outputvalue(widgets, xs, ys);//����ÿ����������ֵ
                    printer.print_lines(widgets, xs, ys);//��������
                    printer.print_ui();//���������
                    xs.print();//���ƺ��������
                    ys.print();//�������������
                    FlushBatchDraw();//ִ�л�������
                    mm = GetMouseMsg();//��ȡ���µ�����¼�
                    if (mm.uMsg == WM_LBUTTONUP)//��⵽�������ɿ�
                        break;
                }
            }
            else if (getMouseY() >= ys.get_b_y() && getMouseY() <= ys.get_b_y() + ys.get_block_length() && getMouseX() >= ys.get_x() && getMouseX() <= ys.get_x() + ys.get_width())
            {
                int m_y = getMouseY() - ys.get_b_y();//��¼����������λ��
                while (true)//����ѭ������ʵ������϶������Ч��
                {
                    ys.set_b_y(getMouseY() - m_y);
                    if (ys.get_b_y() < 0)
                        ys.set_b_y(0);
                    else if (ys.get_b_y() + ys.get_block_length() > ys.get_length())
                        ys.set_b_y(ys.get_length() - ys.get_block_length());
                    ys.set_delta_y(double(ys.get_b_y()) * ys.get_total_h() / ys.get_length());
                    cleardevice();//����
                    printer.print_widgets(widgets, xs, ys);//�������
                    printer.print_outputvalue(widgets, xs, ys);//����ÿ����������ֵ
                    printer.print_lines(widgets, xs, ys);//��������
                    printer.print_ui();//���������
                    xs.print();//���ƺ��������
                    ys.print();//�������������
                    FlushBatchDraw();//ִ�л�������
                    mm = GetMouseMsg();//��ȡ���µ�����¼�
                    if (mm.uMsg == WM_LBUTTONUP)//��⵽�������ɿ�
                        break;
                }
            }
            else if (getMouseX() >= 0 && getMouseX() < 960 && getMouseY() > 640 && getMouseY() <= 720)//������������а���������
            {
                clearFocus(widgets);//��������������ѡ��
                int t;
                if (getMouseX() < 190)//����λ�ü��ѡ������ĸ����
                    t = 1;
                else if (getMouseX() < 380)
                    t = 2;
                else if (getMouseX() < 570)
                    t = 3;
                else if (getMouseX() < 760)
                    t = 4;
                else
                    t = 5;
                while (true)//����ѭ������ʵ������϶������Ч��
                {
                    cleardevice();//����
                    printer.print_widgets(widgets, xs, ys);//�������
                    printer.print_outputvalue(widgets, xs, ys);//����ÿ����������ֵ
                    printer.print_lines(widgets, xs, ys);//��������
                    printer.print_ui();//���������
                    xs.print();//���ƺ��������
                    ys.print();//�������������
                    switch (t)//����ѡ�е�����ı��
                    {
                    case 1:
                        printer.print_and(getMouseX(), getMouseY());//�������
                        break;
                    case 2:
                        printer.print_or(getMouseX(), getMouseY());
                        break;
                    case 3:
                        printer.print_not(getMouseX(), getMouseY());
                        break;
                    case 4:
                        printer.print_input(getMouseX(), getMouseY());
                        break;
                    case 5:
                        printer.print_output(getMouseX(), getMouseY());
                        break;
                    default:
                        break;
                    }
                    FlushBatchDraw();//ִ�л�������
                    mm = GetMouseMsg();//��ȡ���µ�����¼�
                    if (mm.uMsg == WM_LBUTTONUP)//��⵽�������ɿ�
                    {
                        if (getMouseY() <= 640 - 64)//����������ϵĵط��������ƿ����ɿ�
                        {
                            switch (t)//����ѡ�е�����ı��
                            {
                            case 1:
                                distributor.new_and(widgets, getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y());//�������
                                break;
                            case 2:
                                distributor.new_or(widgets, getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y());
                                break;
                            case 3:
                                distributor.new_not(widgets, getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y());
                                break;
                            case 4:
                                distributor.new_input(widgets, getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y());
                                break;
                            case 5:
                                distributor.new_output(widgets, getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y());
                                break;
                            default:
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else if (getMouseX() >= 0 && getMouseX() < 960 && getMouseY() >= 0 && getMouseY() <= 640)//�ڻ��ƿ��ڵ��������
            {
                int x = getMouseX() + xs.get_delta_x();//��¼�������λ��
                int y = getMouseY() + ys.get_delta_y();
                clearFocus(widgets);//��������������ѡ��
                unordered_map<int, widget*>::iterator it;
                for (it = widgets.begin(); it != widgets.end(); it++)//�������������δʵ�����ͼ˳���෴��
                {
                    if (it->second->underMouse(x,y))//�������λ�������
                    {
                        if (it->second->outputUnderMouse(x, y))//�ҵ����λ�������������ܽ�
                        {
                            while (true)//����ѭ������ʵ�������ק���ߵ�Ч��
                            {
                                cleardevice();
                                printer.print_widgets(widgets, xs, ys);
                                printer.print_outputvalue(widgets, xs, ys);
                                printer.print_line(x - xs.get_delta_x(), y - ys.get_delta_y(), getMouseX(), getMouseY());//������
                                printer.print_ui();
                                printer.print_lines(widgets, xs, ys);
                                xs.print();//���ƺ��������
                                ys.print();//�������������
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//��⵽�������ɿ�
                                {
                                    unordered_map<int, widget*>::iterator it2;
                                    for (it2 = widgets.begin(); it2 != widgets.end(); it2++)//�����������
                                    {
                                        if (it2->second->inputUnderMouse(getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y()) > 0)//���ɿ���λ�������������ܽ�
                                        {
                                            it2->second->setPre(it2->second->inputUnderMouse(getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y()), it->second->get_id());//�����������
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        else if (it->second->inputUnderMouse(x, y) > 0)//�������λ�������������ܽ�
                        {
                            while (true)//����ѭ������ʵ�������ק���ߵ�Ч��
                            {
                                cleardevice();
                                printer.print_widgets(widgets, xs, ys);
                                printer.print_outputvalue(widgets, xs, ys);
                                printer.print_line(x - xs.get_delta_x(), y - ys.get_delta_y(), getMouseX(), getMouseY());//������
                                printer.print_ui();
                                printer.print_lines(widgets, xs, ys);
                                xs.print();//���ƺ��������
                                ys.print();//�������������
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//��⵽�������ɿ�
                                {
                                    unordered_map<int, widget*>::iterator it2;
                                    for (it2 = widgets.begin(); it2 != widgets.end(); it2++)
                                    {
                                        if (it2->second->outputUnderMouse(getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y()))//���ɿ���λ�������������ܽ�
                                        {
                                            it->second->setPre(it->second->inputUnderMouse(x,y) + xs.get_delta_x(), it2->second->get_id() + ys.get_delta_y());//�����������
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        else//�������λ�����������
                        {
                            it->second->setFocused();//����Ϊѡ�и����
                            int wx = it->second->get_x(), wy = it->second->get_y();//��¼�������ʱ�������λ��
                            while (true)//����ѭ������ʵ������϶������Ч��
                            {
                                it->second->set_x(getMouseX() - x + wx + xs.get_delta_x());//���¸������λ��Ϊ����ĳ�ʼλ��+����λ�ƣ���ʵ����������ͬ���ƶ�
                                it->second->set_y(getMouseY() - y + wy + ys.get_delta_y());
                                cleardevice();
                                printer.print_widgets(widgets, xs, ys);//�������
                                printer.print_outputvalue(widgets, xs, ys);//����ÿ����������ֵ
                                printer.print_lines(widgets, xs, ys);//��������
                                printer.print_ui();//���������
                                xs.print();//���ƺ��������
                                ys.print();//�������������
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//����������ɿ�
                                {
                                    if (it->second->get_y() > 640 + ys.get_delta_y())//����������ɿ���Ҫ�������ɾ��
                                    {
                                        unordered_map<int, widget*>::iterator it3;
                                        for (it3 = widgets.begin(); it3 != widgets.end(); it3++)//�����������
                                        {
                                            for (int i = 0; i < it3->second->getN(); i++)//����Щ�������������ܽ�
                                            {
                                                int t = it3->second->getPre(i);
                                                if (it3->second->getPre(i) == it->first)//����뱻�϶��������
                                                    it3->second->setPre(i+1, -1);//ȡ������
                                            }
                                        }
                                        if (distributor.get_i() > it->first)//�������������
                                            distributor.set_i(it->first);
                                        widgets.erase(it);//ɾ��������϶������
                                    }
                                    else if (it->second->get_y() + it->second->get_size_y() > 640 + ys.get_delta_y())//���������ɿ�
                                        it->second->set_y(640 + ys.get_delta_y() - it->second->get_size_y());//��������Ƶ����Ḳ��������λ��
                                    else if (x==getMouseX() && y==getMouseY() && it->second->get_type()==4)//���������������û�б��ƶ������������������
                                        it->second->setValue(!it->second->getOutputValue(widgets));//�����ֵȡ����ʵ�ֵ������ˣ�����˵�ֵ
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

void mouse::clearFocus(unordered_map<int, widget*>& widgets)//��������������ѡ��
{
    unordered_map<int, widget*>::iterator it2;
    for (it2 = widgets.begin(); it2 != widgets.end(); it2++)//�����������
    {
        it2->second->setUnfocused();//����۽�
    }
}