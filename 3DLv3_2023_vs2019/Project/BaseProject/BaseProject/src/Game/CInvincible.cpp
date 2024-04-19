#include "CInvincible.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CSound.h"

// �d��
#define GRAVITY 0.0625f
// ���G�A�C�e���̃X�s�[�h
#define INVINCIBLE_SPEED 25.0f
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
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mTotalMovement(0.0f, 0.0f, 0.0f)
	, mElapsedTime(0.0f)
	, mIsGround(false)
	, mInvincibleUsed(false)
	, mIsHeld(false)
{
	// ���G�A�C�e�����f���擾
	mpInvincibleModel = CResourceManager::Get<CModel>("Star");

	// ���G�A�C�e�����������SE�擾
	mpInvincibleSE = CResourceManager::Get<CSound>("8bitMutekiTime");

	// ���G�A�C�e���R���C�_�[�쐬
	mpInvincibleCol = new CColliderSphere
	(
		this, ELayer::eInvincbleCol,
		1.5f
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpInvincibleCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField,});
	mpInvincibleCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpInvincibleCol->Position(0.0f, 1.0f, 0.0f);

	// ���G�A�C�e���R���C�_�[�쐬
	mpFieldCol = new CColliderSphere
	(
		this, ELayer::eInvincbleCol,
		1.5f
	);
	mpFieldCol->SetCollisionTags({ ETag::eRideableObject, ETag::eField, });
	mpFieldCol->SetCollisionLayers({ ELayer::eField,ELayer::eFieldWall });
	mpFieldCol->Position(0.0f, 1.0f, 0.0f);

	// �ŏ��̓R���C�_�[���I���ɂ��Ă���
	mpInvincibleCol->SetEnable(true);
	mpFieldCol->SetEnable(true);

	mStartPos = Position();
}

CInvincible::~CInvincible()
{
	SAFE_DELETE(mpInvincibleCol);
	SAFE_DELETE(mpFieldCol);
}

void CInvincible::ChangeState(EState state)
{
	mState = state;
}

// �Փˏ���
void CInvincible::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�̃R���C�_�[�ł����
	if (self == mpInvincibleCol)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// ���łɖ��G�̃L�����łȂ����
			if (!IsAttachHitObjInvincible(player) && !mInvincibleUsed)
			{
				mMoveVector = CVector::zero;
				mMoveSpeed = CVector::zero;
				mInvincibleUsed = true;
				mpInvincibleCol->SetEnable(false);
				AddAttachHitObjInvincible(player);
				ChangeState(EState::Get);
			}
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

	if (self == mpFieldCol)
	{
		if (other->Layer() == ELayer::eField)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
	}
}

// �ړ�����
// �O�Ɉړ�����
void CInvincible::MoveFront()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	CVector moveDirection = (CVector::forward).Normalized();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

// ���Ɉړ�����
void CInvincible::MoveBack()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	CVector moveDirection = (CVector::back).Normalized();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

// �E�Ɉړ�����
void CInvincible::MoveRight()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	CVector moveDirection = (CVector::right).Normalized();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

// ���Ɉړ�����
void CInvincible::MoveLeft()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	CVector moveDirection = (CVector::left).Normalized();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();
}

// �A�C�e�����������̏���
// �E�Ɉړ������̂�����
void CInvincible::UpdateGet()
{
	// ���x��ݒ�
	float moveSpeed = INVINCIBLE_SPEED;

	// right�ɂ����獶�Ɉړ�����
	CVector moveDirection = (CVector::left).Normalized();

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed * Time::DeltaTime();

	mTotalMovement += mMoveVector;

	// kill���Ă�
	if (mTotalMovement.X() >= 50.0f)
	{
		Kill();
	}
}


void CInvincible::OnTouch(CPlayer* player)
{
	if (mIsHeld)
	{
		player->AddItem(CPlayer::ItemType::INVINCIBLE);
		mIsHeld = true;
	}
}

// �X�V����
void CInvincible::Update()
{
	CDebugPrint::Print("mTotalMovement:%f\n", mTotalMovement.X());
	// �d��
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// �^�C�����Z
	mElapsedTime += Time::DeltaTime();
	
	if (!mInvincibleUsed)
	{
		if (mIsGround)
		{
			mMoveSpeed += CVector(0.0f, BOUNCE_FORCE, 0.0f);
			mIsGround = false;
		}

		// ��]
		float rot = 1.0f;
		Rotate(0.0f, rot, 0.0f);

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
	}

	switch (mState)
	{
	case EState::Get:
		UpdateGet();
		break;
	}

	// �ړ�
	Position(Position() + mMoveVector + mMoveSpeed * 60.0f * Time::DeltaTime());

	// �m�F
	//CDebugPrint::Print("TIme:%f\n", mElapsedTime);

	mIsGround = false;
}

// �`��
void CInvincible::Render()
{
	mpInvincibleModel->SetColor(mColor);
	mpInvincibleModel->Render(Matrix());
}