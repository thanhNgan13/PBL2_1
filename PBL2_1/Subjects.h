#pragma once
#include "LinkedList.h"
#include "Questions.h"
#include "Header.h"
#include <string>

class Subjects
{
private:
	wstring subjectName;
protected:
	wstring subjectCode;
	LinkedList<Questions> questionList;
public:
	Subjects();
	Subjects(wstring subjectName, wstring subjectCode);
	Subjects(const Subjects& x);
	bool operator==(Subjects& x);
	bool operator!=(Subjects& x);
	void setSubjectCode(wstring subjectCode);
	void setSubjectName(wstring subjectName);
	wstring getSubjectCode();
	wstring getSubjectName();
	void setQuestionList(LinkedList<Questions> questionList);
	LinkedList<Questions> getQuestionList();

	friend wistream& operator >> (wistream& in, Subjects& x);
	friend wostream& operator << (wostream& out, const Subjects& x);


};

