#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#pragma warning(disable : 4996)

using namespace std;
static int checkAd = 1;
static int checkUS = 1;
static int checkEx = 1;
static int checkSb = 1;
static int checkCl = 1;

inline wstring subStr(wstring s) {
	int index1 = 0;
	int index2 = 0;
	for (int i = 0; i < s.length(); i++) {
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

inline int hashCode(wstring s) {
	int sum = 0;
	int i = 0;
	while (s[i] != NULL)
	{
		sum += ((i + 1) * (s[i] * s[i]));
		i++;
	}
	return (int)fabs(sum % 2000);
}
inline wstring Upper(wstring s) {
	if (s[0] != L' ') {
		s[0] = towupper(s[0]);
		for (int i = 1; i < s.length(); i++) {
			if (s[i] == L' ' && s[i + 1] != L' ') //viet ki tu sau dau cach thanh chu hoa
				s[i + 1] = towupper(s[i + 1]);
		}
	}
	return s;
}
inline wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
inline void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
inline void gotoxy(short x, short y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };
	SetConsoleCursorPosition(h, c);
}
inline void wirteChar(int x, int y, const wchar_t* z)  {
	gotoxy(x, y);
	wcout << z;
}
inline void writeString(int x, int y, const wchar_t s[], int mau)
{
	gotoxy(x, y);
	textcolor(mau);
	wcout << s;
}
inline int catchEvents()
{
	int c = getch();
	if (c == 8) //phim Backspace
		return 1;
	else if (c == 9) //phim Tab
		return 2;
	else if (c == 13) //phim Enter
		return 3;
	else if (c == 27) //phim Esc
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

inline void bangmenu(int x, int y, int m, int n, int mau)
{
	int i, j;
	textcolor(mau);
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
inline void tbmenu(int x, int y)
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

inline void setFontSize(int FontSize)
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = FontSize; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

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
inline void menuDisplay(int x, int y, int sl)
{
	int i, j;
	textcolor(2);
	for (i = x; i <= x + 89; i++)
		for (j = y; j <= y + sl; j++)
		{
			if (i == x || i == x + 4 || i == x + 20)
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
	writeString(x + 6, y + 1, L"Tên", 11);
	writeString(x + 21, y + 1, L"Mã", 11);

}