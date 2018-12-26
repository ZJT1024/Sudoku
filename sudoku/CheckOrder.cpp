
#include "stdafx.h"
#include "CheckOrder.h"

using namespace std;


int CheckOrder(char order[], int & num, char name[], int & type)
/******************************************************************************
参数：order[]为用户输入的指令		num：记录指令中可能出现的-c的参数（数独终局数量）	name：记录指令中可能出现的-s的参数（题目文件名）
	 type：记录该指令中的操作类型  1为-c，2为-s

返回值：返回值为int型，表示该指令order知否合法，合法为1，不合法为0
******************************************************************************/
{
	int len = strlen(order);
	int flag = 1;		// 作为函数检验结构的记录结构，使函数实现单出口
	int blank_num = 0;	// 记录指令中空格的数量
	int order_site = INF;	//记录操作指令的位置，便于对后面的参数进行校验


	/*  初始化  */
	num = 0;
	type = 0;
	memset(name, 0, sizeof(char) * 100);
	int name_site = 0;
	/*  结束  */

	if (len < 4) // 合法指令至少4位
	{
		flag = 0;
	}
	else
	{
		if (order[0] != '-')  // 合法指令的首位一定为 -
		{
			flag = 0;
		}
		else if( order[2] == ' ')    //  记录操作符类型
		{
			if (order[1] == 'c')
			{
				type = 1;
				order_site = 1;
			}
			else if (order[1] == 's')
			{
				type = 2;
				order_site = 1;
			}
			else  // 非法操作符
			{
				flag = 0;
			}
			blank_num = 1;
		}
	}


	for (int i = 3; i < len; i++)	// 从空格后第一位开始
	{
		if( i > order_site + 1)  // 如果当前位置在操作符之后
		{
			if (type == 1)
			{
				if (order[i] < '0' || order[i] > '9')	// -c的参数智能为数字
				{
					flag = 0;
					num = 0;	//  以防参数为前数字后字符的用例蒙混过关
					break;
				}
				else
				{
					num *= 10;
					num += order[i] - '0';
				}
			}
			else if (type == 2)		// -s的参数不能有空格（需为合法文件名）
			{
				if (order[i] == ' ')
				{
					flag = 0;
					memset(name, 0, sizeof(char) * strlen(name));
					break;
				}
				else
				{
					name[name_site] = order[i];
					name_site++;
				}
			}
		}
	}


	if (blank_num != 1 || order_site == INF || type == 0)  //  合法指令必须有且仅有一个空格，有一个操作符，且操作符合法
	{
		flag = 0;
	}
	if (type == 1 && num == 0)	// 当操作符为-c时，需求数量不能为0
	{
		flag = 0;
	}
	else if (type == 2 && strcmp(name, "") == 0)	// 当操作符为-s时，文件名不能为空
	{
		flag = 0;
	}


	return flag;

}