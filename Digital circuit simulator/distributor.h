#pragma once
#include <unordered_map>
#include "widget.h"
#include "and.h"
#include "or.h"
#include "not.h"
#include "input.h"
#include "output.h"

using namespace std;

class distributor//������
{
private:
	int i;
public:
	distributor();
	int get_i();
	void set_i(int _i);
	void fresh_i(unordered_map<int, widget*> &widgets);//ˢ��i����i����Ϊ��i����δ��ʹ�õ���Сi
	void new_and(unordered_map<int, widget*> &widgets, int x, int y);//��������
	void new_or(unordered_map<int, widget*>& widgets, int x, int y);//��������
	void new_not(unordered_map<int, widget*>& widgets, int x, int y);//��������
	void new_input(unordered_map<int, widget*>& widgets, int x, int y);//���������
	void new_output(unordered_map<int, widget*>& widgets, int x, int y);//���������
};