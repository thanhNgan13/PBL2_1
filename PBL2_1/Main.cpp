#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#include "Header.h"
#include "LinkedList.h"
#include "Subjects.h"
#include "Score.h"
#include "informationClass.h"
#include "Students.h"

using namespace std;
std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);

LinkedList<Subjects> list;
LinkedList<informationClass> listInfC;

class User
{
public:
	void viewExam();
	void correctionUser();
	void multipleChoiceTest();
};

class Admin : public User {
public:
	void editSubject();
	void editClass();
	void editExam();
	void editUser();
};

void login();
void menu();
void teacher();
void student();

void loadSubject();
void loadClass();
void loadQuestions(wstring name);
void loadListStudentOfClass(wstring name);

void writeDataSubject();
void writeDataInfClass();
void writeDataExam(wstring name);
void writeDataStudentInfInClass(wstring name);

void enterClass();
void correctionClass();
void deleteClass();

void enterUser();
void deleteUser();

void enterSubject();
void correctionSubject();
void deleteSubject();

void enterExam();
void correctionExam();
void deleteExam();
int enterResult(wstring answer);

void removeFile(wstring s);
bool checkFileIsEmpty(wstring nameFile);
wstring conCat(wstring s1, wstring s2);

Node<Subjects>* Search(LinkedList<Subjects> head, wstring code);
Node<Questions>* Search(Node<Subjects>* head, int code);
Node<Students>* Search(Node<informationClass>* head, wstring code);
Node<informationClass>* Search(LinkedList<informationClass> head, wstring code);


int wmain(int argc, wchar_t* argv[]) {
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stdin), _O_WTEXT);
	menu();
	return 0;

}

void login()
{
	wstring user;
	wstring pass;
	int isTrue = 1;
	int x, y;
	bangmenu(45, 1, 60, 2, 11);	writeString(50, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
	textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
	writeString(x + 45, y + 3, L" Nhập tài khoản: ", 15);
	getline(wcin, user);
	writeString(x + 45, y + 6, L" Nhập mật khẩu: ", 15);
	getline(wcin, pass);
	while (isTrue) {
		if (user == L"ad" && pass == L"ad") {
			isTrue = 0;
			checkAd = 0;
			system("cls");
			bangmenu(45, 1, 60, 2, 11);	writeString(50, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
			textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
			writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 15);
			writeString(x + 45, y + 3, L" ĐĂNG NHẬP THÀNH CÔNG\n", 15);
			gotoxy(x + 45, y + 6);
			system("pause");
			system("cls");
			teacher();
		}
#if 0
		loadClass();
		classInformationList* temp = listInfC;
		while (temp != NULL) {
			listC = listC->Delete(listC);
			listS = listS->Delete(listS);
			wstring name;
			name = conCat(temp->data.getClassName(), temp->data.getClassCode());
			loadListStudentOfClass(name);
			studentList* temp1 = listS;
			while (temp1 != NULL) {
				if (user == temp1->data.getStudentCode() && pass == temp1->data.getPasswork()) {
					tempS = temp1->data;
					tempInf = temp->data;
					isTrue = 0;
					checkUS = 0;
					system("cls");
					bangmenu(45, 1, 60, 2, 11);	writeString(50, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
					textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
					writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 15);
					writeString(x + 45, y + 3, L" ĐĂNG NHẬP THÀNH CÔNG\n", 15);
					gotoxy(x + 45, y + 6);
					system("pause");
					system("cls");
					student();
				}
				temp1 = temp1->next;
			}
			temp = temp->next;
		}
#endif
		if (isTrue == 1) {
			system("cls");
			bangmenu(45, 1, 60, 2, 11);	writeString(50, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
			textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
			writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 15);
			writeString(x + 50, y + 3, L" ĐĂNG NHẬP KHÔNG THÀNH CÔNG\n", 15);
			gotoxy(x + 50, y + 6);
			system("pause");
			system("cls");
			listInfC.Delete();
			list.Delete();
			menu();
		}

	}

}
void menu()

{
	loadSubject();
	loadClass();
	checkAd = 1;
	checkUS = 1;
	int x, y;
	bangmenu(45, 1, 60, 2, 11);	writeString(50, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
	textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
	bangmenu(x + 2, y + 2, 35, 2, 11);
	writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 15);
	writeString(x + 5, y + 6, L"2>  THÔNG TIN VỀ CHƯƠNG TRÌNH", 6);
	writeString(x + 5, y + 9, L"3>  THOÁT", 6);
	int kt = 1;
	gotoxy(x + 5, y + 35);
	for (;;)
	{
		gotoxy(x + 5, y + 35);
		int h = catchEvents();
		if (h == 6)
		{
			if (kt == 1)
			{
				kt = 2;
				bangmenu(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 6);
				bangmenu(x + 2, y + 5, 35, 2, 11);	writeString(x + 5, y + 6, L"2>  THÔNG TIN VỀ CHƯƠNG TRÌNH", 15);
				bangmenu(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THOÁT", 6);

			}
			else if (kt == 2)
			{
				kt = 3;
				bangmenu(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 6);
				bangmenu(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  THÔNG TIN VỀ CHƯƠNG TRÌNH", 6);
				bangmenu(x + 2, y + 8, 35, 2, 11);	writeString(x + 5, y + 9, L"3>  THOÁT", 15);
			}
			else if (kt == 3)
			{
				kt = 1;
				bangmenu(x + 2, y + 2, 35, 2, 11);	writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 15);
				bangmenu(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  THÔNG TIN VỀ CHƯƠNG TRÌNH", 6);
				bangmenu(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THOÁT", 6);
			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 3;
				bangmenu(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 6);
				bangmenu(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  THÔNG TIN VỀ CHƯƠNG TRÌNH", 6);
				bangmenu(x + 2, y + 8, 35, 2, 11);	writeString(x + 5, y + 9, L"3>  THOÁT", 15);
			}
			else if (kt == 3)
			{
				kt = 2;
				bangmenu(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 6);
				bangmenu(x + 2, y + 5, 35, 2, 11);	writeString(x + 5, y + 6, L"2>  THÔNG TIN VỀ CHƯƠNG TRÌNH", 15);
				bangmenu(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THOÁT", 6);
			}
			else if (kt == 2)
			{
				kt = 1;
				bangmenu(x + 2, y + 2, 35, 2, 11);	writeString(x + 5, y + 3, L"1>  ĐĂNG NHẬP", 15);
				bangmenu(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  THÔNG TIN VỀ CHƯƠNG TRÌNH", 6);
				bangmenu(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THOÁT", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				login();
			}
			else if (kt == 2)
			{
				system("cls");
				wcout << L"em yeu em";
			}
			else if (kt == 3)
			{
				gotoxy(5, 15);	MessageBox(0, convertCharArrayToLPCWSTR("Dang thoat chuong trinh!"), convertCharArrayToLPCWSTR("THONG BAO"), MB_OK);
				gotoxy(x + 5, y + 35);	exit(0);
			}
		}
	}
}
void teacher()

{
	Admin ad;
	int x, y;
	bangmenu(62, 1, 18, 2, 11);	writeString(67, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
	bangmenu(x + 2, y + 2, 36, 2, 11);
	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 15);
	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
	writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
	writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
	writeString(x + 5, y + 18, L"6>  THOÁT", 6);
	int kt = 1;
	gotoxy(x + 5, y + 35);
	for (;;)
	{
		gotoxy(x + 5, y + 35);
		int h = catchEvents();
		if (h == 6)
		{
			if (kt == 1)
			{
				kt = 2;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 11);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 15);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 11);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 15);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 3)
			{
				kt = 4;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 11); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 15);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 4)
			{
				kt = 5;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 11); writeString(x + 5, y + 15, L"5>  THI THỬ", 15);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 5)
			{
				kt = 6;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 11); writeString(x + 5, y + 18, L"6>  THOÁT", 15);
			}
			else if (kt == 6)
			{
				kt = 1;
				bangmenu(x + 2, y + 2, 36, 2, 11);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 15);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 6;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 11); writeString(x + 5, y + 18, L"6>  THOÁT", 15);
			}
			else if (kt == 6)
			{
				kt = 5;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 11); writeString(x + 5, y + 15, L"5>  THI THỬ", 15);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 5)
			{
				kt = 4;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 11); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 15);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 4)
			{
				kt = 3;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 11);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 15);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 3)
			{
				kt = 2;
				bangmenu(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				bangmenu(x + 2, y + 5, 36, 2, 11);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 15);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 2)
			{
				kt = 1;
				bangmenu(x + 2, y + 2, 36, 2, 11);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 15);
				bangmenu(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				bangmenu(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				bangmenu(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				bangmenu(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				bangmenu(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				ad.editClass();
			}
			else if (kt == 2)
			{
				ad.editSubject();
			}
			else if (kt == 3)
			{
				ad.editUser();
			}
			else if (kt == 4)
			{
				ad.editExam();
			}
			else if (kt == 5)
			{
				ad.multipleChoiceTest();
			}
			else if (kt == 6)
			{
				listInfC.Delete();
				list.Delete();
				system("cls");
				menu();
			}
		}
	}
}
void student()
{
}

void loadQuestions(wstring name)
{
	LinkedList<Questions> temp;
	wifstream file;
	Questions data;
	wstring s;
	file.open(name, ios_base::in);
	int max;
	file >> max;
	file.ignore();
	getline(file, s);
	for (int i = 0; i < max; i++) {
		file.imbue(loc);
		wstring s1;
		int id;
		file >> id;
		data.setId(id);
		file.ignore();
		getline(file, s1);
		s1 = Upper(s1);
		data.setContentQuestions(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		data.setA(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		data.setB(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		data.setC(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		data.setD(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		data.setAnswer(s1);
		s1.clear();
		temp.Insert(data);
	}
	Node<Subjects>* head = Search(list, subStr(name));
	head->data.setQuestionList(temp);
	file.close();
}
void loadSubject() {
	wifstream file;
	file.open(L"listSubject.txt", ios_base::in);
	int max;
	file >> max;
	file.ignore();
	for (int i = 0; i < max; i++) {
		file.imbue(loc);
		fstream fileIn;
		Subjects data;
		wstring s1, s2;
		getline(file, s1);
		s1 = Upper(s1);
		data.setSubjectName(s1);
		getline(file, s2);
		s2 = Upper(s2);
		data.setSubjectCode(s2);
		list.Insert(data);
		fileIn.open(conCat(s1, s2), ios::out | ios::app);
		fileIn.close();
	}
	file.close();
}
void loadClass()
{
	wifstream file;
	file.open(L"listClass.txt", ios_base::in);
	int max;
	file >> max;
	file.ignore();
	for (int i = 0; i < max; i++) {
		file.imbue(loc);
		fstream fileIn;
		informationClass data;
		wstring s1, s2;
		getline(file, s1);
		s1 = Upper(s1);
		data.setClassName(s1);
		getline(file, s2);
		s2 = Upper(s2);
		data.setClassCode(s2);
		listInfC.Insert(data);
		fileIn.open(conCat(s1, s2), ios::out | ios::app);
		fileIn.close();
	}
	file.close();
}
void loadListStudentOfClass(wstring name)
{
	wifstream file;
	LinkedList<Students> temp;
	LinkedList<Score> temp1;
	LinkedList<Score> temp2;
	Students dataS;
	wstring s;
	file.open(name, ios_base::in);
	file.imbue(loc);
	int max;
	file >> max;
	file.ignore();
	getline(file, s);
	for (int i = 0; i < max; i++) {
		temp1 = temp2;
		wstring s1;
		getline(file, s1);
		s1 = Upper(s1);
		dataS.setLastName(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		dataS.setFirstName(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		dataS.setSex(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		dataS.setStudentCode(s1);
		s1.clear();
		getline(file, s1);
		s1 = Upper(s1);
		dataS.setPasswork(s1);
		s1.clear();
		int numberOfSubjectsTested;
		file >> numberOfSubjectsTested;
		file.ignore();
		if (numberOfSubjectsTested == 0) {
			dataS.setScoreList(temp2);
		}
		else {
			for (int i = 0; i < numberOfSubjectsTested; i++) {
				Score x;
				float d;
				getline(file, s);
				x.setSubjectCode(s);
				file >> d;
				file.ignore();
				x.setScore(d);
				temp1.Insert(x);
			}
			dataS.setScoreList(temp1);
		}
		temp.Insert(dataS);
	}
	Node<informationClass>* head = Search(listInfC, subStr(name));
	head->data.setStudentList(temp);
	file.close();
}

void writeDataInfClass()
{
	wofstream file;
	file.open("listClass.txt");
	file << listInfC.getCount() << endl;
	for (int i = 0; i < listInfC.getCount(); i++) {
		file.imbue(loc);
		file << listInfC.getNode(i)->data.getClassName() << endl;
		file << listInfC.getNode(i)->data.getClassCode() << endl;
	}
	file.close();
}
void writeDataSubject()
{
	wofstream file;
	file.open("listSubject.txt");
	file << list.getCount() << endl;
	for (int i = 0; i < list.getCount(); i++) {
		file.imbue(loc);
		file << list.getNode(i)->data.getSubjectName() << endl;
		file << list.getNode(i)->data.getSubjectCode() << endl;
	}
	file.close();
}
void writeDataExam(wstring name)
{
	wofstream file;
	file.open(name);
	Node<Subjects>* head = Search(list, subStr(name));
	file << head->data.getQuestionList().getCount() << endl;
	file << subStr(name) << endl;
	for (int i = 0; i < head->data.getQuestionList().getCount(); i++) {
		file.imbue(loc);
		file << head->data.getQuestionList().getNode(i)->data.getId() << endl;
		file << head->data.getQuestionList().getNode(i)->data.getContentQuestions() << endl;
		file << head->data.getQuestionList().getNode(i)->data.getA() << endl;
		file << head->data.getQuestionList().getNode(i)->data.getB() << endl;
		file << head->data.getQuestionList().getNode(i)->data.getC() << endl;
		file << head->data.getQuestionList().getNode(i)->data.getD() << endl;
		file << head->data.getQuestionList().getNode(i)->data.getAnswer() << endl;
	}
	file.close();
}
void writeDataStudentInfInClass(wstring name)
{
	wofstream file;
	file.open(name);
	Node<informationClass>* head = Search(listInfC, subStr(name));
	file << head->data.getStudentList().getCount() << endl;
	file << subStr(name) << endl;
	int len3 = head->data.getStudentList().getData().getScoreList().getCount();
	for (int i = 0; i < head->data.getStudentList().getCount(); i++) {
		file.imbue(loc);
		int len;
		file << head->data.getStudentList().getNode(i)->data.getLastName() << endl;
		file << head->data.getStudentList().getNode(i)->data.getFirstName() << endl;
		file << head->data.getStudentList().getNode(i)->data.getSex() << endl;
		file << head->data.getStudentList().getNode(i)->data.getStudentCode() << endl;
		file << head->data.getStudentList().getNode(i)->data.getPasswork() << endl;
		len = head->data.getStudentList().getNode(i)->data.getScoreList().getCount();
		file << len << endl;
		for (int j = 0; j < len; j++) {
			file << head->data.getStudentList().getNode(i)->data.getScoreList().getNode(j)->data.getSubjectCode() << endl;
			file << head->data.getStudentList().getNode(i)->data.getScoreList().getNode(j)->data.getScore() << endl;
		}
	}
	file.close();
}

void enterSubject()
{
	wcout << L"THÊM MÔN HỌC" << endl;
	int count;
	while (true)
	{
		wcout << L"Nhập số môn học muốn thêm: ";
		if (wcin >> count)
			break;
		else {
			wcin.clear();
			wcin.ignore(1000, '\n');
		}
	}
	wcin.ignore();
	for (int i = 0; i < count; i++) {
		wfstream fileIn;
		Subjects x;
		wstring s1, s2;
		wcout << L"Nhâp tên môn học:  " << endl;
		getline(wcin, s1);
		s1 = Upper(s1);
		x.setSubjectName(s1);
		wcout << L"Nhập mã môn học:  " << endl;
		getline(wcin, s2);
		s2 = Upper(s2);
		x.setSubjectCode(s2);
		if (list.Search(x) != nullptr) {
			wcout << L"Đã có môn học này" << endl;
			i--;
		}
		else {
			list.Insert(x);
			fileIn.open(conCat(s1, s2), ios::out | ios::app);
			fileIn.close();
		}
	}
	writeDataSubject();
}
void correctionSubject()
{
	Node<Subjects>* head;
	wstring s;
	wcout << L"CHỈNH SỬA MÔN HỌC" << endl;
	list.Display();
	do {
		wcout << L"Nhập mã môn học cần chỉnh sửa: ";
		getline(wcin, s);
		head = Search(list, s);
		s.clear();
		if (head == NULL) {
			wcout << L"Môn học không tồn tại hoặc bạn đã nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			Subjects x;
			while (true)
			{
				wcout << L"Nhập lại thông tin môn học" << endl;
				wcin >> x;
				if (list.Search(x) != nullptr) {
					wcout << L"Bạn nhập bị trùng tên hoặc mã môn học!" << endl;
				}
				else {
					wstring s11 = conCat(head->data.getSubjectName(), head->data.getSubjectCode());
					wstring s22 = conCat(x.getSubjectName(), x.getSubjectCode());
					const wchar_t* s1 = s11.c_str();
					const wchar_t* s2 = s22.c_str();
					if (_wrename(s1, s2) != 0) {
						_wperror(L"Error renaming file\n");
					}
					else
						wcout << "File renamed successfully" << endl;
					head->data = x;
					wcout << L"Đã hiệu chỉnh thành công!" << endl;
					writeDataSubject();
					return;
				}
			}
		}

	} while (true);

}
void deleteSubject()
{
	wstring x;
	wcout << L"XÓA MÔN HỌC" << endl;
	list.Display();
	do {
		wcout << L"Nhập mã môn học cần xóa: ";
		getline(wcin, x);
		x = Upper(x);
		Node<Subjects>* head = Search(list, x);
		if (head == nullptr) {
			wcout << L"Môn học không tồn tại hoặc bạn đã nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn lựa chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			removeFile(conCat(head->data.getSubjectName(), head->data.getSubjectCode()));
			list.Delete(head->data);
			writeDataSubject();
			return;
		}
	} while (true);
}
void Admin::editSubject()


{
	int x, y;
	bangmenu(62, 1, 18, 2, 11);	writeString(67, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
	bangmenu(x + 42, y + 2, 40, 2, 11);
	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 15);
	writeString(x + 45, y + 3, L"1. Thêm môn học.", 15);
	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
	writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
	writeString(x + 45, y + 15, L"5. Thoát", 6);
	int kt = 1;
	gotoxy(x + 5, y + 26);
	for (;;)
	{
		gotoxy(x + 5, y + 26);
		int h = catchEvents();
		if (h == 6)
		{
			if (kt == 1)
			{
				kt = 2;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 15);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa môn học", 15);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 4;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 15);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 5;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 1;
				bangmenu(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 15);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 5;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 4;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 15);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 3;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa môn học", 15);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 2;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 15);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 2)
			{
				kt = 1;
				bangmenu(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm môn học", 15);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				system("cls");
				enterSubject();
				system("pause");
				system("cls");
				editSubject();
			}
			else if (kt == 2)
			{
				system("cls");
				correctionSubject();
				system("pause");
				system("cls");
				editSubject();
			}
			else if (kt == 3)
			{
				system("cls");
				deleteSubject();
				system("pause");
				system("cls");
				editSubject();
			}
			else if (kt == 4)
			{
				system("cls");
				list.Display();
				system("pause");
				system("cls");
				editSubject();
			}
			else if (kt == 5)
			{
				system("cls");
				teacher();
			}
		}
	}
}

void enterExam()
{
	system("cls");
	wcout << L"THÊM CÂU HỎI" << endl;
	Node<Subjects>* head;
	LinkedList<Questions> temp;
	int count;
	wstring name;
	wstring s;
	list.Display();
	do {
		wcout << L"Nhập mã môn học cần thêm câu hỏi: ";
		getline(wcin, s);
		s = Upper(s);
		head = Search(list, s);
		if (head == nullptr) {
			wcout << L"Môn học không tồn tại hoặc bạn nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			name = conCat(head->data.getSubjectName(), head->data.getSubjectCode());
			loadQuestions(name);
			while (true)
			{
				wcout << L"Nhập số câu hỏi muốn thêm: ";
				if (wcin >> count) {
					if (count <= 0) {
						cin.clear();
						cin.ignore(1000, '\n');
					}
					else {
						break;
					}
				}
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			for (int i = 0; i < count; i++) {
				Questions x;
				wcout << L"Nhập thông tin câu hỏi" << endl;
				wcin >> x;
				temp = head->data.getQuestionList();
				temp.Insert(x);
				head->data.setQuestionList(temp);
			}
			writeDataExam(name);
			return;
		}
	} while (true);
}
void correctionExam()
{
	Node<Subjects>* head;
	Node<Questions>* head1;
	wstring s;
	wstring name;
	int id;
	system("cls");
	wcout << L"CHỈNH SỬA CÂU HỎI" << endl;
	list.Display();
	do {
		wcout << L"Nhập mã môn học cần thay đổi thông tin câu hỏi: ";
		getline(wcin, s);
		s = Upper(s);
		head = Search(list, s);
		if (head == nullptr) {
			wcout << L"Môn học không tồn tại hoặc bạn nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			name = conCat(head->data.getSubjectName(), head->data.getSubjectCode());
			loadQuestions(name);
			if (checkFileIsEmpty(name)) {
				wcout << L"File rỗng không có gì để xóa!" << endl;
				wcout << L"Vui lòng nhập lại" << endl;
				break;
			}
			else {
				head->data.getQuestionList().Display();
				do {
					wcout << L"Nhập id câu hỏi cần chỉnh sửa:";
					wcin >> id;
					head1 = Search(head, id);
					if (head1 == nullptr) {
						wcout << L"Câu hỏi không tồn tại hoặc bạn đã nhập sai!" << endl;
						wcout << L"1. Tiếp tục nhập" << endl;
						wcout << L"2. Thoát" << endl;
						int select;
						while (true)
						{
							wcout << L"Mời bạn chọn: ";
							if (wcin >> select)
								break;
							else
							{
								wcin.clear();
								wcin.ignore(1000, '\n');
							}
						}
						wcin.ignore();
						if (select != 1) {
							return;
						}
					}
					else {
						wcin.ignore();
						Questions x;
						wstring s1;
						wcout << L"Câu hỏi cũ: " << endl;
						wcout << head1->data;
						wcout << L"Thay đổi thông tin câu hỏi thành: " << endl;
						wcin >> x;
						head1->data = x;
						wcout << L"Đã hiệu chỉnh thành công!" << endl;
						writeDataExam(name);
						return;
					}
				} while (true);
			}
		}
	} while (true);


}
void deleteExam()
{
	LinkedList<Questions> temp;
	Node<Subjects>* head;
	Node<Questions>* head1;
	wstring s;
	wstring name;
	int id;
	system("cls");
	wcout << L"XÓA CÂU HỎI" << endl;
	list.Display();
	do {
		wcout << L"Nhập mã môn học cần thay đổi thông tin câu hỏi: ";
		getline(wcin, s);
		s = Upper(s);
		head = Search(list, s);
		if (head == nullptr) {
			wcout << L"Môn học không tồn tại hoặc bạn nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			name = conCat(head->data.getSubjectName(), head->data.getSubjectCode());
			loadQuestions(name);
			if (checkFileIsEmpty(name)) {
				wcout << L"File rỗng không có gì để chỉnh sửa!" << endl;
				wcout << L"Vui lòng nhập lại" << endl;
				break;
			}
			else {
				head->data.getQuestionList().Display();
				do {
					wcout << L"Nhập id câu hỏi cần chỉnh sửa:";
					wcin >> id;
					head1 = Search(head, id);
					if (head1 == nullptr) {
						wcout << L"Câu hỏi không tồn tại hoặc bạn đã nhập sai!" << endl;
						wcout << L"1. Tiếp tục nhập" << endl;
						wcout << L"2. Thoát" << endl;
						int select;
						while (true)
						{
							wcout << L"Mời bạn chọn: ";
							if (wcin >> select)
								break;
							else
							{
								wcin.clear();
								wcin.ignore(1000, '\n');
							}
						}
						wcin.ignore();
						if (select != 1) {
							return;
						}
					}
					else {
						temp = head->data.getQuestionList();
						temp.Delete(head1->data);
						head->data.setQuestionList(temp);
						writeDataExam(name);
						return;
					}
				} while (true);
			}
		}
	} while (true);


}
void Admin::editExam()
{
	wstring s;
	int x, y;
	bangmenu(62, 1, 18, 2, 11);	writeString(67, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
	bangmenu(x + 42, y + 2, 40, 2, 11);
	writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 15);
	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 15);
	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
	writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
	writeString(x + 45, y + 15, L"5. Thoát", 6);
	int kt = 1;
	gotoxy(x + 5, y + 26);
	for (;;)
	{
		gotoxy(x + 5, y + 26);
		int h = catchEvents();
		if (h == 6)
		{
			if (kt == 1)
			{
				kt = 2;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 15);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 15);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 4;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
				bangmenu(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 15);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 5;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
				bangmenu(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 1;
				bangmenu(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 15);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 5;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
				bangmenu(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 4;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
				bangmenu(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 15);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 3;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 15);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 2;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 15);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 2)
			{
				kt = 1;
				bangmenu(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi", 15);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				system("cls");
				enterExam();
				system("pause");
				system("cls");
				editExam();
			}
			else if (kt == 2)
			{
				system("cls");
				correctionExam();
				system("pause");
				system("cls");
				editExam();
			}
			else if (kt == 3)
			{
				system("cls");
				deleteExam();
				system("pause");
				system("cls");
				editExam();
			}
			else if (kt == 4)
			{
				Node<Subjects>* head;
				system("cls");
				list.Display();
				do {
					wcout << L"Nhập mã môn học cần xem câu hỏi: ";
					getline(wcin, s);
					s = Upper(s);
					head = Search(list, s);
					if (head == nullptr) {
						wcout << L"Môn học không tồn tại hoặc bạn đã nhập sai!" << endl;
						wcout << L"1. Tiếp tục nhập." << endl;
						wcout << L"2. Thoát." << endl;
						int select;
						while (true)
						{
							wcout << L"Mời bạn chọn: ";
							if (wcin >> select)
								break;
							else
							{
								wcin.clear();
								wcin.ignore(1000, '\n');
							}
						}
						wcin.ignore();
						if (select != 1) {
							break;
						}
					}
					else {
						wstring name;
						name = conCat(head->data.getSubjectName(), head->data.getSubjectCode());
						loadQuestions(name);
						if (checkFileIsEmpty(name)) {
							wcout << L"File rỗng không có gì để hiện thị!" << endl;
							wcout << L"Vui lòng nhập lại" << endl;
							break;
						}
						else {
							head->data.getQuestionList().Display();
							head->data.getQuestionList().Delete();
						}
						break;
					}
				} while (true);
				system("pause");
				system("cls");
				editExam();
			}
			else if (kt == 5)
			{
				system("cls");
				teacher();
			}
		}
	}
}
int enterResult(wstring answer) {
	if (answer == L"a" || answer == L"A")
		return 1;
	else if (answer == L"b" || answer == L"B")
		return 2;
	else if (answer == L"c" || answer == L"C")
		return 3;
	else if (answer == L"d" || answer == L"D")
		return 4;
	else
		return -1;
}


void enterClass()

{
	wcout << L"THÊM LỚP HỌC" << endl;
	int count;
	while (true)
	{
		wcout << L"Nhập số lớp học muốn thêm: ";
		if (wcin >> count)
			break;
		else {
			wcin.clear();
			wcin.ignore(1000, '\n');
		}
	}
	wcin.ignore();
	for (int i = 0; i < count; i++) {
		wfstream fileIn;
		informationClass x;
		wstring s1, s2;
		wcout << L"Nhập tên lớp học:  " << endl;
		getline(wcin, s1);
		s1 = Upper(s1);
		x.setClassName(s1);
		wcout << L"Nhập mã lớp học:  " << endl;
		getline(wcin, s2);
		s2 = Upper(s2);
		x.setClassCode(s2);
		if (listInfC.Search(x) != nullptr) {
			wcout << L"Đã có môn lớp này" << endl;
			i--;
		}
		else {
			listInfC.Insert(x);
			fileIn.open(conCat(s1, s2), ios::out | ios::app);
			fileIn.close();
		}
	}
	writeDataInfClass();
}
void correctionClass()

{
	Node<informationClass>* head;
	wstring s;
	wcout << L"CHỈNH SỬA LỚP HỌC" << endl;
	listInfC.Display();
	do {
		wcout << L"Nhập mã lớp học cần chỉnh sửa: ";
		getline(wcin, s);
		head = Search(listInfC, s);
		s.clear();
		if (head == NULL) {
			wcout << L"Lớp học không tồn tại hoặc bạn đã nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			informationClass x;
			while (true)
			{
				wcout << L"Nhập lại thông tin lớp học" << endl;
				wcin >> x;
				if (listInfC.Search(x) != nullptr) {
					wcout << L"Bạn nhập bị trùng tên hoặc mã lớp học!" << endl;
				}
				else {
					wstring s11 = conCat(head->data.getClassName(), head->data.getClassCode());
					wstring s22 = conCat(x.getClassName(), x.getClassCode());
					const wchar_t* s1 = s11.c_str();
					const wchar_t* s2 = s22.c_str();
					if (_wrename(s1, s2) != 0) {
						_wperror(L"Error renaming file\n");
					}
					else
						wcout << "File renamed successfully" << endl;
					head->data = x;
					wcout << L"Đã hiệu chỉnh thành công!" << endl;
					writeDataInfClass();
					return;
				}
			}
		}

	} while (true);

}
void deleteClass()

{
	wstring x;
	wcout << L"XÓA LỚP HỌC" << endl;
	listInfC.Display();
	do {
		wcout << L"Nhập mã lớp học cần xóa: ";
		getline(wcin, x);
		x = Upper(x);
		Node<informationClass>* head = Search(listInfC, x);
		if (head == nullptr) {
			wcout << L"Lớp học không tồn tại hoặc bạn đã nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn lựa chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			removeFile(conCat(head->data.getClassName(), head->data.getClassCode()));
			listInfC.Delete(head->data);
			writeDataSubject();
			return;
		}
	} while (true);
}
void Admin::editClass()

{
	int x, y;
	bangmenu(62, 1, 18, 2, 11);	writeString(67, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
	bangmenu(x + 42, y + 2, 40, 2, 11);
	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 15);
	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 15);
	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
	writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
	writeString(x + 45, y + 15, L"5. Thoát", 6);
	int kt = 1;
	gotoxy(x + 5, y + 26);
	for (;;)
	{
		gotoxy(x + 5, y + 26);
		int h = catchEvents();
		if (h == 6)
		{
			if (kt == 1)
			{
				kt = 2;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 15);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 15);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 4;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 15);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 5;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 1;
				bangmenu(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 15);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 5;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 4;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 15);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 3;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 15);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 2;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 15);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 2)
			{
				kt = 1;
				bangmenu(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm lớp học", 15);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				system("cls");
				enterClass();
				system("pause");
				system("cls");
				editClass();
			}
			else if (kt == 2)
			{
				system("cls");
				correctionClass();
				system("pause");
				system("cls");
				editClass();
			}
			else if (kt == 3)
			{
				system("cls");
				deleteClass();
				system("pause");
				system("cls");
				editClass();
			}
			else if (kt == 4)
			{
				system("cls");
				listInfC.Display();
				system("pause");
				system("cls");
				editClass();
			}
			else if (kt == 5)
			{
				system("cls");
				teacher();
			}
		}
	}
}

void enterUser()
{
	LinkedList<Students> temp;
	LinkedList<Score> temp1;
	Node<informationClass>* head;
	wcout << L"THÊM SINH VIÊN VÀO LỚP HỌC" << endl;
	wcout << L"Danh sách lớp học" << endl;
	wstring x;
	wstring name;
	listInfC.Display();
	do {
		wcout << L"Nhập mã lớp học cần thêm sinh viên: ";
		getline(wcin, x);
		x = Upper(x);
		head = Search(listInfC, x);
		if (head == nullptr) {
			wcout << L"Lớp học không tồn tại hoặc bạn nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			name = conCat(head->data.getClassName(), head->data.getClassCode());
			loadListStudentOfClass(name);
			int count;
			while (true)
			{
				wcout << L"Nhập số sinh viên muốn thêm: ";
				if (wcin >> count)
					break;
				else {
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			for (int i = 0; i < count; i++) {
				wstring check;
				Students st;
				wstring s;
				wcout << L"Nhập tên đăng nhập: " << endl;
				getline(wcin, s);
				st.setStudentCode(s);
				if (Search(head, s) != nullptr || s == check) {
					wcout << L"Bạn đã nhập mã sinh viên bị trùng. Vui lòng nhập lại!" << endl;
					i--;
				}
				else {
					check = s;
					wcout << L"Nhập họ: " << endl;
					getline(wcin, s);
					st.setLastName(s);
					s.clear();
					wcout << L"Nhập tên: " << endl;
					getline(wcin, s);
					st.setFirstName(s);
					s.clear();
					wcout << L"Nhập giới tính: " << endl;
					getline(wcin, s);
					st.setSex(s);
					s.clear();
					wcout << L"Nhập password: " << endl;
					getline(wcin, s);
					st.setPasswork(s);
					s.clear();
					st.setScoreList(temp1);
					temp = head->data.getStudentList();
					temp.Insert(st);
					head->data.setStudentList(temp);
				}
			}
			writeDataStudentInfInClass(name);
			return;

		}
	} while (true);

}
void deleteUser()
{

	system("cls");
	wcout << L"XÓA SINH VIÊN KHỎI LỚP HỌC" << endl;
	wcout << L"Danh sách lớp học" << endl;
	LinkedList<Students> temp;
	LinkedList<Score> temp1;
	Node<informationClass>* head;
	Node<Students>* head1;
	wstring x;
	wstring name;
	listInfC.Display();
	do {
		wcout << L"Nhập mã lớp học cần thay đổi thông tin sinh viên: ";
		getline(wcin, x);
		x = Upper(x);
		head = Search(listInfC, x);
		if (head == nullptr) {
			wcout << L"Lớp học không tồn tại hoặc bạn nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			system("cls");
			name = conCat(head->data.getClassName(), head->data.getClassCode());
			loadListStudentOfClass(name);
			if (checkFileIsEmpty(name)) {
				wcout << L"File rỗng không có gì để chỉnh sửa!" << endl;
				wcout << L"Vui lòng nhập lại" << endl;
				break;
			}
			else {
				head->data.getStudentList().Display();
				string s;
				do {
					wcout << L"Nhập mã sinh viên để xóa dữ liệu: ";
					getline(wcin, x);
					x = Upper(x);
					head1 = Search(head, x);
					if (head1 == nullptr) {
						wcout << L"Sinh viên không tồn tại hoặc bạn nhập sai!" << endl;
						wcout << L"1. Tiếp tục nhập" << endl;
						wcout << L"2. Thoát" << endl;
						int select;
						while (true)
						{
							wcout << L"Mời bạn chọn: ";
							if (wcin >> select)
								break;
							else
							{
								wcin.clear();
								wcin.ignore(1000, '\n');
							}
						}
						wcin.ignore();
						if (select != 1) {
							return;
						}
					}
					else {
						temp = head->data.getStudentList();
						temp.Delete(head1->data);
						head->data.setStudentList(temp);
						writeDataStudentInfInClass(name);
						return;

					}
				} while (true);
				return;
			}
		}
	} while (true);
}
void User::correctionUser()
{
	if (checkAd == 0) {
		LinkedList<Students> temp;
		LinkedList<Score> temp1;
		Node<informationClass>* head;
		Node<Students>* head1;
		wcout << L"ĐIỀU CHỈNH THÔNG TIN SINH VIÊN LỚP HỌC" << endl;
		wcout << L"Danh sách lớp học" << endl;
		wstring x;
		wstring name;
		listInfC.Display();
		do {
			wcout << L"Nhập mã lớp học cần thay đổi thông tin sinh viên: ";
			getline(wcin, x);
			x = Upper(x);
			head = Search(listInfC, x);
			if (head == nullptr) {
				wcout << L"Lớp học không tồn tại hoặc bạn nhập sai!" << endl;
				wcout << L"1. Tiếp tục nhập" << endl;
				wcout << L"2. Thoát" << endl;
				int select;
				while (true)
				{
					wcout << L"Mời bạn chọn: ";
					if (wcin >> select)
						break;
					else
					{
						wcin.clear();
						wcin.ignore(1000, '\n');
					}
				}
				wcin.ignore();
				if (select != 1) {
					return;
				}
			}
			else {
				system("cls");
				name = conCat(head->data.getClassName(), head->data.getClassCode());
				loadListStudentOfClass(name);
				if (checkFileIsEmpty(name)) {
					wcout << L"File rỗng không có gì để xóa!" << endl;
					wcout << L"Vui lòng nhập lại" << endl;

				}
				else {
					head->data.getStudentList().Display();

					wstring s;
					do {
						wcout << L"Nhập mã sinh viên để thay đổi thông tin: ";
						getline(wcin, x);
						x = Upper(x);
						head1 = Search(head, x);
						if (head1 == nullptr) {
							wcout << L"Sinh viên không tồn tại hoặc bạn nhập sai!" << endl;
							wcout << L"1. Tiếp tục nhập" << endl;
							wcout << L"2. Thoát" << endl;
							int select;
							while (true)
							{
								wcout << L"Mời bạn chọn: ";
								if (wcin >> select)
									break;
								else
								{
									wcin.clear();
									wcin.ignore(1000, '\n');
								}
							}
							wcin.ignore();
							if (select != 1) {
								return;
							}
						}
						else {
							system("cls");
							Students st;
							wcout << L"Thông tin sinh viên được chọn là" << endl;
							wcout << L"____________________________________" << endl;
							wcout << head1->data;
							wcout << L"_________________________________________" << endl;
							wcout << L"Thay đổi họ thành: " << endl;
							getline(wcin, s);
							st.setLastName(s);
							s.clear();
							wcout << L"Thay đổi tên thành: " << endl;
							getline(wcin, s);
							st.setFirstName(s);
							s.clear();
							wcout << L"Thay đổi giới tính thành: " << endl;
							getline(wcin, s);
							st.setSex(s);
							s.clear();
							st.setStudentCode(head1->data.getStudentCode());
							wcout << L"Nhập password: " << endl;
							getline(wcin, s);
							st.setPasswork(s);
							s.clear();
							st.setScoreList(head1->data.getScoreList());
							head1->data = st;
							writeDataStudentInfInClass(name);
							return;
						}

					} while (true);
				}
				return;
			}
		} while (true);
	}
#if 0
	else {
		listC = listC->Delete(listC);
		listS = listS->Delete(listS);
		wstring name;
		name = conCat(tempInf.getClassName(), tempInf.getClassCode());
		loadListStudentOfClass(name);
		studentList* head1 = listS->Search(listS, tempS.getStudentCode());
		wstring s;
		system("cls");
		Students st;
		wcout << L"Thông tin sinh viên được chọn là" << endl;
		wcout << L"____________________________________" << endl;
		wcout << L"Họ: ";
		wcout << head1->data.getLastName() << endl;
		wcout << L"Tên: ";
		wcout << head1->data.getFirstName() << endl;
		wcout << L"Giới tính: ";
		wcout << head1->data.getSex() << endl;
		wcout << L"Id: ";
		wcout << head1->data.getStudentCode() << endl;
		wcout << L"Password: ";
		wcout << head1->data.getPasswork() << endl;
		wcout << L"_________________________________________" << endl;
		wcout << L"Thay đổi họ thành: " << endl;
		getline(wcin, s);
		st.setLastName(s);
		s.clear();
		wcout << L"Thay đổi tên thành: " << endl;
		getline(wcin, s);
		st.setFirstName(s);
		s.clear();
		wcout << L"Thay đổi giới tính thành: " << endl;
		getline(wcin, s);
		st.setSex(s);
		s.clear();
		st.setStudentCode(head1->data.getStudentCode());
		wcout << L"Nhập password: " << endl;
		getline(wcin, s);
		st.setPasswork(s);
		s.clear();
		st.setScoreList(head1->data.getScoreList());
		head1->data = st;
		writeDataStudentInfInClass(name);
		system("pause");
		system("cls");
		student();
	}
#endif
}
void Admin::editUser()

{
	wstring s;
	int x, y;
	bangmenu(62, 1, 18, 2, 11);	writeString(67, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	tbmenu(x = 30, y = 6);	textcolor(3);
	bangmenu(x + 42, y + 2, 40, 2, 11);
	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 15);
	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 15);
	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
	writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
	writeString(x + 45, y + 15, L"5. Thoát", 6);
	int kt = 1;
	gotoxy(x + 5, y + 26);
	for (;;)
	{
		gotoxy(x + 5, y + 26);
		int h = catchEvents();
		if (h == 6)
		{
			if (kt == 1)
			{
				kt = 2;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 15);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 15);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 4;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
				bangmenu(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 15);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 5;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
				bangmenu(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 1;
				bangmenu(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 15);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 5;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
				bangmenu(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 4;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
				bangmenu(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4.Hiện thị sinh viên", 15);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 3;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 15);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 2;
				bangmenu(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
				bangmenu(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 15);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 2)
			{
				kt = 1;
				bangmenu(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm sinh viên", 15);
				bangmenu(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
				bangmenu(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
				bangmenu(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
				bangmenu(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				system("cls");
				enterUser();
				system("pause");
				system("cls");
				editUser();
			}
			else if (kt == 2)
			{
				system("cls");
				correctionUser();
				system("pause");
				system("cls");
				editUser();
			}
			else if (kt == 3)
			{
				system("cls");
				deleteUser();
				system("pause");
				system("cls");
				editUser();
			}
			else if (kt == 4)
			{
				Node<informationClass>* head;
				system("cls");
				listInfC.Display();
				do {
					wcout << L"Nhập mã lớp học cần xem thông tin sinh viên: ";
					getline(wcin, s);
					s = Upper(s);
					head = Search(listInfC, s);
					if (head == nullptr) {
						wcout << L"Lớp học không tồn tại hoặc bạn đã nhập sai!" << endl;
						wcout << L"1. Tiếp tục nhập." << endl;
						wcout << L"2. Thoát." << endl;
						int select;
						while (true)
						{
							wcout << L"Mời bạn chọn: ";
							if (wcin >> select)
								break;
							else
							{
								wcin.clear();
								wcin.ignore(1000, '\n');
							}
						}
						wcin.ignore();
						if (select != 1) {
							break;
						}
					}
					else {
						wstring name;
						name = conCat(head->data.getClassName(), head->data.getClassCode());
						loadListStudentOfClass(name);
						if (checkFileIsEmpty(name)) {
							wcout << L"File rỗng không có gì để hiện thị!" << endl;
							wcout << L"Vui lòng nhập lại" << endl;
							break;
						}
						else {
							head->data.getStudentList().Display();
							head->data.getStudentList().Delete();
						}
						break;
					}
				} while (true);
				system("pause");
				system("cls");
				editUser();
			}
			else if (kt == 5)
			{
				system("cls");
				teacher();
			}
		}
	}
}

void User::multipleChoiceTest()
{
	wofstream file;
	Node<Subjects>* head;
	LinkedList<Questions> temp;
	Node<Questions>* head1;
	wstring s;
	wstring name;
#if 1
	system("cls");
	wcout << L"THI TRẮC NGHIỆM" << endl;
	wcout << endl;
	wcout << L"Danh sách môn học" << endl;
	list.Display();
	wstring code;
	do {
		wcout << L"Nhập mã môn học cần thi: ";
		getline(wcin, s);
		s = Upper(s);
		head = Search(list, s);
		if (head == nullptr) {
			wcout << L"Môn học không tồn tại hoặc bạn nhập sai!" << endl;
			wcout << L"1. Tiếp tục nhập" << endl;
			wcout << L"2. Thoát" << endl;
			int select;
			while (true)
			{
				wcout << L"Mời bạn chọn: ";
				if (wcin >> select)
					break;
				else
				{
					wcin.clear();
					wcin.ignore(1000, '\n');
				}
			}
			wcin.ignore();
			if (select != 1) {
				return;
			}
		}
		else {
			name = conCat(head->data.getSubjectName(), head->data.getSubjectCode());
			if (checkFileIsEmpty(name)) {
				wcout << L"File rỗng không có câu hỏi để làm bài!" << endl;
				wcout << L"Vui lòng nhập lại" << endl;
				system("pause");
				system("cls");
				teacher();
			}
			else
			{
				loadQuestions(name);
			}
			break;
		}
	} while (true);
#if 0
	if (checkUS == 0) {
		wstring s1 = tempS.getStudentCode();
		wstring s2 = code;
		file.open(conCat(s1, s2), ios::out | ios::app);
		file.imbue(loc);
		file << L"Lần thi thứ " << checkCountEX << endl;
	}
#endif
	int numberOfQuestions;
	do {
		wcout << L"Nhập số câu hỏi thi " << "(1.." << head->data.getQuestionList().getCount() << "): ";
		wcin >> numberOfQuestions;
		if (checkUS == 0) {
			file << L"Số câu hỏi:" << numberOfQuestions << endl;
		}
	} while (numberOfQuestions > head->data.getQuestionList().getCount() || numberOfQuestions < 1);
	int count = numberOfQuestions;
	int score = 0;
	wcin.ignore();
	do {
		srand(time(NULL));
		wstring answer;
		int r = rand() % head->data.getQuestionList().getCount();
		system("cls");
		head1 = head->data.getQuestionList().getNode(r);
		wcout << head1->data;
#if 0
		if (checkUS == 0) {
			file << L"ID: " << listQ->getQuestion(listQ, r).getId() << endl;
			file << L"Nội dung câu hỏi: " << listQ->getQuestion(listQ, r).contentQuestions << endl;
			file << L"A. " << listQ->getQuestion(listQ, r).A << endl;
			file << L"B. " << listQ->getQuestion(listQ, r).B << endl;
			file << L"C. " << listQ->getQuestion(listQ, r).C << endl;
			file << L"D. " << listQ->getQuestion(listQ, r).D << endl;
			file << L"Đáp án đúng: " << listQ->getQuestion(listQ, r).getAnswer() << endl;
		}
#endif
		do {
			wcout << L"Nhập câu trả lời của bạn(A, B, C, D): ";
			getline(wcin, answer);
			if (checkUS == 0) {

				file << L"Đáp án của bạn: " << answer << endl;
			}
			if (enterResult(answer) != -1) {
				break;
			}
		} while (true);
		if (enterResult(answer) == enterResult(head->data.getQuestionList().getNode(r)->data.getAnswer()))
			score++;
		temp = head->data.getQuestionList();
		temp.Delete(head1->data);
		head->data.setQuestionList(temp);
		numberOfQuestions--;
	} while (numberOfQuestions);
	system("cls");
	float realSocre = (float)10.0f * score / count;
	wcout << L"Sau khi thi điểm của bạn là: " << realSocre << endl;
	file << L"Điểm của bạn là: " << realSocre << endl;
	file.close();
#endif
#if 0
	wstring name;
	if (checkUS == 0) {
		name = conCat(tempInf.getClassName(), tempInf.getClassCode());
		loadListStudentOfClass(name);
		studentList* head = listS->Search(listS, tempS.getStudentCode());
		Score listSc;
		listSc.setScore(realSocre);
		listSc.setSubjectCode(code);
		scoreList* listSc1 = head->data.getScoreList();
		if (listSc1 == NULL) {
			listSc1 = listSc1->Insert(listSc1, listSc);
			head->data.setScoreList(listSc1);
		}
		else {
			int check = 0;
			scoreList* temp = listSc1;
			while (temp != NULL)
			{
				if (temp->data.getSubjectCode() == code) {
					checkCountEX += 1;
					temp->data.setScore(realSocre);
					check = 1;
					break;
				}
				temp = temp->next;
			}
			if (!check) {
				temp = new scoreList(listSc);
				temp->next = listSc1;
				listSc1 = temp;
				head->data.setScoreList(listSc1);
			}
		}
		writeDataStudentInfInClass(name);

		system("pause");
		system("cls");
		student();
	}
#endif 
	system("pause");
	system("cls");
	teacher();
}

void removeFile(wstring s)
{
	const wchar_t* c = s.c_str();
	if (_wremove(c) != 0) {
		cerr << "File deletion failed" << endl;
	}
	else {
		wcout << L"File deleted successfully" << endl;;
	}
}
bool checkFileIsEmpty(wstring nameFile)
{
	wifstream file;
	file.open(nameFile);
	file.seekg(0, ios::end);
	if (file.tellg() == 0) {
		return true;
	}
	return false;
	file.close();
}
wstring conCat(wstring s1, wstring s2)
{
	return s1 + L'_' + s2 + L".txt";
}

Node<Subjects>* Search(LinkedList<Subjects> head, wstring code)
{
	int i = 0;
	while (i != list.getCount()) {
		if (list.getNode(i)->data.getSubjectCode() == code) {
			return list.getNode(i);
			break;
		}
		i++;
	}
	return nullptr;
}
Node<Questions>* Search(Node<Subjects>* head, int code)
{
	int i = 0;
	while (i != head->data.getQuestionList().getCount()) {
		if (head->data.getQuestionList().getNode(i)->data.getId() == code) {
			return head->data.getQuestionList().getNode(i);
			break;
		}
		i++;
	}
	return nullptr;
}
Node<Students>* Search(Node<informationClass>* head, wstring code)
{
	int i = 0;
	while (i != head->data.getStudentList().getCount()) {
		if (head->data.getStudentList().getNode(i)->data.getStudentCode() == code) {
			return head->data.getStudentList().getNode(i);
			break;
		}
		i++;
	}
	return nullptr;
}
Node<informationClass>* Search(LinkedList<informationClass> head, wstring code)
{
	int i = 0;
	while (i != listInfC.getCount()) {
		if (listInfC.getNode(i)->data.getClassCode() == code) {
			return listInfC.getNode(i);
			break;
		}
		i++;
	}
	return nullptr;
}