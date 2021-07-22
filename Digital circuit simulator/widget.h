#pragma once
#include <unordered_map>
using namespace std;
class widget
{
protected:
	int id;//���
	int type;//������� 1:���� 2:���� 3:���� 4:����� 5:�����
	int x;//λ�ú�����
	int y;//λ��������
	int size_x;//���
	int size_y;//�߶�
	int n;//����ܽŸ���
	int* pre = new int[n];//���������������������id
	int* input_x = new int[n];//����ܽ�������еĺ�����
	int* input_y = new int[n];//����ܽ�������е�������
	int output_x;//����ܽ�������еĺ�����
	int output_y;//����ܽ�������е�������
	bool focused = false;//��ѡ�еı��

public:
	int get_id();
	void set_id(int _id);
	int get_x();
	void set_x(int _x);
	int get_y();
	void set_y(int _y);
	int get_size_x();
	int get_size_y();
	int get_type();
	virtual int getOutputValue(unordered_map<int, widget*>& widgets) = 0;//��ȡ���ֵ
	virtual void setValue(int v) = 0;//��������˵�ֵ
	bool underMouse(int x,int y);//�Ƿ��������
	virtual int inputUnderMouse(int x, int y) = 0;//����ܽ��Ƿ��������
	bool outputUnderMouse(int x, int y);//����ܽ��Ƿ��������
	void setFocused();//��Ϊ��ѡ��
	void setUnfocused();//��Ϊδ��ѡ��
	bool isFocused();//�Ƿ�Ϊѡ��״̬
	void setPre(int i,int preid);//��¼���i������ܽ�����������ı��
	int getPre(int i);//��ȡ���i������ܽ�����������ı��
	int getInputX(int i);//��ȡ��i������ܽ��ڴ����еĺ�����
	int getInputY(int i);//��ȡ��i������ܽ��ڴ����е�������
	int getOutputX();//��ȡ����ܽ��ڴ����еĺ�����
	int getOutputY();//��ȡ����ܽ��ڴ����е�������
	virtual int getN() = 0;
	~widget();
};