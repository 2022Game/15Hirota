#include "CVanguard.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CKick.h"
#include "CEnemyManager.h"
#include "CExclamationMark.h"
#include "CStageManager.h"
#include "CVanguardGauge.h"
#include "CMajicSwordEnemy.h"
#include "CScore.h"
#include "CGameManager.h"

#define _USE_MATH_DEFINES

// ���@���K�[�h�֘A
// ���@���K�[�h�̓���
#define VANGUARD_HEIGHT 8.0f
// �ړ����x
#define MOVE_SPEED 0.8f
// �����ړ����x
#define MOVE_AUTOMATIC_SPEED 40.0f
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
// ����̑҂�����
#define ROLLING_END 30.0f

// CVanguard�̃C���X�^���X
CVanguard* CVanguard::spInstance = nullptr;

int CVanguard::sScore = 0;

CVanguard* CVanguard::Instance()
{
	return spInstance;
}

void CVanguard::SetScore(int score)
{
	sScore = score;
}

int CVanguard::GetScore()
{
	return sScore;
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
	{"Character\\Vanguard\\anim\\Vanguard_Rolling_1_86.x",				false,		86.0f	},	// ����s��
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
	, mTimeRolling(0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveVector(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mInitialPosition(0.0f, 0.0f, 0.0f)
	, mTimeToChange(Math::Rand(1.0f, 5.0f))
	, mIsGrounded(false)
	, mKickTimeEnd(false)
	, mDiscovery(false)
	, mDiscoveryEnd(false)
	, mRollingEnd(false)
	, mDamage(false)
	, mpRideObject(nullptr)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	sScore;

	// �����ʒu�̕ۑ�
	mInitialPosition = Position();

	// �\���W���[�̐����擾
	CEnemyManager::IncrementVanguardCount();

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Vanguard");

	// HP�Q�[�W���쐬
	mpGauge = new CVanguardGauge();
	mpGauge->SetShow(true);
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
	mpColliderSphere->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField, ELayer::eFieldEnemyWall, ELayer::ePlayer });
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
	mpDamageCol->SetCollisionTags({ ETag::eWeapon, ETag::eEnemy, ETag::eSlash });
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

	// �}�W�b�N�\�[�h�쐬
	mpSword = new CMajicSwordEnemy();
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHandMiddle1"));
	mpSword->SetOwner(this);
	mpSword->SetAlpha(0.0f);


	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}

