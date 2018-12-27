
#include "stdafx.h"
#include "headFile.h"
#include "solve.h"
#include "Point.h"


using namespace std;


void SetMark(int str[Maxm][Maxm], const int& site, const int& num, const int flag)  // 将str数组的第site行,num列标记为flag，具体意义要看传入的数组是什么
{
	str[site][num] = flag;
}

int GetBlockNum(const int& x, const int& y)  //  根据元素的行号和列号生成元素所在小九宫格好（顺序从0开始，从左到右，从上到下）
{
	return x / 3 * 3 + y / 3;
}

int CheckNum(const int& rm, const int& cm, const int& bm)	//  根据三个打表的参数判断当前试探的数字是否合适，用于DFS中的空位元素试探
{
	return !(rm || cm || bm);
}

bool DFS(Point p[], const int& num, int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm], int step, int block[Maxm][Maxm])
/*****************************************************************************
参数：p[]：空位数组，在扫描之后，记录个空位的坐标（行，列）等有关信息
      num：空位数量，记录空位总数，作为递归重点的依据
	  rm[Maxm][Maxm]：行元素记录表，rm[x][y] == 1 表示x行包含元素y
	  cm[Maxm][Maxm]：列元素记录表，cm[x][y] == 1 表示x列包含元素y
	  bm[Maxm][Maxm]：块元素记录表，bm[x][y] == 1 表示小九宫盒x包含元素y，小九宫格顺序为从0到8，一行一行编码
	  step：表示当前在试探的空位在空位数组中的脚标，用于递归
	  block[Maxm][Maxm]：记录一个数独残局

返回值：bool型，返回1表示递归找到了可行解，否则表示没有找到

作用：通过递归调用自身，按照空位数组p[]中的顺序对每个空位进行试探，当填满所有空位时，递归结束，找到一个可行解
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

	for (int i = 1; i <= 9; i++)	//  对于每个空位，从1到9依次试探
	{
		int r = p[step].row, c = p[step].col;

		if (CheckNum(rm[r][i], cm[c][i], bm[GetBlockNum(r, c)][i]))	// 检查在空位（r,c)上填数字i是否合适
		{
			/* 打表记录 */
			SetMark(rm, r, i, 1);
			SetMark(cm, c, i, 1);
			SetMark(bm, GetBlockNum(r, c), i, 1);
			
			block[r][c] = i;
			/*  结束  */

			if (DFS(p, num, rm, cm, bm, step + 1, block))	//搜索下一个空位
			{
				return true;	// 递归找到了一个可行解
			}

			/*  递归没有找到可行解，当前位置不能填数字i，恢复之前打表的数据  */
			SetMark(rm, r, i, 0);
			SetMark(cm, c, i, 0);
			SetMark(bm, GetBlockNum(r, c), i, 0);

			block[r][c] = 0;
			/*  结束  */
		}
	}

	return false;
}

