#include "CRecoveryObject.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"

#define GRAVITY 0.0625f			// �d��
#define RUN_SPEED 20.0f

#define TIMERETURN 0.5f

CRecoveryObject::CRecoveryObject()
	: mMoveSpeed(0.0f,0.0f,0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mElapsedTime(0.0f)
	, mIsGround(false)
	, mSwitchCounter(0)
	, mRecoveryUsed(false)
{
	mpRecoverModel = CResourceManager::Get<CModel>("Heart");

	// �񕜔���p�̃R���C�_�[�쐬
	mpRecoverCol = new CColliderSphere
	(
		this, ELayer::eRecoverCol,
		1.5f
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	mpRecoverCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpRecoverCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField });
	mpRecoverCol->Position(0.0f, 1.0f, 0.0f);

	mpRecoverCol->SetEnable(true);

}

CRecoveryObject::~CRecoveryObject()
{
	SAFE_DELETE(mpRecoverCol);
}

void CRecoveryObject::Update()
{
	// �d��
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);
	
	// ��]
	float rot = 1.0f;
	Rotate(0.0f, rot, 0.0f);

	// �m�F
	CDebugPrint::Print("TIme:%f\n", mElapsedTime);
	// �^�C�����Z
	mElapsedTime += Time::DeltaTime();

	// �^�C����2�b�ȉ���������
	if (mElapsedTime >= TIMERETURN)
	{
		mSwitchCounter++;
		if (mSwitchCounter == 15)
		{
			Kill();
		}
		// �����_���Ɉړ������鏈��
		int random = Math::Rand(0, 3);
		switch (random)
		{
		case 0:
			Move();
			break;
		case 1:
			MoveX();
			break;
		case 2:
			MoveY();
			break;
		case 3:
			MoveZ();
			break;
		default:
			break;
		}

		mElapsedTime = 0.0f;
	}

	// �ړ�
	Position(Position() + moveVector + mMoveSpeed * 60.0f * Time::DeltaTime());
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
			if (!IsAttachHitObj(player) && !mRecoveryUsed)
			{
				mRecoveryUsed = true;
				// �񕜂�����
				player->TakeRecovery(1);

				// �񕜍ς݃��X�g�ɒǉ�
				AddAttachHitObj(player);

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
			Position(Position() + hit.adjust * hit.weight);
		}
		else if (other->Layer() == ELayer::eBlockCol)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFieldWall)
		{
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
	// ���x��ݒ�
	float moveSpeed = RUN_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	moveVector = mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	//Position(Position() + -moveVector + mMoveSpeed);
}

void CRecoveryObject::MoveZ()
{
	// ���x��ݒ�
	float moveSpeed = RUN_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	moveVector = mTargetDir * -moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	//Position(Position() + moveVector + mMoveSpeed);
}

void CRecoveryObject::MoveX()
{
	// ���x��ݒ�
	float moveSpeed = RUN_SPEED;

	// mTargetDir ���������ɕύX�i���E�ɓ����j
	CVector moveDirection(mTargetDir.Z(), 0.0f, mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	moveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	//Position(Position() + moveVector + mMoveSpeed);
}

void CRecoveryObject::MoveY()
{
	// ���x��ݒ�
	float moveSpeed = RUN_SPEED;

	// mTargetDir ���������ɕύX�i���E�ɓ����j
	CVector moveDirection(-mTargetDir.Z(), 0.0f, mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	moveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	//Position(Position() + moveVector + mMoveSpeed);
}