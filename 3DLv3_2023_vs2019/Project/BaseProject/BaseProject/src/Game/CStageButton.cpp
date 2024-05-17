#include "CStageButton.h"
#include "CCollisionManager.h"
#include "Maths.h"
#include "CInput.h"
#include "CStageMenu.h"
#include "CStageManager.h"
#include "CModel.h"
#include "CTaskManager.h"

// �R���X�g���N�^
CStageButton::CStageButton(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mpStageMenu(nullptr)
{
	// �X�e�[�W�I�����f�����擾
	mpModel = CResourceManager::Get<CModel>("StageButton");

	// �X�e�[�W�I�����f���R���C�_�[���쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	// �X�e�[�W���j���[���쐬���A
	// �X�e�[�W���j���[�̃^�X�N�����݂̃X�e�[�W�̃^�X�N���X�g�ɒǉ�
	mpStageMenu = new CStageMenu();
	CStageManager::AddTask(mpStageMenu);

	//SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CStageButton::~CStageButton()
{
	CStageManager::RemoveTask(mpStageMenu);
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CStageButton::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
			bool paused = CTaskManager::Instance()->IsPaused();
			if (!mpStageMenu->IsOpened())
			{
				if (!paused)
				{
					if (CInput::PushKey(VK_RETURN))
					{
						mpStageMenu->Open();
					}
				}
			}
		}
	}
}

// �X�V����
void CStageButton::Update()
{
	//CDebugPrint::Print("color: %f %f %f %f\n", mColor.R(), mColor.G(), mColor.B(), mColor.A());
}

// �`�揈��
void CStageButton::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}