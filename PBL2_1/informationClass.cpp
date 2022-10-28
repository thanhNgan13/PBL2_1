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
	wcout << L"Nhập tên lớp học: ";
	getline(in, x.className);
	wcout << L"Nhập mã lớp học: ";
	getline(in, x.classCode);
	return in;
}

wostream& operator<<(wostream& out, const informationClass& x) {
	wcout << setw(10) << left << x.className << setw(5) << L" - " << setw(5) << right << x.classCode;
	return out;
}