// �f�X�g���N�^
CVanguard::~CVanguard()
{
	spInstance = nullptr;
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
	mpGauge->Kill();
	mpExclamationMark->Kill();

	// �}�W�b�N�\�[�h�j��
	mpSword->Kill();
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
		else if (other->Layer() == ELayer::ePlayer)
		{
			Position(Position() + hit.adjust);
		}
	}

	// �_���[�W���󂯂�R���C�_�[
	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eAttackCol)
		{
			bool hit = mState != EState::eAttacks3;
			bool hit1 = mState != EState::eAttackSpin1;
			bool hit2 = mState != EState::eAttackSpin2;
			bool hit3 = mState != EState::eAttackSwing;
			if (hit || hit1 || hit2 || hit3)
			{
				// �v���C���[�̃|�C���^��0�ȊO�̎�
				CPlayer* player = CPlayer::Instance();

				// �v���C���[�܂ł̃x�N�g�������߂�
				CVector vp = player->Position() - Position();
				float distancePlayer = vp.Length();
				vp.Y(0.0f);
				mTargetDir = vp.Normalized();

				int hitRand = Math::Rand(0, 100);
				//CDebugPrint::Print("hit1:%d\n", hitRand);
				if (hitRand >= 90)
				{
					int random = Math::Rand(0, 2);
					if (random == 0)
					{
						mpDamageCol->SetEnable(false);
						ChangeState(EState::eHitSlight1);
					}
					else if (random == 1)
					{
						mpDamageCol->SetEnable(false);
						ChangeState(EState::eHitSlight2);
					}
					else if (random == 2)
					{
						mpDamageCol->SetEnable(false);
						ChangeState(EState::eHitSlight3);
					}
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
		ChangeState(EState::eDeath);
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

	//�ő�HP�ƌ���HP��HP�Q�[�W�ɔ��f
	mpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpGauge->SetValue(mCharaStatus.hp);
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

// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
void CVanguard::UpdateGaugeAndFrame()
{
	if (!mDiscovery && mpExclamationMark && IsFoundPlayer())
	{
		mpGauge->SetShow(true);
	}
	else
	{
		mpGauge->SetShow(false);
	}
}

// �r�b�N���}�[�N�̕\���̊m�F�����鏈��
void CVanguard::UpdateExclamation()
{
	if (mDiscovery)
	{
		// �r�b�N���}�[�N�摜�̍��W���X�V
		CVector exclamationMardPos = Position() + CVector(0.0f, 35.0f, 0.0f);
		mpExclamationMark->SetWorldPos(exclamationMardPos);
	}
	else
	{
		mpExclamationMark->SetShow(false);
	}
}

// �ҋ@��ԑJ�ڂ������
bool CVanguard::ShouldTransitionWander()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.01f;
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
// �������̏��
void CVanguard::UpdateReady()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ���
	switch (mStateStep)
	{
		// �X�e�b�v0 ����������
	case 0:
		ChangeAnimation(EAnimType::eIdle1);
		// �S�Ă̏Փ˔�����I�t�ɂ���
		SetEnableCol(false);
		// ���@���K�[�h�̈ړ����x��0�ɂ���
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
			// ���@���K�[�h�̏Փ˔�����I���ɂ���
			SetEnableCol(true);
			// ���݂̏�Ԃ�ҋ@�ɐ؂�ւ�
			mCharaStatus.hp = mCharaMaxStatus.hp;
			ChangeState(EState::eIdle);
		}
		break;
	}
}


// �ҋ@
void CVanguard::UpdateIdle()
{
	mDiscovery = false;
	mDamage = false;
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
	//else
	//{
	//	int random = Math::Rand(0, 10);

	//	if (random >= 0 && random <= 5 && IsAnimationFinished())
	//	{
	//		ChangeAnimation(EAnimType::eIdle1);
	//		if (IsAnimationFinished())
	//		{
	//			// �m���Ŝp�j��ԂɈڍs
	//			if (ShouldTransition())
	//			{
	//				ChangeState(EState::eWander);
	//			}
	//		}
	//	}
	//	else if (random >= 6 && random <= 10 && IsAnimationFinished())
	//	{
	//		ChangeAnimation(EAnimType::eIdle2);
	//		if (IsAnimationFinished())
	//		{
	//			// �m���Ŝp�j��ԂɈڍs
	//			if (ShouldTransition())
	//			{
	//				ChangeState(EState::eWander);
	//			}
	//		}
	//	}
	//}
}

// �ړ����
void CVanguard::UpdateWalk()
{
}

// �����������
void CVanguard::UpdateWalkMutant()
{
}

// �ړ����(���펝��)
void CVanguard::UpdateWalkWeapon()
{
}

// �ړ����(������)
void CVanguard::UpdateWalkShield()
{
}

// �ړ����(������������1)
void CVanguard::UpdateWalkBackShield1()
{
}

// �ړ����(������������2)
void CVanguard::UpdateWalkBackShield2()
{
}

// �_�b�V�����
void CVanguard::UpdateDash()
{
}

// ��������
void CVanguard::UpdateDashBrisk()
{
}

// ��������
void CVanguard::UpdateDashShield()
{
}

// �_�b�V���I��
void CVanguard::UpdateDashEnd()
{
}

// ����s��
void CVanguard::UpdateRolling()
{
	mpDamageCol->SetEnable(false);
	mRollingEnd = true;
	/*CDebugPrint::Print("mMoveVector :%f\n", mMoveVector.Z());
	CDebugPrint::Print("mTargetDir :%f\n", mTargetDir.Z());*/
	ChangeAnimation(EAnimType::eRolling);

	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// mMoveSpeed�͓G�̑��x�x�N�g���AmMoveSpeed.X()��X�������̑��x
	// �K�؂ȑ��x��ݒ肵�AmMoveSpeed��mTargetDir�ɃX�P�[�����O���Ĉړ��B
	// ���x��ݒ�
	float moveSpeed = 20.0f;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	CVector moveVector = -mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	Position(Position() + moveVector + mMoveSpeed);
	// �ړ��x�N�g���𐳋K�����Č������擾
	CVector forward = moveVector.Normalized();

	// CSoldier���ړ������֌�����
	Rotation(CQuaternion::LookRotation(forward));
	if (GetAnimationFrame() >= 50.0f)
	{
		if (IsAnimationFinished())
		{
			// �v���C���[�̃|�C���^��0�ȊO�̎�
			CPlayer* player = CPlayer::Instance();

			// �v���C���[�܂ł̃x�N�g�������߂�
			CVector vp = player->Position() - Position();
			float distancePlayer = vp.Length();
			vp.Y(0.0f);
			mTargetDir = vp.Normalized();

			ChangeState(EState::eChase);
		}
	}
}

// �W�����v�J�n���
void CVanguard::UpdateJumpStart()
{
}

// �W�����v��
void CVanguard::UpdateJump()
{
}

// ����W�����v�J�n���
void CVanguard::UpdateRunJumpStart()
{
}

// ����W�����v�����
void CVanguard::UpdateRunJump()
{
}

// �_�b�V���W�����v�J�n���
void CVanguard::UpdateRunDashJumpStart()
{
}

// �_�b�V���W�����v�����
void CVanguard::UpdateRunDashJump()
{
}

// �W�����v�I��
void CVanguard::UpdateJumpEnd()
{
}

// �����オ����
void CVanguard::UpdateStandUp()
{
}

// ���펝���ҋ@���
void CVanguard::UpdateIdleWeapon()
{
}

// �U�����
void CVanguard::UpdateAttack()
{
	mDiscovery = false;
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

		CPlayer* player = CPlayer::Instance();
		CVector playerPos = player->Position();
		playerPos.Y(Position().Y());

		CVector toPlayer = (playerPos - Position()).Normalized();
		mMoveSpeed += toPlayer * 0.25;
		mTargetDir = toPlayer;


		if (distancePlayer <= BACKSTEP_RANGE && !mRollingEnd)
		{
			ChangeState(EState::eRolling);
			return;
		}
		else if (distancePlayer <= ATTACK_RANGE_KICK && !mKickTimeEnd)
		{
			ChangeState(EState::eAttackKick);
			mKickTimeEnd = true;
			return;
		}
		else if (distancePlayer <= 23.0f)
		{
			int random = Math::Rand(0, 4);
			if (random == 0)
			{
				ChangeState(EState::eAttacks3);
			}
			else if (random == 1)
			{
				ChangeState(EState::eAttackSpin1);
			}
			else if (random == 2)
			{
				ChangeState(EState::eAttackSpin2);
			}
			else if (random == 3)
			{
				ChangeState(EState::eAttackSwing);
			}
		}
	}
	else
	{
		ChangeState(EState::eChase);
		mElapsedTime_End = 0.0f;
		mDiscoveryTime = 0.0f;
		mDiscovery = false;
	}
}

