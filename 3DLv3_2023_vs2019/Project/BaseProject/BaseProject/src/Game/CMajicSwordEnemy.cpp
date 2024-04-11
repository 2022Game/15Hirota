#include "CMajicSwordEnemy.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"

CMajicSwordEnemy::CMajicSwordEnemy()
{
	mpSword = CResourceManager::Get<CModel>("MajicSwordVan");

	// �U������p�̃R���C�_�[���쐬
	mpAttackCol = new CColliderLine
	(
		this, ELayer::eAttackCol,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.5f, 3.0f, -0.9f)
	);
	// �U������p�̃R���C�_�[�ƏՓ˔�����s��
	// ���C���[�ƃ^�O��ݒ�
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });

	// �ŏ��͍U������p�̃R���C�_�[���I�t�ɂ��Ă���
	mpAttackCol->SetEnable(false);
}

CMajicSwordEnemy::~CMajicSwordEnemy()
{
	// �R���C�_�[��j��
	SAFE_DELETE(mpAttackCol);
}

// �Փˏ���
void CMajicSwordEnemy::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
				chara->TakeDamage(2);

				// �U���ς݃��X�g�ɒǉ�
				AddAttackHitObj(chara);
			}
		}
	}
}

// �U���J�n
void CMajicSwordEnemy::AttackStart()
{
	// ���łɍU�����ł���΁A�T�C�h�J�n�����͎��s���Ȃ�
	if (mIsAttack) return;

	CWeaponEnemy::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(true);
}

// �U���I��
void CMajicSwordEnemy::AttackEnd()
{
	CWeaponEnemy::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(false);
}

// ����̍s����擾
CMatrix CMajicSwordEnemy::Matrix() const
{
	const CMatrix* attachMtx = GetAttachMtx();
	// ��Ɏ����Ă��Ȃ��Ƃ��́A�������g�̍s���Ԃ�
	if (attachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// ��Ɏ����Ă���Ƃ��́A�A�^�b�`���Ă���s���Ԃ�
	else
	{
		CMatrix sm;
		sm.Scale(75.0f, 75.0f, 75.0f);

		CMatrix translate;
		translate.Translate(0.0f, 0.0f, -0.5f);

		// 90�x��]��\���s����쐬
		CMatrix rotateY;
		CMatrix rotateZ;
		CMatrix rotateX;

		rotateY.RotateY(45.0f);		// Y�������90�x��]
		rotateX.RotateX(0.0f);		// X������g90�x��]
		rotateZ.RotateZ(-60.0f);		// Z�������90�x��]

		return sm * rotateY * rotateX * rotateZ * translate * (*attachMtx);
	}
}

// �X�V����
void CMajicSwordEnemy::Update()
{

}

// �`�揈��
void CMajicSwordEnemy::Render()
{
	mpSword->SetColor(mColor);
	mpSword->Render(Matrix());
}