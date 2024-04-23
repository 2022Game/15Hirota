#include "CScore.h"
#include "CText.h"
#include "CGameManager.h"

// CScoreƒNƒ‰ƒX‚ÌŽÀ‘•
CScore::CScore()
	: mScore(0)
{
	mpScoreText = new CText(nullptr, 30, CVector2(1100, 100),
		CVector2(1250, 100), CColor(0.0f, 1.0f, 0.5f,1.0f),
		ETaskPriority::eUI, 0);
}

CScore::~CScore()
{
	mpScoreText->Kill();
}

void CScore::Score(int score)
{
	mScore = score;
}

void CScore::Update()
{
	int currentStage = CGameManager::StageNo();
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