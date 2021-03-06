#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<conio.h>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include"Admin.h"

using namespace std;

int Admin::StuCouSco(char* num, char* s) {
	vector<Student>::iterator it;
	for (it = _students.begin();it != _students.end();it++) {
		if (strcmp(it->_num, num) == 0) break;
	}

	vector<course_condition>::iterator it1;
	for (it1 = it->_courses.begin();it1 != it->_courses.end();it1++) {
		if (strcmp(it1->_course_num, s) == 0) return it1->_score;
	}

	return -1;
}

bool Admin::hasStu(char* num) {
	int len = _students.size();
	for (int i = 0; i < len; i++) {
		if (strcmp(_students[i]._num, num) == 0) return true;
	}
	return false;
}

bool Admin::temphasStu(char* num) {
	vector<Student>::iterator it;
	for (it = _temp.begin();it != _temp.end();it++) {
		if (strcmp(num, it->_num) == 0 || strcmp(num, it->_name) == 0) return true;
	}
	return false;
}

bool Admin::hasCou(char* s) {
	int len = _courses.size();
	for (int i = 0; i < len; i++) {
		if (_courses[i]._name != NULL && strcmp(_courses[i]._name, s)== 0 || strcmp(_courses[i]._num, s) == 0) return true;
	}
	return false;
}

bool Admin::StuhasCou(char* num ,char* s) {
	vector<Student>::iterator it;
	for (it = _students.begin();it != _students.end();it++) {
		if (strcmp(it->_num, num) == 0) break;
	}

	vector<course_condition>::iterator it1;
	for (it1 = it->_courses.begin();it1 != it->_courses.end();it1++) {
		if (strcmp(it1->_course_num, s) == 0) return true;
	}

	return false;
}
void Admin::Add_student(char* num, char* name, char* major, int sclass, int nums, vector<course_condition> courses) {
	Student my_student;
	my_student._class = sclass;
	my_student._courses = courses;
	my_student._nums = nums;
	
	my_student._num = new char[strlen(num) + 1];
	strcpy(my_student._num, num);

	my_student._major = new char[strlen(major) + 1];
	strcpy(my_student._major, major);

	my_student._name = new char[strlen(name) + 1];
	strcpy(my_student._name, name);

	_students.push_back(my_student);
}

bool Admin::Add_Cou_Info(char* s, int score) {
	int len = _courses.size();
	for (int i = 0; i < len; i++) {
		if (_courses[i]._name != NULL && strcmp(_courses[i]._name, s) == 0 || strcmp(_courses[i]._num, s) == 0) {
			_courses[i]._stus++;
			_courses[i]._totalscore += score;
			return true;
		}
	}
	return false;
}

void Admin::Add_Cou(char* num, char* name, int stus, int totalscore) {
	Course my_course;
	my_course._num = new char[strlen(num) + 1];
	strcpy(my_course._num, num);

	if (name == NULL) my_course._name = NULL;
	else {
		my_course._name = new char[strlen(name) + 1];
		strcpy(my_course._name, name);
	}

	my_course._stus = stus;
	my_course._totalscore = totalscore;

	_courses.push_back(my_course);
}

void Admin::Delete_student(char* num) {
	vector<Student>::iterator it;
	for (it = _students.begin();it != _students.end();it++) { 
		if (strcmp(it->_num, num) == 0) break;
	}

	if (it->_courses.empty() == false) {
		int len = it->_courses.size();
		for (int i = 0; i < len; i++) {
			Reduce_Course_Info(it->_courses[i]._course_num, it->_courses[i]._score);
		}
	}
	_students.erase(it);
}

void Admin::Reduce_Course_Info(char* s, int score) {
	vector<Course>::iterator it;
	for (it = _courses.begin(); it != _courses.end(); it++) {
		if (it->_name != NULL && strcmp(it->_name, s) == 0 || strcmp(it->_num, s) == 0) {
			it->_stus--; it->_totalscore -= score; break;
		}
	}
}

