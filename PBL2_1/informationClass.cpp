#include "informationClass.h"
#include <string>
#include <iostream>
#include <iomanip>

void informationClass::setClassCode(wstring classCode) {
	this->classCode = classCode;
}

void informationClass::setClassName(wstring className) {
	this->className = className;
}

wstring informationClass::getClassCode() {
	return classCode;
}

wstring informationClass::getClassName() {
	return className;
}

void informationClass::setStudentList(LinkedList<Students> studentList)
{
	this->studentList = studentList;
}

LinkedList<Students> informationClass::getStudentList()
{
	return studentList;
}

bool informationClass::operator==(informationClass& x) {
	if (classCode == x.classCode || className == x.className) {
		return true;
	}
	else
		return false;
}

bool informationClass::operator!=(informationClass& x) {
	if (classCode != x.classCode || className != x.className) {
		return true;
	}
	else
		return false;
}

wistream& operator>>(wistream& in, informationClass& x) {
	writeString(60, 10, L"Nhập tên lớp học: ", 6);
	getline(in, x.className);
	writeString(60, 11, L"Nhập mã lớp học: ", 6);
	getline(in, x.classCode);
	//x.classCode = inputString(9);
	return in;
}

wostream& operator<<(wostream& out, const informationClass& x) {
	wcout << format(L"{:>25}", x.className) << format(L"{:^10}", L'-') << format(L"{:<1}", x.classCode);
	//wcout << setw(10) << left << x.className << setw(5) << L" - " << setw(5) << right << x.classCode << setw(10);
	return out;
}
