#include "CStage2Button.h"
#include "CCollisionManager.h"
#include "Maths.h"
#include "CInput.h"
#include "CModel.h"
#include "CTaskManager.h"
#include "CStageManager.h"
#include "CPlayer.h"
#include "COperationUI.h"
#include "CStageManager.h"

// �X�e�[�W1�I���{�^���̃C���X�^���X
CStage2Button* CStage2Button::spInstance = nullptr;

CStage2Button* CStage2Button::Instance()
{
	return spInstance;
}

// �R���X�g���N�^
CStage2Button::CStage2Button(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eButton, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mIsStage2Button(false)
	, mIsPlayerCollision(false)
	, mElapsedTime(0.0f)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// ENTER�L�[�̉摜�\��
	mpEnter = new COperationUI("EnterUI");
	mpEnter->SetShow(false);

	// �X�e�[�W�I�����f�����擾
	mpStage2ButtonModel = CResourceManager::Get<CModel>("StageButton");

	// �X�e�[�W�I�����f���R���C�_�[���쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpStage2ButtonModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CStage2Button::~CStage2Button()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CStage2Button::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	CPlayer* player = CPlayer::Instance();
	bool stage3Start = player->IsStartStage3();

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
				if (stage3Start)
				{
					mIsStage2Button = true;
				}
			}
			mIsPlayerCollision = true;
		}
	}
}

// �X�e�[�W��I���������Ƃ�`����
bool CStage2Button::IsStage2Button()
{
	return mIsStage2Button;
}

// �X�V����
void CStage2Button::Update()
{
	//CDebugPrint::Print("mStage1:%s\n", mIsStage1Button ? "true" : "false");

	if (mIsStage2Button)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > 0.8f)
		{
			mElapsedTime = 0.0f;
			mIsStage2Button = false;
		}
	}

	CPlayer* player = CPlayer::Instance();
	bool stage2Start = player->IsStartStage2();
	if (!stage2Start)
	{
		SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (mIsPlayerCollision && stage2Start)
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
void CStage2Button::Render()
{
	mpStage2ButtonModel->SetColor(mColor);
	mpStage2ButtonModel->Render(Matrix());
}