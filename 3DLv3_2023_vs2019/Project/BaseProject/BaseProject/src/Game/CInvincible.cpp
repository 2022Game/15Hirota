#include "CInvincible.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"

// �d��
#define GRAVITY 0.0625f
// ���G�A�C�e���̃X�s�[�h
#define INVINCIBLE_SPEED 45.0f
// ���G�A�C�e���̎��Ԑ؂�ւ�����
#define TIMERETURN 2.0f
// ���G�A�C�e���̒��˂鑬�x
#define BOUNCE_FORCE 1.5f
// �J�E���g����
#define SWITCHCOUNTER 15

CInvincible::CInvincible()
	: mSwitchCounter(0)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveVector(0.0f, 0.0f, 0.0f)
	, mElapsedTime(0.0f)
	, mIsGround(false)
	, mRecoveryUsed(false)
{
	// ���G�A�C�e�����f���擾
	mpRecoverModel = CResourceManager::Get<CModel>("Star");

	// ���G�A�C�e���R���C�_�[�쐬
	mpRecoverCol = new CColliderSphere
	(
		this, ELayer::eRecoverCol,
		1.5f
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpRecoverCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField,});
	mpRecoverCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpRecoverCol->Position(0.0f, 1.0f, 0.0f);

	// �ŏ��̓R���C�_�[���I���ɂ��Ă���
	mpRecoverCol->SetEnable(true);

}

CInvincible::~CInvincible()
{
	SAFE_DELETE(mpRecoverCol);
}


// �Փˏ���
void CInvincible::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�̃R���C�_�[�ł����
	if (self == mpRecoverCol)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// ���łɖ��G�̃L�����łȂ����
			if (!IsAttachHitObj(player) && !mRecoveryUsed)
			{
				// ���G���(�R���C�_�[�I�t)
				player->TakeInvincible();

				// ���G���X�g�ɒǉ�
				AddAttachHitObj(player);

				mRecoveryUsed = true;
				if (mRecoveryUsed)
				{
					Kill();
				}
			}
		}
		else if (other->Layer() == ELayer::eField)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eBlockCol)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust);
		}
	}
}


// �ړ�����
void CInvincible::MoveFront()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

void CInvincible::MoveBack()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = mTargetDir * -moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

void CInvincible::MoveLight()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	// mTargetDir ���������ɕύX�i���E�ɓ����j
	CVector moveDirection(mTargetDir.Z(), 0.0f, mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

void CInvincible::MoveReft()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	// mTargetDir ���������ɕύX�i���E�ɓ����j
	CVector moveDirection(-mTargetDir.Z(), 0.0f, mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

void CInvincible::Update()
{
	// �d��
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	if (mIsGround)
	{
		mMoveSpeed += CVector(0.0f, BOUNCE_FORCE, 0.0f);
		mIsGround = false;
	}

	// ��]
	float rot = 1.0f;
	Rotate(0.0f, rot, 0.0f);

	// �^�C�����Z
	mElapsedTime += Time::DeltaTime();
	
	// �^�C����2�b�ȉ���������
	if (mElapsedTime >= TIMERETURN)
	{
		// �J�E���g�𑝉�
		mSwitchCounter++;
		// �J�E���g��15��ɂȂ��Kill���������s
		if (mSwitchCounter == SWITCHCOUNTER)
		{
			Kill();
		}
		// �����_���Ɉړ������鏈��
		int random = Math::Rand(0, 3);
		switch (random)
		{
		case 0:
			// ��O�Ɉړ�
			MoveFront();
			break;
		case 1:
			// ���Ɉړ�
			MoveBack();
			break;
		case 2:
			// �E�Ɉړ�
			MoveLight();
			break;
		case 3:
			// ���Ɉړ�
			MoveReft();
			break;
		default:
			break;
		}

		// ��������I���ƃ^�C����������
		mElapsedTime = 0.0f;
	}

	// �ړ�
	Position(Position() + mMoveVector + mMoveSpeed * 60.0f * Time::DeltaTime());

	// �m�F
	CDebugPrint::Print("TIme:%f\n", mElapsedTime);

	mIsGround = false;
}

// �`��
void CInvincible::Render()
{
	mpRecoverModel->Render(Matrix());
}