#include "CSeesawObject.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CModel.h"

// �R���X�g���N�^
CSeesawObject::CSeesawObject(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer, const float right, const float left,
	const float rotateRSpeed, const float rotateLSpeed)
	: CObjectBase(ETag::eSeesaw, ETaskPriority::eSeesaw, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mpModel(nullptr)
	, mpCollider(nullptr)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mDeafaultRot(rot)
	, mRight(right)
	, mLeft(left)
	, mRotateRSpeed(rotateRSpeed)
	, mRotateLSpeed(rotateLSpeed)
	, mStateStep(0)
	, mRotationAngle(0.0f)
	, mRotateStartAngle(0.0f)
	, mRotateEndAngle(0.0f)
	, mElapsedTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
{
	Position(pos);
	Scale(scale);
	Rotation(mDeafaultRot);

	// �����ʒu
	mStartPos = Position();
}

// �f�X�g���N�^
CSeesawObject::~CSeesawObject()
{
	SAFE_DELETE(mpCollider);
}

// �Փˏ���
void CSeesawObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// �v���C���[���G�ꂽ
	mIsHitCol = true;

	// �v���C���[�̍��W����V�[�\�[�̍��E�ǂ���Ɉʒu���邩�v�Z
	CVector playerPos = owner->Position();
	// �V�[�\�[�̍��W
	CVector seesawPos = Position();
	// �V�[�\�[����v���C���[�܂ł̃x�N�g�������߂�
	CVector vec = playerPos - seesawPos;
	// �V�[�\�[�̉������̃x�N�g�������߂�
	CVector side = VectorX();
	side.Y(0.0f);
	side.Normalize();
	// 2�̃x�N�g���̓��ς���A
	// �v���C���[���V�[�\�[��̂ǂ��Ɉʒu���邩���߂�
	mHitDir = CVector::Dot(vec, side);
}

bool CSeesawObject::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	bool isHit = CCollider::CollisionRay(mpCollider, start, end, hit);
	// �V�[�\�[�̃R���C�_�[�ɓ���������
	if (isHit)
	{
		return true;
	}

	return false;
}

// ��Ԃ�؂�ւ���
void CSeesawObject::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// �ҋ@��Ԃ̍X�V����
void CSeesawObject::UpdateIdle()
{
	// �v���C���[���V�[�\�[�ɐG��Ă���
	if (mIsHitCol)
	{
		// �Z���^�[�R���C�_�[��true�������炻�̂܂�
		if (abs(mHitDir) <= 10.0f)
		{
			// ���̊p�x��ړI�̊p�x(0�x��)�ݒ�
			mRotateEndAngle = 0.0f;
			mElapsedTime = 0.0f;
		}
		// ���C�g�R���C�_�[�ɓ���������E�ɌX����
		else if (mHitDir < 0.0f)
		{
			// �E�ɌX����(�ړI�̊p�x��right�x�ɐݒ�)
			mRotateEndAngle = mRight;
			mElapsedTime = 0.0f;
		}
		// ���t�g�R���C�_�[�ɓ��������獶�ɌX����
		else if (mHitDir > 0.0f)
		{
			// ���ɌX����(�ړI�̊p�x��-left�x�ɐݒ�)
			mRotateEndAngle = -mLeft;
			mElapsedTime = 0.0f;
		}
	}
	// �V�[�\�[�Ɉ�莞�ԐG��Ă��Ȃ�������A
	// ���̊p�x(0�x�ɖ߂�)
	else
	{
		if (mElapsedTime < 0.1f)
		{
			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			mRotateEndAngle = 0.0f;
		}
	}

	// ���݂̊p�x���ړI�̊p�x��菬�����̂ł���΁A
	if (mRotationAngle < mRotateEndAngle)
	{
		// �p�x�����Z(�E�ɌX����)
		mRotationAngle += mRotateRSpeed * Time::DeltaTime();
		if (mRotationAngle > mRotateEndAngle)
		{
			mRotationAngle = mRotateEndAngle;
		}
	}
	// ���݂̊p�x���ړI�̊p�x��菬�����̂ł���΁A
	else if (mRotationAngle > mRotateEndAngle)
	{
		// �p�x�����Z(���ɌX����)
		mRotationAngle -= mRotateLSpeed * Time::DeltaTime();
		if (mRotationAngle < mRotateEndAngle)
		{
			mRotationAngle = mRotateEndAngle;
		}
	}

	// ���݂̊p�x�𔽉f
	Rotation(mDeafaultRot * CQuaternion(0.0f, 0.0f, mRotationAngle));
}

// �X�V����
void CSeesawObject::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
	case EState::eIdle:		// �ҋ@���
		UpdateIdle();
		break;
	}

	mIsHitCol = false;
}

// �`�揈��
void CSeesawObject::Render()
{
	if (mpModel != nullptr)
	{
		mpModel->SetColor(mColor);
		mpModel->Render(Matrix());
	}
}