#pragma once
#include <string>

using namespace std;
class Questions {
private:
	int id;
	int answer;
	wstring contentQuestions;
	wstring A;
	wstring B;
	wstring C;
	wstring D;
public:
	void setId(int id);
	int getId();
	void setContentQuestions(wstring contentQuestions);
	wstring getContentQuestions();
	void setA(wstring A);
	wstring getA();
	void setB(wstring B);
	wstring getB();
	void setC(wstring C);
	wstring getC();
	void setD(wstring D);
	wstring getD();
	void setAnswer(int answer);
	int getAnswer();

	friend wistream& operator >> (wistream& in, Questions& x);
	friend wostream& operator << (wostream& out, const Questions& x);

	bool operator==(Questions& x);
	bool operator!=(Questions& x);
};

