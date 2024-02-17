#include "CStageButton.h"
#include "CCollisionManager.h"
#include "Maths.h"
#include "CInput.h"
#include "CStageMenu.h"

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

	mpStageMenu = new CStageMenu();

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CStageButton::~CStageButton()
{
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
			if (!mpStageMenu->IsOpened())
			{
				if (CInput::PushKey(VK_RETURN))
				{
					mpStageMenu->Open();
				}
			}
		}
	}
}

// �X�V����
void CStageButton::Update()
{

}

// �`�揈��
void CStageButton::Render()
{
	mpModel->Render(Matrix());
	mpModel->SetColor(mColor);
}