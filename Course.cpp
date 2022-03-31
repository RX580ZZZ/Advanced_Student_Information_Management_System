#define _CRT_SECURE_NO_WARNINGS
#include"Course.h"
#include<cstring>

using namespace std;
Course::Course(char* name, char* num, int stus, int totalscore) {
	_name = new char[strlen(name) + 1];
	strcpy(_name, name);

	_num = new char[strlen(num) + 1];
	strcpy(_num, num);

	_stus = stus;
	_totalscore = totalscore;
};

double Course::get_avg_score() {
	if (_stus != 0) return (double)_totalscore / _stus;
	else return 0;
}