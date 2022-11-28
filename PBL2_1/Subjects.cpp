#include "Subjects.h"
#include "Header.h"
#include <string>
#include <iostream>
#include <iomanip>

Subjects::Subjects()
{
	subjectCode = L"NULL";
	subjectName = L"NULL";
}

Subjects::Subjects(wstring subjectCode, wstring subjectName)
{
	this->subjectCode = subjectCode;
	this->subjectName = subjectName;
}

Subjects::Subjects(const Subjects& x)
{
	this->subjectCode = x.subjectCode;
	this->subjectName = x.subjectName;
}

bool Subjects::operator==(Subjects& x)
{
	if (subjectCode == x.subjectCode || subjectName == x.subjectName) {
		return true;
	}
	else
		return false;
}

bool Subjects::operator!=(Subjects& x)
{
	if (subjectCode != x.subjectCode || subjectName != x.subjectName) {
		return true;
	}
	else
		return false;
}

void Subjects::setSubjectCode(wstring subjectCode)
{
	this->subjectCode = subjectCode;
}

void Subjects::setSubjectName(wstring subjectName)
{
	this->subjectName = subjectName;
}

wstring Subjects::getSubjectCode()
{
	return subjectCode;
}

wstring Subjects::getSubjectName()
{
	return subjectName;
}

void Subjects::setQuestionList(LinkedList<Questions> questionList)
{
	this->questionList = questionList;
}

LinkedList<Questions> Subjects::getQuestionList()
{
	return questionList;
}

wistream& operator>>(wistream& in, Subjects& x)
{
	writeString(60, 10, L"Nhâp tên môn học: ", 6);
	getline(in, x.subjectName);
	writeString(60, 11, L"Nhập mã môn học: ", 6);
	getline(in, x.subjectCode);
	//x.subjectCode = inputString(9);
	return in;
}

wostream& operator<<(wostream& out, const Subjects& x)
{
	wcout << format(L"{:>25}", x.subjectName) << format(L"{:^10}", L'-') << format(L"{:<25}", x.subjectCode);
	//wcout << setw(10) << left << x.subjectName << setw(5) << L" - " << setw(5) << right << x.subjectCode << setw(10);
	return out;
}
