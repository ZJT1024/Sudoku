
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
/*****************************************************************************
������source[]����ʼ�����У��������ɵ���������ͨ�������б任���൱������
      start����Ҫ���е�������㣬���ڵݹ�
	  end����Ҫ���е������յ㣬���ڵݹ�
	  target[Maxn][Maxm]��ÿһ�м�¼һ������
	  line����¼��ǰ���ɵ������ǵڼ���
	  max_num����Ҫ��������������

���ã��ú����ܸ���max_num��source[]���ݹ����������ɶԳ�ʼ���е�ȫ���򣬽�������
	  ����target�����У�ÿһ�з�һ�����������max_num��
******************************************************************************/
{
	if (start == end)	//  ��ֹ����
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
			if (line >= max_num)	// ��ǰȫ����û�����ɽ���������ӦΪ��ǰ���վ���������������Ҫ��ô�࣬����ǿ�Ʒ���
			{
				return;
			}

			Swap(source[i], source[start]);		//  ��������Ԫ��λ��
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
/*****************************************************************************
������cnt��ָ����-c�Ĳ���������Ҫ�����������վֵ�����
	  move_step[80][Maxm]����2��9�е���ƽ��ƫ������ÿһ��Ϊ������ÿ�еĵ�i��Ԫ�ض�Ӧ��i + 1�е�ƽ��ƫ����
	  permutation[Maxn][Maxm]����������ÿһ�ж�Ӧһ������

���ã��ú���������ȫ���к�2ֻ9��ÿ��ƽ��ƫ����������������������վ֣�һ������ȫ���к�һ��ƽ��ƫ�������м�
�����һ�������վ�
******************************************************************************/
{
	int pl = cnt / 72;	//	��Ҫ����������
	int ml = cnt % 72;  //	���һ��������Ҫƽ��ƫ����������


	//  Ϊ�˼����������ǣ�д�Ĵ�������һ�������վ���һ���ַ�������ʽ�������������һ�������
	char temp[200];	// һ�������վֵķ�������Ϊ9 * 9 * 2 = 162
	int temp_site = 0;

	memset(temp, 0, sizeof(char) * 200);

	for (int i = 0; i < 9; i++)		//  �����һ�У���Ϊ��һ�в�ƽ�ƣ����Ե�������
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

	for (int i = 1; i < 9; i++)		//  ��� 2 ~ 9 ��
	{
		for (int j = 0; j < 9; j++)
		{
			int site = (j + move_step[ml][i - 1]) % 9;	//  �����н���ƽ�ƣ�����

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