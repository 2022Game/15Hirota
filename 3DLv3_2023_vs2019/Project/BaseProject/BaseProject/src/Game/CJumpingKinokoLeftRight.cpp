#include "CJumpingKinokoLeftRight.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"
#include "Easing.h"

#define SHRINK_SCALE 0.8f
#define SHRINK_TIME 0.15f
#define RETURN_TIME 0.8f

// �R���X�g���N�^
CJumpingKinokoLeftRight::CJumpingKinokoLeftRight(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime, ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eJumpingObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mStartScale(scale)
	, mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mMoveVec(move)
	, mMoveTime(moveTime)
	, mDefaultPos(pos)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mMoveElapsedTime(0.0f)
	, mJumpedElapsedTime(0.0f)
	, mIsCollisionPlayer(false)
{
	// ���˂�L�m�R�̃��f���擾
	mpKinoko = CResourceManager::Get<CModel>("JumpingKinoko3Color");

	// ���˂�L�m�R�̃R���C�_�[�쐬
	CModel* kinokoCol = CResourceManager::Get<CModel>("JumpingKinokoCol");
	mpColliderMesh = new CColliderMesh(this, ELayer::eJumpingCol, kinokoCol, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	/*mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);*/

	Position(mDefaultPos);
	Scale(mStartScale);
	Rotate(rot);

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CJumpingKinokoLeftRight::~CJumpingKinokoLeftRight()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CJumpingKinokoLeftRight::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
			if (mJumpedElapsedTime <= 0.1f)
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
		// ��ɏ�����Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
		float cosAngleDown = cosf(Math::DegreeToRadian(10.0f));
		if (dotdown >= cosAngleDown)
		{
			ChangeState(EState::eIdle);
		}
	}
}

// ��Ԃ�؂�ւ���
void CJumpingKinokoLeftRight::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// ���˂������Ԃ̊J�n����
void CJumpingKinokoLeftRight::BounceStart()
{
	// ���˂������Ԃ֐؂�ւ�
	ChangeState(EState::eBounce);
	mStateStep = 0;
	mElapsedTime = 0.0f;

	// �X�P�[���l���J�n���̃X�P�[���l�ɖ߂�
	Scale(mStartScale);
}

// �ҋ@��Ԃ̏���
void CJumpingKinokoLeftRight::UpdateIdle()
{
	if (mIsCollisionPlayer)
	{
		BounceStart();
	}
}

// ���˂Ă����Ԃ̍X�V����
void CJumpingKinokoLeftRight::UpdateBounce()
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
void CJumpingKinokoLeftRight::Update()
{
	if (CInput::PushKey(VK_SPACE))
	{
		mJumpedElapsedTime = 0.0f;
	}
	else
	{
		mJumpedElapsedTime += Time::DeltaTime();
	}

	float per = mMoveElapsedTime / mMoveTime;
	Position(mDefaultPos + mMoveVec * sinf(M_PI * 2.0f * per));

	mMoveElapsedTime += Time::DeltaTime();
	if (mMoveElapsedTime >= mMoveTime)
	{
		mMoveElapsedTime -= mMoveTime;
	}

	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// ���˂���
	case EState::eBounce:
		UpdateBounce();
		break;

	}
	// �Փ˃t���O��������
	mIsCollisionPlayer = false;
}

// �`�揈��
void CJumpingKinokoLeftRight::Render()
{
	mpKinoko->SetColor(mColor);
	mpKinoko->Render(Matrix());
}