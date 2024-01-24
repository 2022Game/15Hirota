#include "CVanguard.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CKick.h"
#include "CEnemyManager.h"
#include "CExclamationMark.h"
#include "CStageManager.h"

#define _USE_MATH_DEFINES

// ���@���K�[�h�֘A
// ���@���K�[�h�̓���
#define VANGUARD_HEIGHT 8.0f
// �ړ����x
#define MOVE_SPEED 0.9f
// �����ړ����x
#define MOVE_AUTOMATIC_SPEED 50.0f
// �W�����v���x
#define JUMP_SPEED 1.5f
// �d�͉����x
#define GRAVITY 0.0625f


// �Ǐ]���̈ړ����x
// ����̊p�x
#define FOV_ANGLE 100.0f
// �v���C���[�܂ł̋���
#define ATTACK_RANGE 70.0f
// �v���C���[�܂ł̋���(�L�b�N)
#define ATTACK_RANGE_KICK 25.0f
// �v���C���[�܂ł̋���(�o�b�N�X�e�b�v)
#define BACKSTEP_RANGE 24.0f


// HP�֘A
#define HP 5
// ���x���֘A
#define LEVEL 1
// �U���͊֘A
#define ATTACK 10


// �G������������̎���
#define PLAYER_LOST 10.0f

// �L�b�N�R���C�_�[�̎���
#define KICKCOL 10.0f

// �v���C���[�𔭌�������̎���
#define DISCOVERY 2.0f
// �v���C���[�𔭌�������̑҂�����
#define DISCOVERY_END 40.0f

// CVanguard�̃C���X�^���X
CVanguard* CVanguard::spInstance = nullptr;


CVanguard* CVanguard::Instance()
{
	return spInstance;
}

