#include "CPicoChan.h"
#include "CCamera.h"
#include "CBillBoard.h"
#include "CImage.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CInput.h"
#include "CGameManager.h"
#include "CStageManager.h"
#include "CPicoSword.h"
#include "CPicoChanUI.h"

// �s�R�����̓���
#define PICO_HEIGHT 1.0f
// �ړ����x
#define MOVE_SPEED 0.6f
// �_�b�V�����x
#define DASH_SPEED 1.2f
// �����ړ����x
#define MOVE_AUTOMATIC_SPEED 30.0f
// �W�����v���x
#define JUMP_SPEED 1.5f
// �d�͉����x
#define GRAVITY 0.0625f

// ����̊p�x
#define FOV_ANGLE 100.0f
// �v���C���[�܂ł̋���
#define ATTACK_RANGE 70.0f
// �v���C���[�܂ł̋���(�L�b�N)
#define ATTACK_RANGE_KICK 25.0f
// �v���C���[�܂ł̋���(�o�b�N�X�e�b�v)
#define BACKSTEP_RANGE 24.0f
// �o�b�N�X�e�b�v�̑ҋ@����
#define BACKSTEP_WEIT_TIME 5.0f

// �G������������̎���
#define PLAYER_LOST 10.0f

// �L�b�N�R���C�_�[�̎���
#define KICKCOL 10.0f

// �v���C���[�𔭌�������̎���
#define DISCOVERY 1.0f
// �v���C���[�𔭌�������̑҂�����
#define DISCOVERY_END 40.0f

// �s�R�����̃C���X�^���X
CPicoChan* CPicoChan::spInstance = nullptr;

CPicoChan* CPicoChan::Instance()
{
	return spInstance;
}

// �s�R�����̃A�j���[�V�����f�[�^�̃e�[�u��
const CPicoChan::AnimData CPicoChan::ANIM_DATA[] =
{
	{ "",													true,	  0.0f	},	// T�|�[�Y
	{ "Character\\PicoChan\\anim\\Idle_266_2.x",			true,   266.0f	},	// Idle1
	{ "Character\\PicoChan\\anim\\Idle_421_1.x",			true,   421.0f	},	// Idle2
	{ "Character\\PicoChan\\anim\\Walk_61_1.x",				true,   61.0f	},	// ����
	{ "Character\\PicoChan\\anim\\Walk_82_2.x",				true,   82.0f	},	// ���펝������
	{ "Character\\PicoChan\\anim\\Run_44_1.x",				true,   44.0f	},	// ����
	{ "Character\\PicoChan\\anim\\Run_37_2.x",				true,   37.0f	},	// ���펝������
	{ "Character\\PicoChan\\anim\\BackJump_52_1.x",		false,		52.0f	},	// �o�b�N�W�����v(false)
	{ "Character\\PicoChan\\anim\\DashJump_53_1.x",		false,		53.0f	},	// �_�b�V���W�����v(false)
	{ "Character\\PicoChan\\anim\\Death_235_1.x",		false,		235.0f	},	// ���S1(false)
	{ "Character\\PicoChan\\anim\\Death_145_2.x",		false,		145.0f	},	// ���S2(false)
	{ "Character\\PicoChan\\anim\\Kick_105_1.x",		false,		105.0f	},	// �L�b�N(false)
	{ "Character\\PicoChan\\anim\\Putaway_45_1.x",		false,		45.0f	},	// ��������܂�
	{ "Character\\PicoChan\\anim\\WeaponDraw_48_1.x",	false,		48.0f	},	// ������o��(false)
	{ "Character\\PicoChan\\anim\\WeakAttack_77_1.x",	false,		77.0f	},	// ��U��(false)
	{ "Character\\PicoChan\\anim\\SpinAttack_113_1.x",	false,		113.0f	},	// ��]�U��(false)
	{ "Character\\PicoChan\\anim\\Turn180_134.x",		false,		134.0f	},	// �U��Ԃ�(false)
	{ "Character\\PicoChan\\anim\\Alert_223_1.x",			true,	223.0f	},	// �x��1
	{ "Character\\PicoChan\\anim\\Alert_454_2.x",			true,	454.0f	},	// �x��2
	{ "Character\\PicoChan\\anim\\Hit_72_1.x",			false,		72.0f	},	// ��e(false)
};

