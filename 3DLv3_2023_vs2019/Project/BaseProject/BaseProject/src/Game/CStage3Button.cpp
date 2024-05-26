#include "CStage3Button.h"
#include "CCollisionManager.h"
#include "Maths.h"
#include "Easing.h"
#include "CInput.h"
#include "CModel.h"
#include "CTaskManager.h"
#include "CStageManager.h"
#include "CPlayer.h"

// �X�e�[�W1�I���{�^���̃C���X�^���X
CStage3Button* CStage3Button::spInstance = nullptr;

CStage3Button* CStage3Button::Instance()
{
	return spInstance;
}

// �R���X�g���N�^
CStage3Button::CStage3Button(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eButton, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mIsStage3Button(false)
	, mElapsedTime(0.0f)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// �X�e�[�W�I�����f�����擾
	mpStage3ButtonModel = CResourceManager::Get<CModel>("StageButton");

	// �X�e�[�W�I�����f���R���C�_�[���쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpStage3ButtonModel, true);
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
CStage3Button::~CStage3Button()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CStage3Button::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
					mIsStage3Button = true;
				}
			}
		}
	}
}

// �X�e�[�W��I���������Ƃ�`����
bool CStage3Button::IsStage3Button()
{
	return mIsStage3Button;
}

// �X�V����
void CStage3Button::Update()
{
	//CDebugPrint::Print("mStage1:%s\n", mIsStage3Button ? "true" : "false");

	if (mIsStage3Button)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > 0.8f)
		{
			mElapsedTime = 0.0f;
			mIsStage3Button = false;
		}
	}

	CPlayer* player = CPlayer::Instance();
	bool stage3Start = player->IsStartStage3();
	if (!stage3Start)
	{
		SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// �`�揈��
void CStage3Button::Render()
{
	mpStage3ButtonModel->SetColor(mColor);
	mpStage3ButtonModel->Render(Matrix());
}