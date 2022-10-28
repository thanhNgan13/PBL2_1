#pragma once
#include <string>
#include "LinkedList.h" 
#include "Students.h"

using namespace std;
class informationClass {
	wstring classCode;
	wstring className;
	LinkedList<Students> studentList;

public:
	void setClassCode(wstring classCode);
	void setClassName(wstring className);
	wstring getClassCode();
	wstring getClassName();
	void setStudentList(LinkedList<Students> studentList);
	LinkedList<Students> getStudentList();
	bool operator==(informationClass& x);
	bool operator!=(informationClass& x);

	friend wistream& operator >> (wistream& in, informationClass& x);
	friend wostream& operator << (wostream& out, const informationClass& x);
};