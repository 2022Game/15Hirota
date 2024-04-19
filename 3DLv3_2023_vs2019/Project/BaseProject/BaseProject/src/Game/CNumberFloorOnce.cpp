#include "CNumberFloorOnce.h"
#include "Maths.h"
#include "CPlayer.h"

// ������̂ɂ����鎞��
#define FADE_TIME 4.0f
// ��������̑҂�����
#define WAIT_TIME 4.0f

// �R���X�g���N�^
CNumberFloorOnce::CNumberFloorOnce(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eNumberFalling)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mSwitchCount(0)
	, mFallingSwitch(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mElapsedTime(0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
{
	// 1��ŏ��ł��鏰�̃��f���擾
	mpNumberOnce = CResourceManager::Get<CModel>("Number1");

	// 1��ŏ��ł��鏰�̃R���C�_�[�쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpNumberOnce, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionTag(mReactionTag, true);
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);


	Position(pos);
	Scale(scale);
	Rotate(rot);

	// �����ʒu��ݒ�
	mStartPos = Position();

	mStateStep = 0;
}

// �f�X�g���N�^
CNumberFloorOnce::~CNumberFloorOnce()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CNumberFloorOnce::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// �Փ˂��Ă���̂��A��������I�u�W�F�N�g�ł����
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		// ���]���������߂��x�N�g���Ə�����̃x�N�g���̓���(�p�x)�����߂�
		float dot = CVector::Dot(-hit.adjust.Normalized(), CVector::up);
		// ��ɏ�����Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
		float cosAngle = cosf(Math::DegreeToRadian(10.0f));
		// ���߂��p�x���w�肵���p�x�͈͓̔��ł���΁A
		if (dot >= cosAngle)
		{
			// ���݂��ҋ@��Ԃł���΁A�t�F�[�h��Ԃ֐؂�ւ���
			if (mState == EState::Idle)
			{
				ChangeState(EState::Waiting);
			}
		}
		mIsCollision = true;
	}
}

// ��Ԃ�؂�ւ���
void CNumberFloorOnce::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mFallingSwitch = 0;
}

// �ҋ@��Ԃ̏���
void CNumberFloorOnce::UpdateIdle()
{

}

// �҂���Ԃ̏���
void CNumberFloorOnce::UpdateWaiting()
{
	if (mIsCollision)
	{
		SetColor(CColor(0.5f, 0.1f, 0.1f, 1.0f));
	}
	else
	{
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
	}

	switch (mStateStep)
	{
		// �X�e�b�v0 �I�u�W�F�N�g�\���̕ύX
	case 0:
	{
		if (!mIsCollision)
		{
			mStateStep++;
		}
		break;
	}
	case 1:
	{
		mpModel = CResourceManager::Get<CModel>("Number0");
		ChangeState(EState::Falling);
	}
	break;
	}
}

// ������Ԃ̏���
void CNumberFloorOnce::UpdateFalling()
{
	switch (mFallingSwitch)
	{
		// �ԐF�œ_�ł�����
	case 0:
	{
		static const float time = 2.0f;
		if (mElapsedTime < time)
		{
			mElapsedTime += Time::DeltaTime();
			float red = 0.5f + 0.5f * sin(2.0f * M_PI * mElapsedTime);
			CColor color = CColor(red, 0.0f, 0.0f, 1.0f);
			SetColor(color);
		}
		else
		{
			mSwitchCount++;
			mElapsedTime = 0.0f;
			if (mSwitchCount == 2)
			{
				mFallingSwitch++;
			}
		}
	}
	break;
	// ����������
	case 1:
	{
		static const float fall = 10.0f;
		mMoveSpeed = CVector(0.0f, -fall * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);
		if (Position().Y() <= mStartPos.Y() - 30.0f)
		{
			mFallingSwitch++;
			Position(mStartPos);
		}
	}
	break;
	// ���̏�Ԃɖ߂�
	case 2:
	{
		mpModel = CResourceManager::Get<CModel>("Number1");
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
		mStateStep = 0;
		mSwitchCount = 0;
		mElapsedTime = 0;
		mFallingSwitch = 0;
		ChangeState(EState::Idle);
	}
	break;
	}
}

// �X�V����
void CNumberFloorOnce::Update()
{
	// ���̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// �҂����
	case EState::Waiting:
		UpdateWaiting();
		break;
		// �������
	case EState::Falling:
		UpdateFalling();
		break;
	}

	// �Փ˃t���O��������
	mIsCollision = false;

}

// �`�揈��
void CNumberFloorOnce::Render()
{
	mpNumberOnce->SetColor(mColor);
	mpNumberOnce->Render(Matrix());
}