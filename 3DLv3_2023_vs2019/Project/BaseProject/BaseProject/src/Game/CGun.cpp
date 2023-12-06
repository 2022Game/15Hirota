#include "CGun.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CInput.h"
#include "CEffect.h"

//#define M1GARAND_O "Item\\Gun_M1Garand\\Gun_M1Garand.obj"
//#define M1GARAND_M "Item\\Gun_M1Garand\\Gun_M1Garand.mtl"


CGun::CGun()
{
	// ���f���f�[�^�擾
	mpGun = CResourceManager::Get<CModel>("Gun_M1G");

	//// �U������p�̃R���C�_�[���쐬
	//mpAttackCol = new CColliderLine
	//(
	//	this, ELayer::eAttackCol,
	//	CVector(0.0f, 0.0f, 0.0f),
	//	CVector(0.0f, 1.0f, 1.0f)
	//);
	//// �U������p�̃R���C�_�[�ƏՓ˔�����s��
	//// ���C���[�ƃ^�O��ݒ�
	//mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	//mpAttackCol->SetCollisionTags({ ETag::eEnemy });

	// �ŏ��͍U������p�̃R���C�_�[���I�t�ɂ��Ă���
	//mpAttackCol->SetEnable(false);
}

CGun::~CGun()
{

}

void CGun::Update()
{

}

void CGun::Render()
{
	mpGun->Render(Matrix());
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

CMatrix CGun::Matrix() const
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
		sm.Scale(190.0f, 190.0f, 190.0f);

		// ��]��\���s����쐬
		CMatrix rotateY;
		CMatrix rotateZ;
		CMatrix rotateX;

		// �ړ���\���s����쐬
		CMatrix positionX;
		CMatrix positionZ;
		CMatrix positionY;

		//rotateX.RotateX(30.0f);		// X���̉�]
		rotateY.RotateY(-105.0f);	// Y���̉�]
		rotateZ.RotateZ(-22.5f);		// Z���̉�]

		float xOffset = 5.0f;	// X�������̂�����w��
		positionX.Translate(xOffset, 0, 0);
		float yOffset = 17.0f;	// Y�������̂�����w��
		positionY.Translate(0, yOffset, 0);
		float zOffset = 8.0f;	// Z�������̂�����w��3.5f
		positionZ.Translate(0, 0, zOffset);

		return sm * rotateZ * rotateY * positionX * positionY * positionZ * (*mpAttachMtx);
	}
}

// �U���J�n
void CGun::AttackStart()
{
	CWeapon::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(true);
}

// �U���I��
void CGun::AttackEnd()
{
	CWeapon::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(false);
}