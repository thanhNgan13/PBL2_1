#pragma once
#include <string>
#include "Subjects.h"
class Score : public Subjects
{
private:
	float score;
public:
	void setScore(float score);
	float getScore();
	friend wostream& operator << (wostream& in, const Score& x);
	bool operator==(Score& x);
};

