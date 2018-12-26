#pragma once

#include "headFile.h"

using namespace std;

typedef struct Point
{
	int row;	//  所在行
	int col;	//  所在列
	int num;	//  该空格所在行、列、小九宫格中的由题已知的数字的总和
}Point;