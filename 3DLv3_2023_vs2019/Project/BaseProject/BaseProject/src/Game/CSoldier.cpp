#include "CSoldier.h"
#include "CCamera.h"
#include "CBillBoard.h"
#include "CImage.h"
#include "CPlayer.h"
#include <algorithm>
#include "Maths.h"
#include <BaseSystem/CInput.h>
#include "CGun.h"
#include "CBullet.h"
#include "CKick.h"
#include "CSoldierFrame.h"
#include "CSoldierGauge.h"
#include "CStageManager.h"
#include "CEnemyManager.h"
#include "CExclamationMark.h"
#include "CGameManager.h"

#define _USE_MATH_DEFINES

// �\���W���[�֘A
// �\���W���[�̓���
#define ENEMY_HEIGHT 8.0f
// �ړ����x
#define MOVE_SPEED 0.7f
// �����ړ����x
#define MOVE_AUTOMATIC_SPEED 30.0f
// �W�����v���x
#define JUMP_SPEED 1.5f
// �d�͉����x
#define GRAVITY 0.0625f


// �Ǐ]���ړ����x
// ����̊p�x(�[�p�x+�p�x���o)
#define FOV_ANGLE 100.0f
// �v���C���[�܂ł̋���
#define ATTACK_RANGE 70.0f
// �v���C���[�܂ł̋���(�L�b�N)
#define ATTACK_RANGE_KICK 25.0f
// �v���C���[�܂ł̋���(�o�b�N�X�e�b�v)
#define BACKSTEP_RANGE 24.0f
// �o�b�N�X�e�b�v�̑ҋ@����
#define BACKSTEP_WEIT_TIME 5.0f


// HP�֘A
#define HP 5
// ���x���֘A
#define LEVEL 1
// �U���͊֘A
#define ATTACK 10


// �e�ۊ֘A
// �e�ۂ̔��ˊԊu
#define ATTACK 10

// �e�ۂ̔��ˊԊu
#define SHOT_INTERVAL 2.0f

// �G������������̎���
#define PLAYER_LOST 10.0f

// �L�b�N�R���C�_�[�̎���
#define KICKCOL 10.0f

// �v���C���[�𔭌�������̎���
#define DISCOVERY 2.0f
// �v���C���[�𔭌�������̑҂�����
#define DISCOVERY_END 40.0f

// CSoldier�̃C���X�^���X
CSoldier* CSoldier::spInstance = nullptr;

CSoldier* CSoldier::Instance()
{
	return spInstance;
}

// CSoldier�̃A�j���[�V�����f�[�^�̃e�[�u��
const CSoldier::AnimData CSoldier::ANIM_DATA[] =
{
	{ "",																			true,	  0.0f	},	// T�|�[�Y
	{ "Character\\Gas mask soldier\\anim\\Rifle_Idle1_515.x",						true,   515.0f	},	// Idle��
	{ "Character\\Gas mask soldier\\anim\\Rifle_Idle3_187.x",						true,   187.0f	},	// ���C�t��Idle��
	{ "Character\\Gas mask soldier\\anim\\Rifle_walk_79.x",							true,	 79.0f	},	// �ړ�
	{ "Character\\Gas mask soldier\\anim\\Alert_83.x",								true,	 83.0f	},	// �x��
	{ "Character\\Gas mask soldier\\anim\\Rifle_1shot_71.x",						true,	 71.0f	},	// �v���C���[�������U��
	{ "Character\\Gas mask soldier\\anim\\Right foot kick_121.x",				false,		121.0f	},	// �i��
	{ "Character\\Gas mask soldier\\anim\\Reload_199.x",							true,	 99.0f	},	// �����[�h
	{ "Character\\Gas mask soldier\\anim\\Rilfle_Aim_to_Dwon._91.x",			false,		91.0f	},	// �G�C������
	{ "Character\\Gas mask soldier\\anim\\Hit_27.x",							false,		27.0f	},	// Hit
	{ "Character\\Gas mask soldier\\anim\\Death_Fall down1_157.x",				false,		157.0f	},	// ���S
	{ "Character\\Gas mask soldier\\anim\\BackStep_101.x",						false,		101.0f	},	// �o�b�N�X�e�b�v

};