//Vanguard_Walk_1_86
// CVanguard�̃A�j���[�V�����f�[�^�̃e�[�u��
const CVanguard::AnimData CVanguard::ANIM_DATA[] =
{
	{ "",																	true,	  0.0f	},	// T�|�[�Y
	{"Character\\Vanguard\\anim\\Vanguard_Idle_1_111.x",				false,		111.0f	},	// �ҋ@���1
	{"Character\\Vanguard\\anim\\Vanguard_Idle_2_676.x",				false,		676.0f	},	// �ҋ@���2
	{"Character\\Vanguard\\anim\\Vanguard_Walk_1_82.x",						true,	 82.0f  },	// �ړ����1
	//{"Character\\Vanguard\\anim\\Vanguard_WalkBack_1_78.x",					true,    78.0f	},	// ���ړ�1
	{"Character\\Vanguard\\anim\\Vanguard_Walk Mutant_1_86.x",				true,	 86.0f  },	// ��������
	{"Character\\Vanguard\\anim\\Vanguard_Walk Weapon_1_80.x",				true,	 80.0f  },	// �������
	{"Character\\Vanguard\\anim\\Vanguard_ShieldWalk_1_66.x",				true,    77.0f	},	// ������
	{"Character\\Vanguard\\anim\\Vanguard_ShieldBackWalk_1_76.x",			true,    76.0f	},	// ��������1
	{"Character\\Vanguard\\anim\\Vanguard_Run Back Shield_1_17.x",			true,	 17.0f	},	// ��������2
	{"Character\\Vanguard\\anim\\Vanguard_Run_1_43.x",						true,	 43.0f	},	// �_�b�V�����
	{"Character\\Vanguard\\anim\\Vanguard_Walk Brisk_1_45.x",				true,	 45.0f  },	// ������
	{"Character\\Vanguard\\anim\\Vanguard_Run Shield_1_22.x",				true,	 22.0f	},	// ������
	{"Character\\Vanguard\\anim\\Vanguard_Jump_1_114.x",					true,	114.0f	},	// �W�����v
	{"Character\\Vanguard\\anim\\Vanguard_RunDash_1_84.x",					true,	 84.0f	},	// ����W�����v
	{"Character\\Vanguard\\anim\\Vanguard_RunDash_1_26.x",					true,    26.0f	},	// �_�b�V���W�����v
	{"Character\\Vanguard\\anim\\Vanguard_StandUp_1_38.x",				false,		 38.0f	},	// �����オ��
	{"Character\\Vanguard\\anim\\Vanguard_IdleWeapon_1_111.x",			false,		111.0f	},	// ���펝�ҋ@	
	{"Character\\Vanguard\\anim\\Vanguard_Attack Spin_1_105.x",			false,		105.0f	},	// �X�s���U��1
	{"Character\\Vanguard\\anim\\Vanguard_Spin Attack_2_191.x",			false,		191.0f	},	// �X�s���U��2
	{"Character\\Vanguard\\anim\\Vanguard_Attack Swing Up_1_191.x",		false,		191.0f	},	// �U��グ�U��1
	{"Character\\Vanguard\\anim\\Vanguard_Attacks 3_1_219.x",			false,		219.0f	},	// 3�A�U��
	{"Character\\Vanguard\\anim\\Vanguard_Attack Kick_1_112.x",			false,		112.0f	},	// �E���L�b�N
	{"Character\\Vanguard\\anim\\Vanguard_Attack Jump Dash_1_221.x",	false,		221.0f	},	// �W�����v�U��1
	{"Character\\Vanguard\\anim\\Vanguard_Attack Run Jump_1_140.x",		false,		140.0f	},	// �W�����v�U��2
	{"Character\\Vanguard\\anim\\Vanguard_Sword Back Drawn_1_38.x",		false,		 38.0f	},	// ��������ɂ��܂�1
	{"Character\\Vanguard\\anim\\Vanguard_Sheathing of Sword_1_103.x",	false,		103.0f	},	// ��������ɂ��܂�2
	{"Character\\Vanguard\\anim\\Vanguard_Shield_1_84.x",					true,	 84.0f	},	// ���\��
	{"Character\\Vanguard\\anim\\Vanguard_Sword Guard_1_111.x",				true,	111.0f  },	// ����h��
	{"Character\\Vanguard\\anim\\Vanguard_Sword Draw_1_46.x",			false,		 46.0f  },	// ��������o��1
	{"Character\\Vanguard\\anim\\Vanguard_Sword Quick Draw_1_75.x",		false,		 75.0f  },	// ��������o��2
	{"Character\\Vanguard\\anim\\Vanguard_Sword Back Drawn_2_101.x",	false,		101.0f	},	// �����납����o��
	{"Character\\Vanguard\\anim\\Vanguard_Rolling_1_108.x",				false,		108.0f	},	// ����s��
	{"Character\\Vanguard\\anim\\Vanguard_Hit Lean Back_1_43.x",		false,		 43.0f	},	// ���_���[�W1
	{"Character\\Vanguard\\anim\\Vanguard_Hit Slight_1_63.x",			false,		 63.0f	},	// ���_���[�W2
	{"Character\\Vanguard\\anim\\Vanguard_Hit Slight_2_96.x",			false,		 96.0f	},	// ���_���[�W3
	{"Character\\Vanguard\\anim\\Vanguard_GutsPose_1_72.x",				false,		 72.0f	},	// �K�b�c�|�[�Y1
	{"Character\\Vanguard\\anim\\Vanguard_GutsPose_2_171.x",			false,		171.0f	},	// �K�b�c�|�[�Y2	
	{"Character\\Vanguard\\anim\\Vanguard_Lose Sight of_1_221.x",			true,	221.0f	},	// ���������
	{"Character\\Vanguard\\anim\\Vanguard_Pointing_1_62.x",				false,		 62.0f	},	// �w����
	{"Character\\Vanguard\\anim\\Vanguard_Death_2_138.x",				false,		138.0f	},	// ���S1anim\Vanguard_WalkBack_1_78
};