// �R���X�g���N�^
CPicoChan::CPicoChan()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eReady)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mElapsedTimeEnd(0.0f)
	, mKickTime(0.0f)
	, mBackStepTime(0.0f)
	, mDiscoveryTime(0.0f)
	, mDiscoveryTimeEnd(0.0f)
	, mMaxRadius(0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mInitialPosition(0.0f, 0.0f, 0.0f)
	, mCenterPoint(CVector::zero)
	, mTimeToChange(Math::Rand(2.0f, 5.0f))
	, mIsGrounded(false)
	, mKickTimeEnd(false)
	, mDiscovery(false)
	, mDiscoveryEnd(false)
	, mBackStep(false)
	, mIsLerping(false)
	, mpRideObject(nullptr)
	, mDash(false)
	, mDashTime(0.0f)
	, mIsAttack(false)
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// �����ʒu�̕ۑ�
	//Position(mInitialPosition);
	mInitialPosition = Position();

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Pico");

	mpUI = new CPicoChanUI();
	mpUI->SetCenterRatio(CVector2(0.3f, 0.0f));

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
	ChangeAnimation(EAnimType::eIdle1);

	// �t�B�[���h�Ƃ̓����蔻������R���C�_�[
	mpLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PICO_HEIGHT, 0.0f)
	);
	mpLine->SetCollisionLayers({ ELayer::eField });

	// �ꎞ�I�ȓ����蔻������R���C�_�[
	mpCapsule = new CColliderCapsule
	(
		this, ELayer::ePlayer,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PICO_HEIGHT, 0.0f),
		3.0f,
		true,
		1.0f
	);
	mpCapsule->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField, ELayer::eFieldEnemyWall });
	mpCapsule->Position(0.0f, 5.0f, 1.0f);

	// �_���[�W���󂯂�R���C�_�[
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.35f
	);
	// �_���[�W���󂯂�R���C�_�[��
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol, ELayer::eDamageCol,ELayer::eEnemy });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon, ETag::eEnemy });
	// �_���[�W���󂯂�R���C�_�[���������ւ��炷
	mpDamageCol->Position(0.0f, 1.0f, 0.0f);
	//const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	//mpDamageCol->SetAttachMtx(spineMtx);

	// �_���[�W��^����R���C�_�[
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eKickCol,
		0.1f
	);
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
	mpAttackCol->SetEnable(false);
	// �E��
	const CMatrix* spineMtxK = GetFrameMtx("root_LeftToe_end");
	mpAttackCol->SetAttachMtx(spineMtxK);

	// �}�W�b�N�\�[�h�쐬
	mpSword = new CPicoSword();
	//mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	mpSword->SetPicoChanInstance(this);
	mpSword->SetOwner(this);

	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}

// �f�X�g���N�^
CPicoChan::~CPicoChan()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);

	// �R���C�_�[�֘A�̔j��
	SAFE_DELETE(mpLine);
	SAFE_DELETE(mpCapsule);
	SAFE_DELETE(mpDamageCol);
	SAFE_DELETE(mpAttackCol);

	// �}�W�b�N�\�[�h�j��
	mpSword->Kill();

	mpUI->Kill();
}

