#include "CCutInDeath.h"
#include "Maths.h"

#define CUTIN_TIME 4.0f
#define START_ANGLE 0.0f
#define END_ANGLE 90.0f
#define START_Y 0.0f
#define END_Y 15.0f
#define START_DIST 5.0f
#define END_DIST 30.0f
#define WAIT_TIME 1.0f

// �R���X�g���N�^
CCutInDeath::CCutInDeath()
	: mCutInStep(0)
	, mElapsedTime(0.0f)
	, mCenterPos(CVector::zero)
	, mStartAngleY(0.0f)
{

}

// �f�X�g���N�^
CCutInDeath::~CCutInDeath()
{

}

// �J�b�g�C���J�n
bool CCutInDeath::Start()
{
	// �x�[�X�̃J�b�g�C���J�n����
	if (!CCutInCamera::Start()) return false;

	// �J�b�g�C�����Ɏg�p����ϐ��Ȃǂ̏�����
	mCutInStep = 0;
	mElapsedTime = 0.0f;

	return true;
}

// �J�b�g�C���I��
bool CCutInDeath::End()
{
	// �x�[�X�̃J�b�g�C���I������
	if (!CCutInCamera::End()) return false;

	return true;
}

// �J�b�g�C���ɕK�v�ȏ���ݒ�
void CCutInDeath::Setup(CObjectBase* obj)
{
	// �ݒ肳�ꂽ�I�u�W�F�N�g�̈ʒu�𒆐S�n�_�Ƃ���
	mCenterPos = obj->Position();
	// �ݒ肳�ꂽ�I�u�W�F�N�g�̌��݂�Y���̊p�x���擾
	mStartAngleY = obj->EulerAngles().Y();
}

// �X�e�b�v0 �J�����̉�]
void CCutInDeath::CutInStep0()
{
	if (mElapsedTime < CUTIN_TIME)
	{
		float per = mElapsedTime / CUTIN_TIME;

		// �J�����̍������㏸������
		CVector offsetPos = CVector::down;
		float offsetY = Math::Lerp(50.0f, 100.0f, per);
		mAt = mCenterPos + offsetPos;

		// �J�����̈ʒu��ݒ肷��
		float angleY = Math::Lerp(mStartAngleY, mStartAngleY + 90.0f, per);
		float radians = Math::DegreeToRadian(angleY);
		float radius = 80.0f; // ���̔��a
		mEye = CVector(mCenterPos.X() + radius * sin(radians),
			mCenterPos.Y() + offsetY,
			mCenterPos.Z() + radius * cos(radians));

		mElapsedTime += Time::DeltaTime();
	}
	else
	{
		mCutInStep++;
		mElapsedTime = 0.0f;
	}
}

// �X�e�b�v0 �J�b�g�C���I�����̑҂�
void CCutInDeath::CutInStep1()
{
	if (mElapsedTime < WAIT_TIME)
	{
		mElapsedTime += Time::DeltaTime();
	}
	else
	{
		mCutInStep = 0;
		End();
	}
}

// �X�V
void CCutInDeath::Update()
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