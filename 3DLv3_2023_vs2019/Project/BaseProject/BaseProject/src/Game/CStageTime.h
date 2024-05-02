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

	//インスタンスのポインタの取得
	static CStageTime* Instance();

	void Time(int time);
	void Update() override;
	void Render() override;

	int GetTime() const { return mTime; }
private:
	static CStageTime* spInstance;
	int mTime;
	bool mIsStage1;
	bool mIsStage2;
	bool mIsStage3;
	CText* mpTimerText;
	CImage* mpTimer;
};
#endif