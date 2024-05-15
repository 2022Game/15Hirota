#include "CCutInClear.h"
#include "Maths.h"



// �R���X�g���N�^
CCutInClear::CCutInClear()
	: mCutInStep(0)
	, mElapsedTime(0.0f)
	, mCenterPos(CVector::zero)
	, mStartAngleY(0.0f)
	, mStartAngleZ(0.0f)
{

}

// �f�X�g���N�^
CCutInClear::~CCutInClear()
{

}

// �J�b�g�C���J�n
bool CCutInClear::Start()
{
	// �x�[�X�̃J�b�g�C���J�n����
	if (!CCutInCamera::Start()) return false;

	// �J�b�g�C�����Ɏg�p����ϐ��Ȃǂ̏�����
	mCutInStep = 0;
	mElapsedTime = 0.0f;

	return true;
}

// �J�b�g�C���I��
bool CCutInClear::End()
{
	// �x�[�X�̃J�b�g�C���I������
	if (!CCutInCamera::End()) return false;

	return true;
}

// �J�b�g�C���ɕK�v�ȏ���ݒ�
void CCutInClear::Setup(CObjectBase* obj)
{
	// �ݒ肳�ꂽ�I�u�W�F�N�g�̈ʒu�𒆐S�n�_�Ƃ���
	mCenterPos = obj->Position();
	// �ݒ肳�ꂽ�I�u�W�F�N�g�̌��݂�Y���̊p�x���擾
	mStartAngleY = obj->EulerAngles().Y();

	mStartAngleZ = obj->EulerAngles().Z();

	mObject = obj;
}

#define CUTIN_TIME 10.0f
#define START_ANGLE -360.0f
#define END_ANGLE 120.0f
#define START_Y 25.0f
#define END_Y 65.5f
#define START_DIST 45.0f
#define END_DIST 130.0f
#define WAIT_TIME 1.0f

// �X�e�b�v0 �J�����̉�]
void CCutInClear::CutInStep0()
{
	// �J�b�g�C���̎��Ԃ��o�߂���ɂ�ăJ�������ړ������܂�
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

		mAt = mCenterPos;
		mEye = (mCenterPos + offsetPos) + CVector(cosf(radAng), 0.0f, sinf(radAng)) * dist;

		mElapsedTime += Time::DeltaTime();
	}
	else
	{
		CVector offsetPos = CVector::zero;
		offsetPos.Y(END_Y);
		float radAng = Math::DegreeToRadian(mStartAngleY + END_ANGLE);
		float dist = END_DIST;

		mAt = mCenterPos;
		mEye = (mCenterPos + offsetPos) + CVector(cosf(radAng), 0.0f, sinf(radAng)) * dist;

		// �������Ȃ��B�J�����̈ʒu��ύX���Ȃ�
		mCutInStep++;
		mElapsedTime = 0.0f;
	}
}

// �X�e�b�v0 �J�b�g�C���I�����̑҂�
void CCutInClear::CutInStep1()
{
	if (mElapsedTime < 6.0f)
	{
		mElapsedTime += Time::DeltaTime();
	}
	else
	{
		mCutInStep = 0;
		//End();
	}
}

// �X�V
void CCutInClear::Update()
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