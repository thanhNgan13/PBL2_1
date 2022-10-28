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
};

