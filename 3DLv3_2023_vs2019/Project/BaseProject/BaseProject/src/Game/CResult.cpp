#include "CResult.h"
#include "CText.h"
#include "CGameManager.h"
#include "CScore.h"
#include "CStageTime.h"
#include "CImage.h"

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
	, mpTime(nullptr)
	, mpScore(nullptr)
{
	// インスタンスの設定
	spInstance = this;
	mpResultText = new CText(nullptr, 40, CVector2(0, 300),
		CVector2(1250, 600), CColor(1.0f, 0.5f, 0.5f, 1.0f),
		ETaskPriority::eUI, 0);
	mpResultText->SetTextAlign(ETextAlignH::eCenter,ETextAlignV::eMiddle);
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
}

// 別クラスで時間とスコアを取り扱う為の処理
void CResult::SetTimeAndScore(CStageTime* pTime, CScore* pScore)
{
	mpTime = pTime;
	mpScore = pScore;
}

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
		mpResultText->SetShow(true);
	}
	else
	{
		mpResultText->SetShow(false);
	}
}

void CResult::Render()
{
	// 時間 × 10 ＋ スコア
	int totalScore = mRemainingTime * 10 + mScore; // 残り時間に100をかけて、スコアに加える
	char buffer[64];
	sprintf_s(buffer, "RESULT:%04d", totalScore);
	mpResultText->SetText(buffer);
}