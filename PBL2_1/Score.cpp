#include "Score.h"

void Score::setScore(float score)
{
	this->score = score;
}

float Score::getScore()
{
	return score;
}

bool Score::operator==(Score& x)
{
	return (this->score == x.score);
}



wostream& operator<<(wostream& out, const Score& x)
{
	wcout << setw(10) << left << x.subjectCode << setw(5) << L" - " << setw(5) << right << x.score << setw(10);
	return out;
}
