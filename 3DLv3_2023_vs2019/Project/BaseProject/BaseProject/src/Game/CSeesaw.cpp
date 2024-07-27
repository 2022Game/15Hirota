#include "CSeesaw.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CModel.h"

// ��]�ɂ����鎞��
#define ROTATE_TIME 2.5f
// �P�b�Ԃɉ�]����p�x
#define ROTATE_SPEED 50.0f

// �R���X�g���N�^
CSeesaw::CSeesaw(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eSeesaw, ETaskPriority::eSeesaw, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mDeafaultRot(rot)
	, mStateStep(0)
	, mRotationAngle(0.0f)
	, mRotateStartAngle(0.0f)
	, mRotateEndAngle(0.0f)
	, mElapsedTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
{
	// �V�[�\�[���f�����擾
	mpSeesawModel = CResourceManager::Get<CModel>("SeesawModel");

	// �V�[�\�[�S�̃R���C�_�[���쐬
	CModel* ceesaw = CResourceManager::Get<CModel>("SeesawModelCol");
	mpSeesawCol = new CColliderMesh(this, ELayer::eField, ceesaw, true);
	mpSeesawCol->SetCollisionLayers({ ELayer::ePlayer });
	mpSeesawCol->SetCollisionTags({ ETag::ePlayer });


	Position(pos);
	Scale(scale);
	Rotation(mDeafaultRot);

	// �����ʒu
	mStartPos = Position();

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CSeesaw::~CSeesaw()
{
	SAFE_DELETE(mpSeesawCol);
}

// �Փˏ���
void CSeesaw::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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

bool CSeesaw::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	bool isHit = CCollider::CollisionRay(mpSeesawCol, start, end, hit);
	// �V�[�\�[�̃R���C�_�[�ɓ���������
	if (isHit)
	{
		return true;
	}

	return false;
}

// ��Ԃ�؂�ւ���
void CSeesaw::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// �ҋ@��Ԃ̍X�V����
void CSeesaw::UpdateIdle()
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
			// �E�ɌX����(�ړI�̊p�x��45�x�ɐݒ�)
			mRotateEndAngle = 50.0f;
			mElapsedTime = 0.0f;
		}
		// ���t�g�R���C�_�[�ɓ��������獶�ɌX����
		else if (mHitDir > 0.0f)
		{
			// ���ɌX����(�ړI�̊p�x��-45�x�ɐݒ�)
			mRotateEndAngle = -50.0f;
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
		mRotationAngle += ROTATE_SPEED * Time::DeltaTime();
		if (mRotationAngle > mRotateEndAngle)
		{
			mRotationAngle = mRotateEndAngle;
		}
	}
	// ���݂̊p�x���ړI�̊p�x��菬�����̂ł���΁A
	else if (mRotationAngle > mRotateEndAngle)
	{
		// �p�x�����Z(���ɌX����)
		mRotationAngle -= ROTATE_SPEED * Time::DeltaTime();
		if (mRotationAngle < mRotateEndAngle)
		{
			mRotationAngle = mRotateEndAngle;
		}
	}

	// ���݂̊p�x�𔽉f
	Rotation(mDeafaultRot * CQuaternion(0.0f, 0.0f, mRotationAngle));
}

// �X�V����
void CSeesaw::Update()
{
	/*CDebugPrint::Print("mIsCenterCol:%s\n", mIsCenterCol ? "true" : "false");
	CDebugPrint::Print("mIsRightCol:%s\n", mIsRightCol ? "true" : "false");
	CDebugPrint::Print("mIsLeftCol:%s\n", mIsLeftCol ? "true" : "false");*/

	/*CDebugPrint::Print("mRotationAngle:%f\n", mRotationAngle);
	CDebugPrint::Print("mRotateStartAngle:%f\n", mRotateStartAngle);
	CDebugPrint::Print("mRotateEndAngle:%f\n", mRotateEndAngle);*/

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
void CSeesaw::Render()
{
	mpSeesawModel->SetColor(mColor);
	mpSeesawModel->Render(Matrix());
}