// �R���X�g���N�^
CSoldier::CSoldier()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eReady)
	, mTimeShot(0)
	, mTimeShotEnd(5)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mElapsedTime_End(0.0f)
	, mKickTime(0.0f)
	, mBackStepTime(0.0f)
	, mDiscoveryTime(0.0f)
	, mDiscoveryTimeEnd(0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mInitialPosition(0.0f, 0.0f, 0.0f)
	, mTimeToChange(Math::Rand(2.0f, 5.0f))
	, mIsGrounded(false)
	, mKickTimeEnd(false)
	, mDiscovery(false)
	, mDiscoveryEnd(false)
	, mBackStep(false)
	, mpRideObject(nullptr)
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// �����ʒu�̕ۑ�
	//Position(mInitialPosition);
	mInitialPosition = Position();

	// �\���W���[�̐����擾
	CEnemyManager::IncrementSoldierCount();

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Soldier");

	// �t���[���ݒ�
	mpFrame = new CSoldierFrame();
	// 0~1�̒l��ݒ�
	mpFrame->SetCenterRatio(CVector2(0.5f, 0.0f));
	// �Q�[�W�ݒ�
	mpGauge = new CSoldierGauge();
	mpGauge->SetCenterRatio(CVector2(0.3f, 0.0f));
	// �r�b�N���}�[�N�ݒ�
	mpExclamationMark = new CExclamationMark();
	mpExclamationMark->SetCeneterRatio(CVector2(0.3f, 0.5f));


	// �e�[�u�����̃A�j���[�V�����f�[�^��ǂݍ���
	int size = ARRAY_SIZE(ANIM_DATA);
	for (int i = 0; i < size; i++)
	{
		const AnimData& data = ANIM_DATA[i];
		if (data.path.empty()) continue;
		model->AddAnimationSet(data.path.c_str());
	}
	// CXCharacter�̏�����
	Init(model);

	// �ŏ��͑ҋ@�A�j���[�V�������Đ�
	ChangeAnimation(EAnimType::eIdle);

	// �t�B�[���h�Ƃ̓����蔻������R���C�_�[
	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, ENEMY_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField });

	// �ꎞ�I�ȓ����蔻������R���C�_�[
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eEnemy,
		7.0f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField, ELayer::eFieldEnemyWall });
	mpColliderSphere->Position(0.0f, 5.0f, 1.0f);

	// �_���[�W���󂯂�R���C�_�[
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f
	);
	// �_���[�W���󂯂�R���C�_�[��
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol, ELayer::eDamageCol,ELayer::eEnemy });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon, ETag::eEnemy });
	// �_���[�W���󂯂�R���C�_�[���������ւ��炷
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);

	// �_���[�W��^����R���C�_�[
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eKickCol,
		0.3f
	);
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
	mpAttackCol->SetEnable(false);
	// �E��
	const CMatrix* spineMtxK = GetFrameMtx("Armature_mixamorig_RightToeBase");
	mpAttackCol->SetAttachMtx(spineMtxK);

	// �e���쐬���Ď�������
	mpGun = new CGun();
	// �E��
	const CMatrix* gun = GetFrameMtx("Armature_mixamorig_RightHand");
	mpGun->AttachMtx(gun);

	mKickTimeEnd = false;
	mBackStep = false;

	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}

// �f�X�g���N�^
CSoldier::~CSoldier()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);

	// �R���C�_�[�֘A�̔j��
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderSphere);
	SAFE_DELETE(mpDamageCol);
	SAFE_DELETE(mpAttackCol);
	
	// �e�̔j��
	mpGun->Kill();

	// �\���W���[�̃J�E���g��j��
	CEnemyManager::DecrementSoldierCount();

	// UI�����j��
	mpGauge->Kill();
	mpFrame->Kill();
	mpExclamationMark->Kill();
}

