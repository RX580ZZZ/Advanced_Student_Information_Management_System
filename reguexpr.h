#pragma once
#include "Course.h"
#include"Student.h"
#include<vector>

class reguexpr { //存储、分析表达式
private:
	char* head; //存储head与默认情况 ^标识
	char* head_b; //在对应位置存储 | 的情况
	int head_p;
	char* tail;//tail， $标识
	char* tail_b;
	int tail_p;
	bool ishead; //是否有^,有的话只需要匹配前n项，否则需要对齐
	bool istail; //是否有$

public:
	reguexpr(char* expr, int& ret); //初始化
	bool match(char* expr); //判断是否匹配
};