// �Փˏ���
void CPicoChan::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// ����R���C�_�[
	if (self == mpLine)
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

	// ��ɕǂƂ̓����蔻������R���C�_�[
	if (self == mpCapsule)
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
			bool canBeHit = (mState != EState::eWeakAttack && mState != EState::eSpinAttack);
			if (canBeHit)
			{
				CPlayer* player = CPlayer::Instance();
				CVector vp = player->Position() - Position();
				float distancePlayer = vp.Length();
				vp.Y(0.0f);
				mTargetDir = vp.Normalized();

				int hitRand = Math::Rand(0, 100);
				if (hitRand >= 90) // 10%�̊m���ŉ��̏��������s
				{
					int random = Math::Rand(0, 2);
					if (random == 0 || random == 1 || random == 2)
					{
						mpDamageCol->SetEnable(false);
						ChangeState(EState::eHit);
					}
					/*else if (random == 1)
					{
						ChangeState(EState::eHit2);
					}*/
				}
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
void CPicoChan::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// ��_���[�W����
void CPicoChan::TakeDamage(int damage)
{
	mCharaStatus.hp -= damage;

	// HP��0�ɂȂ�����
	if (mCharaStatus.hp <= 0)
	{
		ChangeState(EState::eDeath);
	}
}

// ���x���A�b�v
void CPicoChan::LevelUp()
{
	int level = mCharaStatus.level;
	ChangeLevel(level + 1);
}

// ���x����ύX
void CPicoChan::ChangeLevel(int level)
{
	// �X�e�[�^�X�̃e�[�u���̃C���f�b�N�X�n�ɕϊ�
	int index = Math::Clamp(level - 1, 0, PICOCHAN_LEVEL_MAX);
	// �ő�X�e�[�^�X�ɐݒ�
	mCharaMaxStatus = ENEMY_STATUS[index];
	// ���݂̃X�e�[�^�X���ő�l�ɂ��邱�ƂŁAHP��
	mCharaStatus = mCharaMaxStatus;

	mpUI->SetMaxValue(mCharaMaxStatus.hp);
	mpUI->SetValue(mCharaStatus.hp);
}

// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
void CPicoChan::UpdateGaugeAndFrame()
{
	if (mDiscovery)
	{
		mpUI->SetShow(false);
	}
	else
	{
		// HP�Q�[�W�̍��W���X�V (�G�̍��W�̏�����̍��W)
		CVector gaugePos = Position() + CVector(0.0f, 45.0f, 0.0f);
		mpUI->SetWorldPos(gaugePos);
	}
}

// �s�R�����̕����������_���ɕύX���鏈��
void CPicoChan::ChangeDerection()
{
	// �����_���ȕ����ɕύX
	// �����_���Ȋp�x�����߂�
	float randomAngle = Math::Rand(0.0f, 1.0f) * 360.0f;
	// �����̌v�Z���p�x�ɑ��
	mTargetDir = CalculateDirection(randomAngle);
}

// �ҋ@��ԑJ�ڂ������
bool CPicoChan::ShouldTransitionWander()
{
	// mIsLerping��true�̏ꍇ�A�������X�L�b�v
	if (mIsLerping)
	{
		return false;
	}

	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.05f;
}

// �p�j��ԂɑJ�ڂ������
bool CPicoChan::ShouldTransition()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.01f;  // 0.1%�̊m���Ŝp�j��ԂɑJ��
}

// 360�x�̊p�x�����߂āAx����y������v�Z����
CVector CPicoChan::CalculateDirection(float angleDegrees)
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
void CPicoChan::Move()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	mIsLerping = false;

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	}
	else
	{
		mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	}

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
		mIsLerping = true;

		// �ړI�n�ւ̃x�N�g�����v�Z
		CVector direction = mCenterPoint - Position();
		direction.Normalize(); // �����x�N�g���𐳋K��

		mTargetDir = -mTargetDir;

		// ���S�_���甼�a�܂ł̋���
		CVector targetPosition = mCenterPoint + direction * mMaxRadius;

		// ��葬�x�ŖړI�n�Ɍ������Ĉړ�
		if (mIsLerping)
		{
			// �ړ����x
			float moveSpeed = 0.5f;
			newPosition = Position() + direction * moveSpeed;

			// �ړI�n�ɓ��B������ʒu���X�V
			if (CVector::Distance(Position(), targetPosition) < moveSpeed)
			{
				newPosition = targetPosition;
				mIsLerping = false;
			}
		}

		/*CDebugPrint::Print("Position:%f %f\n", Position().X(), Position().Z());
		CDebugPrint::Print("targetPosition:%f %f\n", targetPosition.X(), targetPosition.Z());*/

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