// �R���X�g���N�^
CVanguard::CVanguard()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eIdle)
	, mElapsedTime(0.0f)
	, mElapsedTime_End(0.0f)
	, mKickTime(0.0f)
	, mBackStepTime(0.0f)
	, mDiscoveryTime(0.0f)
	, mDiscoveryTime_End(0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mInitialPosition(0.0f, 0.0f, 0.0f)
	, mTimeToChange(Math::Rand(1.0f, 5.0f))
	, mIsGrounded(false)
	, mKickTimeEnd(false)
	, mDiscovery(false)
	, mDiscoveryEnd(false)
	, mpRideObject(nullptr)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// �����ʒu�̕ۑ�
	mInitialPosition = Position();

	// �\���W���[�̐����擾
	CEnemyManager::IncrementVanguardCount();

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Vanguard");

	// �r�b�N���}�[�N�ݒ�
	mpExclamationMark = new CExclamationMark();
	mpExclamationMark->SetCeneterRatio(CVector2(0.3f, 0.5f));

	// �e�[�u�����̃A�j���[�V�����f�[�^��ǂݍ���
	int size ARRAY_SIZE(ANIM_DATA);
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
	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, VANGUARD_HEIGHT, 0.0f)
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

	mKickTimeEnd = false;
	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}

// �f�X�g���N�^
CVanguard::~CVanguard()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);

	// �R���C�_�[�֘A�̔j��
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderSphere);
	SAFE_DELETE(mpDamageCol);
	SAFE_DELETE(mpAttackCol);

	// ���@���K�[�h�̃J�E���g��j��
	CEnemyManager::DecrementVanguardCount();

	// UI�����j��
	mpExclamationMark->Kill();
}

// �Փˏ���
void CVanguard::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
void CVanguard::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// ��_���[�W����
void CVanguard::TakeDamage(int damage)
{
	mCharaStatus.hp -= damage;

	// HP��0�ɂȂ�����
	if (mCharaStatus.hp <= 0)
	{
		ChangeState(EState::eDeth);
	}
}

// ���x���A�b�v
void CVanguard::LevelUp()
{
	int level = mCharaStatus.level;
	ChangeLevel(level + 1);
}

// ���x����ύX
void CVanguard::ChangeLevel(int level)
{
	// �X�e�[�^�X�̃e�[�u���̃C���f�b�N�X�l�ɕύX
	int index = Math::Clamp(level - 1, 0, VANGUARD_LEVEL_MAX);
	// �ő�X�e�[�^�X�ɐݒ�
	mCharaMaxStatus = VANGUARD_STATUS[index];
	// ���݂̃X�e�[�^�X���ő�l�ɂ��邱�ƂŁAHP��
	mCharaStatus = mCharaMaxStatus;

	/* �ő�HP�ƌ���HP��HP�Q�[�W�ɔ��f
	mpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpGauge->SetValue(mCharaStatus.hp);*/
}

// ���@���K�[�h�̕����������_���ɕύX���鏈��
void CVanguard::ChangeDerection()
{
	// �����_���ȕ����ɕύX
	// �����_���Ȋp�x�����߂�
	float randomAngle = Math::Rand(0.0f, 1.0f) * 360.0f;
	// �����̌v�Z���p�x�ɑ��
	mTargetDir = CalculateDirection(randomAngle);
}
//
//// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
//void CVanguard::UpdateGaugeAndFrame()
//{
//	if (!mDiscovery)
//	{
//		// HP�Q�[�W�̍��W���X�V (�G�̍��W�̏�����̍��W)
//		CVector gaugePos = Position() + CVector(0.0f, 25.0f, 0.0f);
//		mpGauge->SetWorldPos(gaugePos);
//		CVector framePos = Position() + CVector(0.0f, 25.0f, 0.0f);
//		mpFrame->SetWorldPos(framePos);
//	}
//	else
//	{
//		mpGauge->SetShow(false);
//		mpFrame->SetShow(false);
//	}
//}
//
//// �r�b�N���}�[�N�̕\���̊m�F�����鏈��
//void CVanguard::UpdateExclamation()
//{
//	if (mDiscovery)
//	{
//		// �r�b�N���}�[�N�摜�̍��W���X�V
//		CVector exclamationMardPos = Position() + CVector(0.0f, 25.0f, 0.0f);
//		mpExclamationMark->SetWorldPos(exclamationMardPos);
//	}
//	else
//	{
//		mpExclamationMark->SetShow(false);
//	}
//}

