#include "CRengaBlock.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CSound.h"

// ������̂ɂ����鎞��
#define FADE_TIME 3.0f
// ��������̑҂�����
#define WAIT_TIME 3.0f

#define MAXHEIGHT 15.0f

// �R���X�g���N�^
CRengaBlock::CRengaBlock(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eHatenaOBJ)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
{
	// �����K�u���b�N���f�����擾
	mpModel = CResourceManager::Get<CModel>("RengaBlock");


	mStartPos = Position();

	// �����K���b�N�̃R���C�_�[���쐬
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eBlockCol,
		1.0f, true
	);
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer,ETag::eItem });
	mpColliderSphere->SetCollisionLayers({ ELayer::ePlayer,ELayer::eRecoverCol });
	mpColliderSphere->Position(0.0f, 5.0f, 0.0f);

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderSphere->SetCollisionTag(mReactionTag, true);
	mpColliderSphere->SetCollisionLayer(mReactionLayer, true);

	Position(pos);
	Scale(scale);

}

// �f�X�g���N�^
CRengaBlock::~CRengaBlock()
{
	SAFE_DELETE(mpColliderSphere);
}

// �Փˏ���
void CRengaBlock::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// �Փ˂��Ă���̂���������I�u�W�F�N�g�ł����
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(owner);
		//// ���]���������߂��x�N�g���Ə�����̃x�N�g���̓���(�p�x)�����߂�
		//float dot = CVector::Dot(-hit.adjust.Normalized(), CVector::down);
		//// �����ɓ��������Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
		//float cosAngle = cosf(Math::DegreeToRadian(10.0f)); && dot >= cosAngle
		if (player)
		{
			// ���݂��ҋ@��Ԃł���΁A�����������̏����ɂ���
			if (mState == EState::Idle)
			{
				ChangeState(EState::Hit);
			}
		}
	}
}

// ��Ԃ�؂�ւ���
void CRengaBlock::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}


// �X�e�[�W�J�n���̈ʒu��ݒ�
void CRengaBlock::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// �ҋ@��Ԃ̏���
void CRengaBlock::UpdateIdle()
{

}

// �����������̍X�V����
void CRengaBlock::UpdateHit()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (mStateStep)
	{
		// �X�e�b�v0 �I�u�W�F�N�g����ɗh�炷
	case 0:
		// �h�炷
		// �ő�l�܂�
		if (Position().Y() < mStartPos.Y() + MAXHEIGHT)
		{
			mMoveSpeed = CVector(0.0f, 100.0f * Time::DeltaTime(), 0.0f);
			Position(Position() + mMoveSpeed);
		}
		else
		{
			mStateStep++;
		}
		break;
		// �X�e�b�v1 ���ɖ߂�
	case 1:
		mMoveSpeed = CVector(0.0f, -50.0f * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);
		if (CVector::Distance(Position(), mStartPos) < 0.5f)
		{
			Position(mStartPos);
			// ����������̏�ԂɑJ��
			ChangeState(EState::After);
			mStateStep = 0;
		}
		break;
	}
}

// ����������̍X�V����
void CRengaBlock::UpdateAfter()
{
	SetAlpha(0.0f);
	mpColliderSphere->SetEnable(false);
}

// �X�V����
void CRengaBlock::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// �����������
	case EState::Hit:
		UpdateHit();
		break;
		// ����������̏��
	case EState::After:
		UpdateAfter();
		break;
	}

}

// �`��
void CRengaBlock::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}