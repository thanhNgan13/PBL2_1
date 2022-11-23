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

bool Students::operator>(Students& x)
{
	if (wcscmp(firstName.c_str(), x.firstName.c_str()) >= 0)
		return true;
	return false;
}

bool Students::operator<(Students& x)
{
	if (wcscmp(firstName.c_str(), x.firstName.c_str()) <= 0)
		return true;
	return false;
}

Students& Students::operator=(Students const& st)
{
	if (&st != this) {
		studentCode = st.studentCode;
		passwork = st.passwork;
		lastName = st.lastName;
		firstName = st.firstName;
		sex = st.sex;
		scoreList = st.scoreList;
	}
	return *this;
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
	wcout << L"Danh sách các môn đã thi: " << endl;
	wcout << endl;
	Node<Score>* current = x.scoreList.head;
	if (current == nullptr) {
		wcout << L"Chưa thi môn nào!" << endl;
	}
	else {
		while (current != nullptr)
		{
			wcout << L"Mã Môn: " << current->data.getSubjectCode() << endl;
			wcout << L"Điểm: " << current->data.getScore() << endl;
			wcout << endl;
			current = current->next;
		}
	}
	return out;
}
