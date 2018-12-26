
#include "stdafx.h"
#include "CheckOrder.h"

using namespace std;


int CheckOrder(char order[], int & num, char name[], int & type)
{
	int len = strlen(order);
	int flag = 1;		// ��Ϊ��������ṹ�ļ�¼�ṹ��ʹ����ʵ�ֵ�����
	int blank_num = 0;	// ��¼ָ���пո������
	int order_site = INF;	//��¼����ָ���λ�ã����ڶԺ���Ĳ�������У��


	/*  ��ʼ��  */
	num = 0;
	type = 0;
	memset(name, 0, sizeof(char) * 100);
	int name_site = 0;
	/*  ����  */

	for (int i = 0; i < len; i++)
	{
		if (i < order_site + 1)  // �����ǰλ���ڲ�����֮ǰ�� +1 Ϊ����������Ŀո��
		{
			if (order[i] == ' ')
			{
				blank_num++;
				if (blank_num > 1)  // �Ϸ�ָ��Ӧ��ֻ��һ���ո�
				{
					flag = 0;
					break;
				}
			}

			if (order[i] == '-' && i < len - 2)  //��֤������һ��ָ����Ͽո��λ��
			{
				if (order[i + 2] == ' ')	// ��֤�˴���  -  Ϊ������ǰ���  - 
				{
					if (order[i + 1] == 'c')
					{
						type = 1;		// ��¼��������
					}
					else if (order[i + 1] == 's')
					{
						type = 2;		// ��¼��������
					}
					else
					{
						flag = 0;
						break;
					}

					order_site = i;
					blank_num++;
					i += 2;	// �����������Ϳո�
				}

			}
		}
		else  // �����ǰλ���ڲ�����֮��
		{
			if (type == 1)
			{
				if (order[i] < '0' || order[i] > '9')	// -c�Ĳ�������Ϊ����
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
			else if (type == 2)		// -s�Ĳ��������пո���Ϊ�Ϸ��ļ�����
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


	if (blank_num != 1 || order_site == INF || type == 0)  //  �Ϸ�ָ��������ҽ���һ���ո���һ�����������Ҳ������Ϸ�
	{
		flag = 0;
	}
	if (type == 1 && num == 0)	// ��������Ϊ-cʱ��������������Ϊ0
	{
		flag = 0;
	}
	else if (type == 2 && strcmp(name, "") == 0)	// ��������Ϊ-sʱ���ļ�������Ϊ��
	{
		flag = 0;
	}


	return flag;

}