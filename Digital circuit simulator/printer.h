#pragma once
#include <graphics.h>
#include <unordered_map>
#include "widget.h"
using namespace std;
class printer//��ͼ��
{
protected:
	IMAGE andimg, orimg, notimg, inputimg, outputimg, andfimg, orfimg, notfimg, inputfimg, outputfimg;
public:
	printer();
	void print_ui();//���������
	void print_widgets(unordered_map<int, widget*> &widgets);//�������
	void print_and(int x, int y);//��������
	void print_not(int x, int y);//���Ʒ���
	void print_or(int x, int y);//���ƻ���
	void print_input(int x, int y);//���������
	void print_output(int x, int y);//���������
	void print_andf(int x, int y);//���Ʊ�ѡ��״̬������
	void print_notf(int x, int y);//���Ʊ�ѡ��״̬�ķ���
	void print_orf(int x, int y);//���Ʊ�ѡ��״̬�Ļ���
	void print_inputf(int x, int y);//���Ʊ�ѡ��״̬�������
	void print_outputf(int x, int y);//���Ʊ�ѡ��״̬�������
	void print_lines(unordered_map<int, widget*>& widgets);//������������
	void print_line(int x1, int y1, int x2, int y2);//��������������һ������
	void print_outputvalue(unordered_map<int, widget*>& widgets);//����ÿ����������ֵ
};