// �Փˏ���
void CSoldier::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// ����R���C�_�[
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
			mIsGrounded = true;

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}

	// �J�v�Z���R���C�_���ł���܂ł̃R���C�_�[
	if (self == mpColliderSphere)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight

			 // �ړ������𔽓]
			mTargetDir = -mTargetDir;

			// ���]���������Ɍ����ĉ�]��ݒ�
			CVector current = VectorZ();
			CVector target = mTargetDir;
			CVector forward = CVector::Slerp(current, target, 0.125f);
			Rotation(CQuaternion::LookRotation(forward));

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
		else if (other->Layer() == ELayer::eField)
		{
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFieldEnemyWall)
		{
			Position(Position() + hit.adjust);
		}
	}

	// �_���[�W���󂯂�R���C�_�[
	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eAttackCol)
		{
			if (mState != EState::eKick)
			{
				ChangeState(EState::eHit);
			}
		}

		// �G�Ɠ�����R���C�_�[
		if (other->Layer() == ELayer::eDamageCol)
		{
			(other->Tag() == ETag::eEnemy);
			{
				Position(Position() + hit.adjust);
			}
		}
	}
}

// ��ԕύX
void CSoldier::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// ��_���[�W����
void CSoldier::TakeDamage(int damage)
{
	mCharaStatus.hp -= damage;

	// HP��0�ɂȂ�����
	if (mCharaStatus.hp <= 0)
	{
		ChangeState(EState::eDeth);
	}
}

// ���x���A�b�v
void CSoldier::LevelUp()
{
	int level = mCharaStatus.level;
	ChangeLevel(level + 1);
}

// ���x����ύX
void CSoldier::ChangeLevel(int level)
{
	// �X�e�[�^�X�̃e�[�u���̃C���f�b�N�X�n�ɕϊ�
	int index = Math::Clamp(level - 1, 0, ENEMY_LEVEL_MAX);
	// �ő�X�e�[�^�X�ɐݒ�
	mCharaMaxStatus = ENEMY_STATUS[index];
	// ���݂̃X�e�[�^�X���ő�l�ɂ��邱�ƂŁAHP��
	mCharaStatus = mCharaMaxStatus;

	// �ő�HP�ƌ���HP��HP�Q�[�W�ɔ��f
	mpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpGauge->SetValue(mCharaStatus.hp);
}

// �\���W���[�̕����������_���ɕύX���鏈��
void CSoldier::ChangeDerection()
{
	// �����_���ȕ����ɕύX
	// �����_���Ȋp�x�����߂�
	float randomAngle = Math::Rand(0.0f, 1.0f) * 360.0f;
	// �����̌v�Z���p�x�ɑ��
	mTargetDir = CalculateDirection(randomAngle);
}

// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
void CSoldier::UpdateGaugeAndFrame()
{
	if (mDiscovery)
	{
		mpGauge->SetShow(false);
		mpFrame->SetShow(false);
	}
	else
	{
		// HP�Q�[�W�̍��W���X�V (�G�̍��W�̏�����̍��W)
		CVector gaugePos = Position() + CVector(0.0f, 45.0f, 0.0f);
		mpGauge->SetWorldPos(gaugePos);
		CVector framePos = Position() + CVector(0.0f, 45.0f, 0.0f);
		mpFrame->SetWorldPos(framePos);
	}
}

// �r�b�N���}�[�N�̕\���̊m�F�����鏈��
void CSoldier::UpdateExclamation()
{
	if (mDiscovery)
	{
		// �r�b�N���}�[�N�摜�̍��W���X�V
		CVector exclamationMardPos = Position() + CVector(0.0f, 45.0f, 0.0f);
		mpExclamationMark->SetWorldPos(exclamationMardPos);
	}
	else
	{
		mpExclamationMark->SetShow(false);
	}
}

// �ҋ@��ԑJ�ڂ������
bool CSoldier::ShouldTransitionWander()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.01f;  // 0.01%�̊m���őҋ@�ɑJ��
}

// �p�j��ԂɑJ�ڂ������
bool CSoldier::ShouldTransition()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.1f;  // 0.1%�̊m���Ŝp�j��ԂɑJ��
}

