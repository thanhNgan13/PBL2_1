#pragma once
#include <string>
using namespace std;
class Questions {
private:
	int id;
	int answer;
	wstring contentQuestions;
	wstring answerlist[4];
	static int len;
public:
	void setId(int id);
	int getId();
	void setContentQuestions(wstring contentQuestions);
	wstring getContentQuestions();
	void setAnswer(int answer);
	int getAnswer();
	void setAnswerList(wstring A, wstring B, wstring C, wstring D);
	wstring getA();
	wstring getB();
	wstring getC();
	wstring getD();

public:
	friend wistream& operator >> (wistream& in, Questions& x);
	friend wostream& operator << (wostream& out, const Questions& x);

	bool operator==(Questions& x);
	bool operator!=(Questions& x);
};

