#pragma once

#include "Point.h"
#include "headFile.h"

using namespace std;

void SetMark(int str[Maxm][Maxm], const int& site, const int& num, const int flag);  //  将数组的site行，num列置为flag，具体意义需要结合str代替的是那个数组

int GetBlockNum(const int& x, const int& y);  // 根据元素的行号和列号得到该元素所在小九宫格号（顺序从0开始，从左到右，从上到下）

int CheckNum(const int& rm, const int& cm, const int& bm);  // rm，cm，bm为打表时记录的数据，该函数根据这三个数据返回是否接受当前的试探数字（DFS里用）

bool DFS(Point p[], const int& num, int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm], int step, int block[Maxm][Maxm]);  // 对每个空位进行回溯搜索，当找到一个可行解就停止

void Output(int block[Maxm][Maxm]);  //  输出可行解

bool Cmp(Point& x, Point& y);  // 根绝两个点的num属性进行大小比较，用于对空位数组进行排序，num（周围已知数字）大的在前，降低回溯的可能

void  Solve();  // 解决数独残局的主要模块，调用其他模块
