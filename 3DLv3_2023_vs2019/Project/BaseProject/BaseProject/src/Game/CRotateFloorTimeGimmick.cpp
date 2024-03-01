#include "CRotateFloorTimeGimmick.h"
#include "Maths.h"
#include "CPlayer.h"

// �҂�����
#define WAIT_TIME 5.0f

// �R���X�g���N�^
CRotateFloorTimeGimmick::CRotateFloorTimeGimmick(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eRotate)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mWaitTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
	, mNextRotateIsRotate2(false)
{
	// �����ʒu��ݒ�
	mStartPos = Position();

	// �������鏰�g���f�����擾
	mpRotateFrame = CResourceManager::Get<CModel>("RotateFloorFrame");

	// �Dt�N���鏰���f�����擾(�R���C�_�[��)
	mpRotateFloor = CResourceManager::Get<CModel>("RotateFloor");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpRotateFloor, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	ChangeState(EState::Idle);

	Position(pos);
	Scale(scale);

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CRotateFloorTimeGimmick::~CRotateFloorTimeGimmick()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CRotateFloorTimeGimmick::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;
}

// �X�e�[�W�̊J�n���̈ʒu��ݒ�
void CRotateFloorTimeGimmick::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// ��Ԃ�؂�ւ���
void CRotateFloorTimeGimmick::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
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
			ChangeState(EState::Rotate1);
		}
		else {
			ChangeState(EState::Rotate2);
		}
	}
	CDebugPrint::Print("WaitTime:%f\n", mWaitTime);
}

// ��]��Ԃ̍X�V����1
void CRotateFloorTimeGimmick::UpdateRotate1()
{
	// 1�b�Ԃ�90�x��]����ꍇ�̉�]���x���v�Z
	float rotationSpeed = 130.0f / 60.0f; // 1�b�Ԃ�130�x��]�i60�t���[����1�b�j

	// ���[�Ɉړ�
	Translate(CVector(25.0f, 15.0f, 0.0f));
	// ��]����
	Rotate(CVector(0.0f, 0.0f, rotationSpeed));
	Translate(CVector(-25.0f, -15.0f, 0.0f));

	// ���݂̉�]�p�x���擾
	float currentRotationAngle = GetCurrentRotationAngle();

	// �ڕW�̉�]�p�x��180�x�̏ꍇ
	float targetRotationAngle = 180.0f;

	// Z������̉�]�p�x���ڕW�̊p�x�ɒB���������m�F
	if (currentRotationAngle >= targetRotationAngle - 1.0f && currentRotationAngle <= targetRotationAngle + 1.0f) {
		// �ڕW�̊p�x�ɒB�������]���~���AIdle��ԂɕύX
		Rotate(CVector(0.0f, 0.0f, 0.0f)); // ��]���x���[���ɐݒ肵�Ē�~
		ChangeState(EState::Idle);
		mWaitTime = WAIT_TIME;
	}
}

// ��]��Ԃ̍X�V����2
void CRotateFloorTimeGimmick::UpdateRotate2()
{
	// 1�b�Ԃ�90�x��]����ꍇ�̉�]���x���v�Z
	float rotationSpeed = 130.0f / 60.0f; // 1�b�Ԃ�130�x��]�i60�t���[����1�b�j

	// ���[�Ɉړ�
	Translate(CVector(25.0f, 15.0f, 0.0f));
	// ��]����
	Rotate(CVector(0.0f, 0.0f, -rotationSpeed));
	Translate(CVector(-25.0f, -15.0f, 0.0f));

	// ���݂̉�]�p�x���擾
	float currentRotationAngle = GetCurrentRotationAngle();

	// �ڕW�̉�]�p�x��180�x�̏ꍇ
	float targetRotationAngle = 0.0f;

	// Z������̉�]�p�x���ڕW�̊p�x�ɒB���������m�F
	if (currentRotationAngle >= targetRotationAngle - 1.0f && currentRotationAngle <= targetRotationAngle + 1.0f) {
		// �ڕW�̊p�x�ɒB�������]���~���AIdle��ԂɕύX
		// ��]���x���[���ɐݒ肵�Ē�~
		Rotate(CVector(0.0f, 0.0f, 0.0f));
		ChangeState(EState::Idle);
		mWaitTime = WAIT_TIME;
	}
}

// ���݂̉�]�l�̎擾
float CRotateFloorTimeGimmick::GetCurrentRotationAngle() const
{
	// �N�H�[�^�j�I������I�C���[�p�ɕϊ����AZ������̉�]�p�x���擾
	return GetWorldRotation().Euler().Z();
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
	case EState::Rotate1:
		UpdateRotate1();
		break;
		// ��]���2
	case EState::Rotate2:
		UpdateRotate2();
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
	mpRotateFrame->SetColor(mColor);
	mpRotateFrame->Render(Matrix());
}