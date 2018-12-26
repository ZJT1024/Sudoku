

#include "Point.h"
#include "stdafx.h"
#include "headFile.h"

using namespace std;

class Point
{
private:
	int row;
	int col;
	int num;	//  该空格所在行、列、小九宫格中的由题已知的数字的总和

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

Point::Point()noexcept
{
	row = -1;
	col = -1;
	num = -1;
}

Point::Point(const Point& a)
{
	row = a.row;
	col = a.col;
	num = a.num;
}

void Point::Set_row(const int & x)
{
	row = x;
}

void Point::Set_col(const int & y)
{
	col = y;
}

void Point::Set_num(const int & n)
{
	num = n;
}

int Point::Get_row()
{
	return row;
}

int Point::Get_col()
{
	return col;
}

int Point::Get_num()
{
	return num;
}

bool Point:: operator < (const Point& p)const
{
	return num > p.num;
}
