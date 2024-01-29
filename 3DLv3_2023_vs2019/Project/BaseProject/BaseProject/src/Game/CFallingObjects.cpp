#include "CFallingObjects.h"
#include "Maths.h"
#include "CPlayer.h"

// ������̂ɂ����鎞��
#define FADE_TIME 3.0f
// ��������̑҂�����
#define WAIT_TIME 3.0f
// ���������̍Œ�l
#define MINHEIGHT -30.0f

// �R���X�g���N�^
CFallingObjects::CFallingObjects(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eFalling)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
{
	// �����ʒu��ݒ�
	mStartPos = Position();

	// �������鏰���f�����擾
	mpModel = CResourceManager::Get<CModel>("FieldCube");

	// �������鏰�̃R���C�_�[�쐬
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
			ChangeState(EState::Falling);
			mWaitTime = WAIT_TIME;
		}

		// ��������I�u�W�F�N�g���G��Ă���̂�
		// �Փ˃t���O���I��
		mIsCollision = true;
	}
}

// �X�e�[�W�J�n���̈ʒu��ݒ�
void CFallingObjects::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
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

// ������Ԃ̍X�V����
void CFallingObjects::UpdateFalling()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (mStateStep)
	{
		// �X�e�b�v0 �t�F�[�h��̑҂�����
	case 0:
		// �҂����Ԃ��o�߂��Ă��Ȃ���΁A�o�ߎ��ԕ����炷
		if (Position().Y() > MINHEIGHT)
		{
			// ���~
			float fallSpeed = 50.0f;

			mMoveSpeed = CVector(0.0f, -fallSpeed * Time::DeltaTime(), 0.0f);
			Position(Position() + mMoveSpeed);
		}
		// �ő�l���z������
		else
		{
			mpColliderMesh->SetEnable(false);
			SetAlpha(0.0f);
			mStateStep++;
		}
		break;
		// �X�e�b�v1 �I�u�W�F�N�g���^������
	case 1:
	{
		// �ő�l�ɂȂ����瓖���蔻���
		// �`�������
		if (Position().Y() <= MINHEIGHT)
		{
			if (mWaitTime > 0.0f)
			{
				
				mWaitTime -= Time::DeltaTime();
				//CDebugPrint::Print("mWaitTime %f\n", mWaitTime);
			}
			// �҂����Ԃ��o�߂�����A���̃X�e�b�v��
			else
			{
				mStateStep++;
			}
		}
	}
		break;
	case 2:
	{
		// �ʒu���ŏ��̈ʒu�ɖ߂���
		// �`����ĊJ����
		Position(mStartPos);
		mpColliderMesh->SetEnable(true);
		SetAlpha(1.0f);
		mWaitTime = 0.0f;

		// �ҋ@��Ԃ֖߂�
		ChangeState(EState::Idle);
	}
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

	// �Փ˃t���O��������
	mIsCollision = false;
}

// �`��
void CFallingObjects::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}