// �X�s���U��1
void CVanguard::UpdateAttackSpin1()
{
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	ChangeAnimation(EAnimType::eAttackSpin1);
	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	if (GetAnimationFrame() >= 40.0f)
	{
		mpSword->AttackStart();
		if (IsAnimationFinished())
		{
			ChangeState(EState::eAttackEnd);
		}
	}
}

// �X�s���U��2
void CVanguard::UpdateAttackSpin2()
{
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	ChangeAnimation(EAnimType::eAttackSpin2);
	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	if (GetAnimationFrame() >= 40.0f)
	{
		mpSword->AttackStart();
		if (IsAnimationFinished())
		{
			ChangeState(EState::eAttackEnd);
		}
	}
}

// �U��グ�U��
void CVanguard::UpdateAttackSwing()
{
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	ChangeAnimation(EAnimType::eAttackSwing);
	// �v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();

	// �v���C���[�܂ł̃x�N�g�������߂�
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	if (GetAnimationFrame() >= 40.0f)
	{
		mpSword->AttackStart();
		if (IsAnimationFinished())
		{
			ChangeState(EState::eAttackEnd);
		}
	}
}

// 3�A�U��
void CVanguard::UpdateAttacks3()
{
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	ChangeAnimation(EAnimType::eAttacks3);
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
			mpAttackCol->SetEnable(true);
			ChangeState(EState::eAttackEnd);
		}
	}
}

// �L�b�N
void CVanguard::UpdateAttackKick()
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
		ChangeState(EState::eAttackKickEnd);
	}
}

// �L�b�N�I��
void CVanguard::UpdateAttackKickEnd()
{
	mpAttackCol->SetEnable(false);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// �W�����v�U��1
void CVanguard::UpdateAttackJump1()
{
}

// �W�����v�U��2
void CVanguard::UpdateAttackJump2()
{
}

// �U���I���҂�
void CVanguard::UpdateAttackEnd()
{
	mpSword->AttackEnd();
	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// ��������ɂ��܂�1
void CVanguard::UpdateSwordSheathing1()
{
	ChangeAnimation(EAnimType::eSwordSheathing1);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
}

// ��������ɂ��܂�2
void CVanguard::UpdateSwordSheathing2()
{
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
}

// ���\��
void CVanguard::UpdateShield()
{
}

// ����h��
void CVanguard::UpdateSwordGuard()
{
}

// ��������o��1
void CVanguard::UpdateSwordDrawn1()
{
	ChangeAnimation(EAnimType::eSwordDrawn1);
	if (GetAnimationFrame() >= 20.0f)
	{
		// �}�W�b�N�\�[�h�쐬
		mpSword->SetAlpha(1.0f);
	}

	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// ��������o��2
void CVanguard::UpdateSwordDrawn2()
{
	ChangeAnimation(EAnimType::eSwordDrawn2);
	if (GetAnimationFrame() >= 60.0f)
	{
		// �}�W�b�N�\�[�h�쐬
		mpSword->SetAlpha(1.0f);
	}

	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// �������납����o��
void CVanguard::UpdateSwordBackDrawn()
{
	ChangeAnimation(EAnimType::eSwordBackDrawn);
	if (GetAnimationFrame() >= 90.0f)
	{
		// �}�W�b�N�\�[�h�쐬
		mpSword->SetAlpha(1.0f);
	}

	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// ���_���[�W1
void CVanguard::UpdateHitSlight1()
{
	// �_���[�W���󂯂����͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	mpSword->AttackEnd();

	ChangeAnimation(EAnimType::eHitSlight1);

	if (IsAnimationFinished())
	{
		mpSword->SetAlpha(1.0f);
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
			mDamage = false;
			ChangeState(EState::eChase);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}
}

// ���_���[�W2
void CVanguard::UpdateHitSlight2()
{
	// �_���[�W���󂯂����͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	mpSword->AttackEnd();

	ChangeAnimation(EAnimType::eHitSlight2);

	if (IsAnimationFinished())
	{
		mpSword->SetAlpha(1.0f);
		// �v���C���[�̃|�C���^��0�ȊO�̎�
		CPlayer* player = CPlayer::Instance();

		// �v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - Position();
		float distancePlayer = vp.Length();
		vp.Y(0.0f);
		mTargetDir = vp.Normalized();

		if (mCharaStatus.hp >= 1)
		{
			if (IsAnimationFinished())
			{
				mpDamageCol->SetEnable(true);
				mDamage = false;
				ChangeState(EState::eChase);
			}
		}
		else if (mCharaStatus.hp <= 0)
		{
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}
}

// ���_���[�W3
void CVanguard::UpdateHitSlight3()
{
	// �_���[�W���󂯂����͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	mpSword->AttackEnd();

	ChangeAnimation(EAnimType::eHitSlight3);

	if (IsAnimationFinished())
	{
		mpSword->SetAlpha(1.0f);
		// �v���C���[�̃|�C���^��0�ȊO�̎�
		CPlayer* player = CPlayer::Instance();

		// �v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - Position();
		float distancePlayer = vp.Length();
		vp.Y(0.0f);
		mTargetDir = vp.Normalized();

		if (mCharaStatus.hp >= 1)
		{
			if (IsAnimationFinished())
			{
				mpDamageCol->SetEnable(true);
				mDamage = false;
				ChangeState(EState::eChase);
			}
		}
		else if (mCharaStatus.hp <= 0)
		{
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}
}

// �K�b�c�|�[�Y1
void CVanguard::UpdateGutsPose1()
{
}

// �K�b�c�|�[�Y2
void CVanguard::UpdateGutsPose2()
{
}

// �v���C���[����
void CVanguard::UpdateDiscovery()
{
	mDiscovery = true;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeState(EState::ePointing);
}

// �ǐ�
void CVanguard::UpdateChase()
{
	mpSword->SetAlpha(1.0f);
	mDiscovery = false;
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	if (!IsFoundPlayer())
	{
		ChangeState(EState::eLoseSight);
	}
	else
	{
		ChangeAnimation(EAnimType::eDashBrisk);
		mElapsedTime_End = 0.0f;
		CPlayer* player = CPlayer::Instance();
		CVector playerPos = player->Position();
		playerPos.Y(Position().Y());

		CVector toPlayer = (playerPos - Position()).Normalized();
		mMoveSpeed += toPlayer * MOVE_SPEED;
		mTargetDir = toPlayer;

		// �v���C���[�Ƃ̋��������͈͈ȓ��ł���΍U�����[�h�ɐ؂�ւ���
		float distanceToPlayer = (player->Position() - Position()).Length();

		if (distanceToPlayer <= 35.0f)
		{
			ChangeState(EState::eAttack);
		}
	}
}

// �p�j����
void CVanguard::UpdateWander()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

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

// ���������
void CVanguard::UpdateLoseSight()
{
	ChangeAnimation(EAnimType::eLoseSight);
	mElapsedTime_End += Time::DeltaTime();
	//CDebugPrint::Print("TimeEnd%f\n", mElapsedTime_End);

	if (IsFoundPlayer())
	{
		ChangeState(EState::eChase);
	}

	if (!IsFoundPlayer() && IsAnimationFinished())
	{
		if (mElapsedTime_End >= PLAYER_LOST)
		{
			ChangeState(EState::eSwordSheathing1);
			mpSword->SetAlpha(0.0f);
			mElapsedTime_End = 0.0f; // �v���C���[�����E�����������o�ߎ��Ԃ����Z�b�g
		}
	}
	//CDebugPrint::Print("ElapsedTIme:%f\n", mElapsedTime_End);
}

// �w����
void CVanguard::UpdatePointing()
{
	// �v���C���[�܂ł̃x�N�g�������߂�
	CPlayer* player = CPlayer::Instance();
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	ChangeAnimation(EAnimType::ePointing);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eSwordBackDrawn);
	}

	mDiscoveryTime += Time::DeltaTime();
	if (mDiscoveryTime >= DISCOVERY)
	{
		if (IsFoundPlayer() && GetAnimationFrame() >= 50.0f)
		{
			mDiscovery = false;
			mDiscoveryEnd = true;
			ChangeState(EState::eChase);
		}
		else
		{
			mDiscovery = false;
			mDiscoveryTime = 0.0f;
			ChangeState(EState::eIdleWeapon);
		}
	}
	//CDebugPrint::Print("discovery:%f\n", mDiscoveryTime);
}

// ���S
void CVanguard::UpdateDeath()
{
	mpDamageCol->SetEnable(false);
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eDeath);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eDeathEnd);
	}
}

// ���S�����I��
void CVanguard::UpdateDeathEnd()
{
	if (IsAnimationFinished())
	{
		sScore += 100;
		Kill();
	}
}

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
	mpDamageCol->SetEnable(true);
	mpAttackCol->SetEnable(false);
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
	//CDebugPrint::Print("discoveryTimeEnd:%f\n", mDiscoveryTime_End);

	// ����̎��Ԃ̌v��
	if (mTimeRolling <= ROLLING_END && mRollingEnd)
	{
		mTimeRolling += Time::DeltaTime();
		if (mTimeRolling >= ROLLING_END)
		{
			mRollingEnd = false;
			mTimeRolling = 0.0f;
		}
	}

	// ��Ԃɍ��킹�āA�X�V������؂�ւ���
	switch (mState)
	{
		// �ҋ@���
	case EState::eReady:
		UpdateReady();
		break;
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// �ړ����
	case EState::eWalk:
		UpdateWalk();
		break;
		// �����������
	case EState::eWalkMutant:
		UpdateWalkMutant();
		break;
		// ����������
	case EState::eWalkWeapon:
		UpdateWalkWeapon();
		break;
		// ������
	case EState::eWalkShield1:
		UpdateWalkShield();
		break;
		// ��������1
	case EState::eWalkBackShield1:
		UpdateWalkBackShield1();
		break;
		// ��������2
	case EState::eWalkBackShield2:
		UpdateWalkBackShield2();
		break;
		// ����
	case EState::eDash:
		UpdateDash();
		break;
		// ������
	case EState::eDashBrisk:
		UpdateDashBrisk();
		break;
		// ������
	case EState::eDashShield:
		UpdateDashShield();
		break;
		// ����~��
	case EState::eDashEnd:
		UpdateDashEnd();
		break;
		// ����s��
	case EState::eRolling:
		UpdateRolling();
		break;
		// �W�����v�J�n
	case EState::eJumpStart:
		UpdateJumpStart();
		break;
		// �W�����v��
	case EState::eJump:
		UpdateJump();
		break;
		// ����W�����v�J�n
	case EState::eRunDashJumpStart:
		UpdateRunJumpStart();
		break;
		// ����W�����v��
	case EState::eRunDashJump:
		UpdateRunJump();
		break;
		// �_�b�V���W�����v�J�n
	case EState::eDashJumpStart:
		UpdateRunDashJumpStart();
		break;
		// �_�b�V���W�����v��
	case EState::eDashJump:
		UpdateRunDashJump();
		break;
		// �W�����v�I��
	case EState::eJumpEnd:
		UpdateJumpEnd();
		break;
		// �����オ��
	case EState::eStandUp:
		UpdateStandUp();
		break;
		// ���펝���ҋ@
	case EState::eIdleWeapon:
		UpdateIdleWeapon();
		break;
	case EState::eAttack:
		UpdateAttack();
		break;
		// �X�s���U��1
	case EState::eAttackSpin1:
		UpdateAttackSpin1();
		break;
		// �X�s���U��2
	case EState::eAttackSpin2:
		UpdateAttackSpin2();
		break;
		// �U��グ�U��
	case EState::eAttackSwing:
		UpdateAttackSwing();
		break;
		// 3�A�U��
	case EState::eAttacks3:
		UpdateAttacks3();
		break;
		// �E���L�b�N
	case EState::eAttackKick:
		UpdateAttackKick();
		break;
		// �E���L�b�N�I��
	case EState::eAttackKickEnd:
		UpdateAttackKickEnd();
		break;
		// �W�����v�U��1
	case EState::eAttackJump1:
		UpdateAttackJump1();
		break;
		// �W�����v�U��2
	case EState::eAttackJump2:
		UpdateAttackJump2();
		break;
		// �U���I���҂�
	case EState::eAttackEnd:
		UpdateAttackEnd();
		break;
		// ��������ɂ��܂�1
	case EState::eSwordSheathing1:
		UpdateSwordSheathing1();
		break;
		// ��������ɂ��܂�2
	case EState::eSwordSheathing2:
		UpdateSwordSheathing2();
		break;
		// ���\��
	case EState::eShield:
		UpdateShield();
		break;
		// ����h��
	case EState::eSwordGuard:
		UpdateSwordGuard();
		break;
		// ��������o��1
	case EState::eSwordDrawn1:
		UpdateSwordDrawn1();
		break;
		// ��������o��2
	case EState::eSwordDrawn2:
		UpdateSwordDrawn2();
		break;
		// �������납����o��
	case EState::eSwordBackDrawn:
		UpdateSwordBackDrawn();
		break;
		// ���_���[�W1
	case EState::eHitSlight1:
		UpdateHitSlight1();
		break;
		// ���_���[�W2
	case EState::eHitSlight2:
		UpdateHitSlight2();
		break;
		// ���_���[�W3
	case EState::eHitSlight3:
		UpdateHitSlight3();
		break;
		// �K�b�c�|�[�Y1
	case EState::eGutsPose1:
		UpdateGutsPose1();
		break;
		// �K�b�c�|�[�Y2
	case EState::eGutsPose2:
		UpdateGutsPose2();
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
		// ���������
	case EState::eLoseSight:
		UpdateLoseSight();
		break;
		// �w����
	case EState::ePointing:
		UpdatePointing();
		break;
		// ���S
	case EState::eDeath:
		UpdateDeath();
		break;
		// ���S�I��
	case EState::eDeathEnd:
		UpdateDeathEnd();
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
	mpSword->UpdateAttachMtx();

	mIsGrounded = false;

	// �O�t���[����FPS���Ď�
	//CDebugPrint::Print("FPS:%f\n", Time::FPS());

}

// �`��
void CVanguard::Render()
{
	CXCharacter::Render();
}