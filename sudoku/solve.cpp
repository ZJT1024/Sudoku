
#include "stdafx.h"
#include "headFile.h"
#include "solve.h"
#include "Point.h"


using namespace std;


void SetMark(int str[Maxm][Maxm], const int& site, const int& num, const int flag)  // ��str����ĵ�site��,num�б��Ϊflag����������Ҫ�������������ʲô
{
	str[site][num] = flag;
}

int GetBlockNum(const int& x, const int& y)  //  ����Ԫ�ص��кź��к�����Ԫ������С�Ź���ã�˳���0��ʼ�������ң����ϵ��£�
{
	return x / 3 * 3 + y / 3;
}

int CheckNum(const int& rm, const int& cm, const int& bm)	//  �����������Ĳ����жϵ�ǰ��̽�������Ƿ���ʣ�����DFS�еĿ�λԪ����̽
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

	for (int i = 0; i < 9; i++)		//  ��һ����ά������һ��һά�ַ���������д�Ĵ���
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

bool Cmp(Point& x, Point& y)	// ��������������num���ԣ���Ԫ����Χ����֪�����������Ƚϴ�С
{
	return x.num > y.num;
}


void Init(int rowmark[Maxm][Maxm], int colmark[Maxm][Maxm], int blockmark[Maxm][Maxm],
	int row_num[Maxm], int col_num[Maxm], int block_num[Maxm],
	int& input_row, int& right, int& ans_num)
/**************************************************************
���� ��Solve����ģ��
���ܣ���ʼ������
*************************************************************/
{
	memset(row_num, 0, sizeof(int) * Maxm);
	memset(col_num, 0, sizeof(int) * Maxm);
	memset(block_num, 0, sizeof(int) * Maxm);
	memset(rowmark, 0, sizeof(int) * Maxm * Maxm);
	memset(colmark, 0, sizeof(int) * Maxm * Maxm);
	memset(blockmark, 0, sizeof(int) * Maxm * Maxm);
	input_row = 0;
	right = 1;
	ans_num = 0;
}

void  Solve()
{
	int rowmark[Maxm][Maxm];		//  eg.rowmark[1][3] = 1��ʾ��1���Ѿ�������3
	int colmark[Maxm][Maxm];		//  eg.colmark[2][4] = 1��ʾ��2���Ѿ�������4
	int blockmark[Maxm][Maxm];		//  eg.blockmark[3][5] = 1��ʾ��3��С�ľŹ������Ѿ�������5

	int row_num[Maxm], col_num[Maxm], block_num[Maxm];  // ���ڼ�¼ÿ��ÿ��ÿ��С�Ź�������Ŀ��������֪���ֵ���������������������ȼ����ж�

	int block[Maxm][Maxm];		// ���ڼ�¼һ�����������Ŀ
	Point ans_point[Maxm * Maxm];  //���ڼ�¼��λ����
	int ans_num;  //  ���ڼ�¼��λ����

	int right;	//  ��¼�������֪�����Ƿ���ȷ


	char temp_input[2 * Maxm];
	int input_row;

	int mark = 0;  //  ��¼��ǰ�����ǵڼ��������о֣����������ʱ��ĸ�ʽ�ж�

	Init(rowmark, colmark, blockmark, row_num, col_num, block_num, input_row, right, ans_num);

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

				/*  �����Ŀ�ڶ��Ĺ����У�û�ж���9�о��������У�֤����Ŀ��ȫ  */
				printf("Imcompleted input!\n");
				mark++;
			}

			Init(rowmark, colmark, blockmark, row_num, col_num, block_num, input_row, right, ans_num);
			continue;
		}

		if (right)  // �����ĿǰΪֹ�����������ݶ��Ϸ��Ļ�
		{
			int input_col = 0;  // ��Ϊ��ǰ�����������Ŀ�Ľű꣬���ʵ�ǰ�������һ��

			int len = strlen(temp_input);
			if (len != 17)
			{
				/*  �Ϸ�����Ŀһ��Ӧ�����ҽ���9�����֣�8���ո�  */
				right = 0;
				len = 0;  //��ִ�������forѭ��
			}

			for (int i = 0; i < len; i++)
			{
				if (temp_input[i] <'0' || temp_input[i] > '9')
				{
					if (temp_input[i] != ' ')
					{
						/*  �������һ����0��9֮����ַ���������ַ����ǿո�  */
						right = 0;
						break;
					}

					continue;
				}

				/*  �������ַ���0��9֮��  */
				int temp_num = temp_input[i] - '0';

				block[input_row][input_col] = temp_num;

				if (temp_num == 0)  //  ������ַ���0��֤���ǿ�λ�������λ������
				{
					ans_point[ans_num].row = input_row;
					ans_point[ans_num].col = input_col;
					ans_num++;
				}
				else  // �������0�������¼��Ӧ��Ϣ��ʹ��֮�����ʱ��̽�������ܿ����ж���̽�����Ƿ���Ч
				{
					if (rowmark[input_row][temp_num] == 1 ||
						colmark[input_col][temp_num] == 1 ||
						blockmark[GetBlockNum(input_row, input_col)][temp_num] == 1)
					{
						/*  �����ǰ�����Ѿ��ڸ� �� �� �� �� С�Ź��� �г��ֹ�������Ŀ��������û�н�  */
						right = 0;
						break;
					}
					else  // �������������Ҫ�󣬴��
					{
						SetMark(rowmark, input_row, temp_num, 1);
						SetMark(colmark, input_col, temp_num, 1);
						SetMark(blockmark, GetBlockNum(input_row, input_col), temp_num, 1);

						row_num[input_row] ++;
						col_num[input_col] ++;
						block_num[GetBlockNum(input_row, input_col)] ++;
					}
				}

				input_col++; // �����굱ǰ�����е�һ���ַ���֮������һ��
			}

			input_row++;  //  ������һ�У��ȴ���һ������

			if (input_row == 9) // ����Ѿ�������9��
			{
				if (right)	// �����9�ж���Ϣ��ȷ
				{
					for (int i = 0; i < ans_num; i++)
					{
						int r = ans_point[i].row, c = ans_point[i].col;
						ans_point[i].num = row_num[r] + col_num[c] + block_num[GetBlockNum(r, c)];
					}

					sort(ans_point, ans_point + ans_num, Cmp);	// ���ݿ�λ������ÿ��Ԫ�ص�num����Χ��֪���ĸ��������Խ��дӴ�С������

					if (DFS(ans_point, ans_num, rowmark, colmark, blockmark, 0, block))		// �ݹ���� 
					{
						if (mark != 0)	// �ݹ����ɹ��ҵ�һ���⣬�ҵ�ǰ��Ŀ���ǵ�һ�⣬���������Ŀ֮ǰ���ȿ�һ��
						{
							printf("\n");
						}

						Output(block);
						mark++;
					}
				}
				else  // �������ľ����м�⵽����
				{
					printf("Some errors?\n");
				}
			}
		}
		
	}

	/*  �Ѿ�����������еĶ��룬�����������û����9��  */
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