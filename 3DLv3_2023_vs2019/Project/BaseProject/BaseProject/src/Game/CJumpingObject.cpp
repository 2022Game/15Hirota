#include "CJumpingObject.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"
#include "Easing.h"

#define SHRINK_SCALE 0.8f
#define SHRINK_TIME 0.15f
#define RETURN_TIME 0.8f

// �R���X�g���N�^
CJumpingObject::CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eJumpingObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mpModel(nullptr)
	, mpCollider(nullptr)
	, mState(EState::eIdle)
	, mStartScale(scale)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mJumpedElapsedTime(0.0f)
	, mIsCollisionPlayer(false)
{
	Position(pos);
	Scale(mStartScale);
	Rotate(rot);
}

// �f�X�g���N�^
CJumpingObject::~CJumpingObject()
{
	SAFE_DELETE(mpCollider);
}

// �Փˏ���
void CJumpingObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// ���]���������߂��x�N�g���Ə�����̃x�N�g���̓���(�p�x)�����߂�
	float dot = CVector::Dot(-hit.adjust.Normalized(), CVector::up);
	// ��ɏ�����Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
	float cosAngle = cosf(Math::DegreeToRadian(10.0f));
	// ���߂��p�x���w�肵���p�x�͈͓̔��ł���΁A
	if (dot >= cosAngle)
	{
		if (mJumpedElapsedTime <= 0.2f)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				player->UpdateHighJumpingStart();
				BounceStart();
			}
		}
		else
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				player->UpdateJumpingStart();
				BounceStart();
			}
		}
		mIsCollisionPlayer = true;
	}

	// ���]���������߂��x�N�g���Ə�����̃x�N�g���̓���(�p�x)�����߂�
	float dotdown = CVector::Dot(-hit.adjust.Normalized(), CVector::down);
	// ���ɏ�����Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
	float cosAngleDown = cosf(Math::DegreeToRadian(10.0f));
	if (dotdown >= cosAngleDown)
	{
		ChangeState(EState::eIdle);
	}
}

// ��Ԃ�؂�ւ���
void CJumpingObject::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// ���˂������Ԃ̊J�n����
void CJumpingObject::BounceStart()
{
	// ���˂������Ԃ֐؂�ւ�
	ChangeState(EState::eBounce);
	mStateStep = 0;
	mElapsedTime = 0.0f;

	// �X�P�[���l���J�n���̃X�P�[���l�ɖ߂�
	Scale(mStartScale);
}

// �ҋ@��Ԃ̏���
void CJumpingObject::UpdateIdle()
{
	if (mIsCollisionPlayer)
	{
		BounceStart();
	}
}

// ���˂Ă����Ԃ̍X�V����
void CJumpingObject::UpdateBounce()
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
void CJumpingObject::Update()
{
	if (CInput::PushKey(VK_SPACE))
	{
		mJumpedElapsedTime = 0.0f;
	}
	else
	{
		mJumpedElapsedTime += Time::DeltaTime();
	}

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
void CJumpingObject::Render()
{
	if (mpModel != nullptr)
	{
		mpModel->SetColor(mColor);
		mpModel->Render(Matrix());
	}
}