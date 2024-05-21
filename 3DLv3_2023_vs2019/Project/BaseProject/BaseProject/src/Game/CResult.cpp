#include "CResult.h"
#include "CText.h"
#include "CGameManager.h"
#include "CScore.h"
#include "CStageTime.h"
#include "CImage.h"
#include "CStageManager.h"
#include "CStageManager.h"
#include "CFont.h"

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

// �R���X�g���N�^
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

	// �^�C�g�����S�̃t�H���g�f�[�^�𐶐�
	mpFont = new CFont("res\\Font\\toroman.ttf");
	mpFont->SetFontSize(60);
	mpFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpFont->SetLineLength(WINDOW_WIDTH);

	// ���U���g�̃e�L�X�g�̐ݒ�
	mpResultText = new CText(mpFont, 60, CVector2(100.0f, 0.0f),
		CVector2(1250, 600), CColor(1.0f, 1.0f, 0.0f, 1.0f),
		ETaskPriority::eUI, 0, ETaskPauseType::eDefault, false, true);
	mpResultText->SetTextAlign(ETextAlignH::eLeft, ETextAlignV::eMiddle);
}

// �f�X�g���N�^
CResult::~CResult()
{
	spInstance = nullptr;
	SAFE_DELETE(mpResultText);
	SAFE_DELETE(mpFont);
}

// ���ԂƃX�R�A�̍��v��ݒ�
void CResult::SetResult(int remainingTime, int score)
{
	mRemainingTime = remainingTime;
	mScore = score;
	// �ڕW�X�R�A�Ɍ��݂̍��v�X�R�A����
	mTargetScore = GetTotalScore();
}

// ���ԂƃX�R�A�̍��v���擾
int CResult::GetTotalScore() const
{
	// ���� �~ 10 + �X�R�A
	return mRemainingTime * 10 + mScore;
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

// �X�V����
void CResult::Update()
{
	// ���݂̃X�e�[�W�ԍ�
	int currentStage = CGameManager::StageNo();

	// �X�R�A�Ǝ��Ԃ����Z���ĕ`��
	SetResult(mpTime->Instance()->GetTime(), mpScore->Instance()->GetScore());

	// �Q�[���X�e�[�^�X�����U���g��������
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

// �`�揈��
void CResult::Render()
{
	// �A�j���[�V�������ꂽ�X�R�A��\��
	char buffer[64];
	sprintf_s(buffer, "RESULT �~  %04d", mCurrentDisplayedScore);
	mpResultText->SetText(buffer);

	//// ���� �~ 10 �{ �X�R�A
	//int totalScore = mRemainingTime * 10 + mScore; // �c�莞�Ԃ�100�������āA�X�R�A�ɉ�����
	//char buffer[64];
	//sprintf_s(buffer, "RESULT:%04d", totalScore);
	//mpResultText->SetText(buffer);
}