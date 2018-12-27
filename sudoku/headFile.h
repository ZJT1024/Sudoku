#pragma once


#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream> 

typedef long long int ll;

const int Maxn = 1e6 + 10;	//  需求数最大数 + 10
const int Maxm = 10;		//  理论上用9即可，但是为了防止不知名错误而越界，多加一个可以给字符串用
const int INF = 0x3f3f3f3f; //  视为正无穷使用
const int first_num = (2 + 5) % 9 + 1;  //  按题目要求，学号后两位相加模9再加1为第一行第一个数（所以首行不能动，第一个元素不参与首行全排列）