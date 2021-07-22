#pragma once
#include <unordered_map>
#include "widget.h"
#include "and.h"
#include "or.h"
#include "not.h"
#include "input.h"
#include "output.h"

using namespace std;

class distributor//分配器
{
private:
	int i;
public:
	distributor();
	int get_i();
	void set_i(int _i);
	void fresh_i(unordered_map<int, widget*> &widgets);//刷新i，将i更新为比i大且未被使用的最小i
	void new_and(unordered_map<int, widget*> &widgets, int x, int y);//创建与门
	void new_or(unordered_map<int, widget*>& widgets, int x, int y);//创建或门
	void new_not(unordered_map<int, widget*>& widgets, int x, int y);//创建非门
	void new_input(unordered_map<int, widget*>& widgets, int x, int y);//创建输入端
	void new_output(unordered_map<int, widget*>& widgets, int x, int y);//创建输出端
};