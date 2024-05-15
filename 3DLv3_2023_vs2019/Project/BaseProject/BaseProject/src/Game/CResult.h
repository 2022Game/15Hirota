#ifndef CRESULT_H
#define CRESULT_H

#include "CTask.h"
class CText;
class CStageTime;
class CScore;
class CImage;

class CResult : public CTask
{
public:
	CResult();
	~CResult();

	//インスタンスのポインタの取得
	static CResult* Instance();

	void SetResult(int remainingTime, int score);
	void SetTimeAndScore(CStageTime* pTime, CScore* pScore);
	int GetTotalScore() const;

	void StartScoreAnimation();
	void UpdateScoreAnimation();

	void Update() override;
	void Render() override;

private:
	static CResult* spInstance;
	int mRemainingTime;
	int mScore;
	int mCurrentDisplayedScore;
	int mTargetScore;
	int mScoreAnimationSpeed;
	CText* mpResultText;
	CStageTime* mpTime;
	CScore* mpScore;
};
#endif