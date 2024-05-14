#include "CCutInClear.h"
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

// �X�e�b�v0 �J�����̉�]
void CCutInClear::CutInStep0()
{
	// �J�b�g�C���̎��Ԃ��o�߂���ɂ�ăJ�������ړ������܂�
	if (mElapsedTime < CUTIN_TIME)
	{
		float per = mElapsedTime / CUTIN_TIME;

		// �v���C���[�̈ʒu�Ɗp�x���擾
		CVector playerPos = mObject->Position();
		float playerAngleY = mObject->EulerAngles().Y();

		// �J�����̈ʒu�ƒ����_���v���C���[�̈ʒu�Ɗp�x�ɍ��킹��
		CVector offsetPos = CVector::zero;
		offsetPos.Y(15.0f);

		float dist = Math::Lerp(50.0f, 30.0f, per);

		mAt = playerPos + offsetPos;
		mEye = mAt + CVector(0.0f, 0.0f, 1.0f) * dist; // ��]�Ȃ��Œ����I�Ɉړ�����

		mElapsedTime += Time::DeltaTime();
	}
	else
	{
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