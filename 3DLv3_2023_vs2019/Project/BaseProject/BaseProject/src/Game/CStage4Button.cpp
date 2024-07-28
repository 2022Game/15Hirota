#include "CStage4Button.h"
#include "CCollisionManager.h"
#include "Maths.h"
#include "Easing.h"
#include "CInput.h"
#include "CModel.h"
#include "CTaskManager.h"
#include "CStageManager.h"
#include "CPlayer.h"
#include "COperationUI.h"
#include "CStageManager.h"

// �X�e�[�W1�I���{�^���̃C���X�^���X
CStage4Button* CStage4Button::spInstance = nullptr;

CStage4Button* CStage4Button::Instance()
{
	return spInstance;
}

// �R���X�g���N�^
CStage4Button::CStage4Button(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eButton, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mIsStage4Button(false)
	, mIsPlayerCollision(false)
	, mElapsedTime(0.0f)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// ENTER�L�[�̉摜�\��
	mpEnter = new COperationUI("EnterUI");
	mpEnter->SetShow(false);

	// �X�e�[�W�I�����f�����擾
	mpStage4ButtonModel = CResourceManager::Get<CModel>("StageButton");

	// �X�e�[�W�I�����f���R���C�_�[���쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpStage4ButtonModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CStage4Button::~CStage4Button()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CStage4Button::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	CPlayer* player = CPlayer::Instance();
	bool stage4Start = player->IsStartStage4();

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
				if (stage4Start)
				{
					mIsStage4Button = true;
				}
			}
			mIsPlayerCollision = true;
		}
	}
}

// �X�e�[�W��I���������Ƃ�`����
bool CStage4Button::IsStage4Button()
{
	return mIsStage4Button;
}

// �X�V����
void CStage4Button::Update()
{
	if (mIsStage4Button)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > 0.8f)
		{
			mElapsedTime = 0.0f;
			mIsStage4Button = false;
		}
	}

	CPlayer* player = CPlayer::Instance();
	bool stage4Start = player->IsStartStage4();
	if (!stage4Start)
	{
		SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (mIsPlayerCollision && stage4Start)
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
void CStage4Button::Render()
{
	mpStage4ButtonModel->SetColor(mColor);
	mpStage4ButtonModel->Render(Matrix());
}