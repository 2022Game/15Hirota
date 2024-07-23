#include "CSpringObject.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"
#include "Easing.h"

#define SHRINK_SCALE 0.6f
#define SHRINK_TIME 0.15f
#define RETURN_TIME 0.4f

// �R���X�g���N�^
CSpringObject::CSpringObject(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eJumpingObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mpModel(nullptr)
	, mpCollider(nullptr)
	, mState(ESpring::eIdle)
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
CSpringObject::~CSpringObject()
{
	SAFE_DELETE(mpCollider);
}

// �Փˏ���
void CSpringObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
				SpringStart();
			}
		}
		else
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				player->UpdateJumpingStart();
				SpringStart();
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
		ChangeState(ESpring::eIdle);
	}
}

// ��Ԃ�؂�ւ���
void CSpringObject::ChangeState(ESpring state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// ���˂������Ԃ̊J�n����
void CSpringObject::SpringStart()
{
	// ���˂������Ԃ֐؂�ւ�
	ChangeState(ESpring::eSpring);
	mStateStep = 0;
	mElapsedTime = 0.0f;

	// �X�P�[���l���J�n���̃X�P�[���l�ɖ߂�
	Scale(mStartScale);
}

// �ҋ@��Ԃ̏���
void CSpringObject::UpdateIdle()
{
	if (mIsCollisionPlayer)
	{
		SpringStart();
	}
}

// ���˂Ă����Ԃ̍X�V����
void CSpringObject::UpdateSpring()
{
	switch (mStateStep)
	{
	case 0:
		mStartScale = Scale();
		mShrinkScale = mStartScale;
		mShrinkScale.X(mShrinkScale.X()/* * SHRINK_SCALE*/);
		mShrinkScale.Y(mShrinkScale.Y() * SHRINK_SCALE);
		mShrinkScale.Z(mShrinkScale.Z()/* * SHRINK_SCALE*/);
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
			ChangeState(ESpring::eIdle);
		}
		break;
	}
}

// �X�V����
void CSpringObject::Update()
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
	case ESpring::eIdle:
		UpdateIdle();
		break;
		// ����Ă�����
	case ESpring::eSpring:
		UpdateSpring();
		break;
	}
	// �Փ˃t���O��������
	mIsCollisionPlayer = false;
}

// �`�揈��
void CSpringObject::Render()
{
	if (mpModel != nullptr)
	{
		mpModel->SetColor(mColor);
		mpModel->Render(Matrix());
	}
}