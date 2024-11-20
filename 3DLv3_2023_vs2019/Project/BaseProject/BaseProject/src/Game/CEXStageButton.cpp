#include "CEXStageButton.h"
#include "CCollisionManager.h"
#include "Maths.h"
#include "Easing.h"
#include "CInput.h"
#include "CModel.h"
#include "CTaskManager.h"
#include "CStageManager.h"
#include "COperationUI.h"

// EX�X�e�[�W�I���{�^���̃C���X�^���X
CEXStageButton* CEXStageButton::spInstance = nullptr;

CEXStageButton* CEXStageButton::Instance()
{
	return spInstance;
}

CEXStageButton::CEXStageButton(const CVector& pos, const CVector& scale, const CVector& rot, ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eButton, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mIsEXStageButton(false)
	, mIsPlayerCollision(false)
	, mElapsedTime(0.0f)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// ENTER�L�[�̉摜�\��
	mpEnter = new COperationUI("EnterUI");
	mpEnter->SetShow(false);

	// �X�e�[�W�I�����f�����擾
	mpEXStageButtonModel = CResourceManager::Get<CModel>("StageButton");

	// �X�e�[�W�I�����f���R���C�_�[���쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpEXStageButtonModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CEXStageButton::~CEXStageButton()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpColliderMesh);
	mpEnter->Kill();
}

void CEXStageButton::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
				mIsEXStageButton = true;
			}
			mIsPlayerCollision = true;
		}
	}
}

bool CEXStageButton::IsEXStageButton()
{
	return mIsEXStageButton;
}

void CEXStageButton::Update()
{
	if (mIsEXStageButton)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > 0.8f)
		{
			mElapsedTime = 0.0f;
			mIsEXStageButton = false;
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

void CEXStageButton::Render()
{
	mpEXStageButtonModel->SetColor(mColor);
	mpEXStageButtonModel->Render(Matrix());
}