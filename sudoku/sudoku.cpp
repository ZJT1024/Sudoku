// shuduku.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "headFile.h"
#include "generate.h"
#include "CheckOrder.h"
#include "solve.h"
#include "Point.h"


//    You should complete N according to the concrete issue  


using namespace std;



int main()
{
	char order[100];	//  记录用户输入的指令
	int num, type;		//  num记录终局需求数量，type记录操作类型  1 为生成数独终局  2 为求解数独残局
	char name[100];		//  name记录-s 后的参数，即存储题目的文件名

	if (freopen("sudoku.txt", "w", stdout))
	{
		gets_s(order);		// 接受指令
		while (!CheckOrder(order, num, name, type))   //检查指令是否合法，如果非法，重新取指，如果合法，num中存放终局数量，type中存放问题求解方式
		{
			cout << "Please check the command!" << endl;
			gets_s(order);	    // 少了重新读指令，会出现死循环
		}

		if (type == 1)	//操作符为 -c
		{
			Generate(num);
		}
		else if (type == 2)  // 操作符为 -s
		{
			fclose(stdin);

			if (freopen(name, "r", stdin))
			{
				Solve();
			}
		}

		fclose(stdout);
	}
	return 0;
}

