#include "CInvincible.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CSound.h"
#include "Easing.h"

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

// �A�C�e���̈ړ�����
#define GET_MOVE_TIME 0.75f
// �A�C�e���擾���̏�ړ�
#define GET_MOVE_UP 50.0f

CInvincible::CInvincible()
	: mSwitchCounter(0)
	, mState(EState::Idle)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mGetCameraDist(0.0f)
	, mStartPos(CVector::zero)
	, mMoveSpeed(CVector::zero)
	, mMoveVector(CVector::zero)
	, mGetStartPos(CVector::zero)
	, mGetTargetPos(CVector::zero)
	, mTotalMovement(CVector::zero)
	, mTargetDir(CVector::forward)
	, mIsHeld(false)
	, mIsGround(false)
	, mInvincibleUsed(false)
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

	// ���G�A�C�e���R���C�_�[�쐬
	mpFieldCol = new CColliderSphere
	(
		this, ELayer::eInvincbleCol,
		1.5f
	);
	mpFieldCol->SetCollisionTags({ ETag::eRideableObject, ETag::eField, });
	mpFieldCol->SetCollisionLayers({ ELayer::eField,ELayer::eFieldWall });

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
	mStateStep = 0;
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

void CInvincible::UpdateIdle()
{
	// �V�����|�W�V��������X����50.0f�ړ��������ǂ���
	//CDebugPrint::Print("mTotalMovement:%f\n", mTotalMovement.X());
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

	// �ړ�
	Position(Position() + mMoveVector + mMoveSpeed * 60.0f * Time::DeltaTime());

	// �m�F
	//CDebugPrint::Print("TIme:%f\n", mElapsedTime);

	mIsGround = false;
}

// �A�C�e�����������̏���
void CInvincible::UpdateGet()
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// �X�e�b�v���Ƃɏ����𕪂���
	switch (mStateStep)
	{
		// �X�e�b�v0 : �A�C�e�����ړ��J�n
	case 0:
		// �J�����܂ł̋������L�^���Ă���
		mGetCameraDist = (Position() - cam->Position()).Length();
		// �ړ��J�n���̍��W���L�����Ă���
		mGetStartPos = cam->WorldToScreenPos(Position());

		mElapsedTime = 0.0f;
		SetEnableCol(false);

		// �X�V�^�C�~���O���J��������ɕύX
		SetPriority(ETaskPriority::eLeteCamera);

		mStateStep++;
		break;
		// �X�e�b�v1 : �A�C�e����ړI�n�܂ňړ�
	case 1:
		// UI�̃A�C�e���{�b�N�X��2D���W��
		// 3D��Ԃ̍��W�ɕϊ�
		mGetTargetPos = cam->ScreenToWorldPos
		(
			CVector
			(
				WINDOW_WIDTH * 0.71f,
				WINDOW_HEIGHT * 0.9f,
				mGetCameraDist
			)
		);

		// �A�C�e���擾����3D��Ԃł̍��W���X�N���[�����W���狁�߂�
		mGetStartPos.Z(mGetCameraDist);
		CVector startPos = cam->ScreenToWorldPos(mGetStartPos);

		// �ړ����Ԃ��o�߂��Ă��Ȃ�
		if (mElapsedTime < GET_MOVE_TIME)
		{
			float per = mElapsedTime / GET_MOVE_TIME;
			float per2 = Easing::SineIn(mElapsedTime, GET_MOVE_TIME, 0.0f, 1.0f);
			CVector pos = CVector::Lerp(startPos, mGetTargetPos, per2);
			pos += CVector::up * sinf(M_PI * per) * GET_MOVE_UP;
			Position(pos);
			mElapsedTime += Time::DeltaTime();
		}
		// �ړ����Ԃ��o�߂���
		else
		{
			CPlayer* player = CPlayer::Instance();
			player->AddItem(CPlayer::ItemType::INVINCIBLE);
			// �A�C�e���{�b�N�X�̈ʒu�܂ňړ�������A�폜
			Position(mGetTargetPos);
			Kill();
		}

		// �J�����̕����֌�����
		Rotation
		(
			CQuaternion::LookRotation
			(
				(cam->Position() - Position()).Normalized(),
				CVector::up
			)
		);
		break;
	}
}

// ����Ȃ�����
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
	switch (mState)
	{
	case EState::Idle:
		UpdateIdle();
		break;
	case EState::Get:
		UpdateGet();
		break;
	}
}

// �`��
void CInvincible::Render()
{
	// �擾���̈ړ��������̂݁A�f�v�X�e�X�g���I�t�ɂ��āB
	// ���̃I�u�W�F�N�g����O�ɕ\��
	if (mState == EState::Get)
	{
		glDisable(GL_DEPTH_TEST);
	}
	mpInvincibleModel->SetColor(mColor);
	mpInvincibleModel->Render(Matrix());
	
	glEnable(GL_DEPTH_TEST);
}