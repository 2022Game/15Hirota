#include "CMajicSword.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

#define SWORD_O "Character\\MajicSword\\MajicSword.obj"
#define SWORD_M "Character\\MajicSword\\MajicSword.mtl"

CMajicSword::CMajicSword()
{
	// ���f�����[�h
	mpSword = new CModel();
	mpSword->Load(SWORD_O, SWORD_M);

	// �U������p�̃R���C�_�[���쐬
	mpAttackCol = new CColliderLine
	(
		this, ELayer::eAttackCol,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 1.0f, 1.0f)
	);
	// �U������p�̃R���C�_�[�ƏՓ˔�����s��
	// ���C���[�ƃ^�O��ݒ�
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::eEnemy });

	// �ŏ��͍U������p�̃R���C�_�[���I�t�ɂ��Ă���
	mpAttackCol->SetEnable(false);
}

CMajicSword::~CMajicSword()
{

}

void CMajicSword::Update()
{

}

void CMajicSword::Render()
{
	mpSword->Render(Matrix());
}

// �Փˏ���
void CMajicSword::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�R���C�_�[�ł����
	if (self == mpAttackCol)
	{
		// �L�����̃|�C���^�ɕϊ�
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// ����̃R���C�_�[�̎����傪�L�����ł����
		if (chara != nullptr)
		{
			// ���łɍU���ς݂̃L�����łȂ����
			if (!IsAttackHitObj(chara))
			{
				//�@�_���[�W��^����
				chara->TakeDamage(1);

				// �U���ς݃��X�g�ɒǉ�
				AddAttackHitObj(chara);
			}
		}
	}
}

CMatrix CMajicSword::Matrix() const
{
	// ��Ɏ����Ă��Ȃ��Ƃ��́A�������g�̍s���Ԃ�
	if (mpAttachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// ��Ɏ����Ă���Ƃ��́A�A�^�b�`���Ă���s���Ԃ�
	else
	{
		CMatrix sm;
		sm.Scale(100.0f, 100.0f, 100.0f);
		return sm * (*mpAttachMtx);
	}
}

// �U���J�n
void CMajicSword::AttackStart()
{
	CEnemyWeapon::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(true);
}

// �U���I��
void CMajicSword::AttackEnd()
{
	CEnemyWeapon::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(false);
}