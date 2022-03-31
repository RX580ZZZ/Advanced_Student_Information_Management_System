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
	cout << "����ı��ʽ����" << endl;
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
	
	cout << "��ӭʹ�ø߼�ѧ����Ϣ����ϵͳ��" << endl; 
	cout << "1.���ѧ����Ϣ 2.ɾ��ѧ����Ϣ 3.����ѧ����Ϣ 4.�޸�ѧ����Ϣ 5.��ѯ�γ̡�Ժϵ��༶��Ϣ 6.����ѧ����Ϣ���ļ� 7.���ļ��ж�ȡѧ����Ϣ 8. ģ������ѧ����Ϣ 9. �߼�����ѧ����Ϣ 10.�߼������ַ����� 11.�˳�ϵͳ" << endl;
	printaline();
	cout << "������ѡ��";
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
		default: cout << "���벻��ȷ�����������룺";
			cin >> n;
			break;
		}
	}
	return 1;
}

void Add_student() {
	cout << "������ѧ��ѧ�ţ�";
	char num[20]; cin >> num;
	if (my_admin.hasStu(num) == true) {
		cout << "��ѧ���Ѵ��ڣ�" << endl;
		printaline();
		return;
	}
	cout << "������ѧ��������";
	char name[30]; cin >> name;
	cout << "������ѧ��Ժϵ��";
	char major[50]; cin >> major;
	cout << "������ѧ���༶��";
	int sclass; cin >> sclass;
	cout << "������ѧ�����޿γ�����";
	int nums; cin >> nums;
	vector<course_condition> courses;
	if (nums > 0) {
		cout << "������ѧ��ѡ�޵Ŀγ̱�ż��ɼ���" << endl;
		bool repeated = true;
		while (repeated) {
			repeated = false;
			for (int i = 0; i < nums; i++) {
				course_condition temp;
				temp._course_num = new char[20];
				cin >> temp._course_num >> temp._score;
				
				vector<course_condition>::iterator it;
				for (it = courses.begin();it != courses.end();it++){ //����Ƿ��ظ�
					if (strcmp(it->_course_num, temp._course_num) == 0) {
						repeated = true;
						break;
					}
				}
				courses.push_back(temp);
				if (repeated == true) break;
			}
			if (repeated == true) {
				cout << "�����ظ��Ŀγ̱�ţ���ȫ���������룺" << endl;
				courses.clear();
			}
		}
	}
	int len = courses.size();
	for (int i = 0; i < len; i++) { //����������¿γ���Ϣ
		if (my_admin.hasCou(courses[i]._course_num) == true) {
			my_admin.Add_Cou_Info(courses[i]._course_num, courses[i]._score);
		}
		else {
			my_admin.Add_Cou(courses[i]._course_num, NULL, 1, courses[i]._score);
		}
	}
	my_admin.Add_student(num, name, major, sclass, nums, courses);

	cout << "��ӳɹ���"<< endl;
	printaline();
}

void Delete_student() {
	cout << "������ѧ��ѧ�ţ�";
	char num[20]; cin >> num;
	if (my_admin.hasStu(num) != true) {
		cout << "��ѧ�������ڣ�" << endl;
		printaline();
		return;
	}

	my_admin.Delete_student(num);
	cout << "ɾ���ɹ���" << endl;
	printaline();
}

void Find_student() {
	cout << "������ѧ��ѧ�ţ�";
	char num[20]; cin >> num;

	if (my_admin.hasStu(num) != true) {
		cout << "��ѧ�������ڣ�" << endl;
		printaline();
		return;
	}
	cout << "ѧ����Ϣ��" << endl;
	my_admin.Show_Student_Info(num);

	printaline();
}

void Vague_Search() {
	cout << "��������ʽ��";
	char expr[20]; cin >> expr;
	int ret = 0;
	my_admin.Vague_Search(expr, ret);

	if (ret == -1) cout << "����ı��ʽ����" << endl;
	my_admin.cleartemp();

	printaline();
}

