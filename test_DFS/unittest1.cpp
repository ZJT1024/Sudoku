#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sudoku/solve.h"
#include "../sudoku/solve.cpp"
#include<cstdlib>
#include<time.h>
#include "../sudoku/headFile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_DFS
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		bool Check(int block[Maxm][Maxm])
		/***************************
		 参数：block[Maxm][Maxm]:最后求解出的数独终局
		 功能：判断输入的数独终局是否合法
		 返回类型：bool，终局合法返回true,终局非法返回false
		****************************/
		{
			int rm[Maxm][Maxm], cm[Maxm][Maxm], bm[Maxm][Maxm];		//  打表记录

			/*  初始化  */
			memset(rm, 0, sizeof(int) * Maxm * Maxm);
			memset(cm, 0, sizeof(int) * Maxm * Maxm);
			memset(bm, 0, sizeof(int) * Maxm  * Maxm);
			/*  结束  */

			bool flag = true;

			for (int i = 0; i < 9; i++)		// 重新扫描求解出来的数独终局，打表记录，判断是否合法
			{
				for (int j = 0; j < 9; j++)
				{
					int temp_num = block[i][j];

					if (rm[i][temp_num] || cm[j][temp_num] || bm[GetBlockNum(i, j)][temp_num])	//  当一行或者一列或者一个小九宫格中出现重复元素时，为假
					{
						flag = false;
						break;
					}
				}
			}

			return flag;
		}

		void Init(int block[Maxm][Maxm], int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm], int rnum[Maxm], int cnum[Maxm], int bnum[Maxm])
		/****************************************************************************
		参数block[][]：先存入一个合法的数独终局       rm[][]、cm[][]、bm[][]：打表记录某个元素是否在某行/列/宫
		    rnum[]、cnum[]、bnum[]：记录每行、列、宫非空元素总数

		功能：初始化个数组，将个数组设置为合法数独终局时候的状态
		*****************************************************************************/
		{
			int temp_move[] = { 3,6,1,4,7,2,5,8 };	// 2~9行平偏移量

			memset(block, 0, sizeof(int) * Maxm * Maxm);
			for (int i = 0; i < 9; i++)
			{
				rnum[i] = cnum[i] = bnum[i] = 9;

				for (int j = 0; j < 9; j++)
				{
					rm[i][j] = cm[i][j] = bm[i][j] = 1;

					if (i == 0)
					{
						block[i][j] = j + 1;
					}
					else
					{
						int site = (temp_move[i - 1] + j) % 9;	// 平移
						block[i][j] = block[0][site];
					}
				}
			}
		}

		void Dig(Point ans_point[], int& ans_num, int max_num, int min_num,
			int block[Maxm][Maxm], int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm],
			int rnum[Maxm], int cnum[Maxm], int bnum[Maxm])
			/**********************************************************************
			参数 ans_point[]：存放空位的数组    ans_num：记录空位数量    max_num：挖空位的最大数量
			     min_num：挖空位的最小数量    block[][]：已经存有合法数独终局的数组
				 rm[][]、cm[][]、bm[][]：在挖空位时要抹去对应的记录
				 rnum[]、cnum[]、bnum[]：在挖空位时要抹去对应的记录
			
			功能：在一个合法数独终局上随机挖最多max_num个空位，最少min_num个空位
			************************************************************************/
		{
			if (max_num <= min_num)	//防止非法输入
			{
				max_num = 60;
				min_num = 30;
			}

			for (int i = 0; i < max_num; i++)		//  随机挖至多max_nuum个空，至少min_num个空
			{
				/*  随机取行列值  */
				srand(unsigned(rand()));
				int r = rand() % 9;

				srand(unsigned(rand() + rand()));
				int c = rand() % 9;
				/*  结束  */

				if (block[r][c] != 0)	// 不重复才记录，重复重新算坐标
				{
					/*  挖空，逆向操作  */
					SetMark(rm, r, block[r][c], 0);
					SetMark(cm, c, block[r][c], 0);
					SetMark(bm, GetBlockNum(r, c), block[r][c], 0);

					block[r][c] = 0;
					ans_point[ans_num].row = r;
					ans_point[ans_num].col = c;

					rnum[r] --;
					cnum[c] --;
					bnum[GetBlockNum(r, c)] --;
					/*  结束  */

					ans_num++;
				}
				else
				{
					if (ans_num + 60 - i < min_num)	// 保证至少有min_num个空
					{
						i--;
					}
				}

			}

			for (int i = 0; i < ans_num; i++)
			{
				int r = ans_point[i].row, c = ans_point[i].col;
				ans_point[i].num = rnum[r] + cnum[c] + bnum[GetBlockNum(r, c)];
			}

			sort(ans_point, ans_point + ans_num, Cmp);
		}

		TEST_METHOD(checkDFS_right)
		{
			// TODO: 在此输入测试代码

			int block[Maxm][Maxm];
			int rm[Maxm][Maxm], cm[Maxm][Maxm], bm[Maxm][Maxm];
			int rnum[Maxm], cnum[Maxm], bnum[Maxm];
			
			Init(block, rm, cm, bm, rnum, cnum, bnum);

			Point ans_point[Maxm * Maxm];
			int ans_num = 0;

			Dig(ans_point, ans_num, 60, 30, block, rm, cm, bm, rnum, cnum, bnum);

			bool flag = DFS(ans_point, ans_num, rm, cm, bm, 0, block);
			bool right_ans = Check(block);

			Assert::AreEqual(true, flag);
			//Assert::AreEqual(true, right_ans);
		}

		TEST_METHOD(overflow_error1)
		{
			// TODO: 在此输入测试代码

			int block[Maxm][Maxm];
			int rm[Maxm][Maxm], cm[Maxm][Maxm], bm[Maxm][Maxm];
			int rnum[Maxm], cnum[Maxm], bnum[Maxm];

			Init(block, rm, cm, bm, rnum, cnum, bnum);

			Point ans_point[Maxm * Maxm];
			int ans_num = 0;

			Dig(ans_point, ans_num, 60, 30, block, rm, cm, bm, rnum, cnum, bnum);

			bool flag = DFS(ans_point, ans_num, rm, cm, bm, -1, block);
			//  溢出不考虑block的正确性

			Assert::AreEqual(false, flag);
		}

		TEST_METHOD(overflow_error2)
		{
			// TODO: 在此输入测试代码

			int block[Maxm][Maxm];
			int rm[Maxm][Maxm], cm[Maxm][Maxm], bm[Maxm][Maxm];
			int rnum[Maxm], cnum[Maxm], bnum[Maxm];

			Init(block, rm, cm, bm, rnum, cnum, bnum);

			Point ans_point[Maxm * Maxm];
			int ans_num = 0;

			Dig(ans_point, ans_num, 60, 30, block, rm, cm, bm, rnum, cnum, bnum);

			bool flag = DFS(ans_point, ans_num, rm, cm, bm, ans_num + 1, block);
			//  溢出不考虑block的正确性

			Assert::AreEqual(false, flag);
		}

	};
}