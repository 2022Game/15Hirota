#include "CHatenaBlock.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CRecoveryObject.h"
#include "CInvincible.h"
#include "CSound.h"
#include "CStageManager.h"

// �u���b�N����ɏ㏸����ۂ̍ő�l
#define MAXHEIGHT 15.0f
// �u���b�N�̏㏸�X�s�[�h
#define BLOCK_INCREASE_VALUE 120.0f
// �u���b�N�̉��~�X�s�[�h
#define BLOCK_DESCENDING_VALUE 50.0f

// �R���X�g���N�^
CHatenaBlock::CHatenaBlock(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eHatenaOBJ)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
{
	// �n�e�i�u���b�N���f���擾
	mpModel = CResourceManager::Get<CModel>("HatenaBlock");
	// �u���b�N��@��������SE�擾
	mpHitBlockSE = CResourceManager::Get<CSound>("8bitShot");

	// �n�e�i�u���b�N�̏����ʒu�̕ۑ�
	mStartPos = Position();

	// �n�e�i�u���b�N�̃R���C�_�[���쐬
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eBlockCol,
		1.0f, true
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer, ETag::eItemRecover, ETag::eItemInvincible });
	mpColliderSphere->SetCollisionLayers({ ELayer::ePlayer, ELayer::eRecoverCol, ELayer::eInvincbleCol });
	mpColliderSphere->Position(0.0f, 5.0f, 0.0f);

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderSphere->SetCollisionTag(mReactionTag, true);
	mpColliderSphere->SetCollisionLayer(mReactionLayer, true);

	Position(pos);
	Scale(scale);

	mStartPos = Position();

	mpHeart = nullptr;
	mpStar = nullptr;
}

// �f�X�g���N�^
CHatenaBlock::~CHatenaBlock()
{
	CStageManager::RemoveTask(this);
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

		// ���b�V���ɂ���̂Ȃ�Ώ�L�̏��������s
		// �����ɓ����������̂ݏ���

		// �v���C���[�ɓ���������
		if (player)
		{
			// ���݂��ҋ@��Ԃł���΁A�����������̏����ɂ���
			if (mState == EState::Idle)
			{
				// ��ԑJ��
				ChangeState(EState::Hit);
			}
		}
	}
}

// �X�e�[�W�J�n���̈ʒu��ݒ�
void CHatenaBlock::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}


// ��Ԃ�؂�ւ���
void CHatenaBlock::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CHatenaBlock::UpdateIdle()
{
	
}

// �����������̍X�V����
void CHatenaBlock::UpdateHit()
{
	mpHitBlockSE->Play(1.0f, false, 0.0f);

	bool item = false;
	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (mStateStep)
	{
		// �X�e�b�v0 �I�u�W�F�N�g����ɗh�炷
	case 0:
		// �h�炷
		// �ő�l�܂�
		if (Position().Y() < mStartPos.Y() + MAXHEIGHT)
		{
			// �A�C�e�����o��
			// �����_����
			int randomValue = Math::Rand(0, 5);

			item = false;

			bool obj = !mpHeart && !mpStar;

			// 0 ���� �����o�����Ă��Ȃ� ���� false�������ꍇ
			if ((randomValue >= 0 && randomValue <= 5 && obj && !item))
			{
				item = true;
				mpHeart = new CRecoveryObject();
				mpHeart->Scale(3.0f, 3.0f, 3.0f);
				CVector newPosition = Position() + CVector(0.0f, 45.0f, 0.0f);
				mpHeart->Position(newPosition);
				CStageManager::AddTask(mpHeart);
			}
			//// 1 ���� �����o�����Ă��Ȃ� ���� false�������ꍇ
			//else if ((randomValue >= 6 && randomValue <= 10 && obj && !item))
			//{
			//	item = true;
			//	mpStar = new CInvincible();
			//	mpStar->Scale(3.0f, 3.0f, 3.0f);
			//	CVector newPosition = Position() + CVector(0.0f, 45.0f, 0.0f);
			//	mpStar->Position(newPosition);
			//}

			// �㏸������
			CVector mSpd = mMoveSpeed;
			mSpd = CVector(0.0f, BLOCK_INCREASE_VALUE * Time::DeltaTime(), 0.0f);
			Position(Position() + mSpd);
		}
		else
		{
			// ���̃X�e�b�v��
			mStateStep++;
		}
		break;
		// �X�e�b�v1 ���ɖ߂�
	case 1:
		// ���~������
		mMoveSpeed = CVector(0.0f, -BLOCK_DESCENDING_VALUE * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);

		// �I�u�W�F�N�g�̈ʒu��0.5�����ɂȂ�����
		// ���̈ʒu�ɖ߂�
		if (CVector::Distance(Position(), mStartPos) < 1.0f)
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