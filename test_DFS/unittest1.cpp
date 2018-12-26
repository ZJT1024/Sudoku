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
		 ������block[Maxm][Maxm]:��������������վ�
		 ���ܣ��ж�����������վ��Ƿ�Ϸ�
		 �������ͣ�bool���վֺϷ�����true,�վַǷ�����false
		****************************/
		{
			int rm[Maxm][Maxm], cm[Maxm][Maxm], bm[Maxm][Maxm];		//  ����¼

			/*  ��ʼ��  */
			memset(rm, 0, sizeof(int) * Maxm * Maxm);
			memset(cm, 0, sizeof(int) * Maxm * Maxm);
			memset(bm, 0, sizeof(int) * Maxm  * Maxm);
			/*  ����  */

			bool flag = true;

			for (int i = 0; i < 9; i++)		// ����ɨ���������������վ֣�����¼���ж��Ƿ�Ϸ�
			{
				for (int j = 0; j < 9; j++)
				{
					int temp_num = block[i][j];

					if (rm[i][temp_num] || cm[j][temp_num] || bm[GetBlockNum(i, j)][temp_num])	//  ��һ�л���һ�л���һ��С�Ź����г����ظ�Ԫ��ʱ��Ϊ��
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
		����block[][]���ȴ���һ���Ϸ��������վ�       rm[][]��cm[][]��bm[][]������¼ĳ��Ԫ���Ƿ���ĳ��/��/��
		    rnum[]��cnum[]��bnum[]����¼ÿ�С��С����ǿ�Ԫ������

		���ܣ���ʼ�������飬������������Ϊ�Ϸ������վ�ʱ���״̬
		*****************************************************************************/
		{
			int temp_move[] = { 3,6,1,4,7,2,5,8 };	// 2~9��ƽƫ����

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
						int site = (temp_move[i - 1] + j) % 9;	// ƽ��
						block[i][j] = block[0][site];
					}
				}
			}
		}

		void Dig(Point ans_point[], int& ans_num, int max_num, int min_num,
			int block[Maxm][Maxm], int rm[Maxm][Maxm], int cm[Maxm][Maxm], int bm[Maxm][Maxm],
			int rnum[Maxm], int cnum[Maxm], int bnum[Maxm])
			/**********************************************************************
			���� ans_point[]����ſ�λ������    ans_num����¼��λ����    max_num���ڿ�λ���������
			     min_num���ڿ�λ����С����    block[][]���Ѿ����кϷ������վֵ�����
				 rm[][]��cm[][]��bm[][]�����ڿ�λʱҪĨȥ��Ӧ�ļ�¼
				 rnum[]��cnum[]��bnum[]�����ڿ�λʱҪĨȥ��Ӧ�ļ�¼
			
			���ܣ���һ���Ϸ������վ�����������max_num����λ������min_num����λ
			************************************************************************/
		{
			if (max_num <= min_num)	//��ֹ�Ƿ�����
			{
				max_num = 60;
				min_num = 30;
			}

			for (int i = 0; i < max_num; i++)		//  ���������max_nuum���գ�����min_num����
			{
				/*  ���ȡ����ֵ  */
				srand(unsigned(rand()));
				int r = rand() % 9;

				srand(unsigned(rand() + rand()));
				int c = rand() % 9;
				/*  ����  */

				if (block[r][c] != 0)	// ���ظ��ż�¼���ظ�����������
				{
					/*  �ڿգ��������  */
					SetMark(rm, r, block[r][c], 0);
					SetMark(cm, c, block[r][c], 0);
					SetMark(bm, GetBlockNum(r, c), block[r][c], 0);

					block[r][c] = 0;
					ans_point[ans_num].row = r;
					ans_point[ans_num].col = c;

					rnum[r] --;
					cnum[c] --;
					bnum[GetBlockNum(r, c)] --;
					/*  ����  */

					ans_num++;
				}
				else
				{
					if (ans_num + 60 - i < min_num)	// ��֤������min_num����
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
			// TODO: �ڴ�������Դ���

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
			// TODO: �ڴ�������Դ���

			int block[Maxm][Maxm];
			int rm[Maxm][Maxm], cm[Maxm][Maxm], bm[Maxm][Maxm];
			int rnum[Maxm], cnum[Maxm], bnum[Maxm];

			Init(block, rm, cm, bm, rnum, cnum, bnum);

			Point ans_point[Maxm * Maxm];
			int ans_num = 0;

			Dig(ans_point, ans_num, 60, 30, block, rm, cm, bm, rnum, cnum, bnum);

			bool flag = DFS(ans_point, ans_num, rm, cm, bm, -1, block);
			//  ���������block����ȷ��

			Assert::AreEqual(false, flag);
		}

		TEST_METHOD(overflow_error2)
		{
			// TODO: �ڴ�������Դ���

			int block[Maxm][Maxm];
			int rm[Maxm][Maxm], cm[Maxm][Maxm], bm[Maxm][Maxm];
			int rnum[Maxm], cnum[Maxm], bnum[Maxm];

			Init(block, rm, cm, bm, rnum, cnum, bnum);

			Point ans_point[Maxm * Maxm];
			int ans_num = 0;

			Dig(ans_point, ans_num, 60, 30, block, rm, cm, bm, rnum, cnum, bnum);

			bool flag = DFS(ans_point, ans_num, rm, cm, bm, ans_num + 1, block);
			//  ���������block����ȷ��

			Assert::AreEqual(false, flag);
		}

	};
}