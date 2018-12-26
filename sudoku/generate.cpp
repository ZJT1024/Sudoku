
#include "stdafx.h"
#include "headFile.h"
#include "generate.h"

using namespace std;

int move_step[80][Maxm];
int permutation[Maxn][Maxm];


void Swap(int & a, int & b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Permutate_for_temp(int source[], int start, int end, int target[6][3], int& line)
{
	if (start == end)
	{
		for (int i = 0; i <= end; i++)
		{
			target[line][i] = source[i];
		}
		line++;
	}
	else
	{
		for (int i = start; i <= end; i++)
		{
			Swap(source[i], source[start]);
			Permutate_for_temp(source, start + 1, end, target, line);
			Swap(source[i], source[start]);
		}
	}
}

void Permutate_for_move_step(int temp1[2][2], int temp2[6][3], int temp3[6][3], int max_num, int move_step[80][Maxm])
{
	int cnt = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				for (int r = 0; r < 8; r++)
				{
					if (r < 2)
					{
						move_step[cnt][r] = temp1[i][r];
					}
					else if (r < 5)
					{
						move_step[cnt][r] = temp2[j][r - 2];
					}
					else
					{
						move_step[cnt][r] = temp3[k][r - 5];
					}
				}
				cnt++;
				if (cnt >= max_num)
				{
					return;
				}
			}
		}
	}
}

void Permutate_for_permutation(int source[], int start, int end, int target[Maxn][Maxm], int& line, int max_num)
{
	if (start == end)
	{
		for (int i = 0; i <= end; i++)
		{
			target[line][i] = source[i];
		}
		line++;
	}
	else
	{
		for (int i = start; i <= end; i++)
		{
			if (line >= max_num)
			{
				return;
			}

			Swap(source[i], source[start]);
			Permutate_for_permutation(source, start + 1, end, target, line, max_num);
			Swap(source[i], source[start]);
		}
	}
}

void FillTheMoveStep(const int max_num, int move_step[80][Maxm])
{
	int source2[] = { 1 , 4 , 7 }, source3[] = { 2 , 5 , 8 };
	int temp1[2][2], temp2[6][3], temp3[6][3];
	int line2 = 0, line3 = 0;

	temp1[0][0] = 3, temp1[0][1] = 6;
	temp1[1][0] = 6, temp1[1][1] = 3;

	Permutate_for_temp(source2, 0, 2, temp2, line2);
	Permutate_for_temp(source3, 0, 2, temp3, line3);

	Permutate_for_move_step(temp1, temp2, temp3, max_num, move_step);
}

void FillThePermutaion(const int max_num, int permutation[Maxn][Maxm])
{
	int source[] = { first_num , 1 , 2 ,  3 , 4 , 5 , 6 , 7 , 9 };
	int line = 0;
	Permutate_for_permutation(source, 1, 8, permutation, line, max_num);
}

void FillTheBlock(int cnt, int move_step[80][Maxm], int permutation[Maxn][Maxm])
{
	int pl = cnt / 72;	//	需要的排列数量
	int ml = cnt % 72;  //	最后一个排列需要平移偏移量排列数

	for (int i = 0; i < 9; i++)		//  输出第一行
	{
		printf("%d" , permutation[pl][i]) ; 

		if (i == 8)
		{
			printf("\n") ;
		}
		else
		{
			printf(" ") ;
		}
	}

	for (int i = 1; i < 9; i++)		//  输出 2 ~ 9 行
	{
		for (int j = 0; j < 9; j++)
		{
			int site = (j + move_step[ml][i - 1]) % 9;	//  对整行进行平移（向左）
			
			printf("%d" , permutation[pl][site]) ;

			if (j == 8)
			{
				printf("\n") ;
			}
			else
			{
				printf(" ") ;
			}
		}
	}
}

void Generate(int num)
{

	FillTheMoveStep(min(num, 72), move_step);
	FillThePermutaion(num / 72 + 1, permutation);

	for (int cnt = 0; cnt < num; cnt++)
	{
		FillTheBlock(cnt, move_step, permutation);
		if (cnt != num - 1)
		{
			printf("\n");
		}

	}
}
