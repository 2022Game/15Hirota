#include "CHatenaBlock.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CRecoveryObject.h"
#include "CInvincible.h"

// ������̂ɂ����鎞��
#define FADE_TIME 3.0f
// ��������̑҂�����
#define WAIT_TIME 3.0f

#define MAXHEIGHT 15.0f

#define HEIGHT_ABOVE_BLOCK 3.0f

// �R���X�g���N�^
CHatenaBlock::CHatenaBlock(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eHatenaOBJ)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
	, mMoveSpeed(0.0f,0.0f,0.0f)
{
	// �n�e�i�u���b�N���f�����擾
	mpModel = CResourceManager::Get<CModel>("HatenaBlock");


	mStartPos = Position();

	// �n�e�i�u���b�N�̃R���C�_�[���쐬
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eBlockCol,
		1.0f, true
	);
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer, ETag::eItem });
	mpColliderSphere->SetCollisionLayers({ ELayer::ePlayer, ELayer::eRecoverCol });
	mpColliderSphere->Position(0.0f, 5.0f, 0.0f);

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderSphere->SetCollisionTag(mReactionTag, true);
	mpColliderSphere->SetCollisionLayer(mReactionLayer, true);

	Position(pos);
	Scale(scale);

	mpHeart = nullptr;
	mpStar = nullptr;
}

// �f�X�g���N�^
CHatenaBlock::~CHatenaBlock()
{
	SAFE_DELETE(mpColliderSphere);
}

// �Փˏ���
void CHatenaBlock::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
				int randomValue = Math::Rand(0, 1);
				bool item = false;

				if ((randomValue == 0 && !mpHeart && !item))
				{
					item = true;
					mpHeart = new CRecoveryObject();
					mpHeart->Scale(3.0f, 3.0f, 3.0f);
					CVector newPosition = Position() + CVector(0.0f, 45.0f, 0.0f);
					mpHeart->Position(newPosition);
				}
				else if ((randomValue == 1 && !mpStar && !item))
				{
					item = true;
					mpStar = new CInvincible();
					mpStar->Scale(3.0f, 3.0f, 3.0f);
					CVector newPosition = Position() + CVector(0.0f, 45.0f, 0.0f);
					mpStar->Position(newPosition);
				}
				ChangeState(EState::Hit);
			}
		}
	}
}

// ��Ԃ�؂�ւ���
void CHatenaBlock::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}


// �X�e�[�W�J�n���̈ʒu��ݒ�
void CHatenaBlock::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// �ҋ@��Ԃ̏���
void CHatenaBlock::UpdateIdle()
{
	
}

// �����������̍X�V����
void CHatenaBlock::UpdateHit()
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
			CVector mSpd = mMoveSpeed;
			mSpd = CVector(0.0f, 100.0f * Time::DeltaTime(), 0.0f);
			Position(Position() + mSpd);
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
void CHatenaBlock::UpdateAfter()
{
	// �n�e�i�u���b�N(����������)���f���ɕύX
	mpModel = CResourceManager::Get<CModel>("HatenaBlockAfter");
}

// �X�V����
void CHatenaBlock::Update()
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
void CHatenaBlock::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());	
}

//
//int randomValue = Math::Rand(0, 10);
//bool item = false;
//
//if ((randomValue >= 0 && randomValue <= 5) && !mpHeart && !item)
//{
//	item = true;
//	mpHeart = new CRecoveryObject();
//	mpHeart->Scale(3.0f, 3.0f, 3.0f);
//	CVector newPosition = Position() + CVector(0.0f, 45.0f, 0.0f);
//	mpHeart->Position(newPosition);
//}
//else if ((randomValue >= 6 && randomValue <= 10) && !mpStar && !item)
//{
//	item = true;
//	mpStar = new CInvincible();
//	mpStar->Scale(3.0f, 3.0f, 3.0f);
//	CVector newPosition = Position() + CVector(0.0f, 45.0f, 0.0f);
//	mpStar->Position(newPosition);
//}