#pragma once
#include<cstring>
#define _CRT_SECURE_NO_WARNINGS
class Course {
private:
	char* _name; //课程名
	char* _num; //课程编号
	int _stus; //学生数
	int _totalscore; //当前所有学生获得的总分
public:
	Course(char* name, char* num, int stus, int totalscore);
	Course() { _name = NULL; _num = NULL; _stus = 0; _totalscore = 0; };
	double get_avg_score(); //得到平均分
	friend class Admin;
};