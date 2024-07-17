#include "CStage1Button.h"
#include "CCollisionManager.h"
#include "Maths.h"
#include "Easing.h"
#include "CInput.h"
#include "CModel.h"
#include "CTaskManager.h"
#include "CStageManager.h"
#include "COperationUI.h"

// �X�e�[�W1�I���{�^���̃C���X�^���X
CStage1Button* CStage1Button::spInstance = nullptr;

CStage1Button* CStage1Button::Instance()
{
	return spInstance;
}

// �R���X�g���N�^
CStage1Button::CStage1Button(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eButton, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mIsStage1Button(false)
	, mIsPlayerCollision(false)
	, mElapsedTime(0.0f)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// ENTER�L�[�̉摜�\��
	mpEnter = new COperationUI("EnterUI");
	mpEnter->SetShow(false);

	// �X�e�[�W�I�����f�����擾
	mpStage1ButtonModel = CResourceManager::Get<CModel>("StageButton");

	// �X�e�[�W�I�����f���R���C�_�[���쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpStage1ButtonModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CStage1Button::~CStage1Button()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpColliderMesh);
	mpEnter->Kill();
}

// �Փˏ���
void CStage1Button::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
			if (CInput::PushKey(VK_RETURN))
			{
				mIsStage1Button = true;
			}
			mIsPlayerCollision = true;
		}
	}
}

// �X�e�[�W��I���������Ƃ�`����
bool CStage1Button::IsStage1Button()
{
	return mIsStage1Button;
}

// �X�V����
void CStage1Button::Update()
{
	if (mIsStage1Button)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > 0.8f)
		{
			mElapsedTime = 0.0f;
			mIsStage1Button = false;
		}
	}

	if (mIsPlayerCollision)
	{
		mpEnter->SetShow(true);
	}
	else
	{
		mpEnter->SetShow(false);
	}

	// U�L�[�e�L�X�g�摜��\��
	CVector UkeyPos = Position() + CVector(0.0f, 35.0f, 0.0f);
	mpEnter->SetWorldPos(UkeyPos);

	mIsPlayerCollision = false;
}

// �`�揈��
void CStage1Button::Render()
{
	mpStage1ButtonModel->SetColor(mColor);
	mpStage1ButtonModel->Render(Matrix());
}