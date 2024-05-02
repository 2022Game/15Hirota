#include "CScore.h"
#include "CText.h"
#include "CGameManager.h"
#include "CTaskManager.h"
#include "CVanguard.h"
#include "CBlueMedal.h"

// スコアのインスタンス
CScore* CScore::spInstance = nullptr;

CScore* CScore::Instance()
{
	return spInstance;
}

// CScoreクラスの実装
CScore::CScore()
	: mScore(0)
	, mIsStage1(false)
	, mIsStage2(false)
	, mIsStage3(false)
{
	// インスタンスの設定
	spInstance = this;

	mpScoreText = new CText(nullptr, 30, CVector2(1100, 100),
		CVector2(1250, 100), CColor(0.0f, 1.0f, 0.5f,1.0f),
		ETaskPriority::eUI, 0);
}

CScore::~CScore()
{
	spInstance = nullptr;
	mpScoreText->Kill();
}

void CScore::Score(int score)
{
	mScore = score;
}

void CScore::Update()
{
	int currentStage = CGameManager::StageNo();
	bool pose = CTaskManager::Instance()->IsPaused();
	if (currentStage == 0)
	{
		mIsStage1 = false;
		mIsStage2 = false;
		mIsStage3 = false;
		mScore = 0;
	}
	else
	{
		if (!pose)
		{
			// ステージ1
			if (currentStage == 1)
			{
				if (!mIsStage1)
				{
					mIsStage1 = true;
					mIsStage2 = false;
					mIsStage3 = false;
				}
			}
			// ステージ2
			if (currentStage == 2)
			{
				if (!mIsStage2)
				{
					mIsStage1 = false;
					mIsStage2 = true;
					mIsStage3 = false;
				}
			}
			// ステージ3
			if (currentStage == 3)
			{
				if (!mIsStage3)
				{
					mIsStage1 = false;
					mIsStage2 = false;
					mIsStage3 = true;
				}
			}
		}
		Score(CVanguard::GetScore() + CBlueMedal::GetScore());
	}

	// ステージ1,2,3のみ表示
	if (currentStage == 1 || currentStage == 2 || currentStage == 3)
	{
		mpScoreText->SetShow(true);
	}
	else
	{
		mpScoreText->SetShow(false);
	}
}

void CScore::Render()
{
	char buffer[16];
	sprintf_s(buffer, "SCORE:%04d", mScore);
	mpScoreText->SetText(buffer);
}