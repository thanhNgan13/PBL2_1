#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <chrono>
#include <direct.h>
#include <cstdint>
#include <filesystem>

#include "Header.h"
#include "LinkedList.h"
#include "Subjects.h"
#include "Score.h"
#include "informationClass.h"
#include "Students.h"


using namespace std;
namespace fs = std::filesystem;
namespace cron = std::chrono;
using namespace std::literals::chrono_literals;
std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);

HANDLE hStdin;

LinkedList<Subjects> listS;
LinkedList<informationClass> listInfC;
Node<Students>* tempS;
Node<informationClass>* tempInf;

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
int enterResult(wchar_t answer);

void removeFile(wstring s);
bool checkFileIsEmpty(wstring nameFile);
wstring conCat(wstring s1, wstring s2);

Node<Subjects>* Search(LinkedList<Subjects> list, wstring code); // tìm kiếm môn học

Node<Questions>* Search(Node<Subjects>* node, int code); // tìm kiếm câu hỏi

Node<informationClass>* Search(LinkedList<informationClass> list, wstring code); // tìm kiếm môn học

Node<Students>* Search(Node<informationClass>* node, wstring code); // tìm kiếm sinh viên

Node<Score>* Search(LinkedList<Score> list, wstring code); // tìm kiếm môn đã thi của sinh viên

void DeleteAndCorrection(LinkedList<informationClass> list, wstring code, Subjects sb); // xóa điểm thi của môn học đã bị xóa

void display(LinkedList<Students> list, Node<informationClass>* node);
void display(Students st, int x, int y, int i, wstring s);
void display(LinkedList<Questions> list);

bool Check(LinkedList<informationClass> list, wstring user, wstring pass);

void enterInf(Students& st, wstring code, LinkedList<Score> listSc);

int wmain(int argc, wchar_t* argv[]) {
	try {
		if (_setmode(_fileno(stdout), _O_WTEXT) == -1 || _setmode(_fileno(stdin), _O_WTEXT) == -1) {
			throw 0;
		}
		login();
	}
	catch (...) {
		perror("Cannot set mode");
	}
}


void login()
{
	loadSubject();
	loadClass();
	checkAd = 1;
	checkUS = 1;
	wstring user;
	wstring pass;
	wstring pass1;
	int isTrue = 1;
	int keyUs = 1;
	int keyPs = 1;
	int counter = 0;
	// Vòng lặp để quét qua các event 
	while (!counter)
	{
		if (keyUs == 0) {
			menuBar(50, 1, 60, 2, 11);	writeString(55, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
			menuBar(65, 5, 30, 2, 15); writeString(66, 6, user.c_str(), 6);
			menuBar(65, 8, 30, 2, 15);
			menuBar(65, 11, 30, 2, 8); writeString(66, 12, L"          ĐĂNG NHẬP          ", 135);
		}
		else if (keyPs == 0) {
			menuBar(50, 1, 60, 2, 11);	writeString(55, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
			menuBar(65, 5, 30, 2, 15); writeString(66, 6, L"User", 8);
			menuBar(65, 8, 30, 2, 15); writeString(66, 9, pass1.c_str(), 6);
			menuBar(65, 11, 30, 2, 8); writeString(66, 12, L"          ĐĂNG NHẬP          ", 135);
		}
		else if (keyUs == 0 && keyPs == 0) {
			menuBar(50, 1, 60, 2, 11);	writeString(55, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
			menuBar(65, 5, 30, 2, 15); writeString(66, 6, user.c_str(), 6);
			menuBar(65, 8, 30, 2, 15); writeString(66, 9, pass1.c_str(), 6);
			menuBar(65, 11, 30, 2, 8); writeString(66, 12, L"          ĐĂNG NHẬP          ", 135);
		}
		else {
			menuBar(50, 1, 60, 2, 11);	writeString(55, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
			menuBar(65, 5, 30, 2, 15); writeString(66, 6, L"User", 8);
			menuBar(65, 8, 30, 2, 15); writeString(66, 9, L"Password", 8);
			menuBar(65, 11, 30, 2, 8); writeString(66, 12, L"          ĐĂNG NHẬP          ", 135);;
		}
		// đọc event vào

		ShowCur(false);
		textcolor(6);
		DWORD cNumRead, fdwMode, i;
		INPUT_RECORD irInBuf[128];

		// Get the standard input handle. 

		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		if (hStdin == INVALID_HANDLE_VALUE)
			WriteError(const_cast <LPSTR>("GetStdHandle"));

		// Mở cửa sổ ở chế độ mở
		fdwMode = ENABLE_EXTENDED_FLAGS;
		if (!SetConsoleMode(hStdin, fdwMode)) {
			WriteError(const_cast <LPSTR>("SetConsoleMode"));
		}

		// Mở cửa sổ ở chế độ chấp nhận input

		fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
		if (!SetConsoleMode(hStdin, fdwMode)) {
			WriteError(const_cast <LPSTR>("SetConsoleMode"));
		}
		if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
			WriteError(const_cast <LPSTR>("ReadConsoleInput"));
		}

		// xử lý từng event một
		for (i = 0; i < cNumRead; i++)
		{
			if (GetAsyncKeyState(0x01))
			{
				// Khai báo các biến mà hàm cần
				int x, y;
				INPUT_RECORD Inrec;
				DWORD eventRead;
				HANDLE hStdIn;
				DWORD dwMode;
				bool Captured = false;
				hStdIn = GetStdHandle(STD_INPUT_HANDLE);
				dwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

				//Kiểm tra xem console đã ở chế độ chấp nhận input từ chuột chưa
				if (SetConsoleMode(hStdIn, dwMode | ENABLE_MOUSE_INPUT) == TRUE)

					GetConsoleMode(hStdIn, &dwMode);
				SetConsoleMode(hStdIn, (dwMode & (ENABLE_MOUSE_INPUT)));

				// vòng lặp này sẽ lấy các event của trong bộ nhớ ra để xử lý
				do
				{

					PeekConsoleInput(hStdIn, &Inrec, 1, &eventRead);
					if (eventRead)
					{
						ReadConsoleInput(hStdIn, &Inrec, 1, &eventRead);
						x = Inrec.Event.MouseEvent.dwMousePosition.X;
						y = Inrec.Event.MouseEvent.dwMousePosition.Y;
						switch (Inrec.EventType)
						{

						case MOUSE_EVENT:
						{
							Captured = true;
							if ((x >= 66 && x <= 96) && y == 6)
							{
								if (keyPs == 0) {
									system("cls");
									ShowCur(true);
									menuBar(50, 1, 60, 2, 11);	writeString(55, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
									menuBar(65, 5, 30, 2, 14);
									menuBar(65, 8, 30, 2, 15); writeString(66, 9, pass1.c_str(), 6);
									menuBar(65, 11, 30, 2, 8); writeString(66, 12, L"          ĐĂNG NHẬP          ", 135);
									textcolor(6);
									gotoxy(66, 6); user = inputString(9);
									if (GetKeyState(VK_RETURN)) {
										keyUs = 0;
										break;
									}
								}
								else {
									system("cls");
									ShowCur(true);
									menuBar(50, 1, 60, 2, 11);	writeString(55, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
									menuBar(65, 5, 30, 2, 14);
									menuBar(65, 8, 30, 2, 15); writeString(66, 9, L"Password", 8);
									menuBar(65, 11, 30, 2, 8); writeString(66, 12, L"          ĐĂNG NHẬP          ", 135);
									textcolor(6);
									gotoxy(66, 6); user = inputString(9);
									if (GetKeyState(VK_RETURN)) {
										keyUs = 0;
										break;
									}
								}
							}
							else if ((x >= 66 && x <= 96) && y == 9)
							{
								system("cls");
								ShowCur(true);
								menuBar(50, 1, 60, 2, 11);	writeString(55, 2, L"CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN VÀ THI TRẮC NGHIỆM", 14);
								menuBar(65, 5, 30, 2, 15);
								if (user.length() == 0) {
									writeString(66, 6, L"User", 8);
								}
								else {
									writeString(66, 6, user.c_str(), 6);
								}
								menuBar(65, 8, 30, 2, 14);
								menuBar(65, 11, 30, 2, 8); writeString(66, 12, L"          ĐĂNG NHẬP          ", 135);
								textcolor(6);
								gotoxy(66, 9); pass = inputPassword(20);
								pass1.clear();
								for (auto& x : pass) {
									pass1.push_back(L'*');
								}

								if ((GetKeyState(VK_RETURN))) {
									keyPs = 0;
									break;
								}
							}
							else if ((x >= 66 && x <= 96) && y == 12)
							{
								while (isTrue) {
									if (user == L"ad" && pass == L"ad") {
										isTrue = 0;
										checkAd = 0;
										system("cls");
										writeString(65, 0, L" ĐĂNG NHẬP THÀNH CÔNG\n", 15);
										gotoxy(65, 2);
										system("pause");
										system("cls");
						
										teacher();
									}
									if (Check(listInfC, user, pass)) {
										isTrue = 0;
										checkUS = 0;
										system("cls");
										writeString(65, 0, L" ĐĂNG NHẬP THÀNH CÔNG\n", 15);
										gotoxy(65, 2);
										system("pause");
										system("cls");
			
										student();
									}
									if (isTrue == 1) {
										system("cls");
										writeString(65, 0, L" ĐĂNG NHẬP KHÔNG THÀNH CÔNG\n", 4);
										gotoxy(65, 2);
										system("pause");
										system("cls");
										listInfC.Delete();
										listS.Delete();
										login();
									}
								}
							}
							break;
						}
						}
					}

				} while (!Captured);
			}
		}
	}
}
void teacher()
{
	ShowCur(false);
	Admin ad;
	int x, y;
	menuBar(70, 1, 20, 2, 11);	writeString(75, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	menuTable(x = 30, y = 6);	textcolor(3);
	menuBar(x + 2, y + 2, 36, 2, 11);
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
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 11);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 15);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 11);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 15);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 3)
			{
				kt = 4;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 11); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 15);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 4)
			{
				kt = 5;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 11); writeString(x + 5, y + 15, L"5>  THI THỬ", 15);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 5)
			{
				kt = 6;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 11); writeString(x + 5, y + 18, L"6>  THOÁT", 15);
			}
			else if (kt == 6)
			{
				kt = 1;
				menuBar(x + 2, y + 2, 36, 2, 11);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 15);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 6;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 11); writeString(x + 5, y + 18, L"6>  THOÁT", 15);
			}
			else if (kt == 6)
			{
				kt = 5;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 11); writeString(x + 5, y + 15, L"5>  THI THỬ", 15);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 5)
			{
				kt = 4;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 11); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 15);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 4)
			{
				kt = 3;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 11);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 15);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 3)
			{
				kt = 2;
				menuBar(x + 2, y + 2, 36, 2, 0);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 6);
				menuBar(x + 2, y + 5, 36, 2, 11);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 15);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
			}
			else if (kt == 2)
			{
				kt = 1;
				menuBar(x + 2, y + 2, 36, 2, 11);	writeString(x + 5, y + 3, L"1>  QUẢN LÝ THÔNG TIN LỚP HỌC", 15);
				menuBar(x + 2, y + 5, 36, 2, 0);	writeString(x + 5, y + 6, L"2>  QUẢN LÝ THÔNG TIN MÔN HỌC", 6);
				menuBar(x + 2, y + 8, 36, 2, 0);	writeString(x + 5, y + 9, L"3>  QUẢN LÝ THÔNG TIN SINH VIÊN", 6);
				menuBar(x + 2, y + 11, 36, 2, 0); writeString(x + 5, y + 12, L"4>  QUẢN LÝ THÔNG TIN CÂU HỎI THI", 6);
				menuBar(x + 2, y + 14, 36, 2, 0); writeString(x + 5, y + 15, L"5>  THI THỬ", 6);
				menuBar(x + 2, y + 17, 36, 2, 0); writeString(x + 5, y + 18, L"6>  THOÁT", 6);
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
				listS.Delete();
				system("cls");
				login();
			}
		}
	}
}
void student()
{
	ShowCur(false);
	User us;
	int x, y;
	wstring s = L"Sinh Viên " + tempS->data.getLastName() + L' ' + tempS->data.getFirstName();
	//removeSpaces(s);
	size_t l = s.length();
	const wchar_t* s1 = s.c_str();
	menuBar(int(80 - ((l + 10) / 2)), 1, int(l + 10), 2, 11);	writeString(int(85 - ((l + 10) / 2)), 2, s1, 14);
	textcolor(2);	menuTable(x = 30, y = 6);	textcolor(3);
	menuBar(x + 2, y + 2, 35, 2, 11);
	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 15);
	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 6);
	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 6);
	writeString(x + 5, y + 12, L"4>  THOÁT", 6);
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
				menuBar(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 6);
				menuBar(x + 2, y + 5, 35, 2, 11);	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 15);
				menuBar(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 6);
				menuBar(x + 2, y + 11, 35, 2, 0); writeString(x + 5, y + 12, L"4>  THOÁT", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				menuBar(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 6);
				menuBar(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 6);
				menuBar(x + 2, y + 8, 35, 2, 11);	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 15);
				menuBar(x + 2, y + 11, 35, 2, 0); writeString(x + 5, y + 12, L"4>  THOÁT", 6);
			}
			else if (kt == 3)
			{
				kt = 4;
				menuBar(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 6);
				menuBar(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 6);
				menuBar(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 6);
				menuBar(x + 2, y + 11, 35, 2, 11); writeString(x + 5, y + 12, L"4>  THOÁT", 15);
			}
			else if (kt == 4)
			{
				kt = 1;
				menuBar(x + 2, y + 2, 35, 2, 11);	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 15);
				menuBar(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 6);
				menuBar(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 6);
				menuBar(x + 2, y + 11, 35, 2, 0); writeString(x + 5, y + 12, L"4>  THOÁT", 6);
			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 4;
				menuBar(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 6);
				menuBar(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 6);
				menuBar(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 6);
				menuBar(x + 2, y + 11, 35, 2, 11); writeString(x + 5, y + 12, L"4>  THOÁT", 15);
			}
			else if (kt == 4)
			{
				kt = 3;
				menuBar(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 6);
				menuBar(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 6);
				menuBar(x + 2, y + 8, 35, 2, 11);	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 15);
				menuBar(x + 2, y + 11, 35, 2, 0); writeString(x + 5, y + 12, L"4>  THOÁT", 6);
			}
			else if (kt == 3)
			{
				kt = 2;
				menuBar(x + 2, y + 2, 35, 2, 0);	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 6);
				menuBar(x + 2, y + 5, 35, 2, 11);	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 15);
				menuBar(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 6);
				menuBar(x + 2, y + 11, 35, 2, 0); writeString(x + 5, y + 12, L"4>  THOÁT", 6);
			}
			else if (kt == 2)
			{
				kt = 1;
				menuBar(x + 2, y + 2, 35, 2, 11);	writeString(x + 5, y + 3, L"1>  LÀM BÀI TRẮC NGHIỆM", 15);
				menuBar(x + 2, y + 5, 35, 2, 0);	writeString(x + 5, y + 6, L"2>  XEM CÁC MÔN ĐÃ THI", 6);
				menuBar(x + 2, y + 8, 35, 2, 0);	writeString(x + 5, y + 9, L"3>  THAY ĐỔI THÔNG TIN CÁ NHÂN", 6);
				menuBar(x + 2, y + 11, 35, 2, 0); writeString(x + 5, y + 12, L"4>  THOÁT", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				us.multipleChoiceTest();
			}
			else if (kt == 2)
			{
				us.viewExam();
			}
			else if (kt == 3)
			{
				us.correctionUser();
			}
			else if (kt == 4)
			{
				listInfC.Delete();
				listS.Delete();
				system("cls");
				login();
			}
		}
	}
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
		int ans;
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
		file >> ans;
		data.setAnswer(ans);
		file.ignore();
		temp.Insert(data);
	}
	Node<Subjects>* head = Search(listS, subStr(name));
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
		listS.Insert(data);
		try {
			if (_wmkdir((L"listSubject\\" + s1 + L"_" + s2).c_str()) != -1) {
				throw 3;
			}
			fileIn.open(L"listSubject\\" + conCat(s1, s2), ios::out | ios::app);
			fileIn.close();
		}
		catch (...) {
			cerr << "Error : " << strerror(errno) << endl;
		}
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
		fileIn.open(L"listClass\\" + conCat(s1, s2), ios::out | ios::app);
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
		try {
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
			if (s1.length() != 9) {
				throw 99;
			}
			dataS.setStudentCode(s1);
			s1.clear();
			getline(file, s1);
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
		catch (...) {
			system("cls");
			writeString(60, 0, L"Dữ liệu đầu vào có giá trị không hợp lệ!!!", 4);
			writeString(60, 1, L"Hãy kiểm tra lại dữ liệu và thử lại sau.", 4);
			gotoxy(60, 2);
			system("pause");
			system("cls");
			if (checkAd == 0) {
				teacher();
			}
			else {
				listInfC.Delete();
				listS.Delete();
				login();
			}
		}
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
	Node<informationClass>* temp = listInfC.head;
	while (temp != nullptr)
	{
		file.imbue(loc);
		file << temp->data.getClassName() << endl;
		file << temp->data.getClassCode() << endl;
		temp = temp->next;
	}
	file.close();
}
void writeDataSubject()
{
	wofstream file;
	file.open("listSubject.txt");
	file << listS.getCount() << endl;
	Node<Subjects>* temp = listS.head;
	while (temp != nullptr)
	{
		file.imbue(loc);
		file << temp->data.getSubjectName() << endl;
		file << temp->data.getSubjectCode() << endl;
		temp = temp->next;
	}
	file.close();
}
void writeDataExam(wstring name)
{
	wofstream file;
	file.open(name);
	Node<Subjects>* nodeS = Search(listS, subStr(name));
	file << nodeS->data.getQuestionList().getCount() << endl;
	file << subStr(name) << endl;
	Node<Questions>* nodeQ = nodeS->data.getQuestionList().head;
	while (nodeQ != nullptr)
	{
		file.imbue(loc);
		file << nodeQ->data.getId() << endl;
		file << nodeQ->data.getContentQuestions() << endl;
		file << nodeQ->data.getA() << endl;
		file << nodeQ->data.getB() << endl;
		file << nodeQ->data.getC() << endl;
		file << nodeQ->data.getD() << endl;
		file << nodeQ->data.getAnswer() << endl;
		nodeQ = nodeQ->next;
	}
	file.close();
}
void writeDataStudentInfInClass(wstring name)
{
	wofstream file;
	file.open(name);
	Node<informationClass>* nodeInf = Search(listInfC, subStr(name));
	file << nodeInf->data.getStudentList().getCount() << endl;
	file << subStr(name) << endl;
	Node<Students>* nodeSt = nodeInf->data.getStudentList().head;
	while (nodeSt != nullptr)
	{
		file.imbue(loc);
		file << nodeSt->data.getLastName() << endl;
		file << nodeSt->data.getFirstName() << endl;
		file << nodeSt->data.getSex() << endl;
		file << nodeSt->data.getStudentCode() << endl;
		file << nodeSt->data.getPasswork() << endl;
		file << nodeSt->data.getScoreList().getCount() << endl;
		Node<Score>* nodeSc = nodeSt->data.getScoreList().head;
		while (nodeSc != nullptr)
		{
			file << nodeSc->data.getSubjectCode() << endl;
			file << nodeSc->data.getScore() << endl;
			nodeSc = nodeSc->next;
		}
		nodeSt = nodeSt->next;
	}
	file.close();
}

void enterSubject()
{
	ShowCur(true);
	do
	{
	a:
		menuBar(66, 0, 19, 2, 11);
		writeString(70, 1, L"THÊM MÔN HỌC", 3);
		wcout << endl;
		textcolor(6);
		wfstream fileIn;
		Subjects x;
		wcin >> x;
		if (listS.Search(x) != nullptr) {
			writeString(60, 6, L"Đã có môn học này! Vui lòng nhập lại.", 4);
			gotoxy(60, 7);
			system("pause");
			system("cls");
			goto a;
		}
		else {
			try {
				if (_wmkdir((L"listSubject\\" + x.getSubjectName() + L"_" + x.getSubjectCode()).c_str()) == -1) {
					throw 3;
				}
				writeString(60, 6, L"Thêm mới thành công!", 12);
				listS.Insert(x);
				fileIn.open(conCat(L"listSubject\\" + x.getSubjectName(), x.getSubjectCode()), ios::out | ios::app);
				fileIn.close();
			}
			catch (...) {
				cerr << "Error : " << strerror(errno) << endl;
			}
		}
		ShowCur(false);
		writeString(60, 8, L"Nhấn nút [ESC] để kết thúc nhập", 5);
		writeString(60, 9, L"Nhấn nút bất kì để tiếp tục nhập", 5);
		if (catchEvents() == 4) {
			system("cls");
			break;
		}
		else {
			system("cls");
			goto a;
		}
	} while (true);
	writeDataSubject();
}
void correctionSubject()
{
	ShowCur(true);
	Node<Subjects>* head;
	wstring s;
	if (listS.isEmpty()) {
		system("cls");
		writeString(43, 1, L"CHƯA CÓ MÔN HỌC NÀO TRONG HỆ THỐNG! TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
		gotoxy(70, 2);
		system("pause");
	}
	else {
		do {
			system("cls");
		a:
			menuBar(65, 0, 26, 2, 11);
			writeString(70, 1, L"CHỈNH SỬA MÔN HỌC", 3);
			wcout << endl;
			gotoxy(68, 4);
			textcolor(12);
			wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
			textcolor(2);
			listS.Display();
			gotoxy(65, listS.getCount() + 7);
			textcolor(6);
			wcout << L"Nhập mã môn học cần chỉnh sửa: ";
			s = inputString(9);
			head = Search(listS, s);
			if (head == NULL) {
				system("cls");
				writeString(60, 0, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
				writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
				writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
				if (catchEvents() == 4) {
					system("cls");
					break;
				}
				else {
					system("cls");
					goto a;
				}
			}
			else {
				Subjects x;
				while (true)
				{
					system("cls");
					menuBar(65, 0, 26, 2, 11);
					writeString(70, 1, L"CHỈNH SỬA MÔN HỌC", 3);
					wcout << endl;
					writeString(65, 5, L"Thông tin môn học cần thay đổi", 9);
					gotoxy(68, 7);
					textcolor(6);
					wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
					gotoxy(68, 8);
					wcout << head->data;
					wcout << endl;
					gotoxy(68, 9);
					wcout << L"Nhập lại thông tin mới" << endl;
					wcin >> x;
					if (listS.Search(x) != nullptr) {
						system("cls");
						textcolor(4);
						wcout << L"Bạn nhập bị trùng tên hoặc mã môn học!. Vui lòng nhập lại" << endl;
						system("pause");
					}
					else {
						DeleteAndCorrection(listInfC, s, x);
						wstring s11 = conCat(L"listSubject\\" + head->data.getSubjectName(), head->data.getSubjectCode());
						wstring s22 = conCat(L"listSubject\\" + x.getSubjectName(), x.getSubjectCode());
						const wchar_t* s1 = s11.c_str();
						const wchar_t* s2 = s22.c_str();
						if (_wrename(s1, s2) != 0 || 
							_wrename((L"listSubject\\" + head->data.getSubjectName() + L"_" + head->data.getSubjectCode()).c_str(), 
									(L"listSubject\\" + x.getSubjectName() + L"_" + x.getSubjectCode()).c_str()) != 0) 
						{
							_wperror(L"Error renaming file\n");
						}
						else
						{
							system("cls");
							writeString(60, 6, L"Đã hiệu chỉnh thành công!", 12);
							wcout << endl;
						}
						head->data = x;
						writeDataSubject();
						gotoxy(60, 7);
						textcolor(6);
						system("pause");
						system("cls");
						return;
					}
				}
			}
		} while (true);
	}
}
void deleteSubject()
{
	ShowCur(true);
	wstring s;
	Subjects sb;
	if (listS.isEmpty()) {
		system("cls");
		writeString(43, 1, L"CHƯA CÓ MÔN HỌC NÀO TRONG HỆ THỐNG! TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
		gotoxy(70, 2);
		system("pause");
	}
	else {
		do {
			checkDelete = 0;
			system("cls");
		a:
			menuBar(65, 0, 26, 2, 11);
			writeString(70, 1, L"XÓA MÔN HỌC", 3);
			wcout << endl;
			gotoxy(68, 4);
			textcolor(12);
			wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
			textcolor(2);
			listS.Display();
			gotoxy(65, listS.getCount() + 7);
			textcolor(6);
			wcout << L"Nhập mã môn học cần xóa: ";
			s = inputString(9);
			Node<Subjects>* head = Search(listS, s);
			if (head == NULL) {
				system("cls");
				writeString(60, 0, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
				writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
				writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
				if (catchEvents() == 4) {
					system("cls");
					checkDelete = 1;
					break;
				}
				else {
					system("cls");
					goto a;
				}
			}
			else {
				// fix đoạn này
				//try {
				//	if (_wrmdir((L"listSubject\\" + head->data.getSubjectName() + L"_" + head->data.getSubjectCode()).c_str()) == -1) {
				//		throw 5;
				//	}
				//	removeFile(L"listSubject\\" + conCat(head->data.getSubjectName(), head->data.getSubjectCode()));
				//	listS.Delete(head->data);
				//	Delete(listInfC, s);
				//	writeDataSubject();
				//	system("cls");
				//	writeString(60, 0, L"Đã xóa môn học thành công", 4);
				//	gotoxy(60, 2);
				//	system("pause");
				//	return;
				//}
//				catch (...) {
				system("cls");
				writeString(60, 2, L"Bạn có chắc chắn xóa môn học này không?", 4);
				writeString(60, 3, L"Nếu xóa thì toàn bộ dữ liệu điểm của sinh viên về môn học này sẽ bị hủy", 4);
				writeString(60, 4, L"Nhấn nút [ESC] để kết thúc", 5);
				writeString(60, 5, L"Nhấn nút bất kì để tiếp tục xóa", 5);
				if (catchEvents() == 4) {
					system("cls");
					checkDelete = 1;
					return;
				}
				else {
					fs::remove_all((L"listSubject\\" + head->data.getSubjectName() + L"_" + head->data.getSubjectCode()).c_str());
					removeFile(L"listSubject\\" + conCat(head->data.getSubjectName(), head->data.getSubjectCode()));
					DeleteAndCorrection(listInfC, s, sb);
					listS.Delete(head->data);
					writeDataSubject();
					system("cls");
					writeString(60, 0, L"Đã xóa môn học thành công", 4);
					gotoxy(60, 2);
					system("pause");
					checkDelete = 1;
					return;
				}
				//}
			}
		} while (true);
	}
}
void Admin::editSubject()
{
	ShowCur(false);
	int x, y;
	menuBar(70, 1, 20, 2, 11);	writeString(75, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	menuTable(x = 30, y = 6);	textcolor(3);
	menuBar(x + 42, y + 2, 40, 2, 11);
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
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 15);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa môn học", 15);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 4;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				menuBar(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 15);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 5;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				menuBar(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 1;
				menuBar(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 15);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 5;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				menuBar(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 4;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				menuBar(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 15);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 3;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa môn học", 15);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 2;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm môn học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 15);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 2)
			{
				kt = 1;
				menuBar(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm môn học", 15);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh môn học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa môn học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị môn học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				system("cls");
				enterSubject();
				system("cls");
				editSubject();
			}
			else if (kt == 2)
			{
				system("cls");
				correctionSubject();
				system("cls");
				editSubject();
			}
			else if (kt == 3)
			{
				system("cls");
				deleteSubject();
				system("cls");
				editSubject();
			}
			else if (kt == 4)
			{
				system("cls");
				if (listS.isEmpty()) {
					system("cls");
					writeString(43, 1, L"CHƯA CÓ MÔN HỌC NÀO TRONG HỆ THỐNG! TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
					gotoxy(70, 2);
					system("pause");
					system("cls");
					editSubject();
				}
				else {
					menuBar(65, 0, 26, 2, 11);
					writeString(70, 1, L"DANH SÁCH MÔN HỌC", 3);
					wcout << endl;
					gotoxy(68, 4);
					textcolor(12);
					wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
					textcolor(2);
					listS.Display();
					gotoxy(65, listS.getCount() + 7);
					textcolor(6);
					system("pause");
					system("cls");
					editSubject();
				}
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
	ShowCur(true);
	Node<Subjects>* head;
	LinkedList<Questions> temp;
	wstring name;
	wstring s;
	
	do {
	a:
		system("cls");
		menuBar(65, 0, 26, 2, 11);
		writeString(70, 1, L"THÊM CÂU HỎI", 3);
		wcout << endl;
		gotoxy(68, 4);
		textcolor(12);
		wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
		textcolor(2);
		listS.Display();
		gotoxy(65, listS.getCount() + 7);
		textcolor(6);
		wcout << L"Nhập mã môn học cần thêm câu hỏi: ";
		s = inputString(9);
		head = Search(listS, s);
		if (head == nullptr) {
			system("cls");
			writeString(60, 4, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
			writeString(60, 6, L"Nhấn nút [ESC] để kết thúc nhập", 5);
			writeString(60, 7, L"Nhấn nút bất kì để tiếp tục nhập", 5);
			if (catchEvents() == 4) {
				system("cls");
				break;
			}
			else {
				system("cls");
				goto a;
			}
		}
		else {
			name = conCat(L"listSubject\\" + head->data.getSubjectName(), head->data.getSubjectCode());
			loadQuestions(name);
			do
			{
				system("cls");
				b:
				Questions x;
				textcolor(6);
				wcout << L"Nhập thông tin câu hỏi" << endl;
				wcin >> x;
				temp = head->data.getQuestionList();
				temp.Insert(x);
				head->data.setQuestionList(temp);
				writeString(0, 8, L"Thêm mới thành công!", 12);
				writeString(0, 9, L"Nhấn nút [ESC] để kết thúc nhập", 5);
				writeString(0, 10, L"Nhấn nút bất kì để tiếp tục nhập", 5);
				if (catchEvents() == 4) {
					system("cls");
					break;
				}
				else {
					system("cls");
					goto b;
				}

			} while (true);
			writeDataExam(name);
			return;
		}
	} while (true);
}
void correctionExam()
{
	ShowCur(true);
	Node<Subjects>* head;
	Node<Questions>* head1;
	wstring s;
	wstring name;

	do {
	a:
		system("cls");
		menuBar(65, 0, 26, 2, 11);
		writeString(70, 1, L"CHỈNH SỬA CÂU HỎI", 3);
		wcout << endl;
		gotoxy(68, 4);
		textcolor(12);
		wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
		textcolor(2);
		listS.Display();
		gotoxy(65, listS.getCount() + 7);
		textcolor(6);
		wcout << L"Nhập mã môn học cần thay đổi thông tin câu hỏi: ";
		s = inputString(9);
		head = Search(listS, s);
		if (head == nullptr) {
			system("cls");
			writeString(60, 0, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
			writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
			writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
			if (catchEvents() == 4) {
				system("cls");
				break;
			}
			else {
				system("cls");
				goto a;
			}
		}
		else {
			name = conCat(L"listSubject\\" + head->data.getSubjectName(), head->data.getSubjectCode());
			loadQuestions(name);
			if (checkFileIsEmpty(name)) {
				system("cls");
				writeString(65, 1, L"File rỗng không có gì để sửa!", 4);
				gotoxy(60, 2);
				break;
			}
			// phải fix đoạn này
			// đã fix
			else {
				do {
				b:
					textcolor(6);
					system("cls");
					display(head->data.getQuestionList());
					int id;
					while (true)
					{
						wcout << L"Nhập id câu hỏi cần chỉnh sửa:";
						if (wcin >> id)
						{
							break;
						}
						else
						{
							wcin.clear();
							wcin.ignore(1000, '\n');
						}
					}
					wcin.ignore();
					head1 = Search(head, id);
					if (head1 == nullptr) {
						system("cls");
						writeString(60, 0, L"Câu hỏi không tồn tại hoặc bạn đã nhập sai!", 4);
						writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
						writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
						if (catchEvents() == 4) {
							system("cls");
							break;
						}
						else {
							system("cls");
							goto b;
						}
					}
					else {
						system("cls");
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
	ShowCur(true);
	LinkedList<Questions> temp;
	Node<Subjects>* head;
	Node<Questions>* head1;
	wstring s;
	wstring name;
	do {
	a:
		system("cls");
		menuBar(65, 0, 26, 2, 11);
		writeString(70, 1, L"XÓA CÂU HỎI", 3);
		wcout << endl;
		gotoxy(68, 4);
		textcolor(12);
		wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
		textcolor(2);
		listS.Display();
		gotoxy(65, listS.getCount() + 7);
		textcolor(6);
		wcout << L"Nhập mã môn học cần xóa thông tin câu hỏi: ";
		s = inputString(9);
		head = Search(listS, s);
		if (head == nullptr) {
			system("cls");
			writeString(60, 0, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
			writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
			writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
			if (catchEvents() == 4) {
				system("cls");
				break;
			}
			else {
				system("cls");
				goto a;
			}
		}
		else {
			name = conCat(L"listSubject\\" + head->data.getSubjectName(), head->data.getSubjectCode());
			loadQuestions(name);
			if (checkFileIsEmpty(name)) {
				system("cls");
				writeString(65, 1, L"File rỗng không có gì để xóa!", 4);
				gotoxy(60, 2);
				system("pause");
				break;
			}
			else {
				do {
				b:
					textcolor(6);
					system("cls");
					display(head->data.getQuestionList());
					int id;
					while (true)
					{
						wcout << L"Nhập id câu hỏi cần xóa:";
						if (wcin >> id)
						{
							break;
						}
						else
						{
							wcin.clear();
							wcin.ignore(1000, '\n');
						}
					}
					wcin.ignore();
					head1 = Search(head, id);
					if (head1 == nullptr) {
						system("cls");
						writeString(60, 0, L"Câu hỏi không tồn tại hoặc bạn đã nhập sai!", 4);
						writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
						writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
						if (catchEvents() == 4) {
							system("cls");
							break;
						}
						else {
							system("cls");
							goto b;
						}
					}
					else {
						system("cls");
						temp = head->data.getQuestionList();
						temp.Delete(head1->data);
						head->data.setQuestionList(temp);
						writeDataExam(name);
						writeString(0, 6, L"Xóa thành công!", 12);
						if (head->data.getQuestionList().isEmpty()) {
							wofstream file;
							file.open(name, ios_base::out | ios_base::trunc);
							file.close();
						}
						system("pause");
						return;
					}
				} while (true);
			}
		}
	} while (true);
}
void Admin::editExam()
{
	ShowCur(false);
	wstring s;
	int x, y;
	menuBar(70, 1, 20, 2, 11);	writeString(75, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	menuTable(x = 30, y = 6);	textcolor(3);
	if (listS.isEmpty()) {
		writeString(x + 45, y + 3, L"CHƯA CÓ MÔN HỌC NÀO TRONG HỆ THỐNG!", 4);
		writeString(x + 45, y + 6, L"TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
		gotoxy(x + 45, y + 9);
		system("pause");
		system("cls");
		teacher();
	}
	else {
		menuBar(x + 42, y + 2, 40, 2, 11);
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
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
					menuBar(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 15);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
				}
				else if (kt == 2)
				{
					kt = 3;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
					menuBar(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 15);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 3)
				{
					kt = 4;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
					menuBar(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 15);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 4)
				{
					kt = 5;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
					menuBar(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
				}
				else if (kt == 5)
				{
					kt = 1;
					menuBar(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 15);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
			}
			else if (h == 5)
			{
				if (kt == 1)
				{
					kt = 5;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
					menuBar(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
				}
				else if (kt == 5)
				{
					kt = 4;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
					menuBar(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 15);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 4)
				{
					kt = 3;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
					menuBar(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 15);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 3)
				{
					kt = 2;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi.", 6);
					menuBar(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 15);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 2)
				{
					kt = 1;
					menuBar(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm câu hỏi", 15);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh câu hỏi.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa câu hỏi", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị câu hỏi", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
				}

			}
			else if (h == 3)
			{
				if (kt == 1)
				{
					system("cls");
					enterExam();
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
					system("cls");
					editExam();
				}
				else if (kt == 4)
				{
					Node<Subjects>* head;
					do {
					a:
						system("cls");
						menuBar(65, 0, 26, 2, 11);
						writeString(70, 1, L" HIỂN THỊ CÂU HỎI", 3);
						wcout << endl;
						gotoxy(68, 4);
						textcolor(12);
						wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
						textcolor(2);
						listS.Display();
						gotoxy(65, listS.getCount() + 7);
						textcolor(6);
						ShowCur(true);
						wcout << L"Nhập mã môn học cần xem câu hỏi: ";
						s = inputString(9);
						head = Search(listS, s);
						if (head == nullptr) {
							system("cls");
							writeString(60, 0, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
							writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
							writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
							if (catchEvents() == 4) {
								system("cls");
								break;
							}
							else {
								system("cls");
								goto a;
							}
						}
						else {
							wstring name;
							name = conCat(L"listSubject\\" + head->data.getSubjectName(), head->data.getSubjectCode());
							loadQuestions(name);
							if (checkFileIsEmpty(name)) {
								system("cls");
								writeString(62, 1, L"File rỗng không có gì để hiển thị!", 4);
								gotoxy(60, 2);
								break;
							}
							else {
								system("cls");
								display(head->data.getQuestionList());
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
}
int enterResult(wchar_t answer) {
	if (answer == L'a' || answer == L'A')
		return 1;
	else if (answer == L'b' || answer == L'B')
		return 2;
	else if (answer == L'c' || answer == L'C')
		return 3;
	else if (answer == L'd' || answer == L'D')
		return 4;
	else
		return -1;
}

void enterClass()
{
	ShowCur(true);
	do
	{
	a:
		menuBar(66, 0, 19, 2, 11);
		writeString(70, 1, L"THÊM LỚP HỌC", 3);
		wcout << endl;
		textcolor(6);
		wfstream fileIn;
		informationClass x;
		wcin >> x;
		if (listInfC.Search(x) != nullptr) {
			writeString(60, 6, L"Đã có lớp học này! Vui lòng nhập lại.", 4);
			gotoxy(60, 7);
			system("pause");
			system("cls");
			goto a;
		}
		else {
			writeString(60, 6, L"Thêm mới thành công!", 12);
			listInfC.Insert(x);
			fileIn.open(L"listClass\\" + conCat(x.getClassName(), x.getClassCode()), ios::out | ios::app);
			fileIn.close();
		}
		writeString(60, 8, L"Nhấn nút [ESC] để kết thúc nhập", 5);
		writeString(60, 9, L"Nhấn nút bất kì để tiếp tục nhập", 5);
		if (catchEvents() == 4) {
			system("cls");
			break;
		}
		else {
			system("cls");
			goto a;
		}
	} while (true);
	writeDataInfClass();
}
void correctionClass()
{
	ShowCur(true);
	Node<informationClass>* head;
	wstring s;
	if (listInfC.isEmpty()) {
		system("cls");
		writeString(43, 1, L"CHƯA CÓ LỚP HỌC NÀO TRONG HỆ THỐNG! TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
		gotoxy(70, 2);
		system("pause");
	}
	else {
		do {
			system("cls");
		a:
			menuBar(65, 0, 26, 2, 11);
			writeString(70, 1, L"CHỈNH SỬA LỚP HỌC", 3);
			wcout << endl;
			gotoxy(68, 4);
			textcolor(12);
			wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
			textcolor(2);
			listInfC.Display();
			gotoxy(65, listInfC.getCount() + 7);
			textcolor(6);
			wcout << L"Nhập mã lớp học cần chỉnh sửa: ";
			s = inputString(9);
			head = Search(listInfC, s);
			if (head == NULL) {
				system("cls");
				writeString(60, 0, L"Lớp học không tồn tại hoặc bạn đã nhập sai!", 4);
				writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
				writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
				if (catchEvents() == 4) {
					system("cls");
					break;
				}
				else {
					system("cls");
					goto a;
				}
			}
			else {
				informationClass x;
				while (true)
				{
					system("cls");
					menuBar(65, 0, 26, 2, 11);
					writeString(70, 1, L"CHỈNH SỬA LỚP HỌC", 3);
					wcout << endl;
					writeString(65, 5, L"Thông tin lớp học cần thay đổi", 9);
					gotoxy(68, 7);
					textcolor(6);
					wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
					gotoxy(68, 8);
					wcout << head->data;
					wcout << endl;
					gotoxy(68, 9);
					wcout << L"Nhập lại thông tin mới" << endl;
					wcin >> x;
					if (listInfC.Search(x) != nullptr) {
						system("cls");
						textcolor(4);
						wcout << L"Bạn nhập bị trùng tên hoặc mã lớp học!. Vui lòng nhập lại" << endl;
						system("pause");
					}
					else {
						wstring s11 = conCat(L"listClass\\" + head->data.getClassName(), head->data.getClassCode());
						wstring s22 = conCat(L"listClass\\" + x.getClassName(), x.getClassCode());
						const wchar_t* s1 = s11.c_str();
						const wchar_t* s2 = s22.c_str();
						if (_wrename(s1, s2) != 0) {
							_wperror(L"Error renaming file\n");
						}
						else
						{
							system("cls");
							writeString(60, 6, L"Đã hiệu chỉnh thành công!", 12);
							wcout << endl;
						}
						head->data = x;
						writeDataInfClass();
						gotoxy(60, 7);
						textcolor(6);
						system("pause");
						system("cls");
						return;
					}
				}
			}
		} while (true);
	}

}
void deleteClass()
{
	ShowCur(true);
	wstring name;
	wstring name1;
	wstring s;
	wstring s1;
	LinkedList<Students> temp;
	LinkedList<Students> temp1;
	if (listInfC.isEmpty()) {
		system("cls");
		writeString(43, 1, L"CHƯA CÓ LỚP HỌC NÀO TRONG HỆ THỐNG! TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
		gotoxy(70, 2);
	}
	else {
		do {
			system("cls");
		a:
			menuBar(65, 0, 26, 2, 11);
			writeString(70, 1, L"XÓA LỚP HỌC", 3);
			wcout << endl;
			gotoxy(68, 4);
			textcolor(12);
			wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
			textcolor(2);
			listInfC.Display();
			gotoxy(65, listInfC.getCount() + 7);
			textcolor(6);
			wcout << L"Nhập mã lớp học cần xóa: ";
			s = inputString(9);
			Node<informationClass>* head = Search(listInfC, s);
			if (head == NULL) {
				system("cls");
				writeString(60, 0, L"Lớp học không tồn tại hoặc bạn đã nhập sai!", 4);
				writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
				writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
				if (catchEvents() == 4) {
					system("cls");
					break;
				}
				else {
					system("cls");
					goto a;
				}
			}
			else {
				name = conCat(L"listClass\\" + head->data.getClassName(), head->data.getClassCode());
				if (checkFileIsEmpty(name)) {
					removeFile(name);
					listInfC.Delete(head->data);
					writeDataInfClass();
					system("cls");
					writeString(60, 0, L"Đã xóa lớp học thành công", 4);
					gotoxy(60, 2);
					return;
				}
#if 1
				else {
					loadListStudentOfClass(name);
					temp = head->data.getStudentList(); // danh sách lớp sinh viên bị xóa
					system("cls");
					writeString(30, 1, L"Lớp học này có chứa sinh viên. Hãy chọn lớp bạn muốn chuyển sinh viên qua!", 4);
					gotoxy(30, 3);
					system("pause");
					system("cls");
					do {
					b:
						menuBar(65, 0, 26, 2, 11);
						writeString(70, 1, L"XÓA LỚP HỌC", 3);
						wcout << endl;
						gotoxy(68, 4);
						textcolor(12);
						wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
						textcolor(2);
						listInfC.Display();
						gotoxy(65, listInfC.getCount() + 7);
						textcolor(6);
						wcout << L"Nhập mã lớp học bạn muốn chuyển sinh viên đến: ";
						s1 = inputString(9);
						Node<informationClass>* head1 = Search(listInfC, s1); // tìm kiếm thông tin lớp được chuyển qua
						if (head1 == NULL) {
							system("cls");
							writeString(60, 0, L"Lớp học không tồn tại hoặc bạn đã nhập sai!", 4);
							writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
							writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
							if (catchEvents() == 4) {
								system("cls");
								break;
							}
							else {
								system("cls");
								goto b;
							}
						}
						else if (s1 == s) {
							system("cls");
							writeString(60, 0, L"Bạn đã nhập tên lớp trùng với lớp muốn xóa! Điều này không được phép!!!", 4);
							writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
							writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
							if (catchEvents() == 4) {
								system("cls");
								break;
							}
							else {
								system("cls");
								goto b;
							}
						}
						else {
							name1 = conCat(L"listClass\\" + head1->data.getClassName(), head1->data.getClassCode());
							loadListStudentOfClass(name1);
							temp1 = head1->data.getStudentList(); // danh sách lớp được chọn để chuyển sinh viên qua
							for (int i = 0; i < temp.getCount(); i++) {
								temp1.Insert(temp.getNode(i)->data);
							}
							head1->data.setStudentList(temp1);
							removeFile(name);
							listInfC.Delete(head->data);
							writeDataStudentInfInClass(name1);
							writeDataInfClass();
							system("cls");
							writeString(60, 0, L"Đã xóa lớp học thành công", 4);
							gotoxy(60, 2);
							return;
						}
					} while (true);
				}
#endif
				return;
			}
		} while (true);
	}
}
void Admin::editClass()
{
	ShowCur(false);
	int x, y;
	menuBar(70, 1, 20, 2, 11);	writeString(75, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	menuTable(x = 30, y = 6);	textcolor(3);
	menuBar(x + 42, y + 2, 40, 2, 11);
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
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 15);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}
			else if (kt == 2)
			{
				kt = 3;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 15);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 4;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				menuBar(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 15);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 5;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				menuBar(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 1;
				menuBar(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 15);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
		}
		else if (h == 5)
		{
			if (kt == 1)
			{
				kt = 5;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				menuBar(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
			}
			else if (kt == 5)
			{
				kt = 4;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				menuBar(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 15);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 4)
			{
				kt = 3;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 15);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 3)
			{
				kt = 2;
				menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm lớp học.", 6);
				menuBar(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 15);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

			}
			else if (kt == 2)
			{
				kt = 1;
				menuBar(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm lớp học", 15);
				menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh lớp học.", 6);
				menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa lớp học", 6);
				menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị lớp học", 6);
				menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
			}

		}
		else if (h == 3)
		{
			if (kt == 1)
			{
				system("cls");
				enterClass();
				system("cls");
				editClass();
			}
			else if (kt == 2)
			{
				system("cls");
				correctionClass();
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
				if (listInfC.isEmpty()) {
					system("cls");
					writeString(43, 1, L"CHƯA CÓ LỚP HỌC NÀO TRONG HỆ THỐNG! TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
					gotoxy(70, 2);
					system("pause");
					system("cls");
					editClass();
				}
				else {
					menuBar(65, 0, 26, 2, 11);
					writeString(70, 1, L"DANH SÁCH LỚP HỌC", 3);
					wcout << endl;
					gotoxy(68, 4);
					textcolor(12);
					wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
					textcolor(2);
					listInfC.Display();
					gotoxy(65, listInfC.getCount() + 7);
					textcolor(6);
					system("pause");
					system("cls");
					editClass();
				}
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
	ShowCur(true);
	LinkedList<Students> temp;
	LinkedList<Score> temp1;
	Node<informationClass>* head;
	wstring s;
	wstring name;
	do {
		system("cls");
	a:
		menuBar(61, 0, 37, 2, 11);
		writeString(66, 1, L"THÊM SINH VIÊN VÀO LỚP HỌC", 3);
		wcout << endl;
		gotoxy(68, 4);
		textcolor(12);
		wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
		textcolor(2);
		listInfC.Display();
		gotoxy(65, listInfC.getCount() + 7);
		textcolor(6);
		wcout << L"Nhập mã lớp học cần thêm sinh viên: ";
		s = inputString(9);
		head = Search(listInfC, s);
		if (head == NULL) {
			system("cls");
			writeString(60, 0, L"Lớp học không tồn tại hoặc bạn đã nhập sai!", 4);
			writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
			writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
			if (catchEvents() == 4) {
				system("cls");
				break;
			}
			else {
				system("cls");
				goto a;
			}
		}
		else {
			checkEntUs = 0;
			system("cls");
			name = conCat(L"listClass\\" + head->data.getClassName(), head->data.getClassCode());
			loadListStudentOfClass(name);
			vector<wstring> arr;
			do
			{
			b:
				Students st;
				wstring s1;
				textcolor(6);
				wcout << L"Nhập tên đăng nhập (9 chữ số): " << endl;
				s1 = inputString(9);
				for (auto& x : arr) {
					if (x == s1) {
						textcolor(4);
						wcout << L"Bạn đã nhập mã sinh viên bị trùng. Vui lòng nhập lại!" << endl;
						system("pause");
						system("cls");
						goto b;
					}
				}
				if (Check(listInfC, s1, L"")) {
					textcolor(4);
					wcout << L"Bạn đã nhập mã sinh viên bị trùng. Vui lòng nhập lại!" << endl;
					system("pause");
					system("cls");
					goto b;
					
				}
				if (s1.length() != 9) {
					textcolor(4);
					wcout << L"Mã sinh viên không đủ 9 chữ số!!!" << endl;
					goto b;
				}
				else
				{
					arr.push_back(s1);
					enterInf(st, s1, temp1);
					temp = head->data.getStudentList();
					temp.Insert(st);
					head->data.setStudentList(temp);
					writeDataStudentInfInClass(name);
					writeString(60, 0, L"Thêm mới thành công!", 12);
					writeString(60, 1, L"Nhấn nút [ESC] để kết thúc nhập", 5);
					writeString(60, 2, L"Nhấn nút bất kì để tiếp tục nhập", 5);
					if (catchEvents() == 4) {
						system("cls");
						checkEntUs = 1;
						break;
					}
					else {
						system("cls");
						goto b;
					}
				}
			} while (true);			
			return;
		}
	} while (true);
}
void deleteUser()
{
	ShowCur(true);
	LinkedList<Students> temp;
	LinkedList<Score> temp1;
	Node<informationClass>* head;
	Node<Students>* head1;
	wstring s;
	wstring name;
	do {
		system("cls");
	a:
		menuBar(61, 0, 37, 2, 11);
		writeString(66, 1, L"XÓA SINH VIÊN KHỎI LỚP HỌC", 3);
		wcout << endl;
		gotoxy(68, 4);
		textcolor(12);
		wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
		textcolor(2);
		listInfC.Display();
		gotoxy(65, listInfC.getCount() + 7);
		textcolor(6);
		wcout << L"Nhập mã lớp học cần xóa sinh viên: ";
		s = inputString(9);
		head = Search(listInfC, s);
		if (head == nullptr) {
			system("cls");
			writeString(60, 0, L"Lớp học không tồn tại hoặc bạn đã nhập sai!", 4);
			writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
			writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
			if (catchEvents() == 4) {
				system("cls");
				break;
			}
			else {
				system("cls");
				goto a;
			}
		}
		else {
			system("cls");
			name = conCat(L"listClass\\" + head->data.getClassName(), head->data.getClassCode());
			loadListStudentOfClass(name);
			if (checkFileIsEmpty(name)) {
				writeString(60, 1, L"Lớp học này chưa có sinh viên!", 4);
				gotoxy(60, 2);
				system("pause");
				break;
			}
			else {
				checkEntUs = 0; 
				wstring s;
				do {
				b:
					textcolor(6);
					wcout << L"Nhập mã sinh viên để xóa dữ liệu: ";
					s = inputString(9);
					head1 = Search(head, s);
					if (head1 == nullptr) {
						system("cls");
						writeString(60, 0, L"Sinh viên không tồn tại hoặc bạn đã nhập sai!", 4);
						writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
						writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
						if (catchEvents() == 4) {
							system("cls");
							checkEntUs = 1;
							break;
						}
						else {
							system("cls");
							goto b;
						}
					}
					else {
						system("cls");
						wcout << L"Thông tin sinh viên được chọn là" << endl;
						wcout << L"____________________________________" << endl;
						wcout << head1->data;
						wcout << L"_________________________________________" << endl;
						writeString(60, 0, L"Bạn có chắc chắn muốn xóa sinh viên này hay không?", 4);
						writeString(60, 1, L"Nhấn nút [ESC] để kết thúc xóa", 5);
						writeString(60, 2, L"Nhấn nút bất kì để tiếp tục xóa", 5);
						if (catchEvents() == 4) {
							system("cls");
							checkEntUs = 1;
							return;
						}
						else {
							system("cls");
							temp = head->data.getStudentList();
							temp.Delete(head1->data);
							head->data.setStudentList(temp);
							writeDataStudentInfInClass(name);
							system("cls");
							writeString(60, 0, L"Đã xóa thành công!", 4);
							gotoxy(60, 1);
							system("pause");
							if (head->data.getStudentList().isEmpty()) {
								wofstream file;
								file.open(name, ios_base::out | ios_base::trunc);
								file.close();
							}
							checkEntUs = 1;
							return;
						}
					}
				} while (true);
				return;
			}
		}
	} while (true);
}
void User::viewExam()
{
	wstring s;
	wstring line;
	vector<wstring> lines;
	wifstream file;
	if (listS.isEmpty()) {
		system("cls");
		writeString(43, 1, L"CHƯA CÓ MÔN HỌC NÀO TRONG HỆ THỐNG! TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
		gotoxy(70, 2);
		system("pause");
	}
	do {
		system("cls");
	a:
		menuBar(66, 0, 28, 2, 11);
		writeString(71, 1, L"DANH SÁCH MÔN HỌC", 3);
		wcout << endl;
		gotoxy(68, 4);
		textcolor(12);
		wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
		textcolor(2);
		listS.Display();
		gotoxy(65, listS.getCount() + 7);
		textcolor(6);
		wcout << L"Nhập mã môn học cần xem chi tiết các câu hỏi đã làm: ";
		s = inputString(9);
		Node<Subjects>* head = Search(listS, s);
		if (head == NULL) {
			system("cls");
			writeString(60, 0, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
			writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
			writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
			if (catchEvents() == 4) {
				system("cls");
				student();
				break;
			}
			else {
				system("cls");
				goto a;
			}
		}
		else {
			wstring name;
			name = conCat(L"listCLass\\" + tempInf->data.getClassName(), tempInf->data.getClassCode());
			loadListStudentOfClass(name);
			Node<Students>* head1 = Search(tempInf, tempS->data.getStudentCode());
			Node<Score>* current = head1->data.getScoreList().head;
			while (current != nullptr) {
				if (current->data.getSubjectCode() == s) {
					system("cls");
					wstring s5 = head->data.getSubjectName() + L"_" + head->data.getSubjectCode(); //tên folder môn học
					wstring s3 = tempS->data.getStudentCode();
					wstring name1 = L"listSubject\\" + s5 + L"\\" + conCat(s3, s);
					file.open(name1);
					file.imbue(loc);
					while (getline(file, line))
					{
						lines.push_back(line);
					}
					for (const auto& x : lines) {
						wcout << x << endl;
					}
					file.close();
					system("pause");
					system("cls");
					student();
				}
				current = current->next;
			}
			system("cls");
			writeString(60, 1, L"Chưa thi môn học này", 4);
			writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
			writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
			if (catchEvents() == 4) {
				system("cls");
				student();
				break;
			}
			else {
				system("cls");
				goto a;
			}
		}
	} while (true);
}
void User::correctionUser()
{
	ShowCur(true);
	if (checkAd == 0) {

		LinkedList<Students> temp;
		LinkedList<Score> temp1;
		Node<informationClass>* head;
		Node<Students>* head1;
		wstring s;
		wstring name;
		do {
			system("cls");
		a:
			menuBar(59, 0, 41, 2, 11);
			writeString(64, 1, L"ĐIỀU CHỈNH THÔNG TIN SINH VIÊN", 3);
			wcout << endl;
			gotoxy(68, 4);
			textcolor(12);
			wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
			textcolor(2);
			listInfC.Display();
			gotoxy(65, listInfC.getCount() + 7);
			textcolor(6);
			wcout << L"Nhập mã lớp học cần xóa sinh viên: ";
			s = inputString(9);
			head = Search(listInfC, s);
			if (head == nullptr) {
				system("cls");
				writeString(60, 0, L"Lớp học không tồn tại hoặc bạn đã nhập sai!", 4);
				writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
				writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
				if (catchEvents() == 4) {
					system("cls");
					break;
				}
				else {
					system("cls");
					goto a;
				}
			}
			else {
				system("cls");
				name = conCat(L"listClass\\" + head->data.getClassName(), head->data.getClassCode());
				loadListStudentOfClass(name);
				if (checkFileIsEmpty(name)) {
					writeString(60, 1, L"Lớp học này chưa có sinh viên!", 4);
					gotoxy(60, 2);
					break;
				}
				else {
					checkEntUs = 0;
					wstring s1;
					do {
					b:
						textcolor(6);
						wcout << L"Nhập mã sinh viên để thay đổi thông tin: ";
						s1 = inputString(9);
						head1 = Search(head, s1);
						if (head1 == nullptr) {
							system("cls");
							writeString(60, 0, L"Sinh viên không tồn tại hoặc bạn đã nhập sai!", 4);
							writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
							writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
							if (catchEvents() == 4) {
								system("cls");
								checkEntUs = 1;
								break;
							}
							else {
								system("cls");
								goto b;
							}
						}
						else {
							system("cls");
							Students st;
							wstring nameFolder;
							Node<Score>* current = head1->data.getScoreList().head;
							Node<Subjects> *nodeS;
							wstring nameFile;
							wstring newNameFile;
							wcout << L"Thông tin sinh viên được chọn là" << endl;
							wcout << L"____________________________________" << endl;
							wcout << head1->data;
							wcout << L"_________________________________________" << endl;
							enterInf(st, head1->data.getStudentCode(), head1->data.getScoreList());
							while (current != nullptr)
							{
								nodeS = Search(listS, current->data.getSubjectCode());
								nameFolder = nodeS->data.getSubjectName() + L"_" + nodeS->data.getSubjectCode() + L"\\";
								nameFile = L"listSubject\\" + nameFolder + conCat(head1->data.getStudentCode(), nodeS->data.getSubjectCode());
								newNameFile = L"listSubject\\" + nameFolder + conCat(st.getStudentCode(), nodeS->data.getSubjectCode());
								if (_wrename(nameFile.c_str(), newNameFile.c_str()) != 0)
								{
									_wperror(L"Error renaming file\n");
								}
								current = current->next;
							}
							head->data.getStudentList().Update(head1->data, st);
							writeDataStudentInfInClass(name);		
							checkEntUs = 1;
							textcolor(4);
							wcout << L"Thay đổi thành công" << endl;
							return;
						}
					} while (true);
					return;
				}
			}
		} while (true);
	}
#if 1
	else {
		wstring name;
		name = conCat(L"listClass\\" + tempInf->data.getClassName(), tempInf->data.getClassCode());
		loadListStudentOfClass(name);
		Node<Students>* head1 = Search(tempInf, tempS->data.getStudentCode());
		system("cls");
		Students st;
		wcout << L"Thông tin sinh viên được chọn là" << endl;
		wcout << L"____________________________________" << endl;
		wcout << head1->data;
		wcout << L"_________________________________________" << endl;
		enterInf(st, head1->data.getStudentCode(), head1->data.getScoreList());
		head1->data = st;
		tempS = head1;
		writeDataStudentInfInClass(name);
		system("pause");
		system("cls");
		student();
	}
#endif
}
void Admin::editUser()
{
	ShowCur(false);
	wstring s;
	int x, y;
	menuBar(70, 1, 20, 2, 11);	writeString(75, 2, L"GIÁO VIÊN", 14);
	textcolor(2);	menuTable(x = 30, y = 6);	textcolor(3);
	if (listInfC.isEmpty()) {
		writeString(x + 45, y + 3, L"CHƯA CÓ LỚP HỌC NÀO TRONG HỆ THỐNG!", 4);
		writeString(x + 45, y + 6, L"TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
		gotoxy(x + 45, y + 9);
		system("pause");
		system("cls");
		teacher();
	}
	else {
		menuBar(x + 42, y + 2, 40, 2, 11);
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
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
					menuBar(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 15);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
				}
				else if (kt == 2)
				{
					kt = 3;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
					menuBar(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 15);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 3)
				{
					kt = 4;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
					menuBar(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 15);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 4)
				{
					kt = 5;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
					menuBar(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
				}
				else if (kt == 5)
				{
					kt = 1;
					menuBar(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 15);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
			}
			else if (h == 5)
			{
				if (kt == 1)
				{
					kt = 5;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
					menuBar(x + 42, y + 14, 40, 2, 11); writeString(x + 45, y + 15, L"5. Thoát", 15);
				}
				else if (kt == 5)
				{
					kt = 4;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
					menuBar(x + 42, y + 11, 40, 2, 11); writeString(x + 45, y + 12, L"4.Hiện thị sinh viên", 15);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 4)
				{
					kt = 3;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
					menuBar(x + 42, y + 8, 40, 2, 11);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 15);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 3)
				{
					kt = 2;
					menuBar(x + 42, y + 2, 40, 2, 0);	writeString(x + 45, y + 3, L"1. Thêm sinh viên.", 6);
					menuBar(x + 42, y + 5, 40, 2, 11);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 15);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);

				}
				else if (kt == 2)
				{
					kt = 1;
					menuBar(x + 42, y + 2, 40, 2, 11);	writeString(x + 45, y + 3, L"1. Thêm sinh viên", 15);
					menuBar(x + 42, y + 5, 40, 2, 0);	writeString(x + 45, y + 6, L"2. Điều chỉnh sinh viên.", 6);
					menuBar(x + 42, y + 8, 40, 2, 0);	writeString(x + 45, y + 9, L"3. Xóa sinh viên", 6);
					menuBar(x + 42, y + 11, 40, 2, 0); writeString(x + 45, y + 12, L"4. Hiện thị sinh viên", 6);
					menuBar(x + 42, y + 14, 40, 2, 0); writeString(x + 45, y + 15, L"5. Thoát", 6);
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
					system("cls");
					editUser();
				}
				else if (kt == 4)
				{
					Node<informationClass>* head;
					do {
						system("cls");
					a:
						menuBar(65, 0, 26, 2, 11);
						writeString(70, 1, L"DANH SÁCH LỚP HỌC", 3);
						wcout << endl;
						gotoxy(68, 4);
						textcolor(12);
						wcout << setw(10) << left << L"TÊN LỚP" << setw(5) << L" - " << setw(5) << L"MÃ LỚP" << right << setw(10) << endl;
						textcolor(2);
						listInfC.Display();
						gotoxy(65, listInfC.getCount() + 7);
						textcolor(6); 
						ShowCur(true);
						wcout << L"Nhập mã lớp học cần xem thông tin sinh viên: ";
						s = inputString(9);
						head = Search(listInfC, s);
						if (head == NULL) {
							system("cls");
							writeString(60, 0, L"Lớp học không tồn tại hoặc bạn đã nhập sai!", 4);
							writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
							writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
							if (catchEvents() == 4) {
								system("cls");
								break;
							}
							else {
								system("cls");
								goto a;
							}
						}
						else {
							wstring name;
							name = conCat(L"listClass\\" + head->data.getClassName(), head->data.getClassCode());	 
							if (checkFileIsEmpty(name)) {
								system("cls");
								writeString(60, 1, L"Lớp học này không có sinh viên để hiện thị!.", 4);
								gotoxy(60, 2);
								system("pause");
								break;
							}
							else {
								loadListStudentOfClass(name);
								display(head->data.getStudentList(), head);
								head->data.getStudentList().Delete();
							}
							break;

						}
					} while (true);
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
}

void User::multipleChoiceTest()
{
	wfstream file;
	Node<Subjects>* head;
	LinkedList<Questions> temp;
	wstring s;
	wstring name;
	wstring line;
	vector<wstring> lines;
	wchar_t ch = L'\0';
	if (listS.isEmpty()) {
		system("cls");
		writeString(43, 1, L"CHƯA CÓ MÔN HỌC NÀO TRONG HỆ THỐNG! TÍNH NĂNG NÀY KHÔNG THỂ DÙNG ĐƯỢC!!!", 4);
		gotoxy(70, 2);
		system("pause");
		system("cls");
		teacher();
	}
	else {
		do {
		a:
			system("cls");
			menuBar(67, 0, 26, 2, 11);
			writeString(72, 1, L"THI TRẮC NGHIỆM", 3);
			wcout << endl;
			gotoxy(68, 4);
			textcolor(12);
			wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
			textcolor(2);
			listS.Display();
			gotoxy(65, listS.getCount() + 7);
			textcolor(6);
			wcout << L"Nhập mã môn học cần thi: ";
			s = inputString(9);
			head = Search(listS, s);
			if (head == nullptr) {
				system("cls");
				writeString(60, 0, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
				writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
				writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
				if (catchEvents() == 4) {
					system("cls");
					if (checkAd == 0) {
						teacher();
					}
					else
						student();
				}
				else {
					system("cls");
					goto a;
				}
			}
			else {
				name = conCat(L"listSubject\\" + head->data.getSubjectName(), head->data.getSubjectCode());
				if (checkFileIsEmpty(name)) {
					system("cls");
					writeString(60, 1, L"File rỗng không có câu hỏi để làm bài!", 4);
					gotoxy(60, 2);
					system("pause");
					system("cls");
					if (checkAd == 0) {
						teacher();
					}
					else
						student();
				}
				else
				{
					loadQuestions(name);
				}
				break;
			}
		} while (true);
		wstring s5 = head->data.getSubjectName() + L"_" + s; //tên folder môn học
		if (checkUS == 0) {
			file.open(L"listSubject\\" + s5 + L"\\" + conCat(tempS->data.getStudentCode(), s), ios::out); // lưu trong file môn học
			file.imbue(loc);
		}
		if (checkAd == 0) {
			file.open(conCat(L"Admin_test_", s), ios::out);
			file.imbue(loc);
		}
		system("cls");
		int numberOfQuestions;
		while (true)
		{
			wcout << L"Nhập số câu hỏi thi " << "(1.." << head->data.getQuestionList().getCount() << "): ";
			if (wcin >> numberOfQuestions) {
				if (numberOfQuestions > head->data.getQuestionList().getCount() || numberOfQuestions < 1) {
					wcin.clear();
					wcin.ignore(1000, '\n');
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
		int count = numberOfQuestions;
		int score = 0;
		wcin.ignore();
		int timeEx;
		while (true)
		{
			wcout << L"Nhập thời gian cho mỗi câu hỏi(s): ";
			if (wcin >> timeEx) {
				if (timeEx < 1) {
					wcin.clear();
					wcin.ignore(1000, '\n');
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
		cron::milliseconds time = (timeEx * 1000ms);

		file << L"Số lượng câu hỏi đã chọn: " << numberOfQuestions << endl;
		file << L"Thời gian của mỗi câu hỏi: " << timeEx << L"s" << endl;

		do {
			textcolor(6);
			system("cls");
			Questions value = head->data.getQuestionList().getRandom();
			file << "Id: " << value.getId() << endl;
			file << L"Nội dung câu hỏi: " << value.getContentQuestions() << endl;
			file << L"A. " << value.getA() << endl;
			file << L"B. " << value.getB() << endl;
			file << L"C. " << value.getC() << endl;
			file << L"D. " << value.getD() << endl;
			switch (value.getAnswer())
			{
			case 1:
				ch = L'A';
				break;
			case 2:
				ch = L'B';
				break;
			case 3:
				ch = L'C';
				break;
			case 4:
				ch = L'D';
				break;
			}
			file << L"Đáp án: " << ch << endl;
			wcout << value;
			gotoxy(0, 9);
			ShowCur(false);
			wcout << L"Nhập câu trả lời của bạn(A, B, C, D): ";
			wchar_t answer = charInputTimeout(time, 100ms, 1);
			if (!answer) {

				file << L"Bạn đã không kịp thời cho câu hỏi này" << endl;

				textcolor(4);
				wcout << L"Bạn đã không kịp thời cho câu hỏi này" << endl;
				system("pause");
			}
			else
			{

				file << L"Đáp án của bạn: " << answer << endl;

				if (enterResult(answer) == value.getAnswer())
					score++;
			}
			temp = head->data.getQuestionList();
			temp.Delete(value);
			head->data.setQuestionList(temp);
			numberOfQuestions--;
		} while (numberOfQuestions != 0);
		system("cls");
		float realSocre = (float)10.0f * score / count;
		wcout << L"Sau khi thi điểm của bạn là: " << realSocre << endl;

		file << L"Tổng số câu hỏi đúng: " << score << endl;
		file << L"Điểm của bạn: " << realSocre << endl;
		// Nếu như cờ checkUS được tắt thì đoạn này sẽ ghi điểm
		if (checkUS == 0) {
			name = conCat(L"listClass\\" + tempInf->data.getClassName(), tempInf->data.getClassCode());
			loadListStudentOfClass(name);
			Score listSc;
			listSc.setScore(realSocre);
			listSc.setSubjectCode(s);
			listSc.setSubjectName(head->data.getSubjectName());
			Node<Students>* head2 = Search(tempInf, tempS->data.getStudentCode());
			LinkedList<Score> listSc1 = head2->data.getScoreList();
			if (listSc1.isEmpty() == true) {
				listSc1.Insert(listSc);
				head2->data.setScoreList(listSc1);
			}
			else {
				int check = 0;
				Node<Score>* current = listSc1.head;
				while (current != nullptr)
				{
					if (current->data.getSubjectCode() == s) {
						current->data.setScore(realSocre);
						check = 1;
						break;
					}
					current = current->next;
				}
				if (!check) {
					listSc1.Insert(listSc);
					head2->data.setScoreList(listSc1);
				}
			}
			writeDataStudentInfInClass(name);
			system("pause");
			system("cls");
			file.close();
			student();

		}
		file.close();
		textcolor(4);
		wcout << L"Chi tiết các câu hỏi đã thi" << endl;
		file.open(conCat(L"Admin_test_", s));
		file.imbue(loc);
		textcolor(6);
		while (getline(file, line))
		{
			lines.push_back(line);
		}
		for (const auto& x : lines) {
			wcout << x << endl;
		}
		file.close();
		system("pause");
		system("cls");
		teacher();
	}
}
void removeFile(wstring s)
{
	const wchar_t* c = s.c_str();
	if (_wremove(c) != 0) {
		wcerr << L"File deletion failed" << endl;
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

Node<Subjects>* Search(LinkedList<Subjects> list, wstring code)
{
	Node<Subjects>* current = list.head;
	while (current != nullptr) {
		if (current->data.getSubjectCode() == code) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}
Node<Questions>* Search(Node<Subjects>* node, int code)
{
	Node<Questions>* current = node->data.getQuestionList().head;
	while (current != nullptr) {
		if (current->data.getId() == code) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}
Node<informationClass>* Search(LinkedList<informationClass> list, wstring code)
{
	Node<informationClass>* current = list.head;
	while (current != nullptr) {
		if (current->data.getClassCode() == code) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}
Node<Students>* Search(Node<informationClass>* node, wstring code)
{
	Node<Students>* current = node->data.getStudentList().head;
	while (current != nullptr) {
		if (current->data.getStudentCode() == code) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}
Node<Score>* Search(LinkedList<Score> list, wstring code) {
	Node<Score>* current = list.head;
	while (current != nullptr) {
		if (current->data.getSubjectCode() == code) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

void DeleteAndCorrection(LinkedList<informationClass> list, wstring code, Subjects sb)
{
	Node<informationClass>* currentInf = list.head;
	Node<Students>* currentS;
	Node<Score> *node;
	Node<Subjects>* nodeS;
	Score sc;
	LinkedList<Score> tempSc;
	wstring nameFile;
	wstring newNameFile;
	wstring nameFolder;
	wstring name;
	while (currentInf != nullptr) {
		name = L"listClass\\" + conCat(currentInf->data.getClassName(), currentInf->data.getClassCode());
		loadListStudentOfClass(name);
		currentS = currentInf->data.getStudentList().head;
		while (currentS != nullptr)
		{
			tempSc = currentS->data.getScoreList();
			node = Search(tempSc, code);
			nodeS = Search(listS, code);
			if (node != nullptr) {
				if (checkDelete == 0) {
					tempSc.Delete(node->data);
					currentS->data.setScoreList(tempSc);
					writeDataStudentInfInClass(name);
				}
				else {
					nameFolder = nodeS->data.getSubjectName() + L"_" + code + L"\\";
					nameFile = L"listSubject\\" + nameFolder + conCat(currentS->data.getStudentCode(), code);
					newNameFile = L"listSubject\\" + nameFolder + conCat(currentS->data.getStudentCode(), sb.getSubjectCode());
					if (_wrename(nameFile.c_str(), newNameFile.c_str()) != 0)
					{
						_wperror(L"Error renaming file\n");
					}
					sc.setScore(node->data.getScore());
					sc.setSubjectCode(sb.getSubjectCode());
					node->data = sc;
					writeDataStudentInfInClass(name);
				}
			}
			currentS = currentS->next;
		}
		currentInf = currentInf->next;
	}
}

void display(LinkedList<Students> head, Node<informationClass> *head2)
{
	system("cls");
	head.Sort(LinkedList<Students> ::SORT_ASC);
	int x = 3, y = 3;
	LinkedList<Students> temp = head;
	int count = 10;
	int page = 1;
	int max = temp.getCount();
	int totalPage = max / count;
	int surplus = max % count;
	if (max % count || totalPage == 0) {
		totalPage++;
	}
abc:
	while (true)
	{
		ShowCur(false);
		y = 3;
		checkEx = 1;
		system("cls");
		wstring s1 = L"[ THÔNG TIN SINH VIÊN LỚP " + head2->data.getClassName() + L" ]";
		const wchar_t* s = s1.c_str();
		menuDisplaySt(x, y, 23);
		writeString(x + 1, y - 2, s, 14);	writeString(x + 1, y - 1, L"------------------------", 14);
		writeString(x + 110, y - 1, L"Nhấn ESC để quay trở lại menu", 12);
		writeString(x + 110, y - 3, L"Nhấn TAB để xem danh sách điểm thi theo môn", 12);
		writeString(x + 3, y + 24, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!", 12);
		writeString(x + 135, y - 1, L"Trang:", 7);	gotoxy(x + 142, y - 1); wcout << page << "\\" << totalPage;
		for (int i = (page - 1) * count; i < page * count && i < max; i++) {
			display(temp.getNode(i)->data, x, y, i, L"");
			y += 2;
		}
		int flag = 0;
		while (true)
		{
			Node<Subjects>* head1;
			wstring s;
			int h = catchEvents();
			gotoxy(x + 66, 28);
			switch (h)
			{
			case 2:
				checkEx = 0;
				do {
				a:
					system("cls");
					menuBar(66, 0, 28, 2, 11);
					writeString(71, 1, L"DAHH SÁCH MÔN HỌC", 3);
					wcout << endl;
					gotoxy(68, 4);
					textcolor(12);
					wcout << setw(10) << left << L"TÊN MÔN" << setw(5) << L" - " << setw(5) << L"MÃ MÔN" << right << setw(10) << endl;
					textcolor(2);
					listS.Display();
					gotoxy(65, listS.getCount() + 7);
					textcolor(6);
					wcout << L"Nhập mã môn học cần xem câu hỏi: ";
					getline(wcin, s);
					head1 = Search(listS, s);
					if (head1 == nullptr) {
						system("cls");
						writeString(60, 0, L"Môn học không tồn tại hoặc bạn đã nhập sai!", 4);
						writeString(60, 2, L"Nhấn nút [ESC] để kết thúc nhập", 5);
						writeString(60, 3, L"Nhấn nút bất kì để tiếp tục nhập", 5);
						if (catchEvents() == 4) {
							system("cls");
							goto abc;
						}
						else {
							system("cls");
							goto a;
						}
					}
					else {
						while (true)
						{
							y = 3;
							system("cls");
							wstring s1 = L"[ THÔNG TIN SINH VIÊN LỚP " + head2->data.getClassName() + L"]";
							wstring s2 = L"[ Điểm môn " + head1->data.getSubjectName() + L"]";
							const wchar_t* s = s1.c_str();
							const wchar_t* s3 = s2.c_str();
							menuDisplaySt(x, y, 23);
							writeString(x + 1, y - 2, s, 14);
							writeString(x + 50, y - 2, s3, 14);
							writeString(x + 1, y - 1, L"------------------------", 14);
							writeString(x + 110, y - 1, L"Nhấn ESC để quay trở lại menu sinh viên", 12);
							writeString(x + 3, y + 24, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!", 12);
							writeString(x + 135, y - 2, L"Trang:", 7);	gotoxy(x + 142, y - 2); wcout << page << "\\" << totalPage;
							for (int i = (page - 1) * count; i < page * count && i < max; i++) {
								display(temp.getNode(i)->data, x, y, i, head1->data.getSubjectCode());
								y += 2;
							}
							int flag = 0;
							while (true)
							{
								int h = catchEvents();
								gotoxy(x + 66, 28);
								switch (h)
								{
								case 4:
									goto abc;
									return;
								case 7:
									if (page > 1) {
										page--;
										y = 3;
										flag = 1;
									}
									break;
								case 8:
									if (page < totalPage) {
										page++;
										y = 3;
										flag = 1;
									}
									break;
								}

								if (flag) {
									break;
								}
							}
						}
					}
				} while (true);
				break;
			case 4:
				return;
			case 7:
				if (page > 1) {
					page--;
					y = 3;
					flag = 1;
				}
				break;
			case 8:
				if (page < totalPage) {
					page++;
					y = 3;
					flag = 1;
				}
				break;
			}

			if (flag) {
				break;
			}
		}
	}
}
void display(Students st, int x, int y, int i, wstring s)

{
	textcolor(15);	gotoxy(x + 1, y + 4);
	wcout << i + 1;
	gotoxy(x + 6, y + 4);	wcout << st.getStudentCode();
	gotoxy(x + 23, y + 4);	wcout << st.getLastName();
	gotoxy(x + 43, y + 4);	wcout << st.getFirstName();
	gotoxy(x + 61, y + 4);	wcout << st.getSex();
#if 1
	if (checkEx == 0) {
		int len = 0;
		LinkedList<Score> temp = st.getScoreList();
		if (temp.isEmpty() == true) {
			gotoxy(x + 77, y + 4);	wcout << L"Chưa thi";
		}
		else {
			for (int i = 0; i < temp.getCount(); i++) {
				if (temp.getNode(i)->data.getSubjectCode() == s) {
					gotoxy(x + 77, y + 4);	wcout << temp.getNode(i)->data.getScore();
					break;
				}
				len++;
			}
			if (len == temp.getCount()) {
				gotoxy(x + 77, y + 4);	wcout << L"Chưa thi";
			}
		}
	}
	else {
		gotoxy(x + 77, y + 4);	wcout << st.getPasswork();
	}
#endif
}
void display(LinkedList<Questions> head)
{
	if (head.head != NULL) {
		Node<Questions>* node = head.head;
		while (node != nullptr)
		{
			wcout << node->data << endl;
			node = node->next;
		}
	}
}

bool Check(LinkedList<informationClass> list, wstring user, wstring pass) {	
	Node<informationClass>* currentInf = list.head;
	Node<Students>* currentS;
	while (currentInf != nullptr) {
		loadListStudentOfClass(L"listClass\\" + conCat(currentInf->data.getClassName(), currentInf->data.getClassCode()));
		currentS = currentInf->data.getStudentList().head;
		while (currentS != nullptr)
		{
			if (checkAd == 0 && user == currentS->data.getStudentCode()) {
				return true;
			}
			if (user == currentS->data.getStudentCode() && pass == currentS->data.getPasswork()) {
				tempS = currentS;
				tempInf = currentInf;
				return true;
			}
			currentS = currentS->next;
		}
		currentInf = currentInf->next;
	}
	return false;
}

void enterInf(Students& st, wstring code, LinkedList<Score> listSc) {
	wstring s;
	if (checkAd == 0) {
	ID:
		textcolor(6);
		wcout << L"Nhập tên đăng nhập (9 chữ số): " << endl;
		checkEntUs = 0;
		s = inputString(9);
		if (Check(listInfC, s, L"")) {
			textcolor(4);
			wcout << L"Bạn đã nhập mã sinh viên bị trùng. Vui lòng nhập lại!" << endl;
			goto ID;
		}
		else if (s.length() != 9) {
			textcolor(4);
			wcout << L"Mã sinh viên không đủ 9 chữ số!!!" << endl;
			goto ID;
		}
		else {
			st.setStudentCode(s);
		}
	}	
	else {
		st.setStudentCode(code);
	}
FN:
	textcolor(6);
	wcout << L"Nhập họ: " << endl;
	s = Upper(s);
	getline(wcin, s);
	if (s.length() == 0) {
		textcolor(4);
		wcout << L"Không được bỏ trống!!!" << endl;
		goto FN;
	}
	st.setLastName(s);
	s.clear();
LN:
	textcolor(6);
	wcout << L"Nhập tên: " << endl;
	getline(wcin, s);
	s = Upper(s);
	if (s.length() == 0) {
		textcolor(4);
		wcout << L"Không được bỏ trống!!!" << endl;
		goto LN;
	}
	st.setFirstName(s);
	s.clear();
Sx:
	textcolor(6);
	int sex;
	while (true)
	{
		wcout << L"Nhập giới tính(0: Nam; 1: Nữ; 3: Khác) : " << endl;
		if (wcin >> sex)
		{
			if (sex < 0 || sex > 3) {
				wcin.clear();
				wcin.ignore(1000, '\n');
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
	if (sex == 0)
		s = L"Nam";
	else if (sex == 1)
		s = L"Nữ";
	else
		s = L"Khác";
	s = Upper(s);
	if (s.length() == 0) {
		textcolor(4);
		wcout << L"Không được bỏ trống!!!" << endl;
		goto Sx;
	}
	st.setSex(s);
	s.clear();
	wcin.ignore();
Ps:
	textcolor(6);
	wcout << L"Nhập password: " << endl;
	getline(wcin, s);
	if (s.length() == 0) {
		textcolor(4);
		wcout << L"Không được bỏ trống!!!" << endl;
		goto Ps;
	}
	st.setPasswork(s);
	s.clear();
	st.setScoreList(listSc);
}