void Admin::Show_Student_Info(char* num) {
	vector<Student>::iterator it;
	for (it = _students.begin();it != _students.end();it++) {
		if (strcmp(it->_num, num) == 0) break;
	}

	cout << "?????????" << it->_num << endl;
	cout << "?????????" << it->_name << endl;
	cout << "?????????" << it->_major << endl;
	cout << "?????????" << it->_class << endl;
	cout << "??????????????????" << it->_nums << endl;
	if (it->_nums != 0) {
		cout << "???????????????????????????" << endl;
		for (int i = 0; i < it->_nums; i++) {
			cout << it->_courses[i]._course_num << setw(15) << it->_courses[i]._score << endl;
		}
	}
}

void Admin::Modify_Student_Info(char* num, int n, char* s, int l) {
	vector<Student>::iterator it;
	for (it = _students.begin();it != _students.end();it++) {
		if (strcmp(it->_num, num) == 0) break;
	}

	switch (n) {
	case 1:
		it->_name = new char[strlen(s) + 1];
		strcpy(it->_name, s);
		break;
	case 2:
		it->_major = new char[strlen(s) + 1];
		strcpy(it->_major, s);
		break;
	case 3:
		it->_class = l;
		break;
	case 4:
		if (StuhasCou(num, s) == true) { //??????
			vector<course_condition>::iterator it1;
			for (it1 = it->_courses.begin();it1 != it->_courses.end();it1++) {
				if (strcmp(it1->_course_num, s) == 0) {
					Add_Cou_Info(s, l);
					Reduce_Course_Info(s, it1->_score);
					it1->_score = l;
					break;
				}
			}
		}
		else { //??????
			course_condition temp;
			temp._course_num = new char[strlen(s) + 1];
			strcpy(temp._course_num, s);
			temp._score = l;
			it->_courses.push_back(temp);
			it->_nums++;
			Add_Cou(s, NULL, 1, l);
		}
		break;
	case 5:
		vector<course_condition>::iterator it1;
		for (it1 = it->_courses.begin();it1 != it->_courses.end();it1++) {
			if (strcmp(it1->_course_num, s) == 0) break;
		}
		Reduce_Course_Info(s, it1->_score);
		it->_courses.erase(it1);
		it->_nums--;
		
	}
}

void Admin::Save_Info_to_file(FILE* pfile1, int n, bool b) {
	vector<Student> out;
	if (n == 0) out = _students;
	else out = _temp;

	vector<Student>::iterator it;
	for (it = out.begin();it != out.end();it++) {
		fprintf(pfile1, "%s %s %s %d %d\n", it->_num, it->_name, it->_major, it->_class, it->_nums);
		if (b == true) {
			vector<course_condition>::iterator it1;
			for (it1 = it->_courses.begin();it1 != it->_courses.end();it1++) {
				fprintf(pfile1, "%s %d\n", it1->_course_num, it1->_score);
			}
		}
	}
}

void Admin::Read_info_from_file(FILE* pfile1) {
	bool fault = false;
	while (!feof(pfile1)) {
		fault = false;
		Student temp;
		temp._num = new char[20];
		temp._name = new char[20];
		temp._major = new char[50];
		fscanf(pfile1, "%s %s %s %d %d\n", temp._num, temp._name, temp._major, &temp._class, &temp._nums);
		if (hasStu(temp._num) == true) {
			cout << "Error: ???????????? " << temp._num << "????????????????????????????????????????????????????????????????????????" << endl;
			fault = true;
		}
		if (temp._nums != 0) {
			for (int i = 0; i < temp._nums; i++) {
				course_condition t;
				t._course_num = new char[20];
				fscanf(pfile1, "%s %d\n", t._course_num, &t._score);
				if (fault == false) { //?????????????????????????????????
					vector<course_condition>::iterator it;
					for (it = temp._courses.begin();it != temp._courses.end();it++) { //??????????????????
						if (strcmp(it->_course_num, t._course_num) == 0) {
							fault = true;
							cout << "Error: ???????????? " << temp._num << "?????????????????????????????????????????????????????????" << endl;
							break;
						}
					}
				}
				temp._courses.push_back(t);
			}
		}
		if (fault == false) {
			_students.push_back(temp); //???????????????????????????????????????
			vector<course_condition>::iterator it;
			for (it = temp._courses.begin();it != temp._courses.end();it++) { 
				if (hasCou(it->_course_num) == true) {
					Add_Cou_Info(it->_course_num, it->_score);
				}
				else Add_Cou(it->_course_num, NULL, 1, it->_score);
			}
		}
	}
}

