#pragma once
#include "LinkedList.h"
#include "Score.h"
#include<string>
using namespace std;
class Students {
private:
	wstring studentCode;
	wstring passwork;
	wstring lastName;
	wstring firstName;
	wstring sex;
	LinkedList<Score> scoreList;
public:
	void setStudentCode(wstring studentCode);
	void setPasswork(wstring passwork);
	void setLastName(wstring lastName);
	void setFirstName(wstring firstName);
	void setSex(wstring sex);
	void setScoreList(LinkedList<Score> scoreList);

	wstring getStudentCode();
	wstring getPasswork();
	wstring getLastName();
	wstring getFirstName();
	wstring getSex();
	LinkedList<Score> getScoreList();

	friend wistream& operator >> (wistream& in, Students& x);
	friend wostream& operator << (wostream& out, const Students& x);
	
	bool operator==(Students& x);
	bool operator!=(Students& x);
	
};