// �ҋ@��ԑJ�ڂ������
bool CVanguard::ShouldTransitionWander()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.01f;  // 0.1%�̊m���őҋ@�ɑJ��
}

// �p�j��ԂɑJ�ڂ������
bool CVanguard::ShouldTransition()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.1f;  // 0.1%�̊m���Ŝp�j��ԂɑJ��
}

// 360�x�̊p�x�����߂āAx����y������v�Z����
CVector CVanguard::CalculateDirection(float angleDegrees)
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
void CVanguard::Move()
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
void CVanguard::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �ҋ@
void CVanguard::UpdateIdle()
{
	mDiscovery = false;
	mpAttackCol->SetEnable(false);
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	//�v���C���[����������A�G������Ԃֈڍs
	if (IsFoundPlayer())
	{
		if (mDiscoveryTime_End <= DISCOVERY_END)
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
		int random = Math::Rand(0, 10);

		if (random >= 0 && random <= 5 && IsAnimationFinished())
		{
			ChangeAnimation(EAnimType::eIdle1);
		}
		else if (random >= 6 && random <= 10 && IsAnimationFinished())
		{
			ChangeAnimation(EAnimType::eAttackSpin1);
		}

		//// �m���Ŝp�j��ԂɈڍs
		//if (ShouldTransition())
		//{
		//	ChangeState(EState::eWander);
		//}
	}
}

void CVanguard::UpdateAttack()
{
	mDiscovery = false;

	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	if (distancePlayer <= ATTACK_RANGE)
	{
		if (distancePlayer <= BACKSTEP_RANGE)
		{
			ChangeState(EState::eRolling);
			return;
		}
		else if (distancePlayer <= ATTACK_RANGE_KICK && !mKickTimeEnd)
		{
			ChangeState(EState::eKick);
			mKickTimeEnd = true;
			return;
		}
		ChangeAnimation(EAnimType::eAttackSpin1);
	}
	
}
// �U���I���҂�
void CVanguard::UpdateAttackWait()
{
	ChangeAnimation(EAnimType::eSwordDrawn2);
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
			ChangeState(EState::eAttackEnd);
			mElapsedTime_End = 0.0f;
			mDiscoveryTime = 0.0f;
			mDiscovery = false;
		}
	}
}

// �v���C���[����
void CVanguard::UpdateDiscovery()
{
	mDiscovery = true;
	mMoveSpeed.Y(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eWalkWeapon);

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
			mDiscovery = false;
			mDiscoveryEnd = true;
			ChangeState(EState::eChase);
		}
		else
		{
			mDiscovery = false;
			mDiscoveryTime = 0.0f;
			ChangeState(EState::eAttackEnd);
		}
	}
	//CDebugPrint::Print("discovery:%f\n", mDiscoveryTime);
}

