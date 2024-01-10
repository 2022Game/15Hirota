#include "CFallingObjects.h"
#include "Maths.h"
#include "CPlayer.h"


// ������̂ɂ����鎞��
#define FADE_TIME 3.0f
// ��������̑҂�����
#define WAIT_TIME 3.0f

// �R���X�g���N�^
CFallingObjects::CFallingObjects(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eFallingOBJ)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
	, mMoveSpeed(0.0f,0.0f,0.0f)
	, mPosition(0.0f,0.0f,0.0f)
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
CFallingObjects::~CFallingObjects()
{
	SAFE_DELETE(mpColliderMesh);
}

// �X�e�[�W�J�n���̈ʒu��ݒ�
void CFallingObjects::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// �Փˏ���
void CFallingObjects::Collision(CCollider* slef, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// �Փ˂��Ă���̂��A��������I�u�W�F�N�g�ł����
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		// ���݂��ҋ@��Ԃł���΁A�t�F�[�h��Ԃ֐؂�ւ���
		if (mState == EState::Idle)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				ChangeState(EState::Falling);
				mFadeTime = FADE_TIME;
				mWaitTime = WAIT_TIME;
			}
		}

		// ��������I�u�W�F�N�g���G��Ă���̂�
		// �Փ˃t���O���I��
		mIsCollision = true;
	}
}

// ��Ԃ�؂�ւ���
void CFallingObjects::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CFallingObjects::UpdateIdle()
{

}

// ����Ă����Ԃ̍X�V����
void CFallingObjects::UpdateFalling()
{
	// ��������I�u�W�F�N�g���G��Ă�����
	if (mIsCollision)
	{
		float fallSpeed = 5.0f;
		mMoveSpeed = CVector(0.0f, -fallSpeed * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);
		// �X�e�b�v0�����蒼��
		mStateStep = 0;
		mWaitTime = WAIT_TIME;
		mFadeTime = FADE_TIME;
	}
	else
	{
		// �v���C���[�����ꂽ��㏸
		float ascendSpeed = 5.0f; // �K�؂ȑ��x��ݒ�
		mMoveSpeed = CVector(0.0f, +ascendSpeed * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);

		// ���ꂽ�ʒu�ɒB�����珉���ʒu�ɖ߂�
		if (CVector::Distance(Position(), mStartPos) < 0.1f)
		{
			Position(mStartPos);
			// �ҋ@��Ԃ֖߂�
			ChangeState(EState::Idle);
			mFadeTime = 0.0f;
			mWaitTime = 0.0f;
		}
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

			// �v���C���[���G��Ă����ꍇ�A���̈ʒu�ɖ߂�
			if (mIsCollision)
			{
				Position(mStartPos);
			}
		}
		break;
	}
}

// �X�V
void CFallingObjects::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// �������
	case EState::Falling:
		UpdateFalling();
		break;

	}

	//// �t�F�[�h���Ԃɍ��킹�ď��̃��l�����߂�
	//// ���l��ݒ�
	//float alpha = Math::Clamp01(mFadeTime / FADE_TIME);
	//SetAlpha(alpha);

	// �Փ˃t���O��������
	mIsCollision = false;
}

// �`��
void CFallingObjects::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}