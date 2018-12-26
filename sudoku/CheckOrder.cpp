
#include "stdafx.h"
#include "CheckOrder.h"

using namespace std;


int CheckOrder(char order[], int & num, char name[], int & type)
/******************************************************************************
������order[]Ϊ�û������ָ��		num����¼ָ���п��ܳ��ֵ�-c�Ĳ����������վ�������	name����¼ָ���п��ܳ��ֵ�-s�Ĳ�������Ŀ�ļ�����
	 type����¼��ָ���еĲ�������  1Ϊ-c��2Ϊ-s

����ֵ������ֵΪint�ͣ���ʾ��ָ��order֪��Ϸ����Ϸ�Ϊ1�����Ϸ�Ϊ0
******************************************************************************/
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

	if (len < 4) // �Ϸ�ָ������4λ
	{
		flag = 0;
	}
	else
	{
		if (order[0] != '-')  // �Ϸ�ָ�����λһ��Ϊ -
		{
			flag = 0;
		}
		else if( order[2] == ' ')    //  ��¼����������
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
			else  // �Ƿ�������
			{
				flag = 0;
			}
			blank_num = 1;
		}
	}


	for (int i = 3; i < len; i++)	// �ӿո���һλ��ʼ
	{
		if( i > order_site + 1)  // �����ǰλ���ڲ�����֮��
		{
			if (type == 1)
			{
				if (order[i] < '0' || order[i] > '9')	// -c�Ĳ�������Ϊ����
				{
					flag = 0;
					num = 0;	//  �Է�����Ϊǰ���ֺ��ַ��������ɻ����
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