void Output(int block[Maxm][Maxm])
{
	char temp[200]; // temp 最大数量为9 * 9 * 2 = 162
	int temp_site = 0;

	memset(temp, 0, sizeof(char) * 200);

	for (int i = 0; i < 9; i++)		//  将一个二维数组编程一个一维字符串，减少写的次数
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

bool Cmp(Point& x, Point& y)	// 更具两个参数的num属性（该元素周围的已知数的数量）比较大小
{
	return x.num > y.num;
}


void Init(int rowmark[Maxm][Maxm], int colmark[Maxm][Maxm], int blockmark[Maxm][Maxm],
	int row_num[Maxm], int col_num[Maxm], int block_num[Maxm],
	int& input_row, int& right, int& ans_num)
/**************************************************************
参数 见Solve函数模块
功能：初始化参数
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
	int rowmark[Maxm][Maxm];		//  eg.rowmark[1][3] = 1表示第1行已经有数字3
	int colmark[Maxm][Maxm];		//  eg.colmark[2][4] = 1表示第2列已经有数字4
	int blockmark[Maxm][Maxm];		//  eg.blockmark[3][5] = 1表示第3个小的九宫格中已经有数字5

	int row_num[Maxm], col_num[Maxm], block_num[Maxm];  // 用于记录每行每列每个小九宫格中题目给出的已知数字的数量，用于最后排序优先级的判断

	int block[Maxm][Maxm];		// 用于记录一道数独题的题目
	Point ans_point[Maxm * Maxm];  //用于记录空位数组
	int ans_num;  //  用于记录空位个数

	int right;	//  记录输入的已知数独是否正确


	char temp_input[2 * Maxm];
	int input_row;

	int mark = 0;  //  记录当前求解的是第几个数独残局，用于最后解的时候的格式判断

	Init(rowmark, colmark, blockmark, row_num, col_num, block_num, input_row, right, ans_num);

	while (gets_s(temp_input))
	{
		temp_input[strlen(temp_input)] = '\0';	// 在字符串末加\0防越界
		if (strcmp(temp_input, "") == 0)
		{
			if (input_row != 9)
			{
				if (mark != 0)
				{
					printf("\n");
				}

				/*  如果题目在读的过程中，没有读够9行就遇到空行，证明题目不全  */
				printf("Imcompleted input!\n");
				mark++;
			}

			Init(rowmark, colmark, blockmark, row_num, col_num, block_num, input_row, right, ans_num);
			continue;
		}

		if (right)  // 如果到目前为止，读到的数据都合法的话
		{
			int input_col = 0;  // 作为当前读入的这行题目的脚标，访问当前读入的这一行

			int len = strlen(temp_input);
			if (len != 17)
			{
				/*  合法的题目一行应该有且仅有9个数字，8个空格  */
				right = 0;
				len = 0;  //不执行下面的for循环
			}

			for (int i = 0; i < len; i++)
			{
				if (temp_input[i] <'0' || temp_input[i] > '9')
				{
					if (temp_input[i] != ' ')
					{
						/*  如果读到一个非0到9之间的字符，且这个字符不是空格  */
						right = 0;
						break;
					}

					continue;
				}

				/*  读到的字符在0到9之间  */
				int temp_num = temp_input[i] - '0';

				block[input_row][input_col] = temp_num;

				if (temp_num == 0)  //  如果该字符是0，证明是空位，放入空位数组中
				{
					ans_point[ans_num].row = input_row;
					ans_point[ans_num].col = input_col;
					ans_num++;
				}
				else  // 如果不是0，则打表记录相应信息，使得之后回溯时试探数字是能快速判断试探数字是否有效
				{
					if (rowmark[input_row][temp_num] == 1 ||
						colmark[input_col][temp_num] == 1 ||
						blockmark[GetBlockNum(input_row, input_col)][temp_num] == 1)
					{
						/*  如果当前数字已经在该 行 或 列 或 小九宫格 中出现过，则题目出错，该题没有解  */
						right = 0;
						break;
					}
					else  // 如果该数字满足要求，打表
					{
						SetMark(rowmark, input_row, temp_num, 1);
						SetMark(colmark, input_col, temp_num, 1);
						SetMark(blockmark, GetBlockNum(input_row, input_col), temp_num, 1);

						row_num[input_row] ++;
						col_num[input_col] ++;
						block_num[GetBlockNum(input_row, input_col)] ++;
					}
				}

				input_col++; // 处理完当前输入行的一个字符，之后处理下一个
			}

			input_row++;  //  处理完一行，等待下一行输入

			if (input_row == 9) // 如果已经输入了9行
			{
				if (right)	// 输入的9行都信息正确
				{
					for (int i = 0; i < ans_num; i++)
					{
						int r = ans_point[i].row, c = ans_point[i].col;
						ans_point[i].num = row_num[r] + col_num[c] + block_num[GetBlockNum(r, c)];
					}

					sort(ans_point, ans_point + ans_num, Cmp);	// 根据空位数组中每个元素的num（周围已知数的个数）属性进行从大到小的排序

					if (DFS(ans_point, ans_num, rowmark, colmark, blockmark, 0, block))		// 递归求解 
					{
						if (mark != 0)	// 递归求解成功找到一个解，且当前题目不是第一题，则在输出题目之前，先空一行
						{
							printf("\n");
						}

						Output(block);
						mark++;
					}
				}
				else  // 如果输入的九行中检测到错误
				{
					printf("Some errors?\n");
				}
			}
		}
		
	}

	/*  已经完成了所有行的读入，但是最后这题没有满9行  */
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