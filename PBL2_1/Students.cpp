#include "Students.h"
#include <iostream>
#include <string>
#include <iomanip>
void Students::setStudentCode(wstring studentCode) {
	this->studentCode = studentCode;
}

void Students::setPasswork(wstring passwork) {
	this->passwork = passwork;
}

void Students::setLastName(wstring lastName) {
	this->lastName = lastName;
}

void Students::setFirstName(wstring firstName) {
	this->firstName = firstName;
}

void Students::setSex(wstring sex) {
	this->sex = sex;
}

void Students::setScoreList(LinkedList<Score> scoreList)
{
	this->scoreList = scoreList;
}

wstring Students::getStudentCode() {
	return studentCode;
}

wstring Students::getPasswork() {
	return passwork;
}

wstring Students::getLastName() {
	return lastName;
}

wstring Students::getFirstName() {
	return firstName;
}

wstring Students::getSex() {
	return sex;
}

LinkedList<Score> Students::getScoreList()
{
	return scoreList;
}

bool Students::operator==(Students& x)
{
	if (lastName == x.lastName && firstName == x.firstName && studentCode == x.studentCode && passwork == x.passwork && sex == x.sex) {
		return true;
	}
	else
		return false;
}

bool Students::operator!=(Students& x)
{
	if (lastName != x.lastName && firstName != x.firstName && studentCode != x.studentCode && passwork != x.passwork && sex != x.sex) {
		return true;
	}
	else
		return false;
}

wistream& operator>>(wistream& in, Students& x) {
	wcout << L"Nhập họ : ";
	getline(wcin, x.lastName);
	wcout << L"Nhập tên: ";
	getline(wcin, x.firstName);
	wcout << L"Nhập giới tính: ";
	getline(wcin, x.sex);
	wcout << L"Nhập mã sinh viên: ";
	getline(wcin, x.studentCode);
	wcout << L"Nhập password: ";
	getline(wcin, x.passwork);
	return in;
}

wostream& operator<<(wostream& out, const Students& x) {
	wcout << L"MSV: " << x.studentCode << endl;
	wcout << L"Họ:  " << x.lastName<< endl;
	wcout << L"Tên:  " << x.firstName << endl;
	wcout << L"Giới tính: " << x.sex << endl;
	wcout << L"Mật khẩu: " << x.passwork << endl;
	return out;
}
