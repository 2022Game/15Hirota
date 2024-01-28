#include "CMajicSword.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

CMajicSword::CMajicSword()
{
	mpSword = CResourceManager::Get<CModel>("MajicSword");

	// �U������p�̃R���C�_�[���쐬
	mpAttackCol = new CColliderLine
	(
		this, ELayer::eAttackCol,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 0.0f, 2.5f)
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
	// �R���C�_�[��j��
	SAFE_DELETE(mpAttackCol);
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
				chara->TakeDamage(3);

				// �U���ς݃��X�g�ɒǉ�
				AddAttackHitObj(chara);
			}
		}
	}
}

// �U���J�n
void CMajicSword::AttackStart()
{
	CWeapon::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(true);
}

// �U���I��
void CMajicSword::AttackEnd()
{
	CWeapon::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(false);
}

// ����̍s����擾
CMatrix CMajicSword::Matrix() const
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
		sm.Scale(60.0f, 60.0f, 60.0f);

		// 90�x��]��\���s����쐬
		CMatrix rotateY;
		CMatrix rotateZ;
		CMatrix rotateX;

		rotateY.RotateY(90.0f);		// Y�������90�x��]
		//rotateZ.RotateZ(90.0f);		// Z�������90�x��]
		rotateX.RotateX(90.0f);		// X������g90�x��]


		return sm * rotateY * rotateX * (*attachMtx);
	}
}

// �X�V����
void CMajicSword::Update()
{

}

// �`�揈��
void CMajicSword::Render()
{
	mpSword->SetColor(mColor);
	mpSword->Render(Matrix());
}