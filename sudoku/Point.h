#pragma once

#include "headFile.h"

using namespace std;

class Point
{
private:
	int row;
	int col;
	int num;	//  �ÿո������С��С�С�Ź����е�������֪�����ֵ��ܺ�

public:
	Point()noexcept;

	Point(const Point& a);

	void Set_row(const int & x);

	void Set_col(const int & y);

	void Set_num(const int & n);

	int Get_row();

	int Get_col();

	int Get_num();

	bool operator < (const Point& p)const;
};