
#include "stdafx.h"
#include "CheckOrder.h"

using namespace std;


int CheckOrder(char order[], int & num, char name[], int & type)
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

	for (int i = 0; i < len; i++)
	{
		if (i < order_site + 1)  // 如果当前位置在操作符之前， +1 为操作符后面的空格符
		{
			if (order[i] == ' ')
			{
				blank_num++;
				if (blank_num > 1)  // 合法指令应该只有一个空格
				{
					flag = 0;
					break;
				}
			}

			if (order[i] == '-' && i < len - 2)  //保证后面有一个指令符合空格的位置
			{
				if (order[i + 2] == ' ')	// 保证此处的  -  为操作符前面的  - 
				{
					if (order[i + 1] == 'c')
					{
						type = 1;		// 记录操作类型
					}
					else if (order[i + 1] == 's')
					{
						type = 2;		// 记录操作类型
					}
					else
					{
						flag = 0;
						break;
					}

					order_site = i;
					blank_num++;
					i += 2;	// 跳过操作符和空格
				}

			}
		}
		else  // 如果当前位置在操作符之后
		{
			if (type == 1)
			{
				if (order[i] < '0' || order[i] > '9')	// -c的参数智能为数字
				{
					flag = 0;
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
					memset(name, 0, sizeof(name));
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