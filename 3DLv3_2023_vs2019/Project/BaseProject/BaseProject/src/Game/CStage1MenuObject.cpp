#include "CStage1MenuObject.h"
#include "CCollisionManager.h"
#include "Maths.h"
#include "Easing.h"
#include "CInput.h"
#include "CModel.h"
#include "CTaskManager.h"
#include "CStageManager.h"

#define SHRINK_SCALE 0.65f
#define SHRINK_TIME 0.15f
#define RETURN_TIME 0.3f

// �R���X�g���N�^
CStage1MenuObject::CStage1MenuObject(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eStageMenuObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mStartScale(CVector::one)
	, mShrinkScale(CVector::one)
	, mState(EState::eIdle)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mIsCollisionPlayer(false)
{
	// �񐔐��������f�����擾
	mpSkyModel = CResourceManager::Get<CModel>("Number3");

	// �񐔐��������f���̃R���C�_�[�쐬
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eStageMenuObject,
		10.0f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eDamageCol });
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer });

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CStage1MenuObject::~CStage1MenuObject()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpColliderSphere);
}

// �Փˏ���
void CStage1MenuObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		mIsCollisionPlayer = true;
	}
}

void CStage1MenuObject::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

void CStage1MenuObject::UpdateIdle()
{
	if (mIsCollisionPlayer)
	{
		ChangeState(EState::eReaction);
	}
}

void CStage1MenuObject::UpdateReaction()
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
			float percent = Easing::BackOut
			(
				mElapsedTime,
				RETURN_TIME,
				0.0f, 1.0f, 5.0f
			);

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
void CStage1MenuObject::Update()
{
	// ��]
	float rot = 1.0f;
	Rotate(0.0f, rot, 0.0f);

	switch (mState)
	{
	case EState::eIdle:
		UpdateIdle();
		break;
	case EState::eReaction:
		UpdateReaction();
		break;
	}

	mIsCollisionPlayer = false;
}

// �`�揈��
void CStage1MenuObject::Render()
{
	mpSkyModel->SetColor(mColor);
	mpSkyModel->Render(Matrix());
}