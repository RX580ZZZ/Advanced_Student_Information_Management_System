#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<conio.h>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include"reguexpr.h"
using namespace std;

reguexpr::reguexpr(char* expr, int& ret) {
	ret = 0;
	int len = strlen(expr);
	head = new char[len + 1];
	memset(head, 0, sizeof(char) * (len + 1));
	head_b = new char[len + 1];
	memset(head_b, 0, sizeof(char) * (len + 1));
	tail = new char[len + 1];
	memset(tail, 0, sizeof(char) * (len + 1));
	tail_b = new char[len + 1];
	memset(tail_b, 0, sizeof(char) * (len + 1));

	head_p = 0;
	tail_p = 0;
	ishead = false;
	istail = false;
	int leftnum = 0; //检查匹配括号数
	bool isor = false; //是否是或的情况
	int temp = 0; //记录或的情况

	bool headt = true; // true:读入head, false:读入tail

	for (int i = 0; i < len; i++) {
		if (expr[i] == '^' /*&& (i == 0 || expr[i - 1] >= 0)*/) { //&&之后内容是为了防止中文干扰
			ishead = true; headt = true;
		}
		else if (expr[i] == '$') {
			istail = true; headt = false;
		}
		else if (expr[i] == ')' /*&& (i == 0 || expr[i - 1] >= 0)*/){
			leftnum--;
			temp = 0;
			isor = false;
		}
		else if (expr[i] == '(' /*&& (i == 0 || expr[i - 1] >= 0)*/) {
			leftnum++;
			if (headt == true) temp = head_p;
			else temp = tail_p;
		}
		else if (expr[i] == '|' /*&& (i == 0 || expr[i - 1] >= 0)*/){ //读入备份组
			

			isor = true;
		}
		else{
			if (headt == true) { //仍在头模式
				if (isor == true) { // 记录或
					head_b[temp] = expr[i];
					temp++;
				}
				else {
					head[head_p] = expr[i];
					head_p++;
				}
			}
			else {
				if (isor == true) { 
					tail_b[temp] = expr[i];
					temp++;
				}
				else {
					tail[tail_p] = expr[i];
					tail_p++;
				}
			}
		}
	}

	if (leftnum != 0) ret = -1; //有错
}

bool reguexpr::match(char* expr) {
	int expr_len = strlen(expr);
	int head_t = 0;
	int tail_t = 0;
	int expr_t = 0;

	if (expr_len < head_p) return false; //长度不够
	while (head_t < head_p) {
		if (head[head_t] == '.') { //任意都可以匹配
			if (expr[expr_t] < 0) expr_t++; // 中文字符占2个字节
		}
		else {
			if (head[head_t] != expr[expr_t] && head_b[head_t] != expr[expr_t]) return false; //匹配失败
		}

		head_t++;
		expr_t++;
	}

	if (ishead == false && head_p != 0) { //无'^'的情况，长度必须相同
		if (expr_t != expr_len) return false;
	}

	if (istail == true) {
		expr_t = expr_len - tail_p;
		if (expr_t < 0) return false;
		while (tail_t < tail_p) {
			if (tail[tail_t] == '.') { //任意都可以匹配
				if (expr[expr_t] < 0) expr_t++; // 中文字符占2个字节
			}
			else {
				if (tail[tail_t] != expr[expr_t] && tail_b[tail_t] != expr[expr_t]) return false; //匹配失败
			}

			tail_t++;
			expr_t++;
		}
	}

	return true;
}