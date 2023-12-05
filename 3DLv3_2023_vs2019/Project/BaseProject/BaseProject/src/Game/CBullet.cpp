#include "CBullet.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CEffect.h"

#define BULLET_O "Character\\Bullet1\\Bullet.obj"
#define BULLET_M "Character\\Bullet1\\Bullet.mtl"

// �e�ۂ̈ړ����x
#define MOVE_SPEED 100.0f

CModel* CBullet::mpBullet = nullptr;

CBullet::CBullet()
	: mPos (CVector(0.0f, 0.0f, 0.0f))
	, mMoveDistance(0.0f)
{
	mPos = CVector(0.0f, 0.0f, 0.0f);

	if (mpBullet == nullptr)
	{
		// ���f�����[�h
		mpBullet = new CModel();
		mpBullet->Load(BULLET_O, BULLET_M);
	}

	// �e�ۂƃR���C�_�[�̃X�P�[����ݒ�
	float scale = 50.0f;
	Scale(scale, scale, scale);
	float rad = 1.0f / scale;

	// �U������p�̃R���C�_�[���쐬
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		rad
	);
	// �U������p�̎q���_�[�ƏՓ˔�����s��
	// ���C���[�ƃ^�O��ݒ�
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
}

CBullet::~CBullet()
{
	// �e�ۂ��폜���ꂽ��A�R���C�_�[���폜
	SAFE_DELETE_ARRAY(mpAttackCol);
}

void CBullet::Update()
{
	CVector currentPos = Position();
	float moveSpeed = MOVE_SPEED * Time::DeltaTime();
	currentPos += VectorZ() * moveSpeed;;
	Position(currentPos);

	// �e�ۂ̈ړ����������Z
	mMoveDistance += moveSpeed;
	// ��苗���ړ�������A�e�ۂ��폜
	if (mMoveDistance >= 100.0f)
	{
		Kill();
	}
}


void CBullet::Render()
{
	mpBullet->Render(Matrix());
}

CMatrix CBullet::Matrix() const
{
	// �������g�̍s���Ԃ�
	if (mpAttachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// �A�^�b�`���Ă���s���Ԃ�
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
				bullet->TakeDamage(0);

				// �U���ς݃��X�g�ɒǉ�
				AddAttackHitObj(bullet);
			}
		}
	}
}

//
//// �U���J�n
//void CBullet::AttackStart()
//{
//	CEnemyWeapon::AttackStart();
//	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
//	mpAttackCol->SetEnable(true);
//}
//
//// �U���I��
//void CBullet::AttackEnd()
//{
//	CEnemyWeapon::AttackEnd();
//	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
//	mpAttackCol->SetEnable(false);
//}