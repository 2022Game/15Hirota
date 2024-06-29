#include "CCutInDeathJump.h"
#include "Maths.h"
#include "CResultAnnouncement.h"

// ���S�W�����v�J�����̃C���X�^���X
CCutInDeathJump* CCutInDeathJump::spInstance = nullptr;

CCutInDeathJump* CCutInDeathJump::Instance()
{
	if (spInstance == nullptr)
	{
		spInstance = new CCutInDeathJump();
	}
	return spInstance;
}

// �R���X�g���N�^
CCutInDeathJump::CCutInDeathJump()
	: mCutInStep(0)
	, mElapsedTime(0.0f)
	, mCenterPos(CVector::zero)
	, mStartAngleY(0.0f)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;
}

// �f�X�g���N�^
CCutInDeathJump::~CCutInDeathJump()
{
	spInstance = nullptr;
}

// �J�b�g�C���J�n
bool CCutInDeathJump::Start()
{
	// �x�[�X�̃J�b�g�C���J�n����
	if (!CCutInCamera::Start()) return false;

	// �J�b�g�C�����Ɏg�p����ϐ��Ȃǂ̏�����
	mCutInStep = 0;
	mElapsedTime = 0.0f;

	return true;
}

// �J�b�g�C���I��
bool CCutInDeathJump::End()
{
	// �x�[�X�̃J�b�g�C���I������
	if (!CCutInCamera::End()) return false;

	return true;
}

// �J�b�g�C���ɕK�v�ȏ���ݒ�
void CCutInDeathJump::Setup(CObjectBase* obj)
{
	// �ݒ肳�ꂽ�I�u�W�F�N�g�̈ʒu�𒆐S�n�_�Ƃ���
	mCenterPos = obj->Position();
	// �ݒ肳�ꂽ�I�u�W�F�N�g�̌��݂�Y���̊p�x���擾
	mStartAngleY = obj->EulerAngles().Y();

	mObject = obj;
}

#define CUTIN_TIME 6.2f
#define START_ANGLE 100.0f
#define END_ANGLE 100.0f
#define START_Y 0.0f
#define END_Y -10.0f
#define START_DIST 70.0f
#define END_DIST 70.0f
#define WAIT_TIME 1.0f

// �X�e�b�v0 �J�����̉�]
void CCutInDeathJump::CutInStep0()
{
	// �J�b�g�C���̎��Ԃ��o�߂���ɂ�ăJ�������ړ�������
	if (mElapsedTime < CUTIN_TIME)
	{
		float per = mElapsedTime / CUTIN_TIME;

		CVector offsetPos = CVector::zero;
		float offsetY = Math::Lerp(START_Y, END_Y, per);
		offsetPos.Y(offsetY);

		float startAng = mStartAngleY + START_ANGLE;
		float endAng = mStartAngleY + END_ANGLE;
		float angle = Math::Lerp(startAng, endAng, per);
		float radAng = Math::DegreeToRadian(angle);

		float dist = Math::Lerp(START_DIST, END_DIST, per);

		mAt = mCenterPos + offsetPos;
		mEye = mAt + CVector(cosf(radAng), 0.0f, sinf(radAng)) * dist;

		mElapsedTime += Time::DeltaTime();
	}

	CResultAnnouncement* result = CResultAnnouncement::Instance();
	bool resultEnd = result->IsResultOpened();
	if (resultEnd)
	{
		mCutInStep++;
	}
}

// �X�e�b�v1 �J�b�g�C���I�����̑҂�
void CCutInDeathJump::CutInStep1()
{
	mElapsedTime = 0.0f;
	mCutInStep = 0;
	End();
}

// �X�V
void CCutInDeathJump::Update()
{
	// �J�b�g�C���Đ����łȂ���΁A�������Ȃ�
	if (!mIsPlaying) return;

	switch (mCutInStep)
	{
	case 0:
		CutInStep0();
		break;
	case 1:
		CutInStep1();
		break;
	}

	// �J�����̍X�V
	CCamera::Update();
}