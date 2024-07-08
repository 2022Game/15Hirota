#include "CReflectionObject.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"
#include "Easing.h"

#define SHRINK_SCALE 0.8f
#define SHRINK_TIME 0.15f
#define RETURN_TIME 0.8f

// �R���X�g���N�^
CReflectionObject::CReflectionObject(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eReflection, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mpModel(nullptr)
	, mpCollider1(nullptr)
	, mpCollider2(nullptr)
	, mState(EState::eIdle)
	, mStartScale(scale)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mIsCollisionPlayer(false)
{
	Position(pos);
	Scale(mStartScale);
	Rotate(rot);
}

// �f�X�g���N�^
CReflectionObject::~CReflectionObject()
{
	SAFE_DELETE(mpCollider1);
	SAFE_DELETE(mpCollider2);
}

// �Փˏ���
void CReflectionObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	//// ���]���������߂��x�N�g���Ə�����̃x�N�g���̓���(�p�x)�����߂�
	//float dot = CVector::Dot(-hit.adjust.Normalized(), CVector::up);
	//// ��ɏ�����Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
	//float cosAngle = cosf(Math::DegreeToRadian(10.0f));
	//// ���߂��p�x���w�肵���p�x�͈͓̔��ł���΁A
	//if (dot >= cosAngle)
	CPlayer* player = dynamic_cast<CPlayer*>(owner);
	if (player)
	{
		//player->UpdateReflection();
		BounceStart();
	}
	mIsCollisionPlayer = true;

	//// ���]���������߂��x�N�g���Ə�����̃x�N�g���̓���(�p�x)�����߂�
	//float dotdown = CVector::Dot(-hit.adjust.Normalized(), CVector::down);
	//// ���ɏ�����Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
	//float cosAngleDown = cosf(Math::DegreeToRadian(10.0f));
	//if (dotdown >= cosAngleDown)
	//{
	//	ChangeState(EState::eIdle);
	//}
}

// ��Ԃ�؂�ւ���
void CReflectionObject::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// ���˂������Ԃ̊J�n����
void CReflectionObject::BounceStart()
{
	// ���˂������Ԃ֐؂�ւ�
	ChangeState(EState::eBounce);
	mStateStep = 0;
	mElapsedTime = 0.0f;

	// �X�P�[���l���J�n���̃X�P�[���l�ɖ߂�
	Scale(mStartScale);
}

// �ҋ@��Ԃ̏���
void CReflectionObject::UpdateIdle()
{
	if (mIsCollisionPlayer)
	{
		BounceStart();
	}
}

// ���˂Ă����Ԃ̍X�V����
void CReflectionObject::UpdateBounce()
{
	switch (mStateStep)
	{
	case 0:
		mStartScale = Scale();
		mShrinkScale = mStartScale;
		mShrinkScale.X(mShrinkScale.X() * SHRINK_SCALE);
		mShrinkScale.Y(mShrinkScale.Y() * SHRINK_SCALE);
		mShrinkScale.Z(mShrinkScale.Z() * SHRINK_SCALE);
		Scale(mShrinkScale);
		mStateStep++;
		break;

	case 1:
		if (mElapsedTime < SHRINK_TIME)
		{
			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			mStateStep++;
			mElapsedTime = 0.0f;
		}
		break;
	case 2:
		if (mElapsedTime < RETURN_TIME)
		{
			float percent = Easing::BounceOut
			(
				mElapsedTime,	// ���݂̎���
				RETURN_TIME,	// �ړI�̎���
				0.0f,			// �ŏ��l
				1.0f			// �ő�l
			);

			// ���`���
			CVector scale = CVector::LerpUnclamped(
				mShrinkScale,
				mStartScale,
				percent
			);
			Scale(scale);

			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			Scale(mStartScale);
			mElapsedTime = 0.0f;
			mStateStep++;
		}
		break;
	case 3:
		if (!mIsCollisionPlayer)
		{
			ChangeState(EState::eIdle);
		}
		break;
	}
}

// �X�V����
void CReflectionObject::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// ����Ă�����
	case EState::eBounce:
		UpdateBounce();
		break;

	}
	// �Փ˃t���O��������
	mIsCollisionPlayer = false;
}

// �`�揈��
void CReflectionObject::Render()
{
	if (mpModel != nullptr)
	{
		mpModel->SetColor(mColor);
		mpModel->Render(Matrix());
	}
}