void Admin::Show_Info(int n, char* s, int l, bool b1) {
	if (n == 1) {
		vector<Student>::iterator it;
		for (it = _students.begin();it != _students.end();it++) {
			if (StuhasCou(it->_num, s) == true) _temp.push_back(*it);
		}

		vector<Course>::iterator it1;
		for (it1 = _courses.begin(); it1 != _courses.end(); it1++) {
			if (it1->_name != NULL && strcmp(it1->_name, s) == 0 || strcmp(it1->_num, s) == 0) break;
		}
		cout << "???????????????" << s << endl;
		if (it1->_name != NULL) cout << "???????????????" << it1->_name << endl;
		cout << "???????????????" << it1->_stus << endl;
		cout << "????????????" << it1->get_avg_score() << endl;

		if (_temp.size() == 0 || it1->_stus == 0) b1 = false;
	}
	else if (n == 2) {
		vector<Student>::iterator it;
		for (it = _students.begin();it != _students.end();it++) {
			if (strcmp(it->_major, s) == 0) _temp.push_back(*it);
		}
		if (_temp.empty() == true) {
			cout << "??????????????????????????????" << endl;
			b1 = false;
			return;
		}
		else
		{
			cout << "????????????" << s << endl;
			cout << "???????????????" << _temp.size() << endl;
		}
	}
	else if (n == 3) {
		vector<Student>::iterator it;
		for (it = _students.begin();it != _students.end();it++) {
			if (it->_class == l) _temp.push_back(*it);
		}
		if (_temp.empty() == true) {
			cout << "??????????????????????????????" << endl;
			b1 = false;
			return;
		}
		else
		{
			cout << "?????????" << l << endl;
			cout << "???????????????" << _temp.size() << endl;
		}
	}


	if (b1 == true && n == 1)
	{
		cout << "?????????????????????" << endl;
		cout << setw(20) << "??????" << setw(20) << "??????" << setw(20) << "??????" << setw(10) << "??????" << setw(15) << "???????????????" << setw(15) << "??????????????????" << endl;
		vector<Student>::iterator it;
		for (it = _temp.begin();it != _temp.end();it++) {
			cout << setw(20) << it->_num << setw(20) << it->_name << setw(20) << it->_major << setw(10) << it->_class << setw(15) << it->_nums << setw(15) << StuCouSco(it->_num, s) << endl;
		}
	}
	else if (b1 == true)
	{
		cout << "?????????????????????" << endl;
		print_temp();
	}

	cleartemp();
}

void Admin::print_temp() {
	if (_temp.empty() == false) {
		cout << "???????????????????????????" << endl;
		cout << setw(20) << "??????" << setw(20) << "??????" << setw(20) << "??????" << setw(10) << "??????" << setw(15) << "???????????????" << endl;
		vector<Student>::iterator it;
		for (it = _temp.begin();it != _temp.end();it++) {
			cout << setw(20) << it->_num << setw(20) << it->_name << setw(20) << it->_major << setw(10) << it->_class << setw(15) << it->_nums << endl;
		}
	}
	else {
		cout << "????????????????????????????????????????????????" << endl;
	}
}

void Admin::Vague_Search(char* expr, int& ret) {
	reguexpr my_regu(expr, ret);
	if (ret == -1) return;

	vector<Student>::iterator it;
	for (it = _students.begin();it != _students.end();it++) { //??????????????????
		if (my_regu.match(it->_num) == true || my_regu.match(it->_name) == true) _temp.push_back(*it);
	}

	print_temp();

	cleartemp();
}

