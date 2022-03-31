#include<iostream>
#include<iomanip>
#include<conio.h>
#include"Student.h"
#include"Course.h"
#include"ui.h"
#include"Admin.h"
#include"reguexpr.h"

using namespace std;

Admin my_admin;

int main() {
	int p = 1;
	while (p == 1) {
		p = Maininterface();
	}

	/*char s[50] = "$(李|想)";
	int ret = 0;
	char s1[50] = "张想";
	reguexpr my_regu(s, ret);
	cout << my_regu.match(s1);*/
	return 0;
}