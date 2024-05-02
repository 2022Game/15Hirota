#include "CResult.h"
#include "CText.h"
#include "CGameManager.h"
#include "CScore.h"
#include "CStageTime.h"
#include "CImage.h"

// �X�e�[�W�^�C�}�[�̃C���X�^���X
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
	// �C���X�^���X�̐ݒ�
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

// ���ԂƃX�R�A�̍��v��ݒ�
void CResult::SetResult(int remainingTime, int score)
{
	mRemainingTime = remainingTime;
	mScore = score;
}

// �ʃN���X�Ŏ��ԂƃX�R�A����舵���ׂ̏���
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

	// �X�R�A�Ǝ��Ԃ����Z���ĕ`��
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
	// ���� �~ 10 �{ �X�R�A
	int totalScore = mRemainingTime * 10 + mScore; // �c�莞�Ԃ�100�������āA�X�R�A�ɉ�����
	char buffer[64];
	sprintf_s(buffer, "RESULT:%04d", totalScore);
	mpResultText->SetText(buffer);
}