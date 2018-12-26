#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\sudoku\CheckOrder.h"
#include "../sudoku/CheckOrder.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_instruction
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(right_instruction1)	// ��ȷָ�����1
		{
			// TODO: �ڴ�������Դ���
			char order[] = "-c 1000000";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(1, flag);
		}

		TEST_METHOD(right_instruction2)	//  ��ȷָ�����2
		{
			// TODO: �ڴ�������Դ���
			char order[] = "-s absolute_path_of_puzzle.txt";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(1, flag);
		}

		TEST_METHOD(len_error)	//  ָ��ȴ���
		{
			// TODO: �ڴ�������Դ���
			char order[] = "";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(op_error)	//  ����������
		{
			// TODO: �ڴ�������Դ���
			char order[] = "-a 10";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(sequence_error)	// ָ��˳�����
		{
			// TODO: �ڴ�������Դ���
			char order[] = "s- test.txt";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(match_error)	// �������Ͳ���ƥ�����
		{
			// TODO: �ڴ�������Դ���
			char order[] = "-c test.txt";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(parameter_error)	//  ��������
		{
			// TODO: �ڴ�������Դ���
			char order[] = "-c 1e6";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(blank_num_error1)	//  �ո�������1
		{
			// TODO: �ڴ�������Դ���
			char order[] = "-c20";		//  û�пո�
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(blank_num_error2)	//  �ո�������2
		{
			// TODO: �ڴ�������Դ���
			char order[] = "-c  20";	// �ո�̫��
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(imcomplete_error)	// ָ�����
		{
			// TODO: �ڴ�������Դ���
			char order[] = "c 20";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}
	};
}