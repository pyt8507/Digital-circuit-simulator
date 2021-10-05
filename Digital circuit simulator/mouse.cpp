#include "mouse.h"

int mouse::getMouseX()//获取鼠标在窗口中的横坐标
{
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(hwnd, &point);
    return point.x;
}

int mouse::getMouseY()//获取鼠标在窗口中的纵坐标
{
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(hwnd, &point);
    return point.y;
}

void mouse::check(unordered_map<int, widget*> &widgets, x_scroll_bar& xs, y_scroll_bar& ys)//检查鼠标事件
{
    if (MouseHit())//当前有鼠标消息
    {
        mm = GetMouseMsg();//保存该鼠标事件
        if (mm.uMsg == WM_LBUTTONDOWN)//鼠标事件为鼠标左键被按下
        {
            if (getMouseX() >= xs.get_b_x() && getMouseX() <= xs.get_b_x() + xs.get_block_length() && getMouseY() >= xs.get_y() && getMouseY() <= xs.get_y() + xs.get_width())
            {
                int m_x = getMouseX() - xs.get_b_x();//记录点击鼠标的相对位置
                while (true)//进入循环，以实现鼠标拖动滑块的效果
                {
                    xs.set_b_x(getMouseX() - m_x);
                    if (xs.get_b_x() < 0)
                        xs.set_b_x(0);
                    else if (xs.get_b_x() + xs.get_block_length() > xs.get_length())
                        xs.set_b_x(xs.get_length() - xs.get_block_length());
                    xs.set_delta_x(double(xs.get_b_x()) * xs.get_total_w() / xs.get_length());
                    cleardevice();//清屏
                    printer.print_widgets(widgets, xs, ys);//绘制组件
                    printer.print_outputvalue(widgets, xs, ys);//绘制每个组件的输出值
                    printer.print_lines(widgets, xs, ys);//绘制连线
                    printer.print_ui();//绘制组件框
                    xs.print();//绘制横向滚动条
                    ys.print();//绘制纵向滚动条
                    FlushBatchDraw();//执行绘制任务
                    mm = GetMouseMsg();//获取最新的鼠标事件
                    if (mm.uMsg == WM_LBUTTONUP)//检测到鼠标左键松开
                        break;
                }
            }
            else if (getMouseY() >= ys.get_b_y() && getMouseY() <= ys.get_b_y() + ys.get_block_length() && getMouseX() >= ys.get_x() && getMouseX() <= ys.get_x() + ys.get_width())
            {
                int m_y = getMouseY() - ys.get_b_y();//记录点击鼠标的相对位置
                while (true)//进入循环，以实现鼠标拖动滑块的效果
                {
                    ys.set_b_y(getMouseY() - m_y);
                    if (ys.get_b_y() < 0)
                        ys.set_b_y(0);
                    else if (ys.get_b_y() + ys.get_block_length() > ys.get_length())
                        ys.set_b_y(ys.get_length() - ys.get_block_length());
                    ys.set_delta_y(double(ys.get_b_y()) * ys.get_total_h() / ys.get_length());
                    cleardevice();//清屏
                    printer.print_widgets(widgets, xs, ys);//绘制组件
                    printer.print_outputvalue(widgets, xs, ys);//绘制每个组件的输出值
                    printer.print_lines(widgets, xs, ys);//绘制连线
                    printer.print_ui();//绘制组件框
                    xs.print();//绘制横向滚动条
                    ys.print();//绘制纵向滚动条
                    FlushBatchDraw();//执行绘制任务
                    mm = GetMouseMsg();//获取最新的鼠标事件
                    if (mm.uMsg == WM_LBUTTONUP)//检测到鼠标左键松开
                        break;
                }
            }
            else if (getMouseX() >= 0 && getMouseX() < 960 && getMouseY() > 640 && getMouseY() <= 720)//且是在组件框中按下鼠标左键
            {
                clearFocus(widgets);//清除对所有组件的选中
                int t;
                if (getMouseX() < 190)//根据位置检测选择的是哪个组件
                    t = 1;
                else if (getMouseX() < 380)
                    t = 2;
                else if (getMouseX() < 570)
                    t = 3;
                else if (getMouseX() < 760)
                    t = 4;
                else
                    t = 5;
                while (true)//进入循环，以实现鼠标拖动组件的效果
                {
                    cleardevice();//清屏
                    printer.print_widgets(widgets, xs, ys);//绘制组件
                    printer.print_outputvalue(widgets, xs, ys);//绘制每个组件的输出值
                    printer.print_lines(widgets, xs, ys);//绘制连线
                    printer.print_ui();//绘制组件框
                    xs.print();//绘制横向滚动条
                    ys.print();//绘制纵向滚动条
                    switch (t)//根据选中的组件的编号
                    {
                    case 1:
                        printer.print_and(getMouseX(), getMouseY());//绘制组件
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
                    FlushBatchDraw();//执行绘制任务
                    mm = GetMouseMsg();//获取最新的鼠标事件
                    if (mm.uMsg == WM_LBUTTONUP)//检测到鼠标左键松开
                    {
                        if (getMouseY() <= 640 - 64)//在组件框以上的地方，即绘制框内松开
                        {
                            switch (t)//根据选中的组件的编号
                            {
                            case 1:
                                distributor.new_and(widgets, getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y());//创建组件
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
            else if (getMouseX() >= 0 && getMouseX() < 960 && getMouseY() >= 0 && getMouseY() <= 640)//在绘制框内点击鼠标左键
            {
                int x = getMouseX() + xs.get_delta_x();//记录点击鼠标的位置
                int y = getMouseY() + ys.get_delta_y();
                clearFocus(widgets);//清除对所有组件的选中
                unordered_map<int, widget*>::iterator it;
                for (it = widgets.begin(); it != widgets.end(); it++)//遍历所有组件（未实现与绘图顺序相反）
                {
                    if (it->second->underMouse(x,y))//若点击的位置有组件
                    {
                        if (it->second->outputUnderMouse(x, y))//且点击的位置是组件的输出管脚
                        {
                            while (true)//进入循环，以实现鼠标拖拽连线的效果
                            {
                                cleardevice();
                                printer.print_widgets(widgets, xs, ys);
                                printer.print_outputvalue(widgets, xs, ys);
                                printer.print_line(x - xs.get_delta_x(), y - ys.get_delta_y(), getMouseX(), getMouseY());//绘制线
                                printer.print_ui();
                                printer.print_lines(widgets, xs, ys);
                                xs.print();//绘制横向滚动条
                                ys.print();//绘制纵向滚动条
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//检测到鼠标左键松开
                                {
                                    unordered_map<int, widget*>::iterator it2;
                                    for (it2 = widgets.begin(); it2 != widgets.end(); it2++)//遍历所有组件
                                    {
                                        if (it2->second->inputUnderMouse(getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y()) > 0)//若松开的位置是组件的输入管脚
                                        {
                                            it2->second->setPre(it2->second->inputUnderMouse(getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y()), it->second->get_id());//关联两个组件
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        else if (it->second->inputUnderMouse(x, y) > 0)//若点击的位置是组件的输入管脚
                        {
                            while (true)//进入循环，以实现鼠标拖拽连线的效果
                            {
                                cleardevice();
                                printer.print_widgets(widgets, xs, ys);
                                printer.print_outputvalue(widgets, xs, ys);
                                printer.print_line(x - xs.get_delta_x(), y - ys.get_delta_y(), getMouseX(), getMouseY());//绘制线
                                printer.print_ui();
                                printer.print_lines(widgets, xs, ys);
                                xs.print();//绘制横向滚动条
                                ys.print();//绘制纵向滚动条
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//检测到鼠标左键松开
                                {
                                    unordered_map<int, widget*>::iterator it2;
                                    for (it2 = widgets.begin(); it2 != widgets.end(); it2++)
                                    {
                                        if (it2->second->outputUnderMouse(getMouseX() + xs.get_delta_x(), getMouseY() + ys.get_delta_y()))//若松开的位置是组件的输出管脚
                                        {
                                            it->second->setPre(it->second->inputUnderMouse(x,y) + xs.get_delta_x(), it2->second->get_id() + ys.get_delta_y());//关联两个组件
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        else//若点击的位置是组件主体
                        {
                            it->second->setFocused();//设置为选中该组件
                            int wx = it->second->get_x(), wy = it->second->get_y();//记录按下鼠标时该组件的位置
                            while (true)//进入循环，以实现鼠标拖动组件的效果
                            {
                                it->second->set_x(getMouseX() - x + wx + xs.get_delta_x());//更新该组件的位置为组件的初始位置+鼠标的位移，以实现鼠标与组件同步移动
                                it->second->set_y(getMouseY() - y + wy + ys.get_delta_y());
                                cleardevice();
                                printer.print_widgets(widgets, xs, ys);//绘制组件
                                printer.print_outputvalue(widgets, xs, ys);//绘制每个组件的输出值
                                printer.print_lines(widgets, xs, ys);//绘制连线
                                printer.print_ui();//绘制组件框
                                xs.print();//绘制横向滚动条
                                ys.print();//绘制纵向滚动条
                                FlushBatchDraw();
                                mm = GetMouseMsg();
                                if (mm.uMsg == WM_LBUTTONUP)//检测鼠标左键松开
                                {
                                    if (it->second->get_y() > 640 + ys.get_delta_y())//在组件框内松开，要将该组件删除
                                    {
                                        unordered_map<int, widget*>::iterator it3;
                                        for (it3 = widgets.begin(); it3 != widgets.end(); it3++)//遍历所有组件
                                        {
                                            for (int i = 0; i < it3->second->getN(); i++)//对这些组件的所有输入管脚
                                            {
                                                int t = it3->second->getPre(i);
                                                if (it3->second->getPre(i) == it->first)//如果与被拖动组件相连
                                                    it3->second->setPre(i+1, -1);//取消关联
                                            }
                                        }
                                        if (distributor.get_i() > it->first)//回收这个组件编号
                                            distributor.set_i(it->first);
                                        widgets.erase(it);//删除这个被拖动的组件
                                    }
                                    else if (it->second->get_y() + it->second->get_size_y() > 640 + ys.get_delta_y())//在组件框边松开
                                        it->second->set_y(640 + ys.get_delta_y() - it->second->get_size_y());//将组件上移到不会覆盖组件框的位置
                                    else if (x==getMouseX() && y==getMouseY() && it->second->get_type()==4)//如果组件仅被点击，没有被移动，且这个组件是输入端
                                        it->second->setValue(!it->second->getOutputValue(widgets));//将输出值取反，实现点击输入端，输入端的值
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

void mouse::clearFocus(unordered_map<int, widget*>& widgets)//清除对所有组件的选中
{
    unordered_map<int, widget*>::iterator it2;
    for (it2 = widgets.begin(); it2 != widgets.end(); it2++)//遍历所有组件
    {
        it2->second->setUnfocused();//清除聚焦
    }
}