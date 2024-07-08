#include "CReflectionKinoko.h"
#include "CColliderMesh.h"

// �R���X�g���N�^
CReflectionKinoko::CReflectionKinoko(const CVector& pos, const CVector& scale, const CVector& rot,
	std::string modelPath)
	: CReflectionObject(pos, scale, rot)
{
	// ���˕Ԃ�����L�m�R�̃��f���擾
	mpModel = CResourceManager::Get<CModel>(modelPath);

	// ���˕Ԃ�����L�m�R�̃R���C�_�[�쐬
	CModel* kinokoCol1 = CResourceManager::Get<CModel>("ReflectionKinokoCol");
	mpCollider1 = new CColliderMesh(this, ELayer::eReflection, kinokoCol1, true);
	mpCollider1->SetCollisionTags({ ETag::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpCollider1->SetCollisionLayers({ ELayer::ePlayer });
	mpCollider1->SetCollisionTags({ ETag::ePlayer });

	// ���˕Ԃ�����L�m�R�̃R���C�_�[�쐬
	CModel* kinokoCol2 = CResourceManager::Get<CModel>("ReflectionKinokoTopCol");
	mpCollider2 = new CColliderMesh(this, ELayer::eReflectionJump, kinokoCol2, true);
	mpCollider2->SetCollisionTags({ ETag::ePlayer });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpCollider2->SetCollisionLayers({ ELayer::ePlayer });
	mpCollider2->SetCollisionTags({ ETag::ePlayer });

	Position(pos);
	Scale(mStartScale);
	Rotate(rot);
}

// �f�X�g���N�^
CReflectionKinoko::~CReflectionKinoko()
{
}