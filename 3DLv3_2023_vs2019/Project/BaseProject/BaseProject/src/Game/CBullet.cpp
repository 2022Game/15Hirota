#include "CBullet.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"

#define BULLET_O "Character\\Bullet1\\Bullet.obj"
#define BULLET_M "Character\\Bullet1\\Bullet.obj"

CBullet::CBullet()
{
	mPos = CVector(0.0f, 0.0f, 0.0f);

	// ���f�����[�h
	mpBullet = new CModel();
	mpBullet->Load(BULLET_O, BULLET_M);

	// �U������p�̃R���C�_�[���쐬
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		1.0f //��ŕύX
	);
	// �U������p�̎q���_�[�ƏՓ˔�����s��
	// ���C���[�ƃ^�O��ݒ�
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::eEnemy });

	// �ŏ��͍U������p�̃R���C�_�[���I�t�ɂ��Ă���
	mpAttackCol->SetEnable(false);
}

CBullet::~CBullet()
{

}

void CBullet::Update()
{
	CVector currentPos = Position();
	currentPos = mPos + CVector(0.0f,0.0f,1.0f) * Matrix();

	Position(currentPos);
}


void CBullet::Render()
{
	mpBullet->Render(Matrix());
}

CMatrix CBullet::Matrix() const
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
		sm.Scale(150.0f, 150.0f, 150.0f);

		CMatrix moveMatrix;
		moveMatrix.Translate(0.0f, 0.0f, 10.0f);
		return moveMatrix * sm * (*mpAttachMtx);
	}
}

void CBullet::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�R���C�_�[��
	if (self == mpAttackCol)
	{
		// �e���|�C���^�ɕϊ�
		CCharaBase* bullet = dynamic_cast<CCharaBase*>(other->Owner());
		// ����̃R���C�_�[�̎����傪�e�ł����
		if (bullet != nullptr)
		{
			// ���łɍU���ς݂̒e�łȂ����
			if (!IsAttackHitObj(bullet))
			{
				// �_���[�W��^����
				bullet->TakeDamage(1);

				// �U���ς݃��X�g�ɒǉ�
				AddAttackHitObj(bullet);
			}
		}
	}
}


// �U���J�n
void CBullet::AttackStart()
{
	CEnemyWeapon::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(true);
}

// �U���I��
void CBullet::AttackEnd()
{
	CEnemyWeapon::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(false);
}