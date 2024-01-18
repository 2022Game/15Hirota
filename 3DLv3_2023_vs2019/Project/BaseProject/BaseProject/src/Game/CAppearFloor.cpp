#include "CAppearFloor.h"
#include "Maths.h"

// �����̂ɂ����鎞��
#define FADE_TIME 3.0f
// ������̑҂�����
#define WAIT_TIME 3.0f

// �R���X�g���N�^
CAppearFloor::CAppearFloor(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eTransparent)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
{
	// ���̃��f�����擾
	mpModel = CResourceManager::Get<CModel>("FieldCube");

	// ����鏰�̃R���C�_�[�쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer, ELayer::eEnemy });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer, ETag::eEnemy });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);

	SetColor(CColor(1.0f, 0.0f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CAppearFloor::~CAppearFloor()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CAppearFloor::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// �Փ˂��Ă���̂��A��������I�u�W�F�N�g�ł����
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		// ���݂��ҋ@��Ԃł���΁A�t�F�[�h��Ԃ֐؂�ւ���
		if (mState == EState::Idle)
		{
			ChangeState(EState::Appeared);
			mFadeTime = FADE_TIME;
			mWaitTime = WAIT_TIME;
		}

		// ��������I�u�W�F�N�g���G��Ă���̂�
		// �Փ˃t���O���I��
		mIsCollision = true;
	}
}

// ��Ԃ�؂�ւ���
void CAppearFloor::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CAppearFloor::UpdateIdle()
{

}

// ����Ă����Ԃ̍X�V����
void CAppearFloor::UpdateAppeared()
{
	// ��������I�u�W�F�N�g���G��Ă�����
	if (mIsCollision)
	{
		// �X�e�b�v0�����蒼��
		mStateStep = 0;
		mWaitTime = WAIT_TIME;
		mFadeTime = FADE_TIME;
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

// �X�V
void CAppearFloor::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// ����Ă�����
	case EState::Appeared:
		UpdateAppeared();
		break;

	}

	// �t�F�[�h���Ԃɍ��킹�ď��̃��l�����߂�
	// ���l��ݒ�
	float alpha = Math::Clamp01(mFadeTime / FADE_TIME);
	SetAlpha(alpha);

	// �Փ˃t���O��������
	mIsCollision = false;
}

// �`��
void CAppearFloor::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}