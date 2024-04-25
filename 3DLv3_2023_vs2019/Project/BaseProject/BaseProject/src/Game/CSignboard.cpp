#include "CSignboard.h"
#include "CGamePause.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CSignboardPause.h"
#include "Maths.h"
#include "CSignboardUI.h"
#include "CModel.h"

// �v���C���[�̃C���X�^���X
CSignboard* CSignboard::spInstance = nullptr;

// �C���X�^���X�̃|�C���^�̎擾
CSignboard* CSignboard::Instance()
{
	return spInstance;
}

#define _USE_MATH_DEFINES

// ����̊p�x(�[�p�x+�p�x���o)
#define FOV_ANGLE 100.0f
// �v���C���[�܂ł̋���
#define ATTACK_RANGE 70.0f


// �R���X�g���N�^
CSignboard::CSignboard(const CVector& position, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: mReactionLayer(reactionLayer)
	, mReactionTag(reactionTag)
	, mState(EState::Idle)
	, mIsPaused(false)
{
	// �Ŕ��f���擾
	mpModel = CResourceManager::Get<CModel>("Signboard");

	// U�L�[�̃e�L�X�g�摜�擾
	mpUkye = new CSignboardUI();
	mpUkye->SetCenterRatio(CVector2(0.5f, 0.0f));

	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// �Ŕ��f���R���C�_�[���쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer,ELayer::eEnemy });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer,ETag::eEnemy });
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(position);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CSignboard::~CSignboard()
{
	SAFE_DELETE(mpColliderMesh);

	mpUkye->Kill();
}

// �Փˏ���
void CSignboard::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	CPlayer* player = CPlayer::Instance();

	// �Փ˂��Ă���̂��A��������I�u�W�F�N�g�ł����
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		
	}
}

//�v���C���[����������
bool CSignboard::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector object = Position();

	// �v���C���[�Ƃ̋������v�Z����
	float distance = (playerPos - object).Length();
	const float detectionRadius = 20.0f;

	// �v���C���[�Ƃ̋��������o���a�ȓ��ł���΁A�v���C���[��F������
	if (distance <= detectionRadius)
	{
		return true;
	}

	return false;
}

// �X�V����
void CSignboard::Update()
{
	// U�L�[�e�L�X�g�摜��\��
	CVector UkeyPos = Position() + CVector(0.0f, 20.0f, 0.0f);
	mpUkye->SetWorldPos(UkeyPos);
}

//�@�`�揈��
void CSignboard::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}