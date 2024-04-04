#ifndef CSCORE_H
#define CSCORE_H

#include "CTask.h"
class CText;
class CScore : public CTask
{
public:
	CScore();
	~CScore();
	void Score(int score);
	void Update() override;
	void Render() override;
private:
	int mScore;
	CText* mpScoreText;
};
#endif