#include "CRisingObject.h"
#include "Maths.h"
#include "CPlayer.h"


// ������̂ɂ����鎞��
#define FADE_TIME 3.0f
// ��������̑҂�����
#define WAIT_TIME 3.0f

#define MAXHEIGHT 50.0f

// �R���X�g���N�^
CRisingObject::CRisingObject(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eFallingOBJ)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mMaxHeight(0.0f, 15.0f, 0.0f)
{

	//Position(0.0f, 6.0f, -430.0f);
	mStartPos = Position();

	// ���̃��f�����擾
	mpModel = CResourceManager::Get<CModel>("FieldCube");

	// �����鏰�̃R���C�_�[�쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer, ELayer::eEnemy });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer, ETag::eEnemy });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);

	SetColor(CColor(0.0f, 1.0f, 1.0f, 1.0f));

}

// �f�X�g���N�^
CRisingObject::~CRisingObject()
{
	SAFE_DELETE(mpColliderMesh);
}

// �X�e�[�W�J�n���̈ʒu��ݒ�
void CRisingObject::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// �Փˏ���
void CRisingObject::Collision(CCollider* slef, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// �Փ˂��Ă���̂��A��������I�u�W�F�N�g�ł����
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		// ���݂��ҋ@��Ԃł���΁A�t�F�[�h��Ԃ֐؂�ւ���
		if (mState == EState::Idle)
		{
			ChangeState(EState::Rising);
		}

		// ��������I�u�W�F�N�g���G��Ă���̂�
		// �Փ˃t���O���I��
		mIsCollision = true;
	}
}

// ��Ԃ�؂�ւ���
void CRisingObject::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CRisingObject::UpdateIdle()
{

}

// ����Ă����Ԃ̍X�V����
void CRisingObject::UpdateRising()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (mStateStep)
	{
		// �X�e�b�v0 �t�F�[�h��̑҂�����
	case 0:
		// �ő�l��菭�Ȃ�
		if (Position().Y() < MAXHEIGHT)
		{
			// �㏸
			float fallSpeed = 8.0f;

			mMoveSpeed = CVector(0.0f, +fallSpeed * Time::DeltaTime(), 0.0f);
			Position(Position() + mMoveSpeed);
		}// �ő�l���z������
		else
		{
			mStateStep++;
		}
		break;
		// �X�e�b�v1 �������������Ƃɖ߂�
	case 1:
		// ���~
		float fallSpeed = 8.0f;
		mMoveSpeed = CVector(0.0f, -fallSpeed * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);
		mFadeTime -= Time::DeltaTime();
		// ���ꂽ�ʒu�ɒB�����珉���ʒu�ɖ߂�
		if (CVector::Distance(Position(), mStartPos) < 0.1f)
		{
			Position(mStartPos);
			// �ҋ@��Ԃ֖߂�
			ChangeState(EState::Idle);
			mStateStep = 0;
		}
		break;
	}
}

// �X�V
void CRisingObject::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// �㏸���
	case EState::Rising:
		UpdateRising();
		break;

	}

	// �Փ˃t���O��������
	mIsCollision = false;
}

// �`��
void CRisingObject::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}