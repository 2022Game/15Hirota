#include "CSoldier.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CStageManager.h"
#include "CEnemyManager.h"
#include "CGameManager.h"
#include "CInput.h"
#include "CGun.h"
#include "CBullet.h"
#include "CKick.h"
#include "CSoldierFrame.h"
#include "CSoldierGauge.h"
#include "CExclamationMark.h"
#include "CEffect.h"

#define _USE_MATH_DEFINES

// �\���W���[�֘A
// HP
#define HP 5
// ���x��
#define LEVEL 1
// �U����
#define ATTACK 10
// �\���W���[�̓���
#define ENEMY_HEIGHT 8.0f
// �ړ����x
#define MOVE_SPEED 0.7f
// �����ړ����x
#define MOVE_AUTOMATIC_SPEED 30.0f
// �v���C���[�𔭌�������̎���
#define DISCOVERY 2.0f
// �v���C���[�𔭌�������̑҂�����
#define DISCOVERY_END 40.0f
// �G������������̎���
#define PLAYER_LOST 10.0f
// �L�b�N�R���C�_�[�̎���
#define KICKCOL 10.0f
// �d�͉����x
#define GRAVITY 0.0625f

// �p�x
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

// �e�ۊ֘A
// �e�ۂ̔��ˊԊu
#define ATTACK 10
// �e�ۂ̔��ˊԊu
#define SHOT_INTERVAL 2.0f

// �v���C���[�̃C���X�^���X
#define PLAYER_INSTANCE CPlayer::Instance()

// �\���W���[�̃C���X�^���X
CSoldier* CSoldier::spInstance = nullptr;
// �C���X�^���X
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
	, mStateStep(0)
	, mTimeShot(0)
	, mTimeShotEnd(5)
	, mElapsedTime(0.0f)
	, mElapsedTime_End(0.0f)
	, mChangeTime(0.0f)
	, mRandomCalculationTime(Math::Rand(2.0f, 5.0f))
	, mKickTime(0.0f)
	, mBackStepTime(0.0f)
	, mDiscoveryTime(0.0f)
	, mDiscoveryTimeEnd(0.0f)
	, mMaxRadius(0.0f)
	, mIsGrounded(false)
	, mKickWaitingEnd(false)
	, mDiscovery(false)
	, mDiscoveryEnd(false)
	, mBackStep(false)
	, mEnteredTheRange(false)
	, mTargetDir(CVector::forward)
	, mMoveSpeed(CVector::zero)
	, mInitialPosition(CVector::zero)
	, mCenterPoint(CVector::zero)
	, mpRideObject(nullptr)
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// �����ʒu�̕ۑ�
	mInitialPosition = Position();

	// �\���W���[�̐����擾
	CEnemyManager::IncrementSoldierCount();

	// �\���W���[�̃��f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Soldier");

	// �e���쐬
	mpGun = new CGun();
	// �E��Ɏ�������
	const CMatrix* gun = GetFrameMtx("Armature_mixamorig_RightHand");
	mpGun->AttachMtx(gun);

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

	// �c�̐����R���C�_�[
	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, ENEMY_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField });

	// �ǂ�I�u�W�F�N�g�Ƃ̓����蔻������R���C�_�[
	mpColliderCapsule = new CColliderCapsule
	(
		this, ELayer::eEnemy,
		CVector(0.0f, 4.0f, 2.0f),
		CVector(0.0f, 12.0f, 2.0f),
		5.0f,
		true,
		1.0f
	);
	mpColliderCapsule->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField, ELayer::eFieldEnemyWall });
	//mpColliderCapsule->Position(0.0f, 0.0f, 0.0f);

	// �_���[�W��^����R���C�_�[
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eKickCol,
		1.3f
	);
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
	mpAttackCol->SetEnable(false);
	// �E���̃{�[���ɐݒ�
	const CMatrix* spineMtxK = GetFrameMtx("Armature_mixamorig_RightToeBase");
	mpAttackCol->SetAttachMtx(spineMtxK);

	// �_���[�W���󂯂�R���C�_�[
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		5.0f
	);
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol, ELayer::eDamageCol,ELayer::eEnemy });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon, ETag::eEnemy });
	// �_���[�W���󂯂�R���C�_�[���������ւ��炷
	mpDamageCol->Position(0.0f, 8.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);

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

	// �t���O�ݒ�
	mKickWaitingEnd = false;
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
	SAFE_DELETE(mpColliderCapsule);
	SAFE_DELETE(mpAttackCol);
	SAFE_DELETE(mpDamageCol);
	
	// �e�̔j��
	mpGun->Kill();

	// UI�����j��
	mpGauge->Kill();
	mpFrame->Kill();
	mpExclamationMark->Kill();

	// �\���W���[�̃J�E���g��j��
	CEnemyManager::DecrementSoldierCount();
}

