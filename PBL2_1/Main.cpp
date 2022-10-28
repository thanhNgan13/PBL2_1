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

using namespace std;
std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
 
void editSubject();

int wmain(int argc, wchar_t* argv[]) {
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stdin), _O_WTEXT);


	LinkedList<int> list;
	list.Insert(1);
	list.Insert(2);
	list.Display();

	return 0;

}

void editSubject()


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
				//enterSubject();
				system("pause");
				system("cls");
				editSubject();
			}
			else if (kt == 2)
			{
				system("cls");
				//correctionSubject();
				system("pause");
				system("cls");
				editSubject();
			}
			else if (kt == 3)
			{
				system("cls");
				//deleteSubject();
				system("pause");
				system("cls");
				editSubject();
			}
			else if (kt == 4)
			{
				system("cls");
				//list.Display();
				system("pause");
				system("cls");
				editSubject();
			}
			else if (kt == 5)
			{
				system("cls");
				exit(1);
			}
		}
	}
}
