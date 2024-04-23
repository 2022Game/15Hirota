#ifndef CSTAGETIME_H
#define CSTAGETIME_H

#include "CTask.h"
class CText;
class CImage;
class CStageTime : public CTask
{
public:
	CStageTime();
	~CStageTime();
	void Time(int time);
	void Update() override;
	void Render() override;
private:
	int mTime;
	CText* mpTimerText;
	CImage* mpTimer;

	bool mIsStage1;
	bool mIsStage2;
	bool mIsStage3;
};
#endif