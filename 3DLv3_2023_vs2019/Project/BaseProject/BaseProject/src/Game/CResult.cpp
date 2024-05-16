#include "CResult.h"
#include "CText.h"
#include "CGameManager.h"
#include "CScore.h"
#include "CStageTime.h"
#include "CImage.h"
#include "CStageManager.h"
#include "CStageManager.h"

// ステージタイマーのインスタンス
CResult* CResult::spInstance = nullptr;

CResult* CResult::Instance()
{
	if (spInstance == nullptr)
	{
		spInstance = new CResult();
	}
	return spInstance;
}

CResult::CResult()
	: mRemainingTime(0)
	, mScore(0)
	, mCurrentDisplayedScore(0)
	, mTargetScore(0)
	, mScoreAnimationSpeed(20)
	, mpTime(nullptr)
	, mpScore(nullptr)
{
	// インスタンスの設定
	spInstance = this;
	mpResultText = new CText(nullptr, 40, CVector2(0, 0),
		CVector2(1250, 600), CColor(1.0f, 0.5f, 0.5f, 1.0f),
		ETaskPriority::eUI, 0);
	mpResultText->SetTextAlign(ETextAlignH::eCenter, ETextAlignV::eMiddle);
}

CResult::~CResult()
{
	spInstance = nullptr;
	mpResultText->Kill();
}

// 時間とスコアの合計を設定
void CResult::SetResult(int remainingTime, int score)
{
	mRemainingTime = remainingTime;
	mScore = score;
	// 目標スコアに現在の合計スコアを代入
	mTargetScore = GetTotalScore();
}

// 別クラスで時間とスコアを取り扱う為の処理
void CResult::SetTimeAndScore(CStageTime* pTime, CScore* pScore)
{
	mpTime = pTime;
	mpScore = pScore;
}

// 時間とスコアの合計を取得
int CResult::GetTotalScore() const
{
	return mRemainingTime * 10 + mScore;
}

void CResult::Update()
{
	int currentStage = CGameManager::StageNo();

	// スコアと時間を合算して描画
	SetResult(mpTime->Instance()->GetTime(), mpScore->Instance()->GetScore());

	if (CGameManager::GameState() == EGameState::eResult)
	{
		// リザルト画面の開始時にスコアアニメーションを開始
		if (!mpResultText->IsShow())
		{
			SetResult(mpTime->Instance()->GetTime(), mpScore->Instance()->GetScore());
			StartScoreAnimation();
		}
		mpResultText->SetShow(true);
		UpdateScoreAnimation();
	}
	else
	{
		mpResultText->SetShow(false);
	}
}

// 初期スコアの設定
void CResult::StartScoreAnimation()
{
	mCurrentDisplayedScore = 0;
}

// スコアを増加させるアニメーションの設定
void CResult::UpdateScoreAnimation()
{
	// 現在のスコアが目標スコアより少なかったら
	if (mCurrentDisplayedScore < mTargetScore)
	{
		// アニメーション速度を可算
		mCurrentDisplayedScore += mScoreAnimationSpeed;
		// 現在のスコアが目標スコアより大きくなったら
		if (mCurrentDisplayedScore > mTargetScore)
		{
			// 現在のスコアと目標スコアを同じにする
			mCurrentDisplayedScore = mTargetScore;
		}
	}
}

void CResult::Render()
{
	// アニメーションされたスコアを表示
	char buffer[64];
	sprintf_s(buffer, "RESULT:%04d", mCurrentDisplayedScore);
	mpResultText->SetText(buffer);

	//// 時間 × 10 ＋ スコア
	//int totalScore = mRemainingTime * 10 + mScore; // 残り時間に100をかけて、スコアに加える
	//char buffer[64];
	//sprintf_s(buffer, "RESULT:%04d", totalScore);
	//mpResultText->SetText(buffer);
}