// 360�x�̊p�x�����߂āAx����y������v�Z����
CVector CSoldier::CalculateDirection(float angleDegrees)
{
	// �����p�x�Ƀ����_���ȃI�t�Z�b�g��ǉ�
	float randomOffset = Math::Rand(0.0f, 1.0f);  // 0����1�̃����_���Ȓl
	float randomAngle = angleDegrees + 2.0f * M_PI * randomOffset;

	// �p�x���烉�W�A���ɕϊ�
	float angleRadians = randomAngle * M_PI / 180.0f;

	// �x�N�g���̌v�Z
	float x = cos(angleRadians);
	float y = 0.0f;					// Y�������Ɉړ�������ꍇ�͕K�v�ɉ����ĕύX
	float z = sin(angleRadians);

	return CVector(x, y, z);
}

// �ړ�����
void CSoldier::Move()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// mMoveSpeed�͓G�̑��x�x�N�g���AmMoveSpeed.X()��X�������̑��x
	// �K�؂ȑ��x��ݒ肵�AmMoveSpeed��mTargetDir�ɃX�P�[�����O���Ĉړ��B
	// ���x��ݒ�
	float moveSpeed = MOVE_AUTOMATIC_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	Position(Position() + moveVector + mMoveSpeed);
}

// �A�j���[�V�����؂�ւ�
void CSoldier::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �������̏��
void CSoldier::UpdateReady()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ���
	switch (mStateStep)
	{
		// �X�e�b�v0 ����������
	case 0:
		ChangeAnimation(EAnimType::eIdle);
		// �S�Ă̏Փ˔�����I�t�ɂ���
		SetEnableCol(false);
		// �v���C���[�̈ړ����x��0�ɂ���
		mMoveSpeed = CVector::zero;
		mCharaStatus.stamina = mCharaMaxStatus.stamina;
		mCharaStatus.hp = mCharaMaxStatus.hp;
		// ���̃X�e�b�v��
		mStateStep++;
		break;
		// �X�e�b�v1 �X�e�[�W�̓ǂݍ��݂���
	case 1:
		// �Q�[�����J�n������
		if (CGameManager::GameState() == EGameState::eGame)
		{
			mElapsedTime = 0.0f;
			// �v���C���[�̏Փ˔�����I���ɂ���
			SetEnableCol(true);
			// ���݂̏�Ԃ�ҋ@�ɐ؂�ւ�
			mCharaStatus.hp = mCharaMaxStatus.hp;
			ChangeState(EState::eIdle);
		}
		break;
	}
}

// �ҋ@
void CSoldier::UpdateIdle()
{
	mDiscovery = false;
	mDiscoveryEnd = false;
	mpAttackCol->SetEnable(false);
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	//�v���C���[����������A�G������Ԃֈڍs
	if (IsFoundPlayer())
	{
		if (mDiscoveryTimeEnd <= DISCOVERY_END && !mDiscovery)
		{
			ChangeState(EState::eDiscovery);
		}
		else
		{
			ChangeState(EState::eChase);
		}
	}
	else
	{
		ChangeAnimation(EAnimType::eIdle);

		// �m���Ŝp�j��ԂɈڍs
		if (ShouldTransition())
		{
			ChangeState(EState::eWander);
		}
	}
}

// �U��
void CSoldier::UpdateAttack()
{
	mDiscovery = false;
	// �U������Ƃ��͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	if (distancePlayer <= ATTACK_RANGE)
	{
		if (distancePlayer <= BACKSTEP_RANGE && !mBackStep)
		{
			ChangeState(EState::eBackStep);
			mBackStep = true;
			return;
		}
		else if (distancePlayer <= ATTACK_RANGE_KICK && !mKickTimeEnd)
		{
			ChangeState(EState::eKick);
			mKickTimeEnd = true;
			return;
		}
		ChangeAnimation(EAnimType::eAttack);
		// �e�۔��ˊԊu���Ԃ��o�߂���̂�҂�
		if (mElapsedTime < SHOT_INTERVAL)
		{
			mElapsedTime += Time::DeltaTime();
		}
		// �e�۔��ˊԊu���o�߂���
		else
		{
			mElapsedTime -= SHOT_INTERVAL;

			// �e�ۂ𐶐�
			new CBullet
			(
				// ���ˈʒu
				Position() + CVector(0.0f, 13.0f, 0.0f) + VectorZ() * 20.0f,
				VectorZ(),	// ���˕���
				1000.0f,	// �ړ�����
				1000.0f		// �򋗗�
			);

			// �S�e���˂�����A�U���I��
			mTimeShot++;
			if (mTimeShot >= mTimeShotEnd)
			{
				// �U���I����̑ҋ@��ԂɑJ��
				ChangeState(EState::eAttackWait);
				mTimeShot = 0;
				mElapsedTime = 0.0f;
				mDiscoveryTime = 0.0f;
			}
		}
	}
	else
	{
		ChangeState(EState::eChase);
		mElapsedTime_End = 0.0f;
		mDiscoveryTime = 0.0f;
	}
}

