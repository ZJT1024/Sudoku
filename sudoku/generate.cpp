
#include "stdafx.h"
#include "headFile.h"
#include "generate.h"

using namespace std;


/*  因为放在函数体内的话，堆栈会爆，就只能放在外面，但是不能当做全局变量使用，这样会增加程序的耦合度  */
int move_step[80][Maxm];
int permutation[Maxn][Maxm];


void Swap(int & a, int & b)
/**********************
参数 a、b两个数
功能：交换两个数的数值
***********************/
{
	int temp = a;
	a = b;
	b = temp;
}

void Permutate_for_temp(int source[], int start, int end, int target[6][3], int& line)
/*************************************************************************************
参数	source[]：为原始排列，之后生成的排列都是对该原始排列的变换，相当于种子
		start：排列的起始位置，用于递归		end：排列的终止位置，用于递归
		target[][]：记录排列好的序列，一行为一个排列	line：行号

功能：对2 ~ 9行划分好的平移偏移量小组进行排列，递归完成
*************************************************************************************/
{
	if (start > end)  // 防止错误输入
	{
		start = end;
	}

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
/*******************************************************************************************************
参数	temp1、temp2、temp3分别为二三行，四五六行，七八九行的平移偏移量全排列
		max_num：用于记录需要的最多2 ~ 9行平移偏移量排列数
		move_step[][]：记录2 ~ 9行的平移偏移量排列，每一行为一个排列

功能：对二三行，四五六行，七八九行的平移偏移量的全排列进行组合，生成2 ~ 9行的全排列
********************************************************************************************************/
{
	int cnt = 0;

	for (int i = 0; i < 2; i++)  //  二三行有两个排列，二选一
	{
		for (int j = 0; j < 6; j++)  //  四五六行有六个全排列，六选一
		{
			for (int k = 0; k < 6; k++)  //  七八九行有六个全排列，六选一
			{
				for (int r = 0; r < 8; r++)  //  每个排列有8个元素（首元素不动）
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
/*****************************************************************************
参数：source[]：初始的排列（后续生成的所有排列通过该排列变换，相当于种子
      start：需要排列的序列起点，用于递归
	  end：需要排列的序列终点，用于递归
	  target[Maxn][Maxm]：每一行记录一种排列
	  line：记录当前生成的排列是第几种
	  max_num：需要最多的首行排列数

作用：该函数能更具max_num和source[]，递归调用自身，完成对初始序列的全排序，将排序结果
	  放在target数组中，每一行放一种排序，最多有max_num行
******************************************************************************/
{
	if (start > end)  // 防止输入错误，导致越界
	{
		start = end;
	}

	if (start == end)	//  终止条件
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
			if (line >= max_num)	// 当前全排序还没有生成结束，但是应为当前的终局生成需求数不需要那么多，所以强制返回
			{
				return;
			}

			Swap(source[i], source[start]);		//  交换两个元素位置
			Permutate_for_permutation(source, start + 1, end, target, line, max_num);
			Swap(source[i], source[start]);
		}
	}
}

void FillTheMoveStep(const int max_num, int move_step[80][Maxm])	//  根据最大需求数求2 ~ 9行平移偏移量的排列
{
	int source2[] = { 1 , 4 , 7 }, source3[] = { 2 , 5 , 8 };	// 二三行一组，四五六行一组，七八九行一组
	int temp1[2][2], temp2[6][3], temp3[6][3];
	int line2 = 0, line3 = 0;

	temp1[0][0] = 3, temp1[0][1] = 6;
	temp1[1][0] = 6, temp1[1][1] = 3;

	Permutate_for_temp(source2, 0, 2, temp2, line2);
	Permutate_for_temp(source3, 0, 2, temp3, line3);

	Permutate_for_move_step(temp1, temp2, temp3, max_num, move_step);	//  根据各小组的排列信息组合2 ~ 9 行的排列
}

void FillThePermutaion(const int max_num, int permutation[Maxn][Maxm])
{
	int source[] = { first_num , 1 , 2 ,  3 , 4 , 5 , 6 , 7 , 9 };
	int line = 0;
	Permutate_for_permutation(source, 1, 8, permutation, line, max_num);
}

void FillTheBlock(int cnt, int move_step[80][Maxm], int permutation[Maxn][Maxm])
/*****************************************************************************
参数：cnt：指令中-c的参数，即需要的数独生成终局的数量
	  move_step[80][Maxm]：第2至9行的行平移偏移量，每一行为中排序，每行的第i个元素对应第i + 1行的平移偏移量
	  permutation[Maxn][Maxm]：首行排序，每一行对应一种排序

作用：该函数将首行全排列和2只9行每行平移偏移量结合起来，生成数独终局，一个首行全排列和一个平移偏移量排列即
可组成一个数独终局
******************************************************************************/
{
	int pl = cnt / 72;	//	需要的排列数量
	int ml = cnt % 72;  //	最后一个排列需要平移偏移量排列数


	//  为了减少最后输出是，写的次数，将一个数独终局以一个字符串的形式保存起来，最后一次性输出
	char temp[200];	// 一个数独终局的符号总数为9 * 9 * 2 = 162
	int temp_site = 0;

	memset(temp, 0, sizeof(char) * 200);

	for (int i = 0; i < 9; i++)		//  输出第一行（因为第一行不平移，所以单独处理）
	{
		temp[temp_site] = permutation[pl][i] + '0';
		temp_site++;

		if (i == 8)
		{
			temp[temp_site] = '\n';
			temp_site++;
		}
		else
		{
			temp[temp_site] = ' ';
			temp_site++;
		}
	}

	for (int i = 1; i < 9; i++)		//  输出 2 ~ 9 行
	{
		for (int j = 0; j < 9; j++)
		{
			int site = (j + move_step[ml][i - 1]) % 9;	//  对整行进行平移（向左）

			temp[temp_site] = permutation[pl][site] + '0';
			temp_site++;

			if (j == 8)
			{
				if (i == 8)
				{
					temp[temp_site] = '\0';
					temp_site++;
				}
				else
				{
					temp[temp_site] = '\n';
					temp_site++;
				}
			}
			else
			{
				temp[temp_site] = ' ';
				temp_site++;
			}
		}
	}

	puts(temp);
}

void Generate(int num)
{

	FillTheMoveStep(min(num, 72), move_step);	// 求解2 ~ 8 行平移偏移量排列
	FillThePermutaion(num / 72 + 1, permutation);  // 求解首行全排列

	for (int cnt = 0; cnt < num; cnt++)
	{
		FillTheBlock(cnt, move_step, permutation);  // 生成数独终局并输出
		if (cnt != num - 1)
		{
			printf("\n");
		}

	}
}