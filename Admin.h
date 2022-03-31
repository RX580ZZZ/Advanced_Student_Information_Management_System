#pragma once
#include "Course.h"
#include"Student.h"
#include"reguexpr.h"
#include<vector>
using namespace std;
class Admin { //对存储进行操作的类
private:
	vector<Student> _students; //存储所有学生信息
	vector<Course> _courses; //存储所有课程信息
	vector<Student> _temp; //用于查询时临时存储
	int StuCouSco(char* num, char* s); //用于学生查询具体某门课程的成绩
public:
	Admin() {};
	bool hasStu(char* num); // 判断是否存在某学号的学生
	bool hasCou(char* s);// 判断是否存在该课程信息
	bool StuhasCou(char* num, char* s); //判断某个学生是否有某项课程的记录
	void Add_student(char* num, char* name, char* major, int sclass, int nums, vector<course_condition> courses); //增加一名学生的信息
	bool Add_Cou_Info(char* s, int score); //为课程增加一个分数
	void Add_Cou(char* num, char* name, int stus, int totalscore); //向课程列表增加一项课程
	void Delete_student(char* num); //删除一名学生的信息
	void Reduce_Course_Info(char* s, int score); //某项课程去掉一名学生的分数
	void Show_Student_Info(char* num); //打印学号为num的学生的信息
	void Modify_Student_Info(char* num, int n, char* s, int l); //修改学号为num学生的某项信息
	void Save_Info_to_file(FILE* pfile1, int n ,bool b); //存信息到文件，0:全部学生, 1:_temp中的部分学生；b true需要打印成绩，false不需要打印成绩
	void Read_info_from_file(FILE* pfile1); //从文件中读取学生信息
	void Show_Info(int n, char* s, int l, bool b1);//打印信息 n = 1 课程 2 院系 3 班级; b1是否需要打印学生信息
	//void Print_Info_to_file(FILE* pfile1, int n, char* s, int l, bool b1, bool b); //向文件中写入信息 n = 0 院系 1 班级 2 课程; b 同上
	void Vague_Search(char* expr, int& ret); //模糊匹配
	void Advanced_Search(char* s, int n, int l, bool isand, bool isequal, bool first); //高级匹配 l：1：匹配学号 2：姓名 3：选课 4：院系 5：班级  isequal：相等或不等 isand: 与还是或
	void cleartemp() { _temp.clear(); };//清空暂存变量
	bool temphasStu(char* num); //检查temp中是否存在某学生
	void print_temp(); //输出temp中存储的学生信息
};