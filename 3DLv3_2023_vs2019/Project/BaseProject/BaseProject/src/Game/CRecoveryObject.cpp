#include "CRecoveryObject.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"

#define GRAVITY 0.0625f			// �d��
#define RUN_SPEED 10.0f

#define TIMERETURN 5.0f

CRecoveryObject::CRecoveryObject()
	: mMoveSpeed(0.0f,0.0f,0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mElapsedTime(0.0f)
{
	mpRecoverModel = CResourceManager::Get<CModel>("MajicSword");

	// �񕜔���p�̃R���C�_�[�쐬
	mpRecoverCol = new CColliderSphere
	(
		this, ELayer::eRecoverCol,
		6.0f
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	mpRecoverCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpRecoverCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField });

	mpRecoverCol->SetEnable(true);

}

CRecoveryObject::~CRecoveryObject()
{
	SAFE_DELETE(mpRecoverCol);
}

void CRecoveryObject::Update()
{
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	bool time = false;

	Move();
	if (mElapsedTime < TIMERETURN)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > TIMERETURN)
		{
			mpRecoverCol->SetEnable(false);
			SetAlpha(0.0f);
		}
	}
}

void CRecoveryObject::Render()
{
	mpRecoverModel->Render(Matrix());
}

// �Փˏ���
void CRecoveryObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�̃R���C�_�[�ł����
	if (self == mpRecoverCol)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// ���łɉ񕜍ς݂̃L�����łȂ����
			if (!IsAttachHitObj(player))
			{
				// �񕜂�����
				player->TakeRecovery(1);

				// �񕜍ς݃��X�g�ɒǉ�
				AddAttachHitObj(player);
			}
		}
		else if (other->Layer() == ELayer::eField)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust * hit.weight);
		}
	}
}

// �񕜃X�^�[�g
void CRecoveryObject::RecoverStart()
{
	CItemObjectBase::RecoverStart();
	// �񕜂��n�܂�����A�񕜃R���C�_�[���I���ɂ���
	mpRecoverCol->SetEnable(true);
}

// �񕜏I��
void CRecoveryObject::RecoverEnd()
{
	CItemObjectBase::RecoverEnd();
	// �񕜂��I���΁A�񕜃R���C�_�[���I�t�ɂ����
	mpRecoverCol->SetEnable(false);
}


// �ړ�����
void CRecoveryObject::Move()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// ���x��ݒ�
	float moveSpeed = RUN_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	Position(Position() + -moveVector + mMoveSpeed);
}

void CRecoveryObject::MoveZ()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// ���x��ݒ�
	float moveSpeed = RUN_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	Position(Position() + moveVector + mMoveSpeed);
}