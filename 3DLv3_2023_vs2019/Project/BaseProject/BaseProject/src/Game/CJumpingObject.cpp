#include "CJumpingObject.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"

#define DELETE 5.0f
#define WAIT 5.0f


CJumpingObject::CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CJumpingBase(ETaskPriority::eBackground)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
{
	mpModel = CResourceManager::Get<CModel>("FieldCube");
	mpColliderMesh = new CColliderMesh(this, ELayer::eJumpingCol, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);

	SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));
}

CJumpingObject::~CJumpingObject()
{
	SAFE_DELETE(mpColliderMesh);
}

void CJumpingObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	bool KeyPush = CInput::PushKey(VK_SPACE);

	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// �Փ˂��Ă���̂��A��������I�u�W�F�N�g�ł����
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		if (mState == EState::Idle && KeyPush)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				player->UpdateJumpingStart();
			}
			ChangeState(EState::Bounce);
		}
		else if (mState == EState::Idle)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				player->UpdateJumpStart();
			}
			ChangeState(EState::Bounce);
		}
		mIsCollision = true;
	}
}

// ��Ԃ�؂�ւ���
void CJumpingObject::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CJumpingObject::UpdateIdle()
{

}

// ���˂Ă����Ԃ̍X�V����			�K�v�Ȃ�����
void CJumpingObject::UpdateBounce()
{
	// ��������I�u�W�F�N�g���G��Ă�����
	if (mIsCollision)
	{
		// �X�e�b�v0�����蒼��
		mStateStep = 0;
	}
	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (mStateStep)
	{
		// �X�e�b�v0 �t�F�[�h��̑҂�����
	case 0:
		// �҂����Ԃ��o�߂��Ă��Ȃ���΁A�o�ߎ��ԕ����炷
		if (mWaitTime > 0.0f)
		{
			mWaitTime -= Time::DeltaTime();
		}
		// �҂����Ԃ��o�߂�����A���̃X�e�b�v��
		else
		{
			mStateStep++;
		}
		break;
		// �X�e�b�v1 �������������Ƃɖ߂�
	case 1:
		if (mFadeTime > 0.0f)
		{
			mFadeTime -= Time::DeltaTime();
		}
		else
		{
			// �ҋ@��Ԃ֖߂�
			ChangeState(EState::Idle);
			mFadeTime = 0.0f;
			mWaitTime = 0.0f;

		}
		break;
	}
}

void CJumpingObject::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// ����Ă�����
	case EState::Bounce:
		UpdateBounce();
		break;

	}
	// �Փ˃t���O��������
	mIsCollision = false;

}

void CJumpingObject::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}