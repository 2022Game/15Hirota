#include "CRotateFloorGimmick.h"
#include "Maths.h"
#include "CPlayer.h"

CPlayer* playerInstance = CPlayer::Instance();

// �R���X�g���N�^
CRotateFloorGimmick::CRotateFloorGimmick(const CVector& pos, const CVector& scale,
	 ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eRotate)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mRotationAngle(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
	, mIsJumping(false)
	, mNextRotateIsRotate2(false)
{
	// �����ʒu��ݒ�
	mStartPos = Position();

	// ��]���鏰�g���f�����擾
	mpRotateFrame = CResourceManager::Get<CModel>("RotateFloorFrame");

	// ��]���鏰���f�����擾(�R���C�_�[��)
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
CRotateFloorGimmick::~CRotateFloorGimmick()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CRotateFloorGimmick::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;
}

// �X�e�[�W�J�n���̈ʒu��ݒ�
void CRotateFloorGimmick::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// ��Ԃ�؂�ւ���
void CRotateFloorGimmick::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// ��]��Ԃ�؂�ւ���
void CRotateFloorGimmick::ChangeRotationState() {
	mNextRotateIsRotate2 = !mNextRotateIsRotate2;
}

// �ҋ@��Ԃ̏���
void CRotateFloorGimmick::UpdateIdle()
{
	CPlayer* player = CPlayer::Instance();
	bool isPlayerJumping = player->IsJumping();
	if (isPlayerJumping && IsFoundPlayer() && !mIsJumping) {
		// �v���C���[���W�����v���Ă��邩�ǂ������g�p���Ĕ��ʏ������s��
		mIsJumping = true;
		ChangeRotationState(); // ��]��Ԃ�؂�ւ�
		 // ���݂̉�]��Ԃɉ����ēK�؂ȏ�Ԃ�ݒ�
		if (mNextRotateIsRotate2) {
			ChangeState(EState::Rotate1);
		}
		else {
			ChangeState(EState::Rotate2);
		}
	}
}

// ��]��Ԃ̍X�V����1
void CRotateFloorGimmick::UpdateRotateStart()
{
	// �ڕW�̉�]�p�x��0�x�̏ꍇ
	float targetRotationAngle = 180.0f;

	float totalNumberOfFrames = 180.0f / 15.0f;	// * 60.0f / 4.0f

	// ���݂̉�]�p�x���擾
	float currentRotationAngle = GetCurrentRotationAngle();

	// �ڕW�̉�]�p�x�ƌ��݂̉�]�p�x�̍����v�Z
	float rotationDifference = targetRotationAngle - currentRotationAngle;

	// ��]���x��1�t���[�����Ƃ̉�]�ʂɔ��f
	float rotationSpeedPerFrame = rotationDifference / totalNumberOfFrames;

	// ���[�Ɉړ�
	Translate(CVector(25.0f, 15.0f, 0.0f));
	// ��]����
	Rotate(CVector(0.0f, 0.0f, rotationSpeedPerFrame));
	Translate(CVector(-25.0f, -15.0f, 0.0f));

	// �ڕW�p�x�𐳋K������
	while (targetRotationAngle < 0.0f)
	{
		targetRotationAngle += 360.0f;
	}
	while (targetRotationAngle >= 360.0f)
	{
		targetRotationAngle -= 360.0f;
	}

	const float rotationThreshold = 1.0f;

	// Z������̉�]�p�x���ڕW�̊p�x�ɒB���������m�F
	if (fabs(currentRotationAngle - targetRotationAngle) <= rotationThreshold)
	{
		// �ڕW�̊p�x�ɒB�������]���~���AIdle��ԂɕύX
		// ��]���x���[���ɐݒ肵�Ē�~
		Rotate(CVector(0.0f, 0.0f, 0.0f));
		ChangeState(EState::Idle);
		mIsJumping = false;
	}
}

// ��]��Ԃ̍X�V����2
void CRotateFloorGimmick::UpdateRotateEnd()
{
	// �ڕW�̉�]�p�x��0�x�̏ꍇ
	float targetRotationAngle = 0.0f;

	float totalNumberOfFrames = 180.0f / 15.0f;	// * 60.0f / 4.0f

	// ���݂̉�]�p�x���擾
	float currentRotationAngle = GetCurrentRotationAngle();

	// �ڕW�̉�]�p�x�ƌ��݂̉�]�p�x�̍����v�Z
	float rotationDifference = targetRotationAngle - currentRotationAngle;

	// ��]���x��1�t���[�����Ƃ̉�]�ʂɔ��f
	float rotationSpeedPerFrame = rotationDifference / totalNumberOfFrames;

	// ���[�Ɉړ�
	Translate(CVector(25.0f, 15.0f, 0.0f));
	// ��]����
	Rotate(CVector(0.0f, 0.0f, rotationSpeedPerFrame));
	Translate(CVector(-25.0f, -15.0f, 0.0f));

	// �ڕW�p�x�𐳋K������
	while (targetRotationAngle < 0.0f)
	{
		targetRotationAngle += 360.0f;
	}
	while (targetRotationAngle >= 360.0f)
	{
		targetRotationAngle -= 360.0f;
	}

	const float rotationThreshold = 1.0f;

	// Z������̉�]�p�x���ڕW�̊p�x�ɒB���������m�F
	if (fabs(currentRotationAngle - targetRotationAngle) <= rotationThreshold)
	{
		// �ڕW�̊p�x�ɒB�������]���~���AIdle��ԂɕύX
		// ��]���x���[���ɐݒ肵�Ē�~
		Rotate(CVector(0.0f, 0.0f, 0.0f));
		ChangeState(EState::Idle);
		mIsJumping = false;
	}
}

// ���݂̉�]�l�̎擾
float CRotateFloorGimmick::GetCurrentRotationAngle() const
{
	// �N�H�[�^�j�I������I�C���[�p�ɕϊ����AZ������̉�]�p�x���擾
	float rotationAngle = GetWorldRotation().Euler().Z();
	// �p�x�������̏ꍇ�͐��K������
	while (rotationAngle < 0.0f)
	{
		rotationAngle += 360.0f;
	}
	// �p�x��360�x�𒴂����ꍇ�͐��K������
	while (rotationAngle >= 360.0f)
	{
		rotationAngle -= 360.0f;
	}
	return rotationAngle;
}

// �X�V
void CRotateFloorGimmick::Update()
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
		UpdateRotateStart();
		break;
		// ��]���2
	case EState::Rotate2:
		UpdateRotateEnd();
		break;
	}

	// �Փ˃t���O��������
	mIsCollision = false;
}

// �`��
void CRotateFloorGimmick::Render()
{
	mpRotateFloor->SetColor(mColor);
	mpRotateFloor->Render(Matrix());
	mpRotateFrame->SetColor(mColor);
	mpRotateFrame->Render(Matrix());
}

//�v���C���[����������
bool CRotateFloorGimmick::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector object = Position();

	// �v���C���[�Ƃ̋������v�Z����
	float distance = (playerPos - object).Length();
	const float detectionRadius = 100.0f;

	// �v���C���[�Ƃ̋��������o���a�ȓ��ł���΁A�v���C���[��F������
	if (distance <= detectionRadius)
	{
		return true;
	}

	return false;
}