void Modify_student() {
	cout << "������ѧ��ѧ�ţ�";
	char num[20]; cin >> num;

	if (my_admin.hasStu(num) != true) {
		cout << "��ѧ�������ڣ�" << endl;
		printaline();
		return;
	}
	cout << "��ǰѧ����Ϣ��" << endl;
	my_admin.Show_Student_Info(num);
	printaline();
	bool b = true;
	while (b == true) {
		cout << "��ѡ�޸���Ŀ��1.���� 2.Ժϵ 3.�༶ 4.�γ���Ϣ 5.�˳�����ҳ" << endl;
		cout << "��ѡ��Ҫ�޸ĵ���Ŀ��";
		int n = -1;
		bool b1 = false;
		bool b2 = false;
		
		while (n < 1 || n > 5) {
			cin >> n;
			switch (n) {
			case 1:
				cout << "�������޸ĺ�������";
				char s[20]; cin >> s;
				my_admin.Modify_Student_Info(num, 1, s, -1);
				b1 = true;
				break;
			case 2: 
				cout << "�������޸ĺ�Ժϵ��";
				char s1[50]; cin >> s1;
				my_admin.Modify_Student_Info(num, 2, s1, -1);
				b1 = true;
				break;
			case 3:
				cout << "�������޸ĺ�༶��";
				int k1; cin >> k1;
				my_admin.Modify_Student_Info(num, 3, NULL, k1);
				b1 = true;
				break;
			case 4:
				b2 = false;
				cout << "��ѡ�޸ķ�ʽ��1.��ӻ��޸�ĳ�γ̳ɼ� 2.ɾ��ĳ��γ̼��ɼ� 3.������һ��" << endl;
				cout << "��ѡ���޸ķ�ʽ��";
				int k; 
				while (!b2) {
					
					cin >> k;
					switch (k)
					{
					case 1:
						cout << "������Ҫ��ӻ��޸ĵĿγ̺ż��ɼ���";
						char s[20]; int score; cin >> s >> score;
						my_admin.Modify_Student_Info(num, 4, s, score);
						b2 = true; b1 = true;
						break;
					case 2:
						cout << "������Ҫ�Ӹ�ѧ���α���ɾ���Ŀγ̺ţ�";
						char s2[20]; cin >> s2;
						if (my_admin.StuhasCou(num, s2) == true) {
							my_admin.Modify_Student_Info(num, 5, s2, -1);
							b2 = true; b1 = true;
						}
						else {
							cout << "ɾ���γ̲����ڣ��Զ�������һ��" << endl;
							printaline();
							k = 3;
						}
						break;
					case 3:
						printaline();
						break;
					default:
						cout << "����������������룺";
						break;
					}
					if (k == 3) break;
				}
				if (b2 != false) b1 = true;
				else {
					n = -1;
					cout << "��ѡ�޸���Ŀ��1.���� 2.Ժϵ 3.�༶ 4.�γ���Ϣ 5.�˳�����ҳ" << endl;
					cout << "��ѡ��Ҫ�޸ĵ���Ŀ��";
				}
				break;
			case 5:
				printaline();
				return;
			default:
				cout << "����������������룺";
			}
		}
		cout << "�޸ĳɹ����޸ĺ�ѧ����Ϣ��" << endl;
		my_admin.Show_Student_Info(num);
		cout <<"�Ƿ���Ҫ�����޸ģ�y or Ĭ��n����";
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

		cout << "��ѡ������Ŀ��1.ѧ�� 2.���� 3.Ժϵ 4.ѡ�� 5.�༶ 6.�˳�����ҳ" << endl;
		cout << "��ѡ��Ҫ��������Ŀ��";
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
				cout << "��������ʽ��";
				cin >> s;
				break;
			case 5:
				cout << "������༶��";
				cin >> l;
				break;
			case 6:
				printaline();
				return;
			default:
				cout << "����������������룺";
			}
		}
		if (n >= 1 && n <= 4) { //�����ʽ�Ƿ��д�
			int ret = 0;
			reguexpr my_regu(s, ret);
			if (ret == -1) {
				cout << "����ı��ʽ����" << endl;
				printaline();
				continue;
			}
		}

		char c;
		cout << "��ѡ����Ҫ���������ǵ��ڻ��ǲ����ڸñ��ʽ��Ĭ��y������ or n�������ڣ���";
		cin >> c;
		if (c == 'n') isequal = false;
		else isequal = true;

		if (first != true) {
			cout << "��ѡ���������֮ǰ�����Ĺ�ϵ��Ĭ��y���� or h���򣩣�";
			cin >> c;
			if (c == 'h') isand = false;
			else isand = true;
		}

		my_admin.Advanced_Search(s, n, l, isand, isequal, first);
		if (first == true) first = false;
		cout << "�������Ƿ�Ҫ��������������y or Ĭ��n����";
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
	cout << "��������ʽ��";
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
			while (s[p] != '"' && p != slen) { //��ȡ���ʽ
				if (s[p] != ' ') { //�ո����
					expr[ep] = s[p];
					ep++;
				}
				p++;
			}

			if (p == slen) { // ���Ų�ƥ��
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

			if (strcmp(temp, "ѧ��") == 0) n = 1;
			else if (strcmp(temp, "����") == 0) n = 2;
			else if (strcmp(temp, "Ժϵ") == 0) n = 3;
			else if (strcmp(temp, "ѡ��") == 0) n = 4;
			else if (strcmp(temp, "�༶") == 0) {
				n = 5; l = atoi(expr);
			}
			else { //ѡ�����벻��ȷ
				wrong_expr();
				my_admin.cleartemp();
				return;
			}

			my_admin.Advanced_Search(expr, n, l, isand, isequal, first);
			if (first == true) first = false;
			judge = tp; isand = false;
		}
		else if (s[p] == '!'){ //������
			p++; isequal = false;
		}
		else if (s[p] == '=') { //����
			isequal = true;
		}
		else if (s[p] == '&') {
			p++; isand = true;
		}
		else if (s[p] == '|') {
			p++; isand = false;
		}
		else if (s[p] != ' '){ //����ѡ��, �ո�ֱ�Ӻ���
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
	cout << "�����뱣����ļ�����";
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

	cout << "����ɹ���" << endl;
	printaline();
}

