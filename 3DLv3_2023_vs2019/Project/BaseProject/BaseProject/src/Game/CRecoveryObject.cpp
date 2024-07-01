#include "CRecoveryObject.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CSound.h"
#include "CStageManager.h"

// �d��
#define GRAVITY 0.0625f
// �񕜃A�C�e���̃X�s�[�h
#define ITEM_SPEED 20.0f
// �񕜃A�C�e���̎��Ԑ؂�ւ�����
#define TIMERETURN 0.5f
// �J�E���g����
#define SWITCHCOUNTER 15

CRecoveryObject::CRecoveryObject()
	: mSwitchCounter(0)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveVector(0.0f, 0.0f, 0.0f)
	, mElapsedTime(0.0f)
	, mRecoveryUsed(false)
	, mIsGround(false)
{
	// �񕜃A�C�e�����f���擾
	mpRecoverModel = CResourceManager::Get<CModel>("Heart");

	// �񕜂����Ƃ���SE�擾
	mpRecoberSE = CResourceManager::Get<CSound>("8bitKaifuku");

	// �񕜔���p�̃R���C�_�[�쐬
	mpRecoverCol = new CColliderSphere
	(
		this, ELayer::eRecoverCol,
		1.5f
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpRecoverCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField });
	mpRecoverCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpRecoverCol->Position(0.0f, 1.0f, 0.0f);

	// �ŏ��̓R���C�_�[���I���ɂ��Ă���
	mpRecoverCol->SetEnable(true);

}

CRecoveryObject::~CRecoveryObject()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpRecoverCol);
}

// �Փˏ���
void CRecoveryObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�̃R���C�_�[�ł����
	if (self == mpRecoverCol)
	{
		// �v���C���[��h���N���X�̃|�C���^�ɕϊ�
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// ���łɉ񕜍ς݂̃L�����łȂ����
			if (!IsAttachHitObj(player) && !mRecoveryUsed)
			{
				//CPlayer* player = CPlayer::Instance();
				mpRecoberSE->Play(1.0f, false, 0.0f);
				mRecoveryUsed = true;
				// �񕜂�����
				//player->TakeRecovery(1);

				// �񕜍ς݃��X�g�ɒǉ�
				AddAttachHitObj(player);

				if (mRecoveryUsed)
				{
					Kill();
				}
			}
		}
		// �t�B�[���h�֘A�̓����蔻��
		else if (other->Layer() == ELayer::eField)
		{
			// ���ɂ��Ă���
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust * hit.weight);
		}
		// �u���b�N�֘A�̓����蔻��
		else if (other->Layer() == ELayer::eBlockCol)
		{
			// ���ɂ��Ă���
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		// �ǃR���C�_�[�֘A�̓����蔻��
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
void CRecoveryObject::MoveFront()
{
	// ���x��ݒ�
	float moveSpeed = ITEM_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

void CRecoveryObject::MoveBack()
{
	// ���x��ݒ�
	float moveSpeed = ITEM_SPEED;

	// mMoveVector �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = mTargetDir * -moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

void CRecoveryObject::MoveRight()
{
	// ���x��ݒ�
	float moveSpeed = ITEM_SPEED;

	// mTargetDir ���������ɕύX�i���E�ɓ����j
	CVector moveDirection(mTargetDir.Z(), 0.0f, mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

void CRecoveryObject::MoveLeft()
{
	// ���x��ݒ�
	float moveSpeed = ITEM_SPEED;

	// mTargetDir ���������ɕύX�i���E�ɓ����j
	CVector moveDirection(-mTargetDir.Z(), 0.0f, mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

// �X�V����
void CRecoveryObject::Update()
{
	// �d��
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// ��]
	const float rot = 1.0f;
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
			MoveRight();
			break;
		case 3:
			// ���Ɉړ�
			MoveLeft();
			break;
		default:
			break;
		}

		// ��������I���ƃ^�C����������
		mElapsedTime = 0.0f;
	}

	// �ړ�
	Position(Position() + mMoveVector + mMoveSpeed * 60.0f * Time::DeltaTime());

	// �v�����ԊĎ�
	//CDebugPrint::Print("TIme:%f\n", mElapsedTime);
}


// �`��
void CRecoveryObject::Render()
{
	mpRecoverModel->Render(Matrix());
}