// �Փˏ���
void CSoldier::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �c�̐����R���C�_�[
	if (self == mpColliderLine)
	{
		// ��
		if (other->Layer() == ELayer::eField)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight
			mIsGrounded = true;

			// ����I�u�W�F�N�g
			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}

	// �ǂ�I�u�W�F�N�g�Ƃ̓����蔻������R���C�_�[
	if (self == mpColliderCapsule)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust);

			// �ړ������𔽓]
			mTargetDir = -mTargetDir;

			// ���]���������Ɍ����ĉ�]��ݒ�
			// �Ǎۂɔz�u���Ȃ��ꍇ�͕K�v�Ȃ�����
			CVector current = VectorZ();
			CVector target = mTargetDir;
			CVector forward = CVector::Slerp(current, target, 0.125f);
			Rotation(CQuaternion::LookRotation(forward));

			// ����I�u�W�F�N�g
			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
		// ��
		else if (other->Layer() == ELayer::eField)
		{
			Position(Position() + hit.adjust);
		}
		// �G�p�̕�
		else if (other->Layer() == ELayer::eFieldEnemyWall)
		{
			Position(Position() + hit.adjust);
		}
	}

	// �_���[�W���󂯂�R���C�_�[
	if (self == mpDamageCol)
	{
		// �_���[�W��^����R���C�_�[
		if (other->Layer() == ELayer::eAttackCol)
		{
			if (mState != EState::eKick)
			{
				ChangeState(EState::eHit);
			}
		}

		// �_���[�W���󂯂�R���C�_�[
		if (other->Layer() == ELayer::eDamageCol)
		{
			(other->Tag() == ETag::eEnemy);
			{
				Position(Position() + hit.adjust);
			}
		}
	}
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
	// �X�e�[�^�X�̃e�[�u���̃C���f�b�N�X�l�ɕϊ�
	int index = Math::Clamp(level - 1, 0, ENEMY_LEVEL_MAX);
	// �ő�X�e�[�^�X�ɐݒ�
	mCharaMaxStatus = ENEMY_STATUS[index];
	// ���݂̃X�e�[�^�X���ő�l�ɂ��邱�ƂŁAHP��
	mCharaStatus = mCharaMaxStatus;

	// �ő�HP�ƌ���HP��HP�Q�[�W�ɔ��f
	mpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpGauge->SetValue(mCharaStatus.hp);
}

// �J�n���̒��S���W�Ɣ͈͂�ݒ�
void CSoldier::SetCenterPoint(CVector& center, const float radius)
{
	// �J�n���̔��a
	mMaxRadius = radius;
	// �J�n���̒��S�_
	mCenterPoint = center;
}

