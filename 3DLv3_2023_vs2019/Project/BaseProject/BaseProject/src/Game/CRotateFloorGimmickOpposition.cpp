#include "CRotateFloorGimmickOpposition.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CModel.h"

// ��]���̉�]�ɂ����鎞��
#define ROTATE_TIME 0.5f

// �R���X�g���N�^
CRotateFloorGimmickOpposition::CRotateFloorGimmickOpposition(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eField, ETaskPriority::eRotate, 0, ETaskPauseType::eGame)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mDefaultRot(rot)
	, mStateStep(0)
	, mRotationAngle(0.0f)
	, mRotateStartAngle(0.0f)
	, mRotateEndAngle(0.0f)
	, mElapsedTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
	, mIsJumping(false)
	, mNextRotateIsRotate2(false)
{
	// ��]���鏰���f�����擾(�R���C�_�[��)
	mpRotateFloor = CResourceManager::Get<CModel>("RotateFloorOpposition");

	// ��]���鏰�̕\���̃R���C�_�[���쐬
	CModel* frontCol = CResourceManager::Get<CModel>("RotateFloorFrontColOpposition");
	mpFrontFloorCol = new CColliderMesh(this, ELayer::eField, frontCol, true);
	mpFrontFloorCol->SetCollisionLayers({ ELayer::ePlayer });
	mpFrontFloorCol->SetCollisionTags({ ETag::ePlayer });

	// ��]���鏰�̗������쐬
	CModel* backCol = CResourceManager::Get<CModel>("RotateFloorBackColOpposition");
	mpBackFloorCol = new CColliderMesh(this, ELayer::eField, backCol, true);
	mpBackFloorCol->SetCollisionLayers({ ELayer::ePlayer });
	mpBackFloorCol->SetCollisionTags({ ETag::ePlayer });
	ChangeState(EState::Idle);

	// �ŏ��͕\�����I���A�����̓I�t
	mpFrontFloorCol->SetEnable(true);
	mpBackFloorCol->SetEnable(false);

	Position(pos);
	Scale(scale);
	Rotation(mDefaultRot);

	// �����ʒu��ݒ�
	mStartPos = Position();

	SetColor(CColor(1.0f, 0.5f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CRotateFloorGimmickOpposition::~CRotateFloorGimmickOpposition()
{
	SAFE_DELETE(mpFrontFloorCol);
	SAFE_DELETE(mpBackFloorCol);
}

// �Փˏ���
void CRotateFloorGimmickOpposition::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;
}

// ��Ԃ�؂�ւ���
void CRotateFloorGimmickOpposition::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// ��]��Ԃ�؂�ւ���
void CRotateFloorGimmickOpposition::ChangeRotationState() {
	mNextRotateIsRotate2 = !mNextRotateIsRotate2;
}

// �ҋ@��Ԃ̏���
void CRotateFloorGimmickOpposition::UpdateIdle()
{
	CPlayer* player = CPlayer::Instance();
	bool isPlayerJumping = player->IsJumping();
	if (!isPlayerJumping)
	{
		mIsJumping = false;
	}

	if (isPlayerJumping && /*IsFoundPlayer() &&*/ !mIsJumping) {
		// �v���C���[���W�����v���Ă��邩�ǂ������g�p���Ĕ��ʏ������s��
		mIsJumping = true;
		ChangeRotationState(); // ��]��Ԃ�؂�ւ�
		 // ���݂̉�]��Ԃɉ����ēK�؂ȏ�Ԃ�ݒ�
		if (mNextRotateIsRotate2) {
			mRotateStartAngle = 0.0f;
			mRotateEndAngle = -180.0f;
		}
		else {
			mRotateStartAngle = -180.0f;
			mRotateEndAngle = 0.0f;
		}
		mElapsedTime = 0.0f;
		ChangeState(EState::Rotate);
	}
}

// ��]��Ԃ̍X�V����
void CRotateFloorGimmickOpposition::UpdateRotate()
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
		Rotation(mDefaultRot * CQuaternion(CVector(0.0f, 0.0f, mRotateEndAngle)));
		ChangeState(EState::Idle);

		CPlayer* player = CPlayer::Instance();
		bool isPlayerJumping = player->IsJumping();
		if (!isPlayerJumping)
		{
			mIsJumping = false;
		}
	}
}

// �X�V
void CRotateFloorGimmickOpposition::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
	case EState::Rotate:
		UpdateRotate();
		break;
	}

	// �Փ˃t���O��������
	mIsCollision = false;
}

// �`��
void CRotateFloorGimmickOpposition::Render()
{
	mpRotateFloor->SetColor(mColor);
	mpRotateFloor->Render(Matrix());
}

//�v���C���[����������
bool CRotateFloorGimmickOpposition::IsFoundPlayer() const
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