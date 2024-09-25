#include "CSpikyBallUI.h"
#include "CPlayer.h"
#include "CTaskManager.h"
#include "CImage.h"
#include "CStageManager.h"
#include "Maths.h"
#include "Easing.h"

#define MENU_ALPHA 0.75
// SpikyBall�̓_�Ŏ���
#define SPIKYBALL_BLINK_TIME 0.75f
// SpikyBall�̓_�ŊԊu
#define SPIKYBALL_INTERVAL_TIME 1.0f
// SpikyBall�̃A�j���[�V��������
#define OPEN_ANIM_TIME 0.25f
// SpikyBall�̃A�j���[�V������̑҂�����
#define OPENED_WAIT_TIME 0.5f

// X�|�W�V����
#define POSITION_X 1110.0f
// Y�|�W�V����
#define POSITION_Y 300.0f

// �R���X�g���N�^
CSpikyBallUI::CSpikyBallUI()
	: CTask(ETaskPriority::eUI,0,ETaskPauseType::eGame)
	, mIsOpened(false)
	, mElapsedTime(0.0f)
{
	// �Ƃ��{�[���t���[���摜
	mpSpikyFrame = new CImage
	(
		"UI/AttackUI/ThornBallImages(frame).png",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpSpikyFrame->SetPos(POSITION_X, POSITION_Y);
	mpSpikyFrame->SetSize(140.0f, 140.0f);

	// CTRL�摜
	mpCTRL = new CImage
	(
		"UI/AttackUI/CTRLimage1.png",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpCTRL->SetPos(1115.0f, 220.0f);
	mpCTRL->SetSize(120.0f, 120.0f);

	// �Ƃ��{�[���摜
	mpSpikyBallUI = new CImage
	(
		"UI/AttackUI/ThornBallImages.png",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpSpikyBallUI->SetPos(POSITION_X, POSITION_Y);
	mpSpikyBallUI->SetSize(140.0f, 140.0f);
}

// �f�X�g���N�^
CSpikyBallUI::~CSpikyBallUI()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpSpikyBallUI);
	SAFE_DELETE(mpSpikyFrame);
	SAFE_DELETE(mpCTRL);
}

// ��Ԑ؂�ւ�
void CSpikyBallUI::ChangeState(EState state)
{
	if (state == mState) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// �J��
void CSpikyBallUI::Open()
{
	// ���ɊJ���Ă�����A�������Ȃ�
	if (mIsOpened) return;

	SetEnable(true);
	SetShow(true);
	// ���j���[���J�����t���O���グ��
	mIsOpened = true;
}

// ����
void CSpikyBallUI::Close()
{
	// ���łɕ��Ă�����A�������Ȃ�
	if (!mIsOpened) return;

	SetEnable(false);
	SetShow(false);
	// ���j���[���J�����t���O������
	mIsOpened = false;
}

// �J���Ă��邩�ǂ���
bool CSpikyBallUI::IsOpened() const
{
	return mIsOpened;
}

// �g�p�ҋ@���
void CSpikyBallUI::UpdateIdle()
{
	// �o�E���X���ʂ̃p�����[�^
	static float bounceTime = 0.0f;         // �o�E���X���ʂ̎���
	const float bounceSpeed = 3.0f;         // ���˕Ԃ�̑���
	const float bounceHeight = 9.0f;        // �ő�o�E���X�̍���

	// ��������
	bounceTime += Time::DeltaTime() * bounceSpeed;

	// �V����Y�ʒu���v�Z
	float bounceOffset = sinf(bounceTime) * bounceHeight;

	// �X�p�C�N�{�[��UI�̈ʒu���X�V
	mpSpikyBallUI->SetPos(POSITION_X, POSITION_Y + bounceOffset);
	mpSpikyBallUI->SetAlpha(1.0f);
}

// �g�p�ςݑҋ@���
void CSpikyBallUI::UpdateUsed()
{
	// �ҋ@��Ԃ��X�e�b�v�Ǘ�
	switch (mStateStep)
	{
		// �X�e�b�v0�F�uSPIKYBALL�v�̓_�ő҂�
	case 0:
		mpSpikyBallUI->SetAlpha(0.8f);
		if (mElapsedTime < SPIKYBALL_INTERVAL_TIME)
		{
			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			mElapsedTime = 0.0f;
			mStateStep = 1;
		}
		break;
		// �X�e�b�v1�F�uSPIKYBALL�v�̓_��
	case 1:
		if (mElapsedTime < SPIKYBALL_BLINK_TIME)
		{
			// �T�C���J�[�u�œ_��
			float per = sinf(M_PI * mElapsedTime / SPIKYBALL_BLINK_TIME);
			mpSpikyBallUI->SetAlpha(0.8f - per);
			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			mElapsedTime = 0.0f;
			mpSpikyBallUI->SetAlpha(0.8f);
			mStateStep = 0;
		}
		break;
	}
	// �X�p�C�N�{�[��UI�̈ʒu���X�V
	mpSpikyBallUI->SetPos(POSITION_X, POSITION_Y);
}

void CSpikyBallUI::Update()
{
	switch (mState)
	{
		// �g�p�ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// �g�p�ҋ@���
	case EState::eUsed:
		UpdateUsed();
		break;
	}

	CPlayer* player = CPlayer::Instance();
	float SpikTime = player->GetSpikyTime();
	if (SpikTime <= 0.0f)
	{
		ChangeState(EState::eIdle);
	}
	// �K�X�ύX����\������
	else if (SpikTime >= 5.0f)
	{
		ChangeState(EState::eUsed);
	}
}

void CSpikyBallUI::Render()
{
	// �Ƃ��{�[���t���[�������_�[
	mpSpikyFrame->Render();
	// �X�p�C�N�{�[�������_�[
	mpSpikyBallUI->Render();
	// CTRL�摜
	mpCTRL->Render();
}

void CSpikyBallUI::SetPlayer(CPlayer* player)
{
	mpPlayer = player;
}