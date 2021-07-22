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

void mouse::check(unordered_map<int, widget*> &widgets)//�������¼�
{
    if (MouseHit())//��ǰ�������Ϣ
    {
        mm = GetMouseMsg();//���������¼�
        if (mm.uMsg == WM_LBUTTONDOWN)//����¼�Ϊ������������
        {
            if (getMouseX() >= 0 && getMouseX() < 960 && getMouseY() > 640 && getMouseY() <= 720)//������������а���������
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
                    printer.print_ui();//���������
                    printer.print_lines(widgets);//��������
                    printer.print_widgets(widgets);//�������
                    printer.print_outputvalue(widgets);//����ÿ����������ֵ
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
                                distributor.new_and(widgets, getMouseX(), getMouseY());//�������
                                break;
                            case 2:
                                distributor.new_or(widgets, getMouseX(), getMouseY());
                                break;
                            case 3:
                                distributor.new_not(widgets, getMouseX(), getMouseY());
                                break;
                            case 4:
                                distributor.new_input(widgets, getMouseX(), getMouseY());
                                break;
                            case 5:
                                distributor.new_output(widgets, getMouseX(), getMouseY());
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
                int x = getMouseX();//��¼�������λ��
                int y = getMouseY();
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
                                printer.print_widgets(widgets);
                                printer.print_outputvalue(widgets);
                                printer.print_line(x, y, getMouseX(), getMouseY());//������
                                printer.print_ui();
                                printer.print_lines(widgets);
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//��⵽�������ɿ�
                                {
                                    unordered_map<int, widget*>::iterator it2;
                                    for (it2 = widgets.begin(); it2 != widgets.end(); it2++)//�����������
                                    {
                                        if (it2->second->inputUnderMouse(getMouseX(), getMouseY()) > 0)//���ɿ���λ�������������ܽ�
                                        {
                                            it2->second->setPre(it2->second->inputUnderMouse(getMouseX(), getMouseY()), it->second->get_id());//�����������
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
                                printer.print_widgets(widgets);
                                printer.print_outputvalue(widgets);
                                printer.print_line(x, y, getMouseX(), getMouseY());//������
                                printer.print_ui();
                                printer.print_lines(widgets);
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//��⵽�������ɿ�
                                {
                                    unordered_map<int, widget*>::iterator it2;
                                    for (it2 = widgets.begin(); it2 != widgets.end(); it2++)
                                    {
                                        if (it2->second->outputUnderMouse(getMouseX(), getMouseY()))//���ɿ���λ�������������ܽ�
                                        {
                                            it->second->setPre(it->second->inputUnderMouse(x,y), it2->second->get_id());//�����������
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
                                it->second->set_x(getMouseX() - x + wx);//���¸������λ��Ϊ����ĳ�ʼλ��+����λ�ƣ���ʵ����������ͬ���ƶ�
                                it->second->set_y(getMouseY() - y + wy);
                                cleardevice();
                                printer.print_ui();
                                printer.print_lines(widgets);
                                printer.print_widgets(widgets);
                                printer.print_outputvalue(widgets);
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//����������ɿ�
                                {
                                    if (it->second->get_y() > 640)//����������ɿ���Ҫ�������ɾ��
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
                                    else if (it->second->get_y() + it->second->get_size_y() > 640)//���������ɿ�
                                        it->second->set_y(640 - it->second->get_size_y());//��������Ƶ����Ḳ��������λ��
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