// �ړ�����
void CSoldier::Move()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// ���x�̐ݒ�
	float moveSpeed = MOVE_AUTOMATIC_SPEED;

	// �ړ��x�N�g���̌v�Z
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// �V�����ʒu���v�Z
	CVector newPosition = Position() + moveVector + mMoveSpeed;

	// ���S�_����̋������v�Z
	CVector offset = newPosition - mCenterPoint;
	float distance = offset.Length();

	// ���������a�𒴂����ꍇ�̏C��
	if (distance > mMaxRadius)
	{
		// �J�n���͈͓̔�����o��
		mEnteredTheRange = true;

		// �ړI�n�ւ̃x�N�g�����v�Z
		CVector direction = mCenterPoint - Position();
		// �����x�N�g���𐳋K��
		direction.Normalize();
		// ���]
		mTargetDir = -mTargetDir;

		// ���S�_���甼�a�܂ł̋���
		CVector targetPosition = mCenterPoint + direction * mMaxRadius;

		// ��葬�x�ŖړI�n�Ɍ������Ĉړ�
		if (mEnteredTheRange)
		{
			// �ړ����x
			float moveSpeed = 0.5f;
			newPosition = Position() + direction * moveSpeed;

			// �ړI�n�ɓ��B������ʒu���X�V
			if (CVector::Distance(Position(), targetPosition) < moveSpeed)
			{
				newPosition = targetPosition;
				// �J�n���͈͓̔��ɓ�����
				mEnteredTheRange = false;
			}
		}

		// �G�̌����𒲐�
		mTargetDir = (mCenterPoint - Position()).Normalized();
		mTargetDir.Y(0.0f);

		// �G��ڕW�����ɉ�]������
		CVector forward = CVector::Slerp(VectorZ(), mTargetDir, 0.125f);
		Rotation(CQuaternion::LookRotation(forward));
	}

	// �C�������ʒu��ݒ�
	Position(newPosition);
}

// 360�x�̊p�x�����߂āAx����y������v�Z����
CVector CSoldier::CalculateDirection(float angleDegrees)
{
	// �����p�x�Ƀ����_���ȃI�t�Z�b�g��ǉ�
	// 0����1�̃����_���Ȓl
	float randomOffset = Math::Rand(0.0f, 1.0f);
	float randomAngle = angleDegrees + 2.0f * M_PI * randomOffset;

	// �p�x���烉�W�A���ɕϊ�
	float angleRadians = randomAngle * M_PI / 180.0f;

	// �x�N�g���̌v�Z
	float x = cos(angleRadians);
	float y = 0.0f;				// �K�v�ɉ����ĕύX
	float z = sin(angleRadians);

	return CVector(x, y, z);
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

// �ҋ@��ԂɑJ�ڂ������
bool CSoldier::WaitingCondition()
{
	// mEnteredTheRange��true�̏ꍇ�A�������X�L�b�v
	if (mEnteredTheRange)
	{
		return false;
	}

	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	// 30%
	return randomValue < (0.3f * M_PI);
}

// �p�j��ԂɑJ�ڂ������
bool CSoldier::WanderingConditions()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	// 50%
	return randomValue < (0.5f * M_PI);
}

