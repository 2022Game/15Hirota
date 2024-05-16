#include "CResult.h"
#include "CText.h"
#include "CGameManager.h"
#include "CScore.h"
#include "CStageTime.h"
#include "CImage.h"
#include "CStageManager.h"
#include "CStageManager.h"

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
	, mCurrentDisplayedScore(0)
	, mTargetScore(0)
	, mScoreAnimationSpeed(20)
	, mpTime(nullptr)
	, mpScore(nullptr)
{
	// �C���X�^���X�̐ݒ�
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

// ���ԂƃX�R�A�̍��v��ݒ�
void CResult::SetResult(int remainingTime, int score)
{
	mRemainingTime = remainingTime;
	mScore = score;
	// �ڕW�X�R�A�Ɍ��݂̍��v�X�R�A����
	mTargetScore = GetTotalScore();
}

// �ʃN���X�Ŏ��ԂƃX�R�A����舵���ׂ̏���
void CResult::SetTimeAndScore(CStageTime* pTime, CScore* pScore)
{
	mpTime = pTime;
	mpScore = pScore;
}

// ���ԂƃX�R�A�̍��v���擾
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
		// ���U���g��ʂ̊J�n���ɃX�R�A�A�j���[�V�������J�n
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

// �����X�R�A�̐ݒ�
void CResult::StartScoreAnimation()
{
	mCurrentDisplayedScore = 0;
}

// �X�R�A�𑝉�������A�j���[�V�����̐ݒ�
void CResult::UpdateScoreAnimation()
{
	// ���݂̃X�R�A���ڕW�X�R�A��菭�Ȃ�������
	if (mCurrentDisplayedScore < mTargetScore)
	{
		// �A�j���[�V�������x���Z
		mCurrentDisplayedScore += mScoreAnimationSpeed;
		// ���݂̃X�R�A���ڕW�X�R�A���傫���Ȃ�����
		if (mCurrentDisplayedScore > mTargetScore)
		{
			// ���݂̃X�R�A�ƖڕW�X�R�A�𓯂��ɂ���
			mCurrentDisplayedScore = mTargetScore;
		}
	}
}

void CResult::Render()
{
	// �A�j���[�V�������ꂽ�X�R�A��\��
	char buffer[64];
	sprintf_s(buffer, "RESULT:%04d", mCurrentDisplayedScore);
	mpResultText->SetText(buffer);

	//// ���� �~ 10 �{ �X�R�A
	//int totalScore = mRemainingTime * 10 + mScore; // �c�莞�Ԃ�100�������āA�X�R�A�ɉ�����
	//char buffer[64];
	//sprintf_s(buffer, "RESULT:%04d", totalScore);
	//mpResultText->SetText(buffer);
}