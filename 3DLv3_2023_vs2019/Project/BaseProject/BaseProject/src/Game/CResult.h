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

	// 時間とスコアを設定
	void SetResult(int remainingTime, int score);
	// 時間とスコアを取得
	void SetTimeAndScore(CStageTime* pTime, CScore* pScore);
	// 時間とスコアの合計を取得
	int GetTotalScore() const;

	// 初期スコアの設定
	void StartScoreAnimation();
	// スコアを増加させるアニメーションの設定
	void UpdateScoreAnimation();

	void Update() override;
	void Render() override;

private:
	// インスタンス
	static CResult* spInstance;
	// 時間
	int mRemainingTime;
	// スコア
	int mScore;
	// 現在のスコア
	int mCurrentDisplayedScore;
	// 目標スコア
	int mTargetScore;
	// スコアを増加させるアニメーションの速度
	int mScoreAnimationSpeed;

	CText* mpResultText;
	CStageTime* mpTime;
	CScore* mpScore;
};
#endif