bool CPicoChan::IsAttack()
{
	return mIsAttack;
}

// ���S���W�Ɣ͈͂�ݒ�
void CPicoChan::SetCenterPoint(CVector& center, const float radius)
{
	mMaxRadius = radius;
	mCenterPoint = center;
}

// �A�j���[�V�����؂�ւ�
void CPicoChan::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �������̏��
void CPicoChan::UpdateReady()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ���
	switch (mStateStep)
	{
		// �X�e�b�v0 ����������
	case 0:
		ChangeAnimation(EAnimType::eIdle2);
		// �S�Ă̏Փ˔�����I�t�ɂ���
		SetEnableCol(false);
		// �s�R�����̈ړ����x��0�ɂ���
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
			// �s�R�����̏Փ˔�����I���ɂ���
			SetEnableCol(true);
			// ���݂̏�Ԃ�ҋ@�ɐ؂�ւ�
			mCharaStatus.hp = mCharaMaxStatus.hp;
			ChangeState(EState::eIdle);
		}
		break;
	}
}

// �ҋ@
void CPicoChan::UpdateIdle()
{
	mDiscovery = false;
	mDiscoveryEnd = false;
	mpAttackCol->SetEnable(false);
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	}
	else
	{
		mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	}

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
		// ���݂̃A�j���[�V�������I�����Ă��邩�ǂ������`�F�b�N
		if (IsAnimationFinished())
		{	
			// �����_���Ɏ��̃A�j���[�V������I��
			int random = Math::Rand(0, 1);
			if (random == 1)
			{
				ChangeAnimation(EAnimType::eIdle1);
			}
			else
			{
				ChangeAnimation(EAnimType::eIdle2);
			}
		}

		// �m���Ŝp�j��ԂɈڍs
		if (ShouldTransition())
		{
			ChangeState(EState::eWander);
		}
	}
}

// �v���C���[����
void CPicoChan::UpdateDiscovery()
{
	mDiscovery = true;
	mMoveSpeed.Y(0.0f);
	mMoveSpeed.Z(0.0f);

	// �v���C���[�܂ł̃x�N�g�������߂�
	CPlayer* player = CPlayer::Instance();
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	mIsAttack = true;
	mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	ChangeAnimation(EAnimType::eWeaponDraw);

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
			ChangeState(EState::ePutAway);
		}
	}
	//CDebugPrint::Print("discovery:%f\n", mDiscoveryTime);
}

// �ǐ�
void CPicoChan::UpdateChase()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	}
	else
	{
		mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	}
	
	if (!IsFoundPlayer())
	{
		ChangeAnimation(EAnimType::eAlert1);
		mElapsedTimeEnd += Time::DeltaTime();
		if (mElapsedTimeEnd >= PLAYER_LOST)
		{
			ChangeState(EState::ePutAway);
			mElapsedTime = 0.0f;
			mElapsedTimeEnd = 0.0f; // �v���C���[�����E�����������o�ߎ��Ԃ����Z�b�g
		}
	}
	else
	{
		mElapsedTimeEnd = 0.0f;
		CPlayer* player = CPlayer::Instance();
		CVector playerPos = player->Position();
		playerPos.Y(Position().Y());

		CVector toPlayer = (playerPos - Position()).Normalized();
		float distanceToPlayer = (player->Position() - Position()).Length();

		const float DASH_DISTANCE = 45.0f;
		const float WALK_DISTANCE = 44.0f;

		// �v���C���[�Ƃ̋����Ɋ�Â��ď�Ԃ�ύX
		if (distanceToPlayer > DASH_DISTANCE)
		{
			// Dash��Ԃɂ���
			ChangeAnimation(EAnimType::eWeaponDash);
			mMoveSpeed = toPlayer * DASH_SPEED;
			//mMoveSpeed = toPlayer * 0.0f;
		}
		else if (distanceToPlayer <= WALK_DISTANCE)
		{
			// Walk��Ԃɂ���
			ChangeAnimation(EAnimType::eWeaponWalk);
			mMoveSpeed = toPlayer * MOVE_SPEED;
			//mMoveSpeed = toPlayer * 0.0f;
		}
		//else if (DASH_DISTANCE >= distanceToPlayer <= WALK_DISTANCE)
		else if (DASH_DISTANCE >= distanceToPlayer|| distanceToPlayer <= WALK_DISTANCE)
		{
			mMoveSpeed = toPlayer * MOVE_SPEED;
			//mMoveSpeed = toPlayer * 0.0f;
		}
		
		mTargetDir = toPlayer;

		// ����������Ɉ��ȓ��ł���΍U�����[�h�ɐ؂�ւ���
		if (distanceToPlayer <= 35.0f)
		{
			mIsAttack = true;
			ChangeState(EState::eAttack);
		}
	}
}

