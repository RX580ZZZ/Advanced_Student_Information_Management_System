#pragma once
#include<vector>
using namespace std;

struct course_condition {
	char* _course_num; //课程编号
	int _score; //成绩
};
class Student {
	
private:
	char* _name; //姓名
	char* _major; //院系
	char* _num; //学号
	int _class; //班级
	int _nums;//选修课程数
	vector <course_condition> _courses; //课程情况
public:
	friend class Admin;
	Student() { _name = NULL; _major = NULL; _num = NULL; _class = 0; _nums = 0; };
};
