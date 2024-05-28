#include "CJumpingObject.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"
#include "Easing.h"

// ��������̎���
#define DELETE 5.0f
#define WAIT 5.0f

#define SHRINK_SCALE 0.8f
#define SHRINK_TIME 0.15f
#define RETURN_TIME 0.8f

// �R���X�g���N�^
CJumpingObject::CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eJumpingObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mElapsedTime(0.0f)
	, mIsCollisionPlayer(false)
{
	// ���˂����鏰�̃��f���擾
	mpModel = CResourceManager::Get<CModel>("FieldCube");
	// ���˂����鏰�̃R���C�_�[�쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eJumpingCol, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);

	SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));
}

// �f�X�g���N�^
CJumpingObject::~CJumpingObject()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CJumpingObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	bool KeyPush = CInput::PushKey(VK_SPACE);

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
			if (mState == EState::eIdle && KeyPush)
			{
				CPlayer* player = dynamic_cast<CPlayer*>(owner);
				if (player)
				{
					player->UpdateHighJumpingStart();
				}
				ChangeState(EState::eBounce);
			}
			else if (mState == EState::eIdle)
			{
				CPlayer* player = dynamic_cast<CPlayer*>(owner);
				if (player)
				{
					if (player)
					{
						player->UpdateJumpingStart();
					}
				}
				ChangeState(EState::eBounce);
			}
			mIsCollisionPlayer = true;
		}
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

// �ҋ@��Ԃ̏���
void CJumpingObject::UpdateIdle()
{
	if (mIsCollisionPlayer)
	{
		ChangeState(EState::eBounce);
	}
}

// ���˂Ă����Ԃ̍X�V����			�K�v�Ȃ�����
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
			/*float percent = Easing::BackOut
			(
				mElapsedTime,
				RETURN_TIME,
				0.3f, 1.0f, 5.0f
			);*/

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
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}