void Admin::Advanced_Search(char* s, int n, int l, bool isand, bool isequal, bool first) {
	bool b1 = false;
	if (first == true) { //?????????
		if (n >= 1 && n <= 4) {
			int ret = 0;
			reguexpr my_regu(s, ret);
			vector<Student>::iterator it;
			for (it = _students.begin();it != _students.end();it++) { //??????????????????
				switch (n)
				{
				case 1: //??????
					if ((my_regu.match(it->_num) ^ isequal) == 0) _temp.push_back(*it);
					break;
				case 2: //??????
					if ((my_regu.match(it->_name) ^ isequal) == 0) _temp.push_back(*it);
					break;
				case 3: //??????
					if ((my_regu.match(it->_major) ^ isequal) == 0) _temp.push_back(*it);
					break;
				case 4: //??????
					vector<course_condition>::iterator it1;
					for (it1 = it->_courses.begin();it1 != it->_courses.end();it1++) {
						if (my_regu.match(it1->_course_num) == true) {
							b1 = true;
							break;
						}
					}
					if ((b1 ^ isequal) == 0) _temp.push_back(*it);
					b1 = false;
					break;
				}
			}
		}
		else { //n == 5 ??????
			vector<Student>::iterator it;
			for (it = _students.begin();it != _students.end();it++) {
				if (((it->_class == l) ^ isequal) == 0) _temp.push_back(*it);
			}
		}
	}
	else { //???????????????
		if (isand == false) { //???
			if (n >= 1 && n <= 4) {
				int ret = 0;
				reguexpr my_regu(s, ret);
				vector<Student>::iterator it;
				for (it = _students.begin();it != _students.end();it++) { //??????????????????
					switch (n)
					{
					case 1: //??????
						if ((my_regu.match(it->_num) ^ isequal) == 0 && temphasStu(it->_num) == false) _temp.push_back(*it);
						break;
					case 2: //??????
						if ((my_regu.match(it->_name) ^ isequal) == 0 && temphasStu(it->_num) == false) _temp.push_back(*it);
						break;
					case 3: //??????
						if ((my_regu.match(it->_major) ^ isequal) == 0 && temphasStu(it->_num) == false) _temp.push_back(*it);
						break;
					case 4: //??????
						vector<course_condition>::iterator it1;

						for (it1 = it->_courses.begin();it1 != it->_courses.end();it1++) {
							//if ((my_regu.match(it1->_course_num) ^ isequal) == 0 && temphasStu(it->_num) == false) {
							if (my_regu.match(it1->_course_num) == true){
								b1 = true;
								break;
							}
						}
						if ((b1 ^ isequal) == 0 && temphasStu(it->_num) == false) _temp.push_back(*it);
						b1 = false;
						break;
					}
				}
			}
			else { //n == 5 ??????
				vector<Student>::iterator it;
				for (it = _students.begin();it != _students.end();it++) {
					if (((it->_class == l) ^ isequal) == 0 && temphasStu(it->_num) == false) _temp.push_back(*it);
				}
			}
		}
		else { //???
			if (n >= 1 && n <= 4) {
				int ret = 0;
				reguexpr my_regu(s, ret);
				vector<Student>::iterator it;
				it = _temp.begin();
				while (it != _temp.end()) { //??????????????????
					switch (n)
					{
					case 1: //??????
						if ((my_regu.match(it->_num) ^ isequal) == 1) {
							it = _temp.erase(it);
							continue;
						}
						break;
					case 2: //??????
						if ((my_regu.match(it->_name) ^ isequal) == 1) {
							it = _temp.erase(it);
							continue;
						}
						break;
					case 3: //??????
						if ((my_regu.match(it->_major) ^ isequal) == 1) {
							it = _temp.erase(it);
							continue;
						}
						break;
					case 4: //??????
						vector<course_condition>::iterator it1;
						
						for (it1 = it->_courses.begin();it1 != it->_courses.end();it1++) {
							if (my_regu.match(it1->_course_num) == true) {
								b1 = true;
								break;
							}
						}
						if ((b1 ^ isequal) == 1) {
							it = _temp.erase(it);
							continue;
						}
						b1 = false;
						break;
					}
					it++;
				}
			}
			else { //n == 5 ??????
				vector<Student>::iterator it;
				it = _temp.begin();
				while (it != _temp.end()) {
					if (((it->_class == l) ^ isequal) == 1) {
						it = _temp.erase(it);
						continue;
					}
					it++;
				}
			}
		}
	}

}

