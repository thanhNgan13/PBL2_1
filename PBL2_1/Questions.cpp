#include "Questions.h"
#include "Header.h"
#include <iostream>

using namespace std;

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

void Questions::setA(wstring A) {
	this->A = A;
}

wstring Questions::getA() {
	return A;
}

void Questions::setB(wstring B) {
	this->B = B;
}

wstring Questions::getB() {
	return B;
}

void Questions::setC(wstring C) {
	this->C = C;
}

wstring Questions::getC() {
	return C;
}

void Questions::setD(wstring D) {
	this->D = D;
}

wstring Questions::getD() {
	return D;
}

void Questions::setAnswer(int answer) {
	this->answer = answer;
}

int Questions::getAnswer() {
	return answer;
}

bool Questions::operator==(Questions& x) {
	if (id == x.id && contentQuestions == x.contentQuestions && A == x.A && B == x.B && C == x.C && D == x.D && answer == x.answer) {
		return true;
	}
	else
		return false;
}

bool Questions::operator!=(Questions& x) {
	if (id != x.id || contentQuestions != x.contentQuestions || A != x.A || B != x.B || C != x.C || D != x.D || answer != x.answer) {
		return true;
	}
	else
		return false;
}

wistream& operator>>(wistream& in, Questions& x) {
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
		getline(wcin, x.A);
		if (x.A.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else
			break;
	}
	while (true)
	{

		textcolor(6);
		wcout << L"NNhập đáp án B: ";
		getline(wcin, x.B);
		if (x.B.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else
			break;
	}
	while (true)
	{
		textcolor(6);
		wcout << L"NNhập đáp án C: ";
		getline(wcin, x.C);
		if (x.C.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else
			break;
	}
	while (true)
	{
		textcolor(6);
		wcout << L"NNhập đáp án D: ";
		getline(wcin, x.D);
		if (x.D.empty()) {
			textcolor(4);
			wcout << L"Không được bỏ trống!!!" << endl;
		}
		else
			break;
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
	//if (x.answer.empty()) {
	//	textcolor(4);
	//	wcout << L"Không được bỏ trống!!!" << endl;
	//	goto Ans;
	//}
	//if (x.answer != L"A" || x.answer != L"B" || x.answer != L"C" || x.answer != L"D" || x.answer != L"a" || x.answer != L"b" || x.answer != L"c" || x.answer != L"d") {
	//	textcolor(4);
	//	wcout << L"Nhập không đúng cú pháp!!!" << endl;
	//	goto Ans;
	//}
	x.id = hashCode(x.contentQuestions);
	return in;
}

wostream& operator<<(wostream& out, const Questions& x) {
	//gotoxy(50, 1);
	wcout << L"Id: " << x.id << endl;
	wcout << L"Nội dung câu hỏi: ";
	//gotoxy(50, 3);
	wcout << x.contentQuestions << endl;
	//gotoxy(50, 4);
	wcout << L"Các đáp án: " << endl;
	//gotoxy(50, 5);
	wcout << L"A. " << x.A << endl;
	//gotoxy(50, 6);
	wcout << L"B. " << x.B << endl;
	//gotoxy(50, 7);
	wcout << L"C. " << x.C << endl;
	//gotoxy(50, 8);
	wcout << L"D. " << x.D << endl;;
	return out;
}