// �U�����
void CPicoChan::UpdateAttack()
{
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	}
	else
	{
		mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	}

	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	if (distancePlayer <= ATTACK_RANGE)
	{
		CPlayer* player = CPlayer::Instance();
		CVector playerPos = player->Position();
		playerPos.Y(Position().Y());

		CVector toPlayer = (playerPos - Position()).Normalized();
		mMoveSpeed += toPlayer * 0.25;
		mTargetDir = toPlayer;

		if (distancePlayer <= 24.0f)
		{
			int random = Math::Rand(0, 2);
			if (random == 0)
			{
				ChangeState(EState::eWeakAttack);
			}
			else if (random == 1)
			{
				ChangeState(EState::eSpinAttack);
			}
			else if (random == 2)
			{
				ChangeState(EState::eKick);
			}
		}

		//if (distancePlayer <= BACKSTEP_RANGE/* && !mRollingEnd*/)
		//{
		//	//ChangeState(EState::eRolling);
		//	return;
		//}
		//else if (distancePlayer <= ATTACK_RANGE_KICK && !mKickTimeEnd)
		//{
		//	/*ChangeState(EState::eAttackKick);
		//	mKickTimeEnd = true;*/
		//	return;
		//}
		//else if (distancePlayer <= 23.0f)
		//{
		//	int random = Math::Rand(0, 1);
		//	if (random == 0)
		//	{
		//		ChangeState(EState::eWeakAttack);
		//	}
		//	else if (random == 1)
		//	{
		//		ChangeState(EState::eSpinAttack);
		//	}
		//}
	}
	else
	{
		ChangeState(EState::eChase);
		mElapsedTimeEnd = 0.0f;
		mDiscoveryTime = 0.0f;
		mDiscovery = false;
	}
}

// ��U��
void CPicoChan::UpdateWeakAttack()
{
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	}
	else
	{
		mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	}

	ChangeAnimation(EAnimType::eWeakAttack);
	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	if (GetAnimationFrame() >= 20.0f)
	{
		mpSword->AttackStart();
		if (IsAnimationFinished())
		{
			//mpAttackCol->SetEnable(true);
			ChangeState(EState::eAttackEnd);
		}
	}
}

// ��]�U��
void CPicoChan::UpdateSpinAttack()
{
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	}
	else
	{
		mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	}
	
	ChangeAnimation(EAnimType::eSpinAttack);
	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	// �v���C���[�̕����ɏ��������ړ�
	float moveAmount = 0.1f;
	mMoveSpeed = mTargetDir * moveAmount;

	if (GetAnimationFrame() >= 70.0f)
	{
		mpSword->AttackStart();
		if (IsAnimationFinished())
		{
			ChangeState(EState::eAttackEnd);
		}
	}
}


// �L�b�N
void CPicoChan::UpdateKick()
{
	// �U������Ƃ��͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	}
	else
	{
		mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	}

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
		ChangeState(EState::eKickEnd);
	}
}

