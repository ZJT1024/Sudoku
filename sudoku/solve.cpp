
#include "stdafx.h"
#include "headFile.h"
#include "solve.h"
#include "Point.h"


using namespace std;


void SetMark(int str[Maxm][Maxm], const int& site, const int& num, const int flag)
{
	str[site][num] = flag;
}

int GetBlockNum(const int& x, const int& y)
{
	return x / 3 * 3 + y / 3;
}

int CheckNum(const int& rm, const int& cm, const int& bm)
{
	return !(rm || cm || bm);
}

int DFS(Point p[], const int& num, int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm], int step, int block[Maxm][Maxm])
{
	if (step == num)
	{
		return true;
	}

	for (int i = 1; i <= 9; i++)
	{
		int r = p[step].Get_row(), c = p[step].Get_col();

		if (CheckNum(rm[r][i], cm[c][i], bm[GetBlockNum(r, c)][i]))
		{
			SetMark(rm, r, i, 1);
			SetMark(cm, c, i, 1);
			SetMark(bm, GetBlockNum(r, c), i, 1);

			block[r][c] = i;

			if (DFS(p, num, rm, cm, bm, step + 1, block))
			{
				return true;
			}

			SetMark(rm, r, i, 0);
			SetMark(cm, c, i, 0);
			SetMark(bm, GetBlockNum(r, c), i, 0);

			block[r][c] = 0;
		}
	}

	return false;
}

void Output(int block[Maxm][Maxm])
{
	char temp[Maxm * 2];
	int temp_site = 0;

	memset(temp, 0, sizeof(char) * Maxm * 2);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			temp[temp_site] = char(block[i][j] + '0');
			temp_site++;

			if (j == 8)
			{
				temp[temp_site] = '\0';
				temp_site++;
			}
			else
			{
				temp[temp_site] = ' ';
				temp_site++;
			}
		}
		puts(temp);
		temp_site = 0;
	}
}

void  Solve()
{
	int rowmark[Maxm][Maxm];		//  eg.rowmark[1][3] = 1表示第1行已经有数字3
	int colmark[Maxm][Maxm];		//  eg.colmark[2][4] = 1表示第2列已经有数字4
	int blockmark[Maxm][Maxm];		//  eg.blockmark[3][5] = 1表示第3个小的九宫格中已经有数字5

	int row_num[Maxm], col_num[Maxm], block_num[Maxm];  // 用于记录每行每列每个小九宫格中题目给出的已知数字的数量，用于最后排序优先级的判断

	int block[Maxm][Maxm];		// 用于记录一道数独题的题目
	Point ans_point[Maxm * Maxm];
	int ans_num = 0;

	int right = 1;	//  记录输入的已知数独是否正确


	char temp_input[2 * Maxm];
	int input_row;

	int mark = 0;



	memset(row_num, 0, sizeof(int) * Maxm);
	memset(col_num, 0, sizeof(int) * Maxm);
	memset(block_num, 0, sizeof(int) * Maxm);
	memset(rowmark, 0, sizeof(int) * Maxm * Maxm);
	memset(colmark, 0, sizeof(int) * Maxm * Maxm);
	memset(blockmark, 0, sizeof(int) * Maxm * Maxm);
	input_row = 0;



	while (gets_s(temp_input))
	{
		temp_input[strlen(temp_input)] = '\0';
		if (strcmp(temp_input, "") == 0)
		{
			if (input_row != 9)
			{
				if (mark != 0)
				{
					printf("\n");
				}

				printf("Imcompleted input!\n");
				mark++;
			}

			memset(row_num, 0, sizeof(int) * Maxm);
			memset(col_num, 0, sizeof(int) * Maxm);
			memset(block_num, 0, sizeof(int) * Maxm);
			memset(rowmark, 0, sizeof(int) * Maxm * Maxm);
			memset(colmark, 0, sizeof(int) * Maxm * Maxm);
			memset(blockmark, 0, sizeof(int) * Maxm * Maxm);
			input_row = 0;
			right = 1;
			ans_num = 0;
			continue;
		}

		if (right)
		{
			int input_col = 0;

			int len = strlen(temp_input);
			for (int i = 0; i < len; i++)
			{
				if (temp_input[i] <'0' || temp_input[i] > '9')
				{
					if (temp_input[i] != ' ')
					{
						right = 0;
						break;
					}

					continue;
				}

				int temp_num = temp_input[i] - '0';

				block[input_row][input_col] = temp_num;

				if (temp_num == 0)
				{
					ans_point[ans_num].Set_row(input_row);
					ans_point[ans_num].Set_col(input_col);
					ans_num++;
				}
				else
				{
					if (rowmark[input_row][temp_num] == 1 ||
						colmark[input_col][temp_num] == 1 ||
						blockmark[GetBlockNum(input_row, input_col)][temp_num] == 1)
					{
						right = 0;
						break;
					}
					else
					{
						SetMark(rowmark, input_row, temp_num, 1);
						SetMark(colmark, input_col, temp_num, 1);
						SetMark(blockmark, GetBlockNum(input_row, input_col), temp_num, 1);

						row_num[input_row] ++;
						col_num[input_col] ++;
						block_num[GetBlockNum(input_row, input_col)] ++;
					}
				}

				input_col++;
			}

			input_row++;

			if (input_row == 9)
			{
				if (right)
				{
					int max_point = -INF, min_point = INF;
					int sort_num = 40;


					for (int i = 0; i < ans_num; i++)
					{
						int r = ans_point[i].Get_row(), c = ans_point[i].Get_col();
						int temp_num = row_num[r] + col_num[c] + block_num[GetBlockNum(r, c)];

						ans_point[i].Set_num(temp_num);

						if (temp_num > max_point)
						{
							max_point = temp_num;
						}
						if (temp_num < min_point)
						{
							min_point = temp_num;
						}
					}

					//if (max_point - min_point > 10)  // 10为参数，可为0到21  （9 + 6 + 6）之间任何数，主要为限制排序条件，避免浪费时间
					//{
						sort(ans_point, ans_point + ans_num);
					//}

					if (DFS(ans_point, ans_num, rowmark, colmark, blockmark, 0, block))
					{
						if (mark != 0)
						{
							printf("\n");
						}

						Output(block);
						mark++;
					}
				}
				else
				{
					printf("Some errors?\n");
				}
			}
		}
		
	}

	if (input_row != 9)
	{
		if (mark != 0)
		{
			printf("\n");
		}

		printf("Imcompleted input!");
		mark++;
	}
}