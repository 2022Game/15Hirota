#include "CRotateFloorTimeGimmick.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CModel.h"

// �҂�����
#define WAIT_TIME 3.0f
// ��]���̉�]�ɏ���k�鎞��
#define ROTATE_TIME 0.6f

// �R���X�g���N�^
CRotateFloorTimeGimmick::CRotateFloorTimeGimmick(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eField, ETaskPriority::eRotate, 0, ETaskPauseType::eGame)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mDefaultRot(rot)
	, mStateStep(0)
	, mWaitTime(0.0f)
	, mRotationAngle(0.0f)
	, mRotateStartAngle(0.0f)
	, mRotateEndAngle(0.0f)
	, mElapsedTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
	, mNextRotateIsRotate2(false)
{
	// ��]���鏰���f�����擾(�R���C�_�[��)
	mpRotateFloor = CResourceManager::Get<CModel>("RotateFloor");

	// ��]���鏰�̕\���̃R���C�_�[���쐬
	CModel* frontCol = CResourceManager::Get<CModel>("RotateFloorFrontCol");
	mpFrontFloorCol = new CColliderMesh(this, ELayer::eField, frontCol, true);
	mpFrontFloorCol->SetCollisionLayers({ ELayer::ePlayer });
	mpFrontFloorCol->SetCollisionTags({ ETag::ePlayer });

	// ��]���鏰�̗������쐬
	CModel* backCol = CResourceManager::Get<CModel>("RotateFloorBackCol");
	mpBackFloorCol = new CColliderMesh(this, ELayer::eField, backCol, true);
	mpBackFloorCol->SetCollisionLayers({ ELayer::ePlayer });
	mpBackFloorCol->SetCollisionTags({ ETag::ePlayer });
	ChangeState(EState::Idle);

	// �ŏ��͕\�����I���A�����̓I�t
	mpFrontFloorCol->SetEnable(true);
	mpBackFloorCol->SetEnable(false);

	ChangeState(EState::Idle);

	Position(pos);
	Scale(scale);
	Rotation(mDefaultRot);

	// �����ʒu��ݒ�
	mStartPos = Position();

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CRotateFloorTimeGimmick::~CRotateFloorTimeGimmick()
{
	SAFE_DELETE(mpFrontFloorCol);
	SAFE_DELETE(mpBackFloorCol);
}

// �Փˏ���
void CRotateFloorTimeGimmick::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;
}

// ��Ԃ�؂�ւ���
void CRotateFloorTimeGimmick::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mWaitTime = WAIT_TIME;
}

// ��]��Ԃ�؂�ւ���
void CRotateFloorTimeGimmick::ChangeRotationState()
{
	mNextRotateIsRotate2 = !mNextRotateIsRotate2;
}

// �ҋ@��Ԃ̏���
void CRotateFloorTimeGimmick::UpdateIdle()
{
	mWaitTime -= Time::DeltaTime();
	if (mWaitTime <= 0.0f)
	{
		ChangeRotationState();
		// ���݂̉�]��Ԃɉ����ēK�؂ȏ�Ԃ�ݒ�
		if (mNextRotateIsRotate2) {
			mRotateStartAngle = 0.0f;
			mRotateEndAngle = 180.0f;
		}
		else {
			mRotateStartAngle = 180.0f;
			mRotateEndAngle = 0.0f;
		}
		mElapsedTime = 0.0f;
		ChangeState(EState::Rotate);
	}
	//CDebugPrint::Print("WaitTime:%f\n", mWaitTime);
}


// ��]��Ԃ̍X�V����
void CRotateFloorTimeGimmick::UpdateRotate()
{
	// ��]�ɂ����鎞�Ԃ��o�߂��Ă��Ȃ�
	if (mElapsedTime < ROTATE_TIME)
	{
		// ��]�J�n���̊p�x���珙�X�ɉ�]�I�����̊p�x�։�]����
		float per = mElapsedTime / ROTATE_TIME;
		float angleZ = Math::Lerp
		(mRotateStartAngle,
			mRotateEndAngle,
			per
		);
		Rotation(mDefaultRot * CQuaternion(CVector(0.0f, 0.0f, angleZ)));
		mElapsedTime += Time::DeltaTime();

		// ��]���鏰�̊p�x��90�x�ȉ��ł���΁A
		if (fabsf(angleZ) <= 90.0f)
		{
			// ���̃R���C�_�[�̕\�����I���ɂ��āA�������I�t�ɂ���
			mpFrontFloorCol->SetEnable(true);
			mpBackFloorCol->SetEnable(false);
		}
		// ��]���鏰�̊p�x��90�x���z����΁A
		else
		{
			// ���̃R���C�_�[�̗������I���ɂ��āA�\�����I�t�ɂ���
			mpFrontFloorCol->SetEnable(false);
			mpBackFloorCol->SetEnable(true);
		}
	}
	// ��]�ɂ����鎞�Ԃ��o�߂���
	else
	{
		mElapsedTime = 0.0f;
		mWaitTime = WAIT_TIME;
		Rotation(mDefaultRot * CQuaternion(CVector(0.0f, 0.0f, mRotateEndAngle)));
		ChangeState(EState::Idle);
	}
}

// �X�V
void CRotateFloorTimeGimmick::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// ��]���1
	case EState::Rotate:
		UpdateRotate();
		break;
	}

	// �Փ˃t���O��������
	mIsCollision = false;
}

// �`��
void CRotateFloorTimeGimmick::Render()
{
	mpRotateFloor->SetColor(mColor);
	mpRotateFloor->Render(Matrix());
}