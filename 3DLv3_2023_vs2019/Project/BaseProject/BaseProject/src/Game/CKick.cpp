#include "CKick.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

CKick::CKick()
{
	// �E���Ƀv���C���[�Ƀ_���[�W��^����R���C�_�[���쐬
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		0.5f
	);
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });

	mpAttackCol->SetEnable(false);
}

CKick::~CKick()
{

}

void CKick::Update()
{

}

void CKick::Render()
{
}

// �Փˏ���
void CKick::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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

CMatrix CKick::Matrix() const
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
		sm.Scale(80.0f, 80.0f, 80.0f);

		return sm * (*mpAttachMtx);
	}
}

// �U���J�n
void CKick::AttackStart()
{
	CWeaponEnemy::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(true);
}

// �U���I��
void CKick::AttackEnd()
{
	CWeaponEnemy::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(false);
}