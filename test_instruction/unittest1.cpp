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
		
		TEST_METHOD(right_instruction1)	// 正确指令测试1
		{
			// TODO: 在此输入测试代码
			char order[] = "-c 1000000";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(1, flag);
		}

		TEST_METHOD(right_instruction2)	//  正确指令测试2
		{
			// TODO: 在此输入测试代码
			char order[] = "-s absolute_path_of_puzzle.txt";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(1, flag);
		}

		TEST_METHOD(len_error)	//  指令长度错误
		{
			// TODO: 在此输入测试代码
			char order[] = "";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(op_error)	//  操作符错误
		{
			// TODO: 在此输入测试代码
			char order[] = "-a 10";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(sequence_error)	// 指令顺序错误
		{
			// TODO: 在此输入测试代码
			char order[] = "s- test.txt";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(match_error)	// 操作符和参数匹配错误
		{
			// TODO: 在此输入测试代码
			char order[] = "-c test.txt";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(parameter_error)	//  参数错误
		{
			// TODO: 在此输入测试代码
			char order[] = "-c 1e6";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(blank_num_error1)	//  空格数错误1
		{
			// TODO: 在此输入测试代码
			char order[] = "-c20";		//  没有空格
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(blank_num_error2)	//  空格数错误2
		{
			// TODO: 在此输入测试代码
			char order[] = "-c  20";	// 空格太多
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}

		TEST_METHOD(imcomplete_error)	// 指令不完整
		{
			// TODO: 在此输入测试代码
			char order[] = "c 20";
			int type, num;
			char name[100];

			int flag = CheckOrder(order, num, name, type);

			Assert::AreEqual(0, flag);
		}
	};
}