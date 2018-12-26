#pragma once


#include "headFile.h"

using namespace std;

void Swap(int & a, int & b);

void Permutate_for_temp(int source[], int start, int end, int target[6][3], int& line);

void Permutate_for_move_step(int temp1[2][2], int temp2[6][3], int temp3[6][3], int max_num, int move_step[80][Maxm]);

void Permutate_for_permutation(int source[], int start, int end, int target[Maxn][Maxm], int& line, int max_num);

void FillTheMoveStep(const int max_num, int move_step[80][Maxm]);

void FillThePermutaion(const int max_num, int permutation[Maxn][Maxm]);

void FillTheBlock(int cnt, int move_step[80][Maxm], int permutation[Maxn][Maxm]);

void Generate(int num);