void Read_stu_data_to_program() {
	cout << "���������ȡ���ļ�����";
	char s[50]; cin >> s;
	FILE* pfile1 = fopen(s, "r");
	if (pfile1 == NULL) {
		cout << "�ļ������ڣ�" << endl;
		printaline();
		return;
	}

	my_admin.Read_info_from_file(pfile1);

	fclose(pfile1);
	cout << "��ȡ�ɹ���" << endl;
	printaline();
}

void Find_info() {
	cout << "��ѡ��ѯ��Ŀ��1.�γ���Ϣ 2.Ժϵ��Ϣ 3.�༶��Ϣ 4.�˳�����ҳ" << endl;
	cout << "��ѡ��Ҫ�޸ĵ���Ŀ��";
	int n = -1;
	bool b1 = false;
	char c;
	char s[50];
	int k;

	while (n < 1 || n > 4) {
		cin >> n; b1 = false;
		switch (n) {
		case 1:
			cout << "������Ҫ��ѯ�Ŀγ̱�Ż�γ�����";
			cin >> s;
			if (my_admin.hasCou(s) == false) {
				cout << "�����������Ŀγ̣�" << endl;
				printaline();
				return;
			}
			cout << "�Ƿ���Ҫ�������������ѧ������(y or Ĭ��n)��";
			cin >> c;
			if (c == 'y') b1 = true;
			my_admin.Show_Info(n , s, -1, b1);
			break;
		case 2:
			cout << "������Ҫ��ѯ��Ժϵ��";
			cin >> s;
			cout << "�Ƿ���Ҫ�������������ѧ������(y or Ĭ��n)��";
			cin >> c;
			if (c == 'y') b1 = true;
			my_admin.Show_Info(n, s, -1, b1);
			break;
		case 3:
			cout << "������Ҫ��ѯ�İ༶��";
			cin >> k;
			cout << "�Ƿ���Ҫ�������������ѧ������(y or Ĭ��n)��";
			cin >> c;
			if (c == 'y') b1 = true;
			my_admin.Show_Info(n, NULL, k, b1);
			break;
		case 4:
			printaline();
			return;
		default:
			cout << "����������������룺";
		}
	}
	my_admin.cleartemp();

/*	cout << endl;
	cout << "�Ƿ���Ҫ����ѯ��������ļ�(y or Ĭ��n)��";
	char c; cin >> c;
	if (c == 'y') {
		cout << "�����������ļ�����";
		char s[50]; cin >> s;
		FILE* pfile1 = NULL;
		if (fopen(s, "r") != NULL) {
			pfile1 = fopen(s, "a");
		}
		else {
			pfile1 = fopen(s, "w");
		}
		cout << "�Ƿ���Ҫ���ļ��д�ӡѧ���ľ���ɼ�(y or Ĭ��n)��";
		bool b;

		cout << "����ɹ���" << endl;
	}
	else {
		my_admin.cleartemp();
	}
	*/
	printaline();
}