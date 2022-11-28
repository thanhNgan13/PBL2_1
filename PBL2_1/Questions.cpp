#include "Questions.h"
#include "Header.h"
#include <iostream>

using namespace std;
int Questions::len = 4;

void Questions::setId(int id) {
	this->id = id;
}

int Questions::getId() {
	return id;
}

void Questions::setContentQuestions(wstring contentQuestions) {
	this->contentQuestions = contentQuestions;
}

wstring Questions::getContentQuestions() {
	return contentQuestions;
}

void Questions::setAnswer(int answer) {
	this->answer = answer;
}

int Questions::getAnswer() {
	return answer;
}

void Questions::setAnswerList(wstring A, wstring B, wstring C, wstring D)
{
	answerlist[0] = A;
	answerlist[1] = B;
	answerlist[2] = C;
	answerlist[3] = D;
}

wstring Questions::getA()
{
	return this->answerlist[0];
}

wstring Questions::getB()
{
	return this->answerlist[1];
}

wstring Questions::getC()
{
	return this->answerlist[2];
}

wstring Questions::getD()
{
	return this->answerlist[3];
}

bool Questions::operator==(Questions& x) {
	if (id == x.id && contentQuestions == x.contentQuestions && answer == x.answer) {
		return true;
	}
	else
		return false;
}

bool Questions::operator!=(Questions& x) {
	if (id != x.id || contentQuestions != x.contentQuestions || answer != x.answer) {
		return true;
	}
	else
		return false;
}

wistream& operator>>(wistream& in, Questions& x) {
	wstring s;
	while (true)
	{
		textcolor(6);
		wcout << L"Nhập nội dung câu hỏi: ";
		getline(wcin, x.contentQuestions);
		if (x.contentQuestions.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else
			break;
	}
	while (true)
	{
		textcolor(6);
		wcout << L"NNhập đáp án A: ";
		getline(wcin, s);
		if (s.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else {
			x.answerlist[0] = s;
			s.clear();
			break;
		}
	}
	while (true)
	{

		textcolor(6);
		wcout << L"NNhập đáp án B: ";
		getline(wcin, s);
		if (s.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else {
			x.answerlist[1] = s;
			s.clear();
			break;
		}
	}
	while (true)
	{
		textcolor(6);
		wcout << L"NNhập đáp án C: ";
		getline(wcin, s);
		if (s.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else {
			x.answerlist[2] = s;
			s.clear();
			break;
		}
	}
	while (true)
	{
		textcolor(6);
		wcout << L"NNhập đáp án D: ";
		getline(wcin, s);
		if (s.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else {
			x.answerlist[3] = s;
			s.clear();
			break;
		}
	}

	while (true) {
		textcolor(6);
		wcout << L"Nhập đáp án chính xác của câu hỏi(1: A; 2: B; 3: C, 4: D): ";
		if ((wcin >> x.answer))
		{
			if (x.answer < 0 || x.answer > 4) {
				textcolor(4);
				wcout << L"Đáp án chứa ký tự không hợp lệ!!!" << endl;
				wcin.clear();
				wcin.ignore(1000, '\n');
			}
			else
				break;
		}
		else {
			textcolor(4);
			wcout << L"Đáp án chứa ký tự không hợp lệ!!!" << endl;
			wcin.clear();
			wcin.ignore(1000, '\n');
		}
	}
	x.id = hashCode(x.contentQuestions);
	return in;
}

wostream& operator<<(wostream& out, const Questions& x) {
	wstring value;
	wstring* temp = new wstring[Questions::len];
	for (int i = 0; i < Questions::len; i++) {
		temp[i] = x.answerlist[i];
	}
	srand((unsigned int) time(NULL));
	wcout << L"Id: " << x.id << endl;
	wcout << L"Nội dung câu hỏi: ";
	wcout << x.contentQuestions << endl;
	wcout << L"Các đáp án: " << endl;
	wchar_t ch = L'A';
	do {
		int index = rand() % Questions::len;
		wcout << ch << L". " << temp[index] << endl;
		deleteAnElementInTheArray(temp, Questions::len, index);
		ch++;

	} while (Questions::len);
	Questions::len = 4;
	delete[] temp;
	return out;
}
