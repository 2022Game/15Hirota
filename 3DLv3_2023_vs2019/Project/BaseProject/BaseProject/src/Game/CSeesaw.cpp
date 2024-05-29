#include "CSeesaw.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CModel.h"

// ��]�ɂ����鎞��
#define ROTATE_TIME 1.5f

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
	, mElpasedTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
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
	mElpasedTime = 0.0f;
}

// �ҋ@��Ԃ̍X�V����
void CSeesaw::UpdateIdle()
{
	// �Z���^�[�R���C�_�[��true�������炻�̂܂�
	if (mIsCenterCol)
	{
		// �������Ȃ�
		// ����Ȃ�����
	}
	// ���C�g�R���C�_�[�ɓ���������E�ɌX����
	else if (mIsRightCol)
	{
		mRotateStartAngle = mRotationAngle; // ���݂̊p�x���J�n�p�x�ɐݒ�
		mRotateEndAngle = 45.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eRight);
	}
	// ���t�g�R���C�_�[�ɓ��������獶�ɌX����
	else if (mIsLeftCol)
	{
		mRotateStartAngle = mRotationAngle; // ���݂̊p�x���J�n�p�x�ɐݒ�
		mRotateEndAngle = -45.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eLeft);
	}
	// �V�[�\�[�ɐG��Ă��Ȃ������猳�̊p�x�ɖ߂�
	else
	{
		mRotateStartAngle = mRotationAngle; // ���݂̊p�x���J�n�p�x�ɐݒ�
		mRotateEndAngle = 0.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eReturn);
	}
}

// �E�ɌX���X�V����
void CSeesaw::UpdateRight()
{
	if (mIsLeftCol)
	{
		mRotateStartAngle = mRotationAngle; // ���݂̊p�x���J�n�p�x�ɐݒ�
		mRotateEndAngle = -45.0f;
		//mElpasedTime = 0.0f;
		ChangeState(EState::eLeft);
	}
	
	// ��]�ɂ����鎞�Ԃ��o�߂��Ă��Ȃ�
	if (mElpasedTime < ROTATE_TIME)
	{
		// ��]�J�n���̊p�x���珙�X�ɉ�]�I�����̊p�x�։�]������
		float per = mElpasedTime / ROTATE_TIME;
		float angleZ = Math::Lerp
		(
			mRotateStartAngle,
			mRotateEndAngle,
			per
		);
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, angleZ)));
		mElpasedTime += Time::DeltaTime();
	}
	// ��]�ɂ����鎞�Ԃ��o�߂���
	else
	{
		mRotationAngle = mRotateEndAngle;
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, mRotateEndAngle)));
		if (!mIsRightCol)
		{
			ChangeState(EState::eIdle);
		}
	}
}

// ���ɌX���X�V����
void CSeesaw::UpdateLeft()
{
	if (mIsRightCol)
	{
		mRotateStartAngle = mRotationAngle; // ���݂̊p�x���J�n�p�x�ɐݒ�
		mRotateEndAngle = 45.0f;
		//mElpasedTime = 0.0f;
		ChangeState(EState::eRight);
		return;
	}

	// ��]�ɂ����鎞�Ԃ��o�߂��Ă��Ȃ�
	if (mElpasedTime < ROTATE_TIME)
	{
		// ��]�J�n���̊p�x���珙�X�ɉ�]�I�����̊p�x�։�]������
		float per = mElpasedTime / ROTATE_TIME;
		float angleZ = Math::Lerp
		(
			mRotateStartAngle,
			mRotateEndAngle,
			per
		);
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, angleZ)));
		mElpasedTime += Time::DeltaTime();
	}
	// ��]�ɂ����鎞�Ԃ��o�߂���
	else
	{
		mRotationAngle = mRotateEndAngle;
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, mRotateEndAngle)));
		if (!mIsLeftCol)
		{
			ChangeState(EState::eIdle);
		}
	}
}

// ���ɖ߂��X�V����
void CSeesaw::UpdateReturn()
{
	if (mIsRightCol)
	{
		mRotateStartAngle = mRotationAngle; // ���݂̊p�x���J�n�p�x�ɐݒ�
		mRotateEndAngle = 45.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eRight);
		return;
	}
	else if (mIsLeftCol)
	{
		mRotateStartAngle = mRotationAngle; // ���݂̊p�x���J�n�p�x�ɐݒ�
		mRotateEndAngle = -45.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eLeft);
		return;
	}

	// ��]�ɂ����鎞�Ԃ��o�߂��Ă��Ȃ�
	if (mElpasedTime < ROTATE_TIME)
	{
		// ��]�J�n���̊p�x���珙�X�Ɍ��̊p�x�։�]������
		float per = mElpasedTime / ROTATE_TIME;
		float angleZ = Math::Lerp
		(
			mRotateStartAngle,
			mIsRightCol ? 45.0f : (mIsLeftCol ? -45.0f : 0.0f), // �X���Ă�������̊p�x�ɖ߂�
			per
		);
		mRotationAngle = angleZ; // ���݂̊p�x���X�V
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, angleZ)));
		mElpasedTime += Time::DeltaTime();
	}
	// ��]�ɂ����鎞�Ԃ��o�߂���
	else
	{
		mElpasedTime = 0.0f;
		mRotationAngle = mIsRightCol ? 45.0f : (mIsLeftCol ? -45.0f : 0.0f); // �X���Ă�������̊p�x�ɐݒ�
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, 0.0f)));
		ChangeState(EState::eIdle); // �ҋ@��Ԃɖ߂�
	}
}

// �X�V����
void CSeesaw::Update()
{
	/*CDebugPrint::Print("mIsCenterCol:%s\n", mIsCenterCol ? "true" : "false");
	CDebugPrint::Print("mIsRightCol:%s\n", mIsRightCol ? "true" : "false");
	CDebugPrint::Print("mIsLeftCol:%s\n", mIsLeftCol ? "true" : "false");*/

	CDebugPrint::Print("mRotationAngle:%f\n", mRotationAngle);
	CDebugPrint::Print("mRotateStartAngle:%f\n", mRotateStartAngle);
	CDebugPrint::Print("mRotateEndAngle:%f\n", mRotateEndAngle);

	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
	case EState::eIdle:		// �ҋ@���
		UpdateIdle();
		break;
	case EState::eRight:	// �E�ɌX�����
		UpdateRight();
		break;
	case EState::eLeft:		// ���ɌX�����
		UpdateLeft();
		break;
	case EState::eReturn:	// ���ɖ߂���
		UpdateReturn();
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