#include "CSpring.h"
#include "CColliderMesh.h"
#include "CStageManager.h"

// �R���X�g���N�^
CSpring::CSpring(const CVector& pos, const CVector& scale, const CVector& rot,
	std::string modelPath)
	: CSpringObject(pos, scale, rot)
{
	// ���˂�L�m�R�̃��f���擾
	mpModel = CResourceManager::Get<CModel>(modelPath);

	// ���˂�L�m�R�̃R���C�_�[�쐬
	CModel* kinokoCol = CResourceManager::Get<CModel>("SpringCol");
	mpCollider = new CColliderMesh(this, ELayer::eJumpingCol, kinokoCol, true);
	mpCollider->SetCollisionTags({ ETag::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpCollider->SetCollisionLayers({ ELayer::ePlayer });
	mpCollider->SetCollisionTags({ ETag::ePlayer });

	Position(pos);
	Scale(mStartScale);
	Rotate(rot);
}

// �f�X�g���N�^
CSpring::~CSpring()
{
	CStageManager::RemoveTask(this);
}


CSpringLower::CSpringLower(const CVector& pos, const CVector& scale, const CVector& rot,
	std::string modelPath)
{
	// ���˂�L�m�R�̃��f���擾
	mpModel = CResourceManager::Get<CModel>(modelPath);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CSpringLower::~CSpringLower()
{
	CStageManager::RemoveTask(this);
}

void CSpringLower::Update()
{

}

void CSpringLower::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}