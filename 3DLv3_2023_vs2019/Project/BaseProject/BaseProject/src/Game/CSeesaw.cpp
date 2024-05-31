#include "CSeesaw.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CModel.h"

// ��]�ɂ����鎞��
#define ROTATE_TIME 1.5f
// �P�b�Ԃɉ�]����p�x
#define ROTATE_SPEED 30.0f

// �R���X�g���N�^
CSeesaw::CSeesaw(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eField, ETaskPriority::eSeesaw, 0, ETaskPauseType::eGame)
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
	, mIsCenterCol(false)
	, mIsRightCol(false)
	, mIsLeftCol(false)
{
	// �V�[�\�[���f�����擾
	mpSeesawModel = CResourceManager::Get<CModel>("SeesawModel");

	// �V�[�\�[�Z���^�[�R���C�_�[���쐬
	CModel* center = CResourceManager::Get<CModel>("centerCol");
	mpCenterCol = new CColliderMesh(this, ELayer::eField, center, true);
	mpCenterCol->SetCollisionLayers({ ELayer::ePlayer });
	mpCenterCol->SetCollisionTags({ ETag::ePlayer });

	// �V�[�\�[���C�g�R���C�_�[���쐬
	CModel* right = CResourceManager::Get<CModel>("rightCol");
	mpRightCol = new CColliderMesh(this, ELayer::eField, right, true);
	mpRightCol->SetCollisionLayers({ ELayer::ePlayer });
	mpRightCol->SetCollisionTags({ ETag::ePlayer });

	// �V�[�\�[���t�g�R���C�_�[���쐬
	CModel* left = CResourceManager::Get<CModel>("leftCol");
	mpLeftCol = new CColliderMesh(this, ELayer::eField, left, true);
	mpLeftCol->SetCollisionLayers({ ELayer::ePlayer });
	mpLeftCol->SetCollisionTags({ ETag::ePlayer });

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
	SAFE_DELETE(mpCenterCol);
	SAFE_DELETE(mpRightCol);
	SAFE_DELETE(mpLeftCol);
}

// �Փˏ���
void CSeesaw::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// �Z���^�[�R���C�_�[�ɓ���������
	if (self == mpCenterCol)
	{
		mIsCenterCol = true;
	}
	// ���C�g�R���C�_�[�ɓ���������
	else if (self == mpRightCol)
	{
		mIsRightCol = true;
	}
	// ���t�g�R���C�_�[�ɓ���������
	else if (self == mpLeftCol)
	{
		mIsLeftCol = true;
	}
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
	// �Z���^�[�R���C�_�[��true�������炻�̂܂�
	if (mIsCenterCol)
	{
		// ���̊p�x��ړI�̊p�x(0�x��)�ݒ�
		mRotateEndAngle = 0.0f;
		mElapsedTime = 0.0f;
	}
	// ���C�g�R���C�_�[�ɓ���������E�ɌX����
	else if (mIsRightCol)
	{
		// �E�ɌX����(�ړI�̊p�x��45�x�ɐݒ�)
		mRotateEndAngle = 45.0f;
		mElapsedTime = 0.0f;
	}
	// ���t�g�R���C�_�[�ɓ��������獶�ɌX����
	else if (mIsLeftCol)
	{
		// ���ɌX����(�ړI�̊p�x��-45�x�ɐݒ�)
		mRotateEndAngle = -45.0f;
		mElapsedTime = 0.0f;
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

	mIsCenterCol = false;
	mIsRightCol = false;
	mIsLeftCol = false;
}

// �`�揈��
void CSeesaw::Render()
{
	mpSeesawModel->SetColor(mColor);
	mpSeesawModel->Render(Matrix());
}