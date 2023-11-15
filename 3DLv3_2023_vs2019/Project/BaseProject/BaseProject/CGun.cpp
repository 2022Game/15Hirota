#include "CGun.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

#define M1GARAND_O "Character\\Gun_M1Garand\\Gun"
#define M1GARAND_M "Character\\Gun_M1Garand\\Gun"

CGun::CGun()
{
	mpGun = new CModel();
	mpGun->Load("M1GARAND_O", M1GARAND_M);

	// �U������p�̃R���C�_�[���쐬
	mpAttackCol = new CColliderLine
	(
		this, ELayer::eAttackCol,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 1.0f, 0.0f)
	);
	// �U������p�̃R���C�_�[�ƏՓ˔�����s��
	// ���C���[�ƃ^�O��ݒ�
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
}

CGun::~CGun()
{

}

void CGun::Update()
{

}

void CGun::Render()
{

}

// �Փˏ���
void CGun::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�R���C�_�[�ł����
	if (self == mpAttackCol)
	{
		// �L�����̃|�C���^�ɕϊ�
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// ����̃R���C�_�[�̎����傪�L�����ł����
		if (chara != nullptr)
		{
			//�@�_���[�W��^����
			chara->TakeDamage(1);
		}
	}
}