// �v���C���[�ǐՏ���
bool CSoldier::IsFoundPlayer() const
{
	CVector playerPos = PLAYER_INSTANCE->Position();
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

// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
void CSoldier::UpdateGaugeAndFrame()
{
	// �v���C���[�𔭌����Ĉ�莞�Ԍo�������ǂ���
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
	// �v���C���[�𔭌����Ĉ�莞�Ԍo�������ǂ���
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

// �L�b�N�̑҂�����
void CSoldier::KickWaitTime()
{
	if (mKickWaitingEnd)
	{
		mKickTime += Time::DeltaTime();
		if (mKickTime >= KICKCOL)
		{
			mKickWaitingEnd = false;
			mKickTime = 0.0f;
		}
	}
}

// �o�b�N�X�e�b�v�̑҂�����
void CSoldier::BackStepWaitTime()
{
	if (mBackStep)
	{
		mBackStepTime += Time::DeltaTime();
		if (mBackStepTime >= BACKSTEP_WEIT_TIME)
		{
			mBackStep = false;
			mBackStepTime = 0.0f;
		}
	}
}

// �v���C���[�𔭌�������̑҂�����
void CSoldier::DiscoveryWaitTime()
{
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
}

// ��ԕύX
void CSoldier::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
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

// �ҋ@���
void CSoldier::UpdateIdle()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	mDiscovery = false;
	mDiscoveryEnd = false;
	mpAttackCol->SetEnable(false);

	// �v���C���[����������A�G������Ԃ֑J��
	if (IsFoundPlayer())
	{
		// ������̑҂����Ԃ�菭�Ȃ�
		// �v���C���[�𔭌����Ĉ�莞�Ԍo�������ǂ���
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

		// �m���Ŝp�j��ԂɑJ��
		if (WanderingConditions())
		{
			ChangeState(EState::eWander);
		}
	}
}

// �U�����
void CSoldier::UpdateAttack()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	mDiscovery = false;
	
	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = PLAYER_INSTANCE->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	// �U�������W�ɓ��������ǂ���
	if (distancePlayer <= ATTACK_RANGE)
	{
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
				Position() + CVector(0.0f, 15.5f, 0.0f) + VectorZ() * 20.0f,
				VectorZ(),	// ���˕���
				1000.0f,	// �ړ�����
				1000.0f		// �򋗗�
			);

			// �S�e���˂�����A�U���I��
			mTimeShot++;
			if (mTimeShot >= mTimeShotEnd)
			{
				mTimeShot = 0;
				mElapsedTime = 0.0f;
				mDiscoveryTime = 0.0f;
				// �U���I����̑ҋ@��ԂɑJ��
				ChangeState(EState::eAttackWait);
			}
		}

		// �o�b�N�X�e�b�v�����W�ɓ��������ǂ���
		// �o�b�N�X�e�b�v���s���邩�ǂ���
		if (distancePlayer <= BACKSTEP_RANGE && !mBackStep)
		{
			mBackStep = true;
			ChangeState(EState::eBackStep);
			return;
		}
		// �L�b�N�����W�ɓ��������ǂ���
		// // �L�b�N�̑҂����Ԃ��I����Ă��邩�ǂ���
		else if (distancePlayer <= ATTACK_RANGE_KICK && !mKickWaitingEnd)
		{
			mKickWaitingEnd = true;
			ChangeState(EState::eKick);
			return;
		}
	}
	else
	{
		mDiscoveryTime = 0.0f;
		mElapsedTime_End = 0.0f;
		ChangeState(EState::eChase);
	}
}

// �U���I���҂����
void CSoldier::UpdateAttackWait()
{
	ChangeAnimation(EAnimType::eReload);
	if (IsAnimationFinished())
	{
		// �v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = PLAYER_INSTANCE->Position() - Position();
		float distancePlayer = vp.Length();
		vp.Y(0.0f);
		mTargetDir = vp.Normalized();

		// �v���C���[�܂ł̋������U�������W���ł����
		if (distancePlayer <= ATTACK_RANGE)
		{
			ChangeState(EState::eAttack);
		}
		// �͈͊O
		else
		{
			mDiscoveryTime = 0.0f;
			mElapsedTime_End = 0.0f;
			ChangeState(EState::eAimDwon);
		}
	}
}

// �L�b�N���
void CSoldier::UpdateKick()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	ChangeAnimation(EAnimType::eKick);

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = PLAYER_INSTANCE->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	// �A�j���[�V�����̃t���[����45f�ȏ�
	if (mAnimationFrame >= 45.0f)
	{
		// �R���C�_�[���I��
		mpAttackCol->SetEnable(true);
		ChangeState(EState::eKickWait);
	}
}

// �L�b�N�I�����
void CSoldier::UpdateKickWait()
{
	// �A�j���[�V�����̃t���[����75f�ȏ�
	if (mAnimationFrame >= 70.0f)
	{
		// �R���C�_�[���I�t
		mpAttackCol->SetEnable(false);
		if (IsAnimationFinished())
		{
			ChangeAnimation(EAnimType::eIdle);
			ChangeState(EState::eChase);
		}
	}
}

// �G�C���������
void CSoldier::UpdateAimDwon()
{
	ChangeAnimation(EAnimType::eAimDwou);
	if (IsAnimationFinished())
	{
		mElapsedTime_End = 0.0f;
		ChangeState(EState::eIdle);
	}
}

// �v���C���[�������
void CSoldier::UpdateDiscovery()
{
	mMoveSpeed.Y(0.0f);
	mMoveSpeed.Z(0.0f);
	mDiscovery = true;

	// �v���C���[�������̎��Ԃ𑝉�
	mDiscoveryTime += Time::DeltaTime();

	ChangeAnimation(EAnimType::eRifleIdle);

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = PLAYER_INSTANCE->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();
	
	// �v���C���[�������Ԃ�DISCOVERY���傫���ǂ���
	if (mDiscoveryTime >= DISCOVERY)
	{
		// �v���C���[�����������ǂ���
		if (IsFoundPlayer())
		{
			mDiscoveryEnd = true;
			ChangeState(EState::eChase);
		}
		// �v���C���[���������Ă��邩�ǂ���
		else
		{
			mDiscoveryTime = 0.0f;
			ChangeState(EState::eAimDwon);
		}
	}
}

// �ǐՏ��
void CSoldier::UpdateChase()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// �v���C���[���������Ă��邩�ǂ���
	if (!IsFoundPlayer())
	{
		ChangeAnimation(EAnimType::eRifleIdle);

		mElapsedTime_End += Time::DeltaTime();
		// �������Ԃ�PLAYER_LOST���傫�����ǂ���
		if (mElapsedTime_End >= PLAYER_LOST)
		{
			mElapsedTime_End = 0.0f;
			ChangeState(EState::eAimDwon);
		}
	}
	// �v���C���[��������
	else
	{
		ChangeAnimation(EAnimType::eAlert);

		mElapsedTime_End = 0.0f;

		// Y���W�����݂̃I�u�W�F�N�g��Y���W�ɕύX��
		CVector playerPos = PLAYER_INSTANCE->Position();
		playerPos.Y(Position().Y());

		// �v���C���[�Ɍ������Ĉړ����邽�߂̕����Ƒ��x���v�Z
		CVector toPlayer = (playerPos - Position()).Normalized();
		mMoveSpeed += toPlayer * MOVE_SPEED;
		mTargetDir = toPlayer;

		// �v���C���[�Ƃ̋��������͈͈ȓ��ł���΍U�����[�h�ɐ؂�ւ���
		CVector vp = PLAYER_INSTANCE->Position() - Position();
		float distancePlayer = vp.Length();
		vp.Y(0.0f);
		
		// �U�������W�ɓ��������ǂ���
		if (distancePlayer <= ATTACK_RANGE)
		{
			ChangeState(EState::eAttack);
		}
	}
}

// �p�j���
void CSoldier::UpdateWander()
{
	// �R���C�_�[�I�t
	mpAttackCol->SetEnable(false);
	ChangeAnimation(EAnimType::eWalk);

	// �ړ�����
	Move();

	// ��莞�Ԃ��Ƃɕ����]��
	mChangeTime += Time::DeltaTime();
	if (mChangeTime >= mRandomCalculationTime)
	{
		ChangeDerection();
		mChangeTime = 0.0f;
	}

	// �v���C���[�����������ǂ���
	if (IsFoundPlayer())
	{
		// �v���C���[��������̎��Ԃ��o�߂��Ă��Ȃ�
		if (mDiscoveryTimeEnd <= DISCOVERY_END)
		{
			ChangeState(EState::eDiscovery);
		}
		// �v���C���[��������̎��Ԃ��o�߂��Ă���
		else
		{
			ChangeState(EState::eChase);
		}
	}
	// �v���C���[���������Ă��邩�ǂ���
	else
	{
		// �m���őҋ@��ԂɑJ��
		if (WaitingCondition())
		{
			ChangeState(EState::eIdle);
		}
	}
}

// �o�b�N�X�e�b�v���
void CSoldier::UpdateBackStep()
{
	mMoveSpeed.X(0.0f);

	ChangeAnimation(EAnimType::eBackStep);

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = PLAYER_INSTANCE->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	// �o�b�N�X�e�b�v���鋗��
	const float backStepDistance = 15.0f;

	CVector playerPos = PLAYER_INSTANCE->Position();
	CVector soldierPos = Position();
	CVector toPlayer = (playerPos - soldierPos).Normalized();

	Position(Position() - toPlayer * backStepDistance * Time::DeltaTime());
	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// �v���C���[�̍U��Hit���
void CSoldier::UpdateHit()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	ChangeAnimation(EAnimType::eHit);
	if (IsAnimationFinished())
	{
		// �v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = PLAYER_INSTANCE->Position() - Position();
		float distancePlayer = vp.Length();
		vp.Y(0.0f);
		mTargetDir = vp.Normalized();

		// HP��1���傫����ΐ���
		if (mCharaStatus.hp >= 1)
		{
			ChangeState(EState::eChase);
		}
		// ���S
		else if (mCharaStatus.hp <= 0)
		{
			// �R���C�_�[�I�t
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeth);
		}
	}
}

// ���S���
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

// ���S�����I�����
void CSoldier::UpdateDethEnd()
{
	if (IsAnimationFinished())
	{
		Kill();
	}
}

// �X�V����
void CSoldier::Update()
{
	SetParent(mpRideObject);
	mpRideObject = nullptr;

	// �L�b�N�̑҂�����
	KickWaitTime();
	// �o�b�N�X�e�b�v�̑҂�����
	BackStepWaitTime();
	// �v���C���[�𔭌�������̑҂�����
	DiscoveryWaitTime();
	
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
		// �U�����
	case EState::eAttack:
		UpdateAttack();
		break;
		// �U���I���҂����
	case EState::eAttackWait:
		UpdateAttackWait();
		break;
		// �L�b�N���
	case EState::eKick:
		UpdateKick();
		break;
		// �L�b�N�I�����
	case EState::eKickWait:
		UpdateKickWait();
		break;
		// �G�C���������
	case EState::eAimDwon:
		UpdateAimDwon();
		break;
		// �v���C���[�������
	case EState::eDiscovery:
		UpdateDiscovery();
		break;
		// �ǐՏ��
	case EState::eChase:
		UpdateChase();
		break;
		// �p�j�������
	case EState::eWander:
		UpdateWander();
		break;
		// �o�b�N�X�e�b�v���
	case EState::eBackStep:
		UpdateBackStep();
		break;
		// �v���C���[�̍U��Hit���
	case EState::eHit:
		UpdateHit();
		break;
		// ���S���
	case EState::eDeth:
		UpdateDeth();
		break;
		// ���S�����I�����
	case EState::eDethEnd:
		UpdateDethEnd();
		break;
	}

	// ������Ԃł͂Ȃ��Ƃ��̏���
	if (mState != EState::eReady)
	{
		mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

		// �ړ�
		Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());

		// �\���W���[���ړ������֌�����
		CVector current = VectorZ();
		CVector target = mTargetDir;
		CVector forward = CVector::Slerp(current, target, 0.125f);
		Rotation(CQuaternion::LookRotation(forward));
	}

	// �t���[���ƃQ�[�W�̕\������
	UpdateGaugeAndFrame();
	// �r�b�N���}�[�N�̕\������
	UpdateExclamation();

	// ���݂�Hp��ݒ�
	mpGauge->SetValue(mCharaStatus.hp);

	// �\���W���[�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpAttackCol->Update();
	mpGun->UpdateAttachMtx();

	mIsGrounded = false;
}

// �`�揈��
void CSoldier::Render()
{
	CXCharacter::Render();
}