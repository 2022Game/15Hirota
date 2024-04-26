#include "CCutInTest.h"
#include "Maths.h"

#define CUTIN_TIME 30.0f
#define START_ANGLE 0.0f
#define END_ANGLE 90.0f
#define START_Y 0.0f
#define END_Y 15.0f
#define START_DIST 5.0f
#define END_DIST 30.0f
#define WAIT_TIME 1.0f

// �R���X�g���N�^
CCutInTest::CCutInTest()
	: mCutInStep(0)
	, mElapsedTime(0.0f)
	, mCenterPos(CVector::zero)
	, mStartAngleY(0.0f)
{

}

// �f�X�g���N�^
CCutInTest::~CCutInTest()
{

}

// �J�b�g�C���J�n
bool CCutInTest::Start()
{
	// �x�[�X�̃J�b�g�C���J�n����
	if (!CCutInCamera::Start()) return false;

	// �J�b�g�C�����Ɏg�p����ϐ��Ȃǂ̏�����
	mCutInStep = 0;
	mElapsedTime = 0.0f;

	return true;
}

// �J�b�g�C���I��
bool CCutInTest::End()
{
	// �x�[�X�̃J�b�g�C���I������
	if (!CCutInCamera::End()) return false;

	return true;
}

// �J�b�g�C���ɕK�v�ȏ���ݒ�
void CCutInTest::Setup(CObjectBase* obj)
{
	// �ݒ肳�ꂽ�I�u�W�F�N�g�̈ʒu�𒆐S�n�_�Ƃ���
	mCenterPos = obj->Position();
	// �ݒ肳�ꂽ�I�u�W�F�N�g�̌��݂�Y���̊p�x���擾
	mStartAngleY = obj->EulerAngles().Y();
}

// �X�e�b�v0 �J�����̉�]
void CCutInTest::CutInStep0()
{
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
	else
	{
		CVector offsetPos = CVector::zero;
		offsetPos.Y(END_Y);
		float radAng = Math::DegreeToRadian(mStartAngleY + END_ANGLE);
		float dist = END_DIST;

		mAt = mCenterPos + offsetPos;
		mEye = mAt + CVector(cosf(radAng), 0.0f, sinf(radAng)) * dist;

		mCutInStep++;
		mElapsedTime = 0.0f;
	}
}

// �X�e�b�v0 �J�b�g�C���I�����̑҂�
void CCutInTest::CutInStep1()
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
void CCutInTest::Update()
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