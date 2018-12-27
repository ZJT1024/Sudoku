#pragma once


#include "headFile.h"

using namespace std;

void Swap(int & a, int & b);	// 交换两个数的值

void Permutate_for_temp(int source[], int start, int end, int target[6][3], int& line);		//  在为2 ~ 9 行排序的函数里会用到，对每个小分区进行全排列

void Permutate_for_move_step(int temp1[2][2], int temp2[6][3], int temp3[6][3], int max_num, int move_step[80][Maxm]);  // 对2 ~ 9 行的平移偏移两进行全排列，三个temp参数将8行按2:3:3分成三份（第一行不能动）

void Permutate_for_permutation(int source[], int start, int end, int target[Maxn][Maxm], int& line, int max_num);  //  对的后8个元素进行全排列

void FillTheMoveStep(const int max_num, int move_step[80][Maxm]);  //  因为一个首行排列能产生2! x 3! x 3! = 72个数独终局，当需求量小于72时，不需要对2 ~ 8 行进行全排列

void FillThePermutaion(const int max_num, int permutation[Maxn][Maxm]);  //  因为一个首行排列能产生2! x 3! x 3! = 72个数独终局，所以只需要产生 （当前需求数/72）上取整 的首行全排列就好

void FillTheBlock(int cnt, int move_step[80][Maxm], int permutation[Maxn][Maxm]);  //  根据首行全排列和2 ~ 8 行平移偏移量全排列，进行组合，生成数独终局，并输出

void Generate(int num);  //  生成数独终局的总模块，负责调用其他模块，num为数独终局需求数量