// �U���I���҂�
void CSoldier::UpdateAttackWait()
{
	ChangeAnimation(EAnimType::eReload);
	if (IsAnimationFinished())
	{
		CPlayer* player = CPlayer::Instance();
		float distanceToPlayer = (player->Position() - Position()).Length();

		if (distanceToPlayer <= ATTACK_RANGE)
		{
			ChangeState(EState::eAttack);
		}
		else
		{
			ChangeState(EState::eAimDwon);
			mElapsedTime_End = 0.0f;
			mDiscoveryTime = 0.0f;
		}
	}
}

// �v���C���[����
void CSoldier::UpdateDiscovery()
{
	mDiscovery = true;
	mMoveSpeed.Y(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eRifleIdle);

	// �v���C���[�܂ł̃x�N�g�������߂�
	CPlayer* player = CPlayer::Instance();
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();
	
	mDiscoveryTime += Time::DeltaTime();
	if (mDiscoveryTime >= DISCOVERY)
	{
		if (IsFoundPlayer())
		{
			mDiscoveryEnd = true;
			ChangeState(EState::eChase);
		}
		else
		{
			mDiscoveryTime = 0.0f;
			ChangeState(EState::eAimDwon);
		}
	}
	//CDebugPrint::Print("discovery:%f\n", mDiscoveryTime);
}

// �ǐ�
void CSoldier::UpdateChase()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	if (!IsFoundPlayer())
	{
		ChangeAnimation(EAnimType::eRifleIdle);
		mElapsedTime_End += Time::DeltaTime();
		//CDebugPrint::Print("TimeEnd%f\n", mElapsedTime_End);
		if (mElapsedTime_End >= PLAYER_LOST)
		{
			ChangeState(EState::eAimDwon);
			mElapsedTime_End = 0.0f; // �v���C���[�����E�����������o�ߎ��Ԃ����Z�b�g
		}
	}
	else
	{
		mElapsedTime_End = 0.0f;
		CPlayer* player = CPlayer::Instance();
		CVector playerPos = player->Position();
		playerPos.Y(Position().Y());

		CVector toPlayer = (playerPos - Position()).Normalized();
		mMoveSpeed += toPlayer * MOVE_SPEED;
		mTargetDir = toPlayer;

		// �v���C���[�Ƃ̋��������͈͈ȓ��ł���΍U�����[�h�ɐ؂�ւ���
		float distanceToPlayer = (player->Position() - Position()).Length();
		ChangeAnimation(EAnimType::eAlert);
		
		if (distanceToPlayer <= ATTACK_RANGE)
		{
			ChangeState(EState::eAttack);
		}
	}
}

// �L�b�N
void CSoldier::UpdateKick()
{
	// �U������Ƃ��͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	ChangeAnimation(EAnimType::eKick);
	if (mAnimationFrame >= 45.0f)
	{
		mpAttackCol->SetEnable(true);
		ChangeState(EState::eKickWait);
	}
}

// �L�b�N�I��
void CSoldier::UpdateKickWait()
{
	if (mAnimationFrame >= 70.0f)
	{
		mpAttackCol->SetEnable(false);
		if (IsAnimationFinished())
		{
			ChangeState(EState::eChase);
			ChangeAnimation(EAnimType::eIdle);
		}
		
	}
}

// �G�C������
void CSoldier::UpdateAimDwon()
{
	ChangeAnimation(EAnimType::eAimDwou);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
		mElapsedTime_End = 0.0f;
	}
}

// �v���C���[�̍U�����󂯂���
void CSoldier::UpdateHit()
{
	// �_���[�W���󂯂����͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	ChangeAnimation(EAnimType::eHit);
	if (IsAnimationFinished())
	{
		// �v���C���[�̃|�C���^��0�ȊO�̎�
		CPlayer* player = CPlayer::Instance();

		// �v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - Position();
		float distancePlayer = vp.Length();
		vp.Y(0.0f);
		mTargetDir = vp.Normalized();

		if (mCharaStatus.hp >= 1)
		{
			ChangeState(EState::eChase);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeth);
		}
	}
}

// ���S
void CSoldier::UpdateDeth()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eDeth);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eDethEnd);
	}
}

// ���S�����I��
void CSoldier::UpdateDethEnd()
{
	if (IsAnimationFinished())
	{
		Kill();
	}
}

// �p�j����
void CSoldier::UpdateWander()
{
	mpAttackCol->SetEnable(false);
	ChangeAnimation(EAnimType::eWalk);

	// ��莞�Ԃ��Ƃɕ����]��
	mElapsedTime += Time::DeltaTime();
	if (mElapsedTime >= mTimeToChange)
	{
		ChangeDerection();
		mElapsedTime = 0.0f;
	}

	Move();

	if (IsFoundPlayer())
	{
		if (mDiscoveryTimeEnd <= DISCOVERY_END)
		{
			ChangeState(EState::eDiscovery);
		}
		else
		{
			ChangeState(EState::eChase);
		}
	}
	else
	{
		if (ShouldTransitionWander())
		{
			ChangeState(EState::eIdle);
		}
	}
}

// �o�b�N�X�e�b�v
void CSoldier::UpdateBackStep()
{
	mMoveSpeed.X(0.0f);

	ChangeAnimation(EAnimType::eBackStep);

	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();


	// �o�b�N�X�e�b�v���鋗��
	const float backStepDistance = 15.0f;

	CVector playerPos = CPlayer::Instance()->Position();
	CVector soldierPos = Position();
	CVector toPlayer = (playerPos - soldierPos).Normalized();

	Position(Position() - toPlayer * backStepDistance * Time::DeltaTime());
	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// �W�����v�J�n
void CSoldier::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eJump);

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// �W�����v��
void CSoldier::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpEnd);
	}
}

// �W�����v�I��
void CSoldier::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
}

// �v���C���[�ǐ�
bool CSoldier::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector enemyPos = Position();

	CVector toPlayer = (playerPos - enemyPos).Normalized();
	CVector forward = Matrix().VectorZ().Normalized();

	float dot = forward.Dot(toPlayer);

	// ����p�̔������v�Z����
	float halfFOV = FOV_ANGLE * 0.5f;


	// ����p�̔�����菬�������v���C���[�Ƃ̋��������͈͈ȓ��ł���΁A�v���C���[��F������
	if (dot >= cosf(halfFOV * M_PI / 180.0f))
	{
		float distance = (playerPos - enemyPos).Length();
		const float chaseRange = 100.0f;

		if (distance <= chaseRange)
			return true;
	}

	return false;
}

// �X�V
void CSoldier::Update()
{
	SetParent(mpRideObject);
	mpRideObject = nullptr;

	// �L�b�N�̑҂�����
	if (mKickTimeEnd)
	{
		mKickTime += Time::DeltaTime();
		if (mKickTime >= KICKCOL)
		{
			mKickTimeEnd = false;
			mKickTime = 0.0f;
		}
	}
	//CDebugPrint::Print("kickTime%f\n", mKickTime);

	// �o�b�N�X�e�b�v�̑҂�����
	if (mBackStep)
	{
		mBackStepTime += Time::DeltaTime();
		if (mBackStepTime >= BACKSTEP_WEIT_TIME)
		{
			mBackStep = false;
			mBackStepTime = 0.0f;
		}
	}

	// �v���C���[�𔭌�������̎��Ԃ̌v��
	if (mDiscoveryTimeEnd <= DISCOVERY_END && mDiscoveryEnd)
	{
		mDiscoveryTimeEnd += Time::DeltaTime();
		if (mDiscoveryTimeEnd >= DISCOVERY_END)
		{
			mDiscovery = false;
			mDiscoveryEnd = false;
			mDiscoveryTimeEnd = 0.0f;
		}
	}
	CDebugPrint::Print("mDiscovery:%s\n", mDiscovery ? "true" : "false");
	//CDebugPrint::Print("discoveryTimeEnd:%f\n", mDiscoveryTimeEnd);

	// ��Ԃɍ��킹�āA�X�V������؂�ւ���
	switch (mState)
	{
		// �������
	case EState::eReady:
		UpdateReady();
		break;
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// �U��
	case EState::eAttack:
		UpdateAttack();
		break;
		// �L�b�N
	case EState::eKick:
		UpdateKick();
		break;
		// �L�b�N�I��
	case EState::eKickWait:
		UpdateKickWait();
		break;
		// �G�C������
	case EState::eAimDwon:
		UpdateAimDwon();
		break;
		// �U���I���҂�
	case EState::eAttackWait:
		UpdateAttackWait();
		break;
		// �v���C���[����
	case EState::eDiscovery:
		UpdateDiscovery();
		break;
		// �ǐՏ��
	case EState::eChase:
		UpdateChase();
		break;
		// �v���C���[�̍U��Hit
	case EState::eHit:
		UpdateHit();
		break;
		// ���S
	case EState::eDeth:
		UpdateDeth();
		break;
		// ���S�����I��
	case EState::eDethEnd:
		UpdateDethEnd();
		break;
		// �p�j����
	case EState::eWander:
		UpdateWander();
		break;
		// �o�b�N�X�e�b�v
	case EState::eBackStep:
		UpdateBackStep();
		break;
		// �W�����v�J�n
	case EState::eJumpStart:
		UpdateJumpStart();
		break;
		// �W�����v��
	case EState::eJump:
		UpdateJump();
		break;
		// �W�����v�I��
	case EState::eJumpEnd:
		UpdateJumpEnd();
		break;
	}

	if (mState != EState::eReady)
	{
		mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

		// �ړ�
		Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());

		CVector PlayerPosition;

		// CSoldier���ړ������֌�����
		CVector current = VectorZ();
		CVector target = mTargetDir;
		CVector forward = CVector::Slerp(current, target, 0.125f);
		Rotation(CQuaternion::LookRotation(forward));
	}

	//// CSoldier�̃f�o�b�O�\��
	//static bool debug = false;
	//if (CInput::PushKey('F'))
	//{
	//	debug = !debug;
	//}
	//if (debug)
	//{
	//	//CDebugPrint::Print(" ���x�� %d\n", mCharaMaxStatus.level);
	//	CDebugPrint::Print(" HP%d / %d\n", mCharaStatus.hp, mCharaMaxStatus.hp);
	//	CDebugPrint::Print(" �U���l%d\n", mCharaStatus.power);
	//	CDebugPrint::Print(" ST%d / %d\n", mCharaStatus.stamina, mCharaMaxStatus.stamina);
	//}
	//// 1�L�[�������Ȃ���A�� �� ��HP����
	//if (CInput::Key('3'))
	//{
	//	if (CInput::PushKey(VK_UP)) mCharaStatus.hp++;
	//	else if (CInput::PushKey(VK_DOWN)) mCharaStatus.hp--;
	//}
	//else if (CInput::Key('2'))
	//{
	//	LevelUp();
	//}

	// �t���[���ƃQ�[�W�̕\������
	UpdateGaugeAndFrame();
	// �r�b�N���}�[�N�̕\������
	UpdateExclamation();

	// ���݂�Hp��ݒ�
	mpGauge->SetValue(mCharaStatus.hp);


	// CSoldier�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpAttackCol->Update();
	mpGun->UpdateAttachMtx();

	mIsGrounded = false;

	//// �e�̊J�n�l���Ď�
	//CDebugPrint::Print("Shot%d\n", mTimeShot);
	//// �e�̏I���l���Ď�
	//CDebugPrint::Print("Shotend%d\n", mTimeShotEnd);
	//// �O�t���[����FPS���Ď�
	//CDebugPrint::Print("FPS:%f\n", Time::FPS());
	
}

// �`��
void CSoldier::Render()
{
	CXCharacter::Render();
}