// �ǐ�
void CVanguard::UpdateChase()
{
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	if (!IsFoundPlayer())
	{
		ChangeAnimation(EAnimType::eLoseSight);
		mElapsedTime_End += Time::DeltaTime();
		//CDebugPrint::Print("TimeEnd%f\n", mElapsedTime_End);
		if (mElapsedTime_End >= PLAYER_LOST)
		{
			ChangeState(EState::eAttackEnd);
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
		ChangeAnimation(EAnimType::eWalkWeapon);

		if (distanceToPlayer <= ATTACK_RANGE)
		{
			ChangeState(EState::eAttack);
		}
	}
}

// �L�b�N
void CVanguard::UpdateKick()
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

	ChangeAnimation(EAnimType::eAttackKick);
	if (mAnimationFrame >= 45.0f)
	{
		mpAttackCol->SetEnable(true);
		ChangeState(EState::eKickEnd);
	}
}

// �L�b�N�I��
void CVanguard::UpdateKickWait()
{
	if (mAnimationFrame >= 70.0f)
	{
		mpAttackCol->SetEnable(false);
		if (IsAnimationFinished())
		{
			ChangeState(EState::eChase);
			ChangeAnimation(EAnimType::eIdle1);
		}

	}
}

//// ��������
//void CVanguard::UpdateDisarmament()
//{
//	ChangeAnimation(EAnimType::);
//	if (IsAnimationFinished())
//	{
//		ChangeState(EState::eIdle);
//		mElapsedTime_End = 0.0f;
//		mDiscovery = false;
//	}
//}
//
//// �v���C���[�̍U�����󂯂���
//void CVanguard::UpdateHit()
//{
//	// �_���[�W���󂯂����͈ړ����~
//	mMoveSpeed.X(0.0f);
//	mMoveSpeed.Z(0.0f);
//
//	ChangeAnimation(EAnimType::eHit);
//	if (IsAnimationFinished())
//	{
//		// �v���C���[�̃|�C���^��0�ȊO�̎�
//		CPlayer* player = CPlayer::Instance();
//
//		// �v���C���[�܂ł̃x�N�g�������߂�
//		CVector vp = player->Position() - Position();
//		float distancePlayer = vp.Length();
//		vp.Y(0.0f);
//		mTargetDir = vp.Normalized();
//
//		if (mCharaStatus.hp > 1)
//		{
//			ChangeState(EState::eChase);
//		}
//		else if (mCharaStatus.hp <= 0)
//		{
//			mpDamageCol->SetEnable(false);
//			ChangeState(EState::eDeth);
//		}
//	}
//}
//
//// ���S
//void CVanguard::UpdateDeth()
//{
//	mMoveSpeed.X(0.0f);
//	mMoveSpeed.Z(0.0f);
//	ChangeAnimation(EAnimType::eDeth);
//	if (IsAnimationFinished())
//	{
//		ChangeState(EState::eDethEnd);
//	}
//}
//
//// ���S�����I��
//void CVanguard::UpdateDethEnd()
//{
//	if (IsAnimationFinished())
//	{
//		Kill();
//	}
//}
//
// �p�j����
void CVanguard::UpdateWander()
{
	mDiscovery = false;
	mpAttackCol->SetEnable(false);
	ChangeAnimation(EAnimType::eWalkMutant);

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
		if (mDiscoveryTime_End <= DISCOVERY_END)
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

// ����s��
void CVanguard::UpdateRolling()
{
	mMoveSpeed.X(0.0f);

	ChangeAnimation(EAnimType::eRolling);

	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	// �o�b�N�X�e�b�v���鋗��
	const float backStepDistance = 0.1f;

	CVector playerPos = CPlayer::Instance()->Position();
	CVector soldierPos = Position();
	CVector toPlayer = (playerPos - soldierPos).Normalized();

	// ���̋��������o�b�N�X�e�b�v
	Position(Position() - toPlayer * backStepDistance);

	// ���[�����O���͌�����ύX���Ȃ��悤�ɂ���
	if (IsAnimationFinished())
	{
		// ���[�����O���I��������v���C���[�̕�������
		CVector newFacingDirection = (player->Position() - Position()).Normalized();
		// Y�������͕ύX���Ȃ��悤�ɂ���
		newFacingDirection.Y(0.0f);

		// ������ύX
		SetFacingDirection(newFacingDirection);

		ChangeState(EState::eChase);
	}
}

//// �v���C���[�܂ł̃x�N�g�������߂�
	//CVector vp = player->Position() - Position();
	//float distancePlayer = vp.Length();
	//vp.Y(0.0f);
	//mTargetDir = vp.Normalized();



//// �W�����v�J�n
//void CVanguard::UpdateJumpStart()
//{
//	ChangeAnimation(EAnimType::eJumpStart);
//	ChangeState(EState::eJump);
//
//	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
//	mIsGrounded = false;
//}
//
//// �W�����v��
//void CVanguard::UpdateJump()
//{
//	if (mMoveSpeed.Y() <= 0.0f)
//	{
//		ChangeAnimation(EAnimType::eJumpEnd);
//		ChangeState(EState::eJumpEnd);
//	}
//}
//
//// �W�����v�I��
//void CVanguard::UpdateJumpEnd()
//{
//	if (IsAnimationFinished())
//	{
//		ChangeState(EState::eIdle);
//	}
//}

// �v���C���[�ǐ�
bool CVanguard::IsFoundPlayer() const
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
void CVanguard::Update()
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

	// �v���C���[�𔭌�������̎��Ԃ̌v��
	if (mDiscoveryTime_End <= DISCOVERY_END && mDiscoveryEnd)
	{
		mDiscoveryTime_End += Time::DeltaTime();
		if (mDiscoveryTime_End >= DISCOVERY_END)
		{
			mDiscoveryEnd = false;
			mDiscoveryTime_End = 0.0f;
		}
	}
	CDebugPrint::Print("discoveryTimeEnd:%f\n", mDiscoveryTime_End);

	// ��Ԃɍ��킹�āA�X�V������؂�ւ���
	switch (mState)
	{
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
	case EState::eKickEnd:
		UpdateKickWait();
		break;
		// �U���I���҂�
	case EState::eAttackEnd:
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
		// �p�j����
	case EState::eWander:
		UpdateWander();
		break;
		// �o�b�N�X�e�b�v
	case EState::eRolling:
		UpdateRolling();
		break;
	}

	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// CSoldier�̃f�o�b�O�\��
	static bool debug = false;
	if (CInput::PushKey('F'))
	{
		debug = !debug;
	}
	if (debug)
	{
		//CDebugPrint::Print(" ���x�� %d\n", mCharaMaxStatus.level);
		CDebugPrint::Print(" HP%d / %d\n", mCharaStatus.hp, mCharaMaxStatus.hp);
		CDebugPrint::Print(" �U���l%d\n", mCharaStatus.power);
		CDebugPrint::Print(" ST%d / %d\n", mCharaStatus.stamina, mCharaMaxStatus.stamina);
	}
	// 1�L�[�������Ȃ���A�� �� ��HP����
	if (CInput::Key('3'))
	{
		if (CInput::PushKey(VK_UP)) mCharaStatus.hp++;
		else if (CInput::PushKey(VK_DOWN)) mCharaStatus.hp--;
	}
	else if (CInput::Key('2'))
	{
		LevelUp();
	}

	// �ړ�
	Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());

	CVector PlayerPosition;

	// CSoldier���ړ������֌�����
	CVector current = VectorZ();
	CVector target = mTargetDir;
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	//// �t���[���ƃQ�[�W�̕\������
	//UpdateGaugeAndFrame();
	//// �r�b�N���}�[�N�̕\������
	//UpdateExclamation();

	//// ���݂�Hp��ݒ�
	//mpGauge->SetValue(mCharaStatus.hp);


	// CSoldier�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpAttackCol->Update();

	mIsGrounded = false;

	//// �O�t���[����FPS���Ď�
	//CDebugPrint::Print("FPS:%f\n", Time::FPS());

}

// �`��
void CVanguard::Render()
{
	CXCharacter::Render();
}