// �L�b�N�I��
void CPicoChan::UpdateKickEnd()
{
	if (IsAnimationFinished())
	{
		mpAttackCol->SetEnable(false);
		ChangeState(EState::eChase);
	}
}


// ��������o��
void CPicoChan::UpdateDrawn()
{
	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// ��������܂�
void CPicoChan::UpdatePutAway()
{
	ChangeAnimation(EAnimType::ePutAway);
	if (GetAnimationFrame() >= 40.0f)
	{
		mIsAttack = false;
		ChangeState(EState::eIdle);
	}

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("root_RightHand"));
	}
	else
	{
		mpSword->AttachMtx(GetFrameMtx("root_HoodMain02"));
	}

	if (IsAnimationFinished())
	{
		if (mElapsedTime >= 0.1f)
		{
			mElapsedTime = 0.0f;
			ChangeState(EState::eIdle);
		}
		else
		{
			mElapsedTime += Time::DeltaTime();
		}
	}
	//CDebugPrint::Print("elapsed:%f\n", mElapsedTime);
}

// �U���I���҂�
void CPicoChan::UpdateAttackEnd()
{
	mpSword->AttackEnd();
	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// �v���C���[�̍U�����󂯂���
void CPicoChan::UpdateHit()
{
	// �_���[�W���󂯂����͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	mpSword->AttackEnd();

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
			mpDamageCol->SetEnable(true);
			ChangeState(EState::eChase);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}
}

// ���S
void CPicoChan::UpdateDeath()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eDeath1);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eDeathEnd);
	}
}

// ���S�����I��
void CPicoChan::UpdateDeathEnd()
{
	if (IsAnimationFinished())
	{
		Kill();
	}
}

// �p�j����
void CPicoChan::UpdateWander()
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
			ChangeAnimation(EAnimType::eIdle1);
			ChangeState(EState::eIdle);
		}
	}
}

// �v���C���[�ǐ�
bool CPicoChan::IsFoundPlayer() const
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
void CPicoChan::Update()
{
	//CDebugPrint::Print("mIsAttack:%s\n", mIsAttack ? "true" : "false");
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
		// �U��
	case EState::eAttackEnd:
		UpdateAttackEnd();
		break;
		// �U���I���҂�
	case EState::eAttackWait:
		UpdateAttackEnd();
		break;
		// ��U��
	case EState::eWeakAttack:
		UpdateWeakAttack();
		break;
		// ��]�U��
	case EState::eSpinAttack:
		UpdateSpinAttack();
		break;
		// ��������o�����
	case EState::eDrawn:
		UpdateDrawn();
		break;
		// ��������܂����
	case EState::ePutAway:
		UpdatePutAway();
		break;
		// �L�b�N
	case EState::eKick:
		UpdateKick();
		break;
		// �L�b�N�I��
	case EState::eKickEnd:
		UpdateKickEnd();
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
	case EState::eDeath:
		UpdateDeath();
		break;
		// ���S�����I��
	case EState::eDeathEnd:
		UpdateDeathEnd();
		break;
		// �p�j����
	case EState::eWander:
		UpdateWander();
		break;
	//	// �o�b�N�X�e�b�v
	//case EState::eBackStep:
	//	UpdateBackStep();
	//	break;
	//	// �W�����v�J�n
	//case EState::eJumpStart:
	//	UpdateJumpStart();
	//	break;
	//	// �W�����v��
	//case EState::eJump:
	//	UpdateJump();
	//	break;
	//	// �W�����v�I��
	//case EState::eJumpEnd:
	//	UpdateJumpEnd();
	//	break;
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

	mpUI->SetValue(mCharaStatus.hp);

	// CSoldier�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpSword->UpdateAttachMtx();
	mpAttackCol->Update();

	UpdateGaugeAndFrame();

	mIsGrounded = false;
}

// �`��
void CPicoChan::Render()
{
	CXCharacter::Render();
}