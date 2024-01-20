#include "CNumberFloor1.h"
#include "Maths.h"
#include "CPlayer.h"

// ������̂ɂ����鎞��
#define FADE_TIME 3.0f
// ��������̑҂�����
#define WAIT_TIME 3.0f

// �R���X�g���N�^
CNumberFloor1::CNumberFloor1(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	:CRideableObject(ETaskPriority::eNumberFalling)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mElapsedTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mCase0End(false)
	, mCase1End(false)
	, mIsCollision(false)
{
	// �����ʒu��ݒ�
	mStartPos = Position();

	// �񐔂ŗ����鏰(3��)�̃��f���擾
	mpModel = CResourceManager::Get<CModel>("Number3");

	// �񐔂ŗ����鏰(3��)�̃R���C�_�[�쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionTag(mReactionTag, true);
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);

	Position(pos);
	Scale(scale);

	mStateStep = 0;
}

// �f�X�g���N�^
CNumberFloor1::~CNumberFloor1()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CNumberFloor1::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
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
			// ���݂��ҋ@��Ԃł���΁A�t�F�[�h��Ԃ֐؂�ւ���
			if (mState == EState::Idle)
			{
				ChangeState(EState::Waiting);
			}
		}
		mIsCollision = true;
	}
}

// �X�e�[�W�J�n���̈ʒu��ݒ�
void CNumberFloor1::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// ��Ԃ�؂�ւ���
void CNumberFloor1::ChangeState(EState state)
{
	mState = state;
	/*mStateStep = 0;*/
}

// �ҋ@��Ԃ̏���
void CNumberFloor1::UpdateIdle()
{

}

// �ҋ@��Ԃ̏���
void CNumberFloor1::UpdateWaiting()
{
	/*if (mIsCollision)
	{
		mStateStep = 0;
		if (mCase0End)
		{
			mStateStep = 1;
		}
		if (mCase1End)
		{
			mStateStep = 2;
		}
	}*/
	
	switch (mStateStep)
	{
		// �X�e�b�v0 �I�u�W�F�N�g�\���̕ύX
	case 0:
	{
		if (!mCase0End)
		{
			mpModel = CResourceManager::Get<CModel>("Number2");

			// �v���C���[�����ꂽ��Idle�ɑJ��
			if (!mIsCollision)
			{
				mCase0End = true;
				ChangeState(EState::Idle);
				mStateStep++;
			}
			break;
		}
		else
		{
			mStateStep++;
		}
		break;
	}
	// �X�e�b�v1 �I�u�W�F�N�g�\���̕ύX
	case 1:
	{
		if (!mCase1End && mCase0End)
		{
			mpModel = CResourceManager::Get<CModel>("Number1");
			
			// �v���C���[�����ꂽ��Idle�ɑJ��
			if (!mIsCollision)
			{
				ChangeState(EState::Idle);
				mStateStep++;
				mCase1End = true;
			}
			break;
		}
		if (!mIsCollision && mCase0End && mCase1End)
		{
			mStateStep++;
		}
		break;
	}
	// �X�e�b�v2 ��ԑJ��
	case 2:
	{
		ChangeState(EState::Falling);
	}
	break;
	}
	CDebugPrint::Print("mCase0: %s\n", mCase0End ? "true" : "false");
	CDebugPrint::Print("mCase1: %s\n", mCase1End ? "true" : "false");
}

// ������Ԃ̍X�V����
void CNumberFloor1::UpdateFalling()
{
	
}

// �X�V����
void CNumberFloor1::Update()
{
	// ���E�̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// �ҋ@���
	case EState::Waiting:
		UpdateWaiting();
		break;
		// �������
	case EState::Falling:
		UpdateFalling();
		break;
	}

	// �Փ˃t���O��������
	mIsCollision = false;

	
	CDebugPrint::Print("mIsCollsion:%s\n", mIsCollision ? "true" : "false");
	CDebugPrint::Print("mStateStep: %d\n", mStateStep);
}

// �`�揈��
void CNumberFloor1::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}