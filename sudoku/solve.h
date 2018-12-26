#pragma once

#include "Point.h"
#include "headFile.h"

using namespace std;

void SetMark(int str[Maxm][Maxm], const int& site, const int& num, const int flag);

int GetBlockNum(const int& x, const int& y);

int CheckNum(const int& rm, const int& cm, const int& bm);

int DFS(Point p[], const int& num, int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm], int step, int block[Maxm][Maxm]);

void Output(int block[Maxm][Maxm]);

void  Solve();