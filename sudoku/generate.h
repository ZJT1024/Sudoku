#pragma once


#include "headFile.h"

using namespace std;

void Swap(int & a, int & b);	// ������������ֵ

void Permutate_for_temp(int source[], int start, int end, int target[6][3], int& line);		//  ��Ϊ2 ~ 9 ������ĺ�������õ�����ÿ��С��������ȫ����

void Permutate_for_move_step(int temp1[2][2], int temp2[6][3], int temp3[6][3], int max_num, int move_step[80][Maxm]);  // ��2 ~ 9 �е�ƽ��ƫ��������ȫ���У�����temp������8�а�2:3:3�ֳ����ݣ���һ�в��ܶ���

void Permutate_for_permutation(int source[], int start, int end, int target[Maxn][Maxm], int& line, int max_num);  //  �Եĺ�8��Ԫ�ؽ���ȫ����

void FillTheMoveStep(const int max_num, int move_step[80][Maxm]);  //  ��Ϊһ�����������ܲ���2! x 3! x 3! = 72�������վ֣���������С��72ʱ������Ҫ��2 ~ 8 �н���ȫ����

void FillThePermutaion(const int max_num, int permutation[Maxn][Maxm]);  //  ��Ϊһ�����������ܲ���2! x 3! x 3! = 72�������վ֣�����ֻ��Ҫ���� ����ǰ������/72����ȡ�� ������ȫ���оͺ�

void FillTheBlock(int cnt, int move_step[80][Maxm], int permutation[Maxn][Maxm]);  //  ��������ȫ���к�2 ~ 8 ��ƽ��ƫ����ȫ���У�������ϣ����������վ֣������

void Generate(int num);  //  ���������վֵ���ģ�飬�����������ģ�飬numΪ�����վ���������