
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

bool DFS(Point p[], const int& num, int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm], int step, int block[Maxm][Maxm])
/*****************************************************************************
������p[]����λ���飬��ɨ��֮�󣬼�¼����λ�����꣨�У��У����й���Ϣ
      num����λ��������¼��λ��������Ϊ�ݹ��ص������
	  rm[Maxm][Maxm]����Ԫ�ؼ�¼��rm[x][y] == 1 ��ʾx�а���Ԫ��y
	  cm[Maxm][Maxm]����Ԫ�ؼ�¼��cm[x][y] == 1 ��ʾx�а���Ԫ��y
	  bm[Maxm][Maxm]����Ԫ�ؼ�¼��bm[x][y] == 1 ��ʾС�Ź���x����Ԫ��y��С�Ź���˳��Ϊ��0��8��һ��һ�б���
	  step����ʾ��ǰ����̽�Ŀ�λ�ڿ�λ�����еĽű꣬���ڵݹ�
	  block[Maxm][Maxm]����¼һ�������о�

����ֵ��bool�ͣ�����1��ʾ�ݹ��ҵ��˿��н⣬�����ʾû���ҵ�

���ã�ͨ���ݹ�����������տ�λ����p[]�е�˳���ÿ����λ������̽�����������п�λʱ���ݹ�������ҵ�һ�����н�
******************************************************************************/
{
	if (step == num)
	{
		return true;
	}
	else if (step < 0 || step > num)
	{
		return false;
	}

	for (int i = 1; i <= 9; i++)	//  ����ÿ����λ����1��9������̽
	{
		int r = p[step].row, c = p[step].col;

		if (CheckNum(rm[r][i], cm[c][i], bm[GetBlockNum(r, c)][i]))	// ����ڿ�λ��r,c)��������i�Ƿ����
		{
			/* ����¼ */
			SetMark(rm, r, i, 1);
			SetMark(cm, c, i, 1);
			SetMark(bm, GetBlockNum(r, c), i, 1);
			
			block[r][c] = i;
			/*  ����  */

			if (DFS(p, num, rm, cm, bm, step + 1, block))	//������һ����λ
			{
				return true;	// �ݹ��ҵ���һ�����н�
			}

			/*  �ݹ�û���ҵ����н⣬��ǰλ�ò���������i���ָ�֮ǰ��������  */
			SetMark(rm, r, i, 0);
			SetMark(cm, c, i, 0);
			SetMark(bm, GetBlockNum(r, c), i, 0);

			block[r][c] = 0;
			/*  ����  */
		}
	}

	return false;
}

void Output(int block[Maxm][Maxm])
{
	char temp[200]; // temp �������Ϊ9 * 9 * 2 = 162
	int temp_site = 0;

	memset(temp, 0, sizeof(char) * 200);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			temp[temp_site] = block[i][j] + '0';
			temp_site++;

			if (j == 8)
			{
				if (i == 8)
				{
					temp[temp_site] = '\0';
				}
				else
				{
					temp[temp_site] = '\n';
				}
				temp_site++;
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

bool Cmp(Point& x, Point& y)
{
	return x.num > y.num;
}

void  Solve()
{
	int rowmark[Maxm][Maxm];		//  eg.rowmark[1][3] = 1��ʾ��1���Ѿ�������3
	int colmark[Maxm][Maxm];		//  eg.colmark[2][4] = 1��ʾ��2���Ѿ�������4
	int blockmark[Maxm][Maxm];		//  eg.blockmark[3][5] = 1��ʾ��3��С�ľŹ������Ѿ�������5

	int row_num[Maxm], col_num[Maxm], block_num[Maxm];  // ���ڼ�¼ÿ��ÿ��ÿ��С�Ź�������Ŀ��������֪���ֵ���������������������ȼ����ж�

	int block[Maxm][Maxm];		// ���ڼ�¼һ�����������Ŀ
	Point ans_point[Maxm * Maxm];
	int ans_num = 0;

	int right = 1;	//  ��¼�������֪�����Ƿ���ȷ


	char temp_input[2 * Maxm];
	int input_row;

	int mark = 0;



	/*  ��ʼ��  */
	memset(row_num, 0, sizeof(int) * Maxm);
	memset(col_num, 0, sizeof(int) * Maxm);
	memset(block_num, 0, sizeof(int) * Maxm);
	memset(rowmark, 0, sizeof(int) * Maxm * Maxm);
	memset(colmark, 0, sizeof(int) * Maxm * Maxm);
	memset(blockmark, 0, sizeof(int) * Maxm * Maxm);
	input_row = 0;
	/*  ����  */



	while (gets_s(temp_input))
	{
		temp_input[strlen(temp_input)] = '\0';	// ���ַ���ĩ��\0��Խ��
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
					ans_point[ans_num].row = input_row;
					ans_point[ans_num].col = input_col;
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

					for (int i = 0; i < ans_num; i++)
					{
						int r = ans_point[i].row, c = ans_point[i].col;
						ans_point[i].num = row_num[r] + col_num[c] + block_num[GetBlockNum(r, c)];
					}

					sort(ans_point, ans_point + ans_num, Cmp);

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