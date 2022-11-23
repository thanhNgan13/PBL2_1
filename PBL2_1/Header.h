#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <strsafe.h>
#include <chrono>
#include <iomanip>

#pragma warning(disable : 4996)

using namespace std;
// Khai báo cáo namespace để dùng cho hàm nhập kí tự theo thười gian
namespace cron = std::chrono;
using namespace std::literals::chrono_literals;

//Khai báo các biến toàn cục
static int checkAd = 1;
static int checkUS = 1;
static int checkEx = 1;
static int checkEntUs = 1;
static int checkDelete = 1;


inline wstring inputStr(size_t length_max) {
	wstring strRet;
	wchar_t ch;
	do
	{
		ch = getch();
		if (checkEntUs == 0) {
			if ((strRet.size() < length_max) && (isdigit(ch)))
			{
				wcout << ch;
				strRet.push_back(ch);
			}
			if (L'\b' == ch && !strRet.empty())
			{
				wcout << L"\b \b";
				strRet.pop_back();
			}
		}
		else {
			if ((strRet.size() < length_max) && (isalnum(ch) || isalpha(ch)))
			{
				wcout << ch;
				strRet.push_back(ch);
			}
			if (L'\b' == ch && !strRet.empty())
			{
				wcout << L"\b \b";
				strRet.pop_back();
			}
		}
	} while (L'\r' != ch);
	wcout << endl;
	return strRet;
}
//Làm ẩn con trỏ chuột
inline void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//Chỉnh màu sắc chữ
inline void textcolor(int x)
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}
//Di chuyển con trỏ chuột đến tọa độ (x, y)
inline void gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD   Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//Nhập kí tự trong thời gian nhất định
inline wchar_t charInputTimeout(cron::milliseconds duration, cron::milliseconds displayInterval, int timerPrecision) {
	wchar_t ret = 0;
	auto now = cron::steady_clock::now();
	auto timerEnd = now + duration;
	cron::duration<double> timeLeft = timerEnd - now;
	auto lastIntervalDisplayTime = now;
	bool redraw = true;

	while (timeLeft > 0s) {
		// Check if we need to redraw time because of key hit
		textcolor(6);
		gotoxy(45, 9);
		if (_kbhit()) {
			wchar_t ch = _getch();
			if (ch == L'\b') {
				ret = 0;
				wcout << L"\b \b"; // quick and dirty backspace
				redraw = true;
			}
			else if (ch == L'\r' || ch == L'\n') {
				if (ret) break;
				// else do nothing
			}
			else if (ch != L'a' && ch != L'b' && ch != L'c' && ch != L'd' && ch != L'A' && ch != L'B' && ch != L'C' && ch != L'D') {
				if (ret) wcin.clear();
				ret = L'\0';
			}
			else {
				ret = ch;
				redraw = true;
			}
		}
		// Check if we need to redraw time interval
		now = cron::steady_clock::now();
		timeLeft = timerEnd - now;
		if (timeLeft < 0s) timeLeft = 0s;
		if (now - lastIntervalDisplayTime >= displayInterval) {
			redraw = true;
			lastIntervalDisplayTime = now;
		}
		// Draw
		if (redraw) {
			gotoxy(0, 10);
			textcolor(5);
			wcout << L"\rBạn còn " << fixed << setprecision(timerPrecision) << timeLeft.count() << L"s" << endl;
			textcolor(6);
			gotoxy(45, 9);
			if (ret) wcout << ret;
			redraw = false;
		}
		Sleep(16); // don't rape your CPU!
	}
	wcout << L'\n';
	return ret;
}
//Nhập chuỗi với số lượng cố định
inline wstring inputString(size_t length_max)
{
	wstring strRet;
	wchar_t ch;
	do
	{
		ch = getch();
		if (checkEntUs == 0) {
			if ((strRet.size() < length_max) && (isdigit(ch)))
			{
				wcout << ch;
				strRet.push_back(ch);
			}
			if (L'\b' == ch && !strRet.empty())
			{
				wcout << L"\b \b";
				strRet.pop_back();
			}
		}
		else {
			if ((strRet.size() < length_max) && (isalnum(ch) || isalpha(ch)))
			{
				wcout << ch;
				strRet.push_back(ch);
			}
			if (L'\b' == ch && !strRet.empty())
			{
				wcout << L"\b \b";
				strRet.pop_back();
			}
		}
	} while (L'\r' != ch);
	wcout << endl;
	return strRet;
}
//Nhập chuỗi với số lượng cố định và ẩn hiện chuỗi
inline wstring inputPassword(size_t length_max)
{
	wstring strRet;
	wchar_t ch = 0;
	bool bShow = false;
	do
	{
		ch = getch();
		if ((strRet.size() < length_max) && (isalpha(ch) || isalnum(ch) || isgraph(ch)))
		{
			wcout << (bShow ? ch : L'*');
			strRet.push_back(ch);
		}
		else
		{
			if (0x1B == ch) // 0x1B mã ASCII của phím esc.
			{
				bShow = !bShow;
				wcout << wstring(strRet.size(), L'\b');

				if (bShow)
					wcout << strRet;
				else
					wcout << wstring(strRet.size(), L'*');

			}
			if (L'\b' == ch && !strRet.empty())
			{
				wcout << L"\b \b";
				strRet.pop_back();
			}
		}

	} while (L'\r' != ch);
	wcout << endl;
	return strRet;
}
//Ghi lỗi và thoát ra ( dùng trong bắt sự kiện chuột)
inline VOID WriteError(LPSTR lpszMessage) {
	printf("%s\n", lpszMessage);
	ExitProcess(0);
}
// Xóa các khoảng trắng dư thừa
inline void removeSpaces(wstring& str)
{

	size_t n = str.length();
	size_t i = 0, j = -1;
	bool spaceFound = false;
	while (++j < n && str[j] == ' ');
	while (j < n)
	{
		if (str[j] != ' ')
		{
			if ((str[j] == '.' || str[j] == ',' ||
				str[j] == '?') && i - 1 >= 0 &&
				str[i - 1] == ' ')
				str[i - 1] = str[j++];
			else

				str[i++] = str[j++];
			spaceFound = false;
		}
		else if (str[j++] == ' ')
		{
			if (!spaceFound)
			{
				str[i++] = ' ';
				spaceFound = true;
			}
		}
	}
	if (i <= 1)
		str.erase(str.begin() + i, str.end());
	else
		str.erase(str.begin() + i - 1, str.end());
}
// Hàm tách tên với mã môn/lớp học
inline wstring subStr(wstring s) {
	size_t index1 = 0;
	size_t index2 = 0;
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] == L'_') {
			index1 = i + 1;
		}
		if (s[i] == L'.') {
			index2 = i; ;
		}
	}
	wstring reslut = s.substr(index1, index2 - index1);
	return reslut;
}
// Hàm hash để tạo mã cho câu hỏi
inline int hashCode(wstring s) {
	int sum = 0;
	int i = 0;
	while (s[i] != NULL)
	{
		sum += ((i + 1) * (s[i] * s[i]));
		i++;
	}
	return (int)fabs(sum % 6997);
}
// Viết hoa chữ cái đầu và sau khoảng trắng
inline wstring Upper(wstring s) {
	if (s[0] != L' ') {
		s[0] = towupper(s[0]);
		for (size_t i = 1; i < s.length(); i++) {
			if (s[i] == L' ' && s[i + 1] != L' ') 
				s[i + 1] = towupper(s[i + 1]);
		}
	}
	return s;
}
// chuyền từ kiểu char sang LPCWSTR
inline wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
// Viết kí tự tại vị trí có tọa độ (x, y)
inline void wirteChar(int x, int y, const wchar_t* z) {
	gotoxy(x, y);
	wcout << z;
}
// Viết chuỗi có màu sắc tại vị trí có tọa độ (x, y)
inline void writeString(int x, int y, const wchar_t* s, int color)
{
	gotoxy(x, y);
	textcolor(color);
	wcout << s;
}
// Bắt sự kiện bàn phím
inline int catchEvents()
{
	int c = getch();
	if (c == 8) //Backspace
		return 1;
	else if (c == 9) //Tab
		return 2;
	else if (c == 13) //Enter
		return 3;
	else if (c == 27) //Esc
		return 4;
	else if (c == 224)
	{
		c = getch();
		if (c == 72) //Keyup
			return 5;
		else if (c == 80) //KeyDown
			return 6;
		else if (c == 75) //KeyLeft
			return 7;
		else if (c == 77) //KeyRight
			return 8;
		else if (c == 83) //Delete
			return 9;
	}
	else if (c == 0)
	{
		c = getch();
		if (c == 60) //F2
			return 12;
		if (c == 62) //F4
			return 13;
	}
}
// Vẽ khung có màu và kích thước m*n tại vị trí có tọa độ (x, y)
inline void menuBar(int x, int y, int m, int n, int color)
{
	int i, j;
	textcolor(color);
	for (i = x; i <= x + m; i++)
		for (j = y; j <= y + n; j++)
		{
			if (i == x || i == x + m)
			{
				if (j == y && i != x + m)
					wirteChar(i, j, L"┌");
				else if (j == y && i != x)
					wirteChar(i, j, L"┐");
				else if (j == y + n && i != x + m)
					wirteChar(i, j, L"└");
				else if (j == y + n && i != x)
					wirteChar(i, j, L"┘");
				else wirteChar(i, j, L"│");
			}
			else if (j == y || j == y + n)
				wirteChar(i, j, L"─");
		}
}
// Vẽ bảng tại vị trí có tọa độ (x, y)
inline void menuTable(int x, int y)
{
	int i, j;
	for (i = x; i <= x + 90; i++)
		for (j = y; j <= y + 20; j++)
		{
			if (i == x || i == x + 40 || i == x + 90)
			{
				if (j == y && i != x && i != x + 90)
					wirteChar(i, j, L"╦");
				else if (j == y && i != x + 90)
					wirteChar(i, j, L"╔");
				else if (j == y && i != x)
					wirteChar(i, j, L"╗");
				else if (j == y + 20 && i != x && i != x + 90)
					wirteChar(i, j, L"╩");
				else if (j == y + 20 && i != x + 90)
					wirteChar(i, j, L"╚");
				else if (j == y + 20 && i != x)
					wirteChar(i, j, L"╝");
				else wirteChar(i, j, L"║");
			}
			else if (j == y || j == y + 20)
				wirteChar(i, j, L"═");
		}
}
// Bảng hiện sinh viên tại tọa độ (x, y)
inline void menuDisplaySt(int x, int y, int sl)
{
	int i, j;
	textcolor(2);
	for (i = x; i <= x + 89; i++)
		for (j = y; j <= y + sl; j++)
		{
			if (i == x || i == x + 4 || i == x + 20 || i == x + 42 || i == x + 60 || i == x + 76 || i == x + 89)
			{
				if (j == y && i != x && i != x + 89)
					wirteChar(i, j, L"┬");
				else if (j == y && i != x + 89)
					wirteChar(i, j, L"┌");
				else if (j == y && i != x)
					wirteChar(i, j, L"┐");
				else if (j == y + 2 && i != x && i != x + 89)
					wirteChar(i, j, L"┼");
				else if (j == y + 2 && i != x + 89)
					wirteChar(i, j, L"├");
				else if (j == y + 2 && i != x)
					wirteChar(i, j, L"┤");
				else if (j == y + sl && i != x && i != x + 89)
					wirteChar(i, j, L"┴");
				else if (j == y + sl && i != x + 89)
					wirteChar(i, j, L"└");
				else if (j == y + sl && i != x)
					wirteChar(i, j, L"┘");
				else wirteChar(i, j, L"│");
			}
			else if (j == y || j == y + 2 || j == y + sl)
				wirteChar(i, j, L"─");
		}
	writeString(x + 1, y + 1, L"STT", 11);
	writeString(x + 6, y + 1, L"Mã sinh viên", 11);
	writeString(x + 21, y + 1, L"Họ", 11);
	writeString(x + 43, y + 1, L"Tên", 11);
	writeString(x + 61, y + 1, L"Giới tính", 11);
	if (checkEx == 1) {
		writeString(x + 77, y + 1, L"Password", 11);
	}
	else {
		writeString(x + 77, y + 1, L"Điểm", 11);
	}
}

