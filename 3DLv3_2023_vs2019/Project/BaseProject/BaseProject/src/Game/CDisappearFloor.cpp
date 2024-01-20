#include "CDisappearFloor.h"
#include "Maths.h"

// ������̂ɂ����鎞��
#define FADE_TIME 3.0f
// ��������̑҂�����
#define WAIT_TIME 3.0f

// �R���X�g���N�^
CDisappearFloor::CDisappearFloor(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eTransparent)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
{
	// �����鏰�̃��f���擾
	mpModel = CResourceManager::Get<CModel>("FieldCube");

	// �����鏰�̃R���C�_�[�쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionTag(mReactionTag, true);
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);

	Position(pos);
	Scale(scale);

	SetColor(CColor(1.0f, 0.0f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CDisappearFloor::~CDisappearFloor()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CDisappearFloor::Collision(CCollider* slef, CCollider* other, const CHitInfo& hit)
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
				ChangeState(EState::Fade);
			}
		}
	}
}

// ��Ԃ�؂�ւ���
void CDisappearFloor::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CDisappearFloor::UpdateIdle()
{

}

// �t�F�[�h���̍X�V����
void CDisappearFloor::UpdateFade()
{
	// �t�F�[�h���Ԃ��o���Ă��Ȃ�
	if (mFadeTime < FADE_TIME)
	{
		// �o�ߎ��Ԃ����Z
		mFadeTime += Time::DeltaTime();
	}
	// �t�F�[�h���Ԃ��o�߂���
	else
	{
		// �t�F�[�h��̑҂������֑J��
		ChangeState(EState::Wait);
		mFadeTime = FADE_TIME;
		mWaitTime = WAIT_TIME;

		// ���S�ɏ������^�C�~���O��
		// �R���C�_�[���I�t�ɂ��āA���Ȃ��悤�ɂ���
		mpColliderMesh->SetEnable(false);
	}
}

// �t�F�[�h��̒�����
void CDisappearFloor::UpdateWait()
{
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

			// ���̏�Ԃɖ߂����^�C�~���O��
			// �R���C�_�[���I���ɂ��āA����悤�ɂ���
			mpColliderMesh->SetEnable(true);
		}
		break;
	}
}

// �X�V
void CDisappearFloor::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// �t�F�[�h��
	case EState::Fade:
		UpdateFade();
		break;
		// �t�F�[�h��̑҂�
	case EState::Wait:
		UpdateWait();
		break;
	}

	// �t�F�[�h���Ԃɍ��킹�ď��̃��l�����߂�
	// ���l��ݒ�
	float alpha = 1.0f - Math::Clamp01(mFadeTime / FADE_TIME);
	SetAlpha(alpha);
}

// �`��
void CDisappearFloor::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}