#pragma once

#include "Point.h"
#include "headFile.h"

using namespace std;

void SetMark(int str[Maxm][Maxm], const int& site, const int& num, const int flag);  //  �������site�У�num����Ϊflag������������Ҫ���str��������Ǹ�����

int GetBlockNum(const int& x, const int& y);  // ����Ԫ�ص��кź��кŵõ���Ԫ������С�Ź���ţ�˳���0��ʼ�������ң����ϵ��£�

int CheckNum(const int& rm, const int& cm, const int& bm);  // rm��cm��bmΪ���ʱ��¼�����ݣ��ú����������������ݷ����Ƿ���ܵ�ǰ����̽���֣�DFS���ã�

bool DFS(Point p[], const int& num, int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm], int step, int block[Maxm][Maxm]);  // ��ÿ����λ���л������������ҵ�һ�����н��ֹͣ

void Output(int block[Maxm][Maxm]);  //  ������н�

bool Cmp(Point& x, Point& y);  // �����������num���Խ��д�С�Ƚϣ����ڶԿ�λ�����������num����Χ��֪���֣������ǰ�����ͻ��ݵĿ���

void  Solve();  // ��������оֵ���Ҫģ�飬��������ģ��
