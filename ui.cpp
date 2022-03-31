#define _CRT_SECURE_NO_WARNINGS
#include"ui.h"
#include"Admin.h"
#include"Student.h"
#include"Course.h"
#include<iostream>
#include<cstdlib>
using namespace std;

extern Admin my_admin;

void wrong_expr() {
	cout << "输入的表达式有误！" << endl;
	printaline();
}
void printaline()
{
	for (int i = 0;i < 120;i++)
	{
		cout << "=";
	}
	cout << endl;
}

int Maininterface() {
	
	cout << "欢迎使用高级学生信息管理系统！" << endl; 
	cout << "1.添加学生信息 2.删除学生信息 3.查找学生信息 4.修改学生信息 5.查询课程、院系或班级信息 6.保存学生信息至文件 7.从文件中读取学生信息 8. 模糊搜索学生信息 9. 高级搜索学生信息 10.高级搜索字符串版 11.退出系统" << endl;
	printaline();
	cout << "请输入选择：";
	int n = 0;
	cin >> n;
	bool b = false;
	while (!b)
	{
		switch (n)
		{
		case 1:
			Add_student();
			b = true;
			break;
		case 2:
			Delete_student();
			b = true;
			break;
		case 3:
			Find_student();
			b = true;
			break;
		case 4:
			Modify_student();
			b = true;
			break;
		case 5:
			Find_info();
			b = true;
			break;
		case 6:
			Save_student_info_to_file();
			b = true;
			break;
		case 7:
			Read_stu_data_to_program();
			b = true;
			break;
		case 8:
			Vague_Search();
			b = true;
			break;
		case 9:
			Advanced_Search();
			b = true;
			break;
		case 10:
			Advanced_Search_string();
			b = true;
			break;
		case 11: return 0;
		default: cout << "输入不正确！请重新输入：";
			cin >> n;
			break;
		}
	}
	return 1;
}

void Add_student() {
	cout << "请输入学生学号：";
	char num[20]; cin >> num;
	if (my_admin.hasStu(num) == true) {
		cout << "该学生已存在！" << endl;
		printaline();
		return;
	}
	cout << "请输入学生姓名：";
	char name[30]; cin >> name;
	cout << "请输入学生院系：";
	char major[50]; cin >> major;
	cout << "请输入学生班级：";
	int sclass; cin >> sclass;
	cout << "请输入学生已修课程数：";
	int nums; cin >> nums;
	vector<course_condition> courses;
	if (nums > 0) {
		cout << "请输入学生选修的课程编号及成绩：" << endl;
		bool repeated = true;
		while (repeated) {
			repeated = false;
			for (int i = 0; i < nums; i++) {
				course_condition temp;
				temp._course_num = new char[20];
				cin >> temp._course_num >> temp._score;
				
				vector<course_condition>::iterator it;
				for (it = courses.begin();it != courses.end();it++){ //检测是否重复
					if (strcmp(it->_course_num, temp._course_num) == 0) {
						repeated = true;
						break;
					}
				}
				courses.push_back(temp);
				if (repeated == true) break;
			}
			if (repeated == true) {
				cout << "存在重复的课程编号！请全部重新输入：" << endl;
				courses.clear();
			}
		}
	}
	int len = courses.size();
	for (int i = 0; i < len; i++) { //根据输入更新课程信息
		if (my_admin.hasCou(courses[i]._course_num) == true) {
			my_admin.Add_Cou_Info(courses[i]._course_num, courses[i]._score);
		}
		else {
			my_admin.Add_Cou(courses[i]._course_num, NULL, 1, courses[i]._score);
		}
	}
	my_admin.Add_student(num, name, major, sclass, nums, courses);

	cout << "添加成功！"<< endl;
	printaline();
}

void Delete_student() {
	cout << "请输入学生学号：";
	char num[20]; cin >> num;
	if (my_admin.hasStu(num) != true) {
		cout << "该学生不存在！" << endl;
		printaline();
		return;
	}

	my_admin.Delete_student(num);
	cout << "删除成功！" << endl;
	printaline();
}

void Find_student() {
	cout << "请输入学生学号：";
	char num[20]; cin >> num;

	if (my_admin.hasStu(num) != true) {
		cout << "该学生不存在！" << endl;
		printaline();
		return;
	}
	cout << "学生信息：" << endl;
	my_admin.Show_Student_Info(num);

	printaline();
}

void Vague_Search() {
	cout << "请输入表达式：";
	char expr[20]; cin >> expr;
	int ret = 0;
	my_admin.Vague_Search(expr, ret);

	if (ret == -1) cout << "输入的表达式有误！" << endl;
	my_admin.cleartemp();

	printaline();
}

void Modify_student() {
	cout << "请输入学生学号：";
	char num[20]; cin >> num;

	if (my_admin.hasStu(num) != true) {
		cout << "该学生不存在！" << endl;
		printaline();
		return;
	}
	cout << "当前学生信息：" << endl;
	my_admin.Show_Student_Info(num);
	printaline();
	bool b = true;
	while (b == true) {
		cout << "可选修改项目：1.姓名 2.院系 3.班级 4.课程信息 5.退出至首页" << endl;
		cout << "请选择要修改的项目：";
		int n = -1;
		bool b1 = false;
		bool b2 = false;
		
		while (n < 1 || n > 5) {
			cin >> n;
			switch (n) {
			case 1:
				cout << "请输入修改后姓名：";
				char s[20]; cin >> s;
				my_admin.Modify_Student_Info(num, 1, s, -1);
				b1 = true;
				break;
			case 2: 
				cout << "请输入修改后院系：";
				char s1[50]; cin >> s1;
				my_admin.Modify_Student_Info(num, 2, s1, -1);
				b1 = true;
				break;
			case 3:
				cout << "请输入修改后班级：";
				int k1; cin >> k1;
				my_admin.Modify_Student_Info(num, 3, NULL, k1);
				b1 = true;
				break;
			case 4:
				b2 = false;
				cout << "可选修改方式：1.添加或修改某课程成绩 2.删除某项课程及成绩 3.返回上一级" << endl;
				cout << "请选择修改方式：";
				int k; 
				while (!b2) {
					
					cin >> k;
					switch (k)
					{
					case 1:
						cout << "请输入要添加或修改的课程号及成绩：";
						char s[20]; int score; cin >> s >> score;
						my_admin.Modify_Student_Info(num, 4, s, score);
						b2 = true; b1 = true;
						break;
					case 2:
						cout << "请输入要从该学生课表中删除的课程号：";
						char s2[20]; cin >> s2;
						if (my_admin.StuhasCou(num, s2) == true) {
							my_admin.Modify_Student_Info(num, 5, s2, -1);
							b2 = true; b1 = true;
						}
						else {
							cout << "删除课程不存在！自动返回上一级" << endl;
							printaline();
							k = 3;
						}
						break;
					case 3:
						printaline();
						break;
					default:
						cout << "输入错误！请重新输入：";
						break;
					}
					if (k == 3) break;
				}
				if (b2 != false) b1 = true;
				else {
					n = -1;
					cout << "可选修改项目：1.姓名 2.院系 3.班级 4.课程信息 5.退出至首页" << endl;
					cout << "请选择要修改的项目：";
				}
				break;
			case 5:
				printaline();
				return;
			default:
				cout << "输入错误！请重新输入：";
			}
		}
		cout << "修改成功！修改后学生信息：" << endl;
		my_admin.Show_Student_Info(num);
		cout <<"是否需要继续修改（y or 默认n）：";
		char c; cin >> c;
		if (c != 'y') b = false;
		printaline();
	}
}

void Advanced_Search() {
	bool b = true;

	bool first = true;
	while (b == true)
	{

		cout << "可选搜索项目：1.学号 2.姓名 3.院系 4.选课 5.班级 6.退出至首页" << endl;
		cout << "请选择要搜索的项目：";
		int n = -1;
		bool isand = true;
		bool isequal = true;
		char s[20];
		memset(s, 0, sizeof(s));
		int l = -1;

		while (n < 1 || n > 6) {
			cin >> n;
			switch (n) {
			case 1:
			case 2:
			case 3:
			case 4:
				cout << "请输入表达式：";
				cin >> s;
				break;
			case 5:
				cout << "请输入班级：";
				cin >> l;
				break;
			case 6:
				printaline();
				return;
			default:
				cout << "输入错误！请重新输入：";
			}
		}
		if (n >= 1 && n <= 4) { //检查表达式是否有错
			int ret = 0;
			reguexpr my_regu(s, ret);
			if (ret == -1) {
				cout << "输入的表达式有误！" << endl;
				printaline();
				continue;
			}
		}

		char c;
		cout << "请选择需要搜索的项是等于还是不等于该表达式（默认y：等于 or n：不等于）：";
		cin >> c;
		if (c == 'n') isequal = false;
		else isequal = true;

		if (first != true) {
			cout << "请选择该条件与之前条件的关系（默认y：与 or h：或）：";
			cin >> c;
			if (c == 'h') isand = false;
			else isand = true;
		}

		my_admin.Advanced_Search(s, n, l, isand, isequal, first);
		if (first == true) first = false;
		cout << "请输入是否要继续增加条件（y or 默认n）：";
		cin >> c;
		if (c != 'y') b = false;
		printaline();
	}

	my_admin.print_temp();
	printaline();
	my_admin.cleartemp();
}

void Advanced_Search_string() {
	char* s = new char[100];
	cout << "请输入表达式：";
	cin.get();
	cin.getline(s, 100);
	int slen = strlen(s);
	int p = 0;
	char* temp = new char[100];
	memset(temp, 0, 100 * sizeof(char));
	int tp = 0;
	bool isand = false;
	bool isequal = false;
	bool first = true;
	int n = 0;
	int l = 0;
	int judge = -1;
	while (p < slen) {
		if (s[p] == '"') {
			int ret = 0;
			char* expr = new char[100];
			memset(expr, 0, 100 * sizeof(char));
			int ep = 0;
			p++;
			while (s[p] != '"' && p != slen) { //读取表达式
				if (s[p] != ' ') { //空格忽略
					expr[ep] = s[p];
					ep++;
				}
				p++;
			}

			if (p == slen) { // 引号不匹配
				wrong_expr();
				my_admin.cleartemp();
				return;
			}
			reguexpr my_regu(expr, ret);
			if (ret == -1) {
				wrong_expr();
				my_admin.cleartemp();
				return;
			}

			if (strcmp(temp, "学号") == 0) n = 1;
			else if (strcmp(temp, "姓名") == 0) n = 2;
			else if (strcmp(temp, "院系") == 0) n = 3;
			else if (strcmp(temp, "选课") == 0) n = 4;
			else if (strcmp(temp, "班级") == 0) {
				n = 5; l = atoi(expr);
			}
			else { //选项输入不正确
				wrong_expr();
				my_admin.cleartemp();
				return;
			}

			my_admin.Advanced_Search(expr, n, l, isand, isequal, first);
			if (first == true) first = false;
			judge = tp; isand = false;
		}
		else if (s[p] == '!'){ //不等于
			p++; isequal = false;
		}
		else if (s[p] == '=') { //等于
			isequal = true;
		}
		else if (s[p] == '&') {
			p++; isand = true;
		}
		else if (s[p] == '|') {
			p++; isand = false;
		}
		else if (s[p] != ' '){ //读入选项, 空格直接忽略
			if (tp == judge) {
				judge = -1;
				memset(temp, 0, 100 * sizeof(char));
				tp = 0;
				isequal = false;
				n = 0;
				l = 0;
			}
			
			temp[tp] = s[p];
			tp++;
		}
		p++;
	}
	
	my_admin.print_temp();
	printaline();
	my_admin.cleartemp();
}

void Save_student_info_to_file() {
	cout << "请输入保存的文件名：";
	char s[50]; cin >> s;
	FILE* pfile1 = NULL;
	if (fopen(s, "r") != NULL) {
		pfile1 = fopen(s, "a");
	}
	else {
		pfile1 = fopen(s, "w");
	}

	my_admin.Save_Info_to_file(pfile1, 0, true);
	fclose(pfile1);

	cout << "保存成功！" << endl;
	printaline();
}

void Read_stu_data_to_program() {
	cout << "请输入待读取的文件名：";
	char s[50]; cin >> s;
	FILE* pfile1 = fopen(s, "r");
	if (pfile1 == NULL) {
		cout << "文件不存在！" << endl;
		printaline();
		return;
	}

	my_admin.Read_info_from_file(pfile1);

	fclose(pfile1);
	cout << "读取成功！" << endl;
	printaline();
}

void Find_info() {
	cout << "可选查询项目：1.课程信息 2.院系信息 3.班级信息 4.退出至首页" << endl;
	cout << "请选择要修改的项目：";
	int n = -1;
	bool b1 = false;
	char c;
	char s[50];
	int k;

	while (n < 1 || n > 4) {
		cin >> n; b1 = false;
		switch (n) {
		case 1:
			cout << "请输入要查询的课程编号或课程名：";
			cin >> s;
			if (my_admin.hasCou(s) == false) {
				cout << "不存在搜索的课程！" << endl;
				printaline();
				return;
			}
			cout << "是否需要输出符合条件的学生名单(y or 默认n)：";
			cin >> c;
			if (c == 'y') b1 = true;
			my_admin.Show_Info(n , s, -1, b1);
			break;
		case 2:
			cout << "请输入要查询的院系：";
			cin >> s;
			cout << "是否需要输出符合条件的学生名单(y or 默认n)：";
			cin >> c;
			if (c == 'y') b1 = true;
			my_admin.Show_Info(n, s, -1, b1);
			break;
		case 3:
			cout << "请输入要查询的班级：";
			cin >> k;
			cout << "是否需要输出符合条件的学生名单(y or 默认n)：";
			cin >> c;
			if (c == 'y') b1 = true;
			my_admin.Show_Info(n, NULL, k, b1);
			break;
		case 4:
			printaline();
			return;
		default:
			cout << "输入错误！请重新输入：";
		}
	}
	my_admin.cleartemp();

/*	cout << endl;
	cout << "是否需要将查询结果存入文件(y or 默认n)：";
	char c; cin >> c;
	if (c == 'y') {
		cout << "请输入存入的文件名：";
		char s[50]; cin >> s;
		FILE* pfile1 = NULL;
		if (fopen(s, "r") != NULL) {
			pfile1 = fopen(s, "a");
		}
		else {
			pfile1 = fopen(s, "w");
		}
		cout << "是否需要在文件中打印学生的具体成绩(y or 默认n)：";
		bool b;

		cout << "保存成功！" << endl;
	}
	else {
		my_admin.cleartemp();
	}
	*/
	printaline();
}