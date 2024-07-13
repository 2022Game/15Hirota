#include "CJumpingKinoko.h"
#include "CColliderMesh.h"
#include "CStageManager.h"

// �R���X�g���N�^
CJumpingKinoko::CJumpingKinoko(const CVector& pos, const CVector& scale, const CVector& rot,
	std::string modelPath)
	: CJumpingObject(pos, scale, rot)
	, mRotateAngle(false)
{
	// ���˂�L�m�R�̃��f���擾
	mpModel = CResourceManager::Get<CModel>(modelPath);

	// ���˂�L�m�R�̃R���C�_�[�쐬
	CModel* kinokoCol = CResourceManager::Get<CModel>("JumpingKinokoCol");
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
CJumpingKinoko::~CJumpingKinoko()
{
	CStageManager::RemoveTask(this);
}