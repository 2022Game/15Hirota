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

#define _USE_MATH_DEFINES

// CSoldier�̃C���X�^���X
CSoldier* CSoldier::spInstance = nullptr;

int CSoldier::enemyCount = 0;


#define EFFECT	 "Effect\\exp.tga"

// CSoldier�̃A�j���[�V�����f�[�^�̃e�[�u��
const CSoldier::AnimData CSoldier::ANIM_DATA[] =
{
	{ "",																				true,	  0.0f	},	// T�|�[�Y
	{ "Character\\Gas mask soldier\\anim\\Rifle_Idle1_515.x",							true,   515.0f	},	// Idle��
	{ "Character\\Gas mask soldier\\anim\\Rifle_Idle3_187.x",							true,   187.0f	},	// ���C�t��Idle��
	{ "Character\\Gas mask soldier\\anim\\Rifle_walk_79.x",								true,	 79.0f	},	// �ړ�
	{ "Character\\Gas mask soldier\\anim\\Alert_83.x",									true,	 83.0f	},	// �x��
	{ "Character\\Gas mask soldier\\anim\\Rifle_1shot_71.x",							true,	 71.0f	},	// �v���C���[�������U��
	{ "Character\\Gas mask soldier\\anim\\Right foot kick_121.x",					false,	121.0f	},		// �i��
	{ "Character\\Gas mask soldier\\anim\\Reload_199.x",								true,	 99.0f	},	// �����[�h
	{ "Character\\Gas mask soldier\\anim\\Rilfle_Aim_to_Dwon._91.x",				false,	 91.0f	},		// �G�C������
	{ "Character\\Gas mask soldier\\anim\\Hit_27.x",								false,	 27.0f	},		// Hit
	{ "Character\\Gas mask soldier\\anim\\Death_Fall down1_157.x",					false,	157.0f	},		// ���S

};


#define ENEMY_HEIGHT 8.0f
#define ENEMY_HEIGHT2 20.0f
#define MOVE_SPEED 0.5f
#define RUN_SPEED 25.0f
#define JUMP_SPEED 1.5f
#define GRAVITY 0.0625f
#define JUMP_END_Y 1.0f

//�ړ����x
#define FOV_ANGLE 100.0f		// ����̊p�x(�[�p�x+�p�x���o)
#define ATTACK_RANGE 70.0f	// �v���C���[�܂ł̋���
#define ATTACK_RANGE_KICK 27.0f

// HP�֘A
#define HP 5

// ���x���֘A
#define LEVEL 1

// �U���͊֘A
#define ATTACK 10

// �e�ۂ̔��ˊԊu
#define ATTACK 10

// �e�ۂ̔��ˊԊu
#define SHOT_INTERVAL 2.0f

// �G������������̎���
#define PLAYER_LOST 10.0f


// �R���X�g���N�^
CSoldier::CSoldier()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eIdle)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveSpeed(0.0f,0.0f,0.0f)
	, mpRideObject(nullptr)
	, mTimeShot(0)
	, mTimeShotEnd(5)
	, mElapsedTime(0.0f)
	, mElapsedTime_End(0.0f)
	, mTimeToChange(Math::Rand(2.0f,5.0f))
	, wanderRadius(0.0f)
	, initialPosition(0.0f,0.0f,0.0f)
{
	Position(initialPosition);

	enemyCount++;
	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Soldier");


	mpFrame = new CSoldierFrame();
	// 0~1�̒l��ݒ�
	mpFrame->SetCenterRatio(CVector2(0.5f, 0.0f));
	mpGauge = new CSoldierGauge();
	mpGauge->SetCenterRatio(CVector2(0.3f, 0.0f));

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


	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, ENEMY_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField });

	
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eEnemy,
		7.0f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField });
	mpColliderSphere->Position(0.0f, 5.0f, 1.0f);


	// �_���[�W���󂯂�R���C�_�[���쐬
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f //��ŕύX
	);
	// �_���[�W���󂯂�R���C�_�[��
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol, ELayer::eDamageCol,ELayer::eEnemy });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon, ETag::eEnemy });
	// �_���[�W���󂯂�R���C�_�[���������ւ��炷
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);


	// �E���Ƀ_���[�W�R���C�_�[��ݒ�
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eKickCol,
		0.3f
	);
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
	mpAttackCol->SetEnable(false);
	const CMatrix* spineMtxK = GetFrameMtx("Armature_mixamorig_RightToeBase");
	mpAttackCol->SetAttachMtx(spineMtxK);


	// �e���쐬���Ď�������
	mpGun = new CGun();
	const CMatrix* gun = GetFrameMtx("Armature_mixamorig_RightHand");
	mpGun->AttachMtx(gun);


	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}


CSoldier::~CSoldier()
{
	CStageManager::RemoveTask(this);

	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	if (mpColliderSphere != nullptr)
	{
		delete mpColliderSphere;
		mpColliderSphere = nullptr;
	}

	// �_���[�W���󂯂�R���C�_�[���폜
	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
	}

	if (mpAttackCol != nullptr)
	{
		delete mpAttackCol;
		mpAttackCol = nullptr;
	}

	mpGun->Kill();

	enemyCount--;

	// UI���������
	mpGauge->Kill();
	mpFrame->Kill();
}


CSoldier* CSoldier::Instance()
{
	return spInstance;
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


// �A�j���[�V�����؂�ւ�
void CSoldier::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}


// �ҋ@
void CSoldier::UpdateIdle()
{
	mpAttackCol->SetEnable(false);
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	//�v���C���[����������A�ǐՏ�Ԃֈڍs
	if (IsFoundPlayer())
	{
		mState = EState::eChase;
	}
	else
	{
		ChangeAnimation(EAnimType::eIdle);

		// �m���Ŝp�j��ԂɈڍs
		if (ShouldTransition())
		{
			mState = EState::eWander;
		}
	}
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
		CDebugPrint::Print("TimeEnd%f\n", mElapsedTime_End);
		if (mElapsedTime_End >= PLAYER_LOST)
		{
			mState = EState::eAimDwon;
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
			mState = EState::eAttack;
		}
	}
}


// �U��
void CSoldier::UpdateAttack()
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
				Position() + CVector(0.0f, 10.0f, 0.0f) + VectorZ() * 20.0f,
				VectorZ(),	// ���˕���
				1000.0f,	// �ړ�����
				1000.0f		// �򋗗�
			);

			// �S�e���˂�����A�U���I��
			mTimeShot++;
			if (mTimeShot >= mTimeShotEnd)
			{
				// �U���I����̑ҋ@��ԂɑJ��
				mState = EState::eAttackWait;
				mTimeShot = 0;
				mElapsedTime = 0.0f;
			}
			if (distancePlayer <= ATTACK_RANGE_KICK)
			{
				mState = EState::eKick;
				return;
			}
		}
	}
	else
	{
		mState = EState::eChase;
		mElapsedTime_End = 0.0f;
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
		mState = EState::eKickWait;
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
			mState = EState::eChase;
			ChangeAnimation(EAnimType::eIdle);
		}
		
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
			mState = EState::eAttack;
		}
		else
		{
			mState = EState::eAimDwon;
			mElapsedTime_End = 0.0f;
		}
	}
}

// �G�C������
void CSoldier::UpdateAimDwon()
{
	ChangeAnimation(EAnimType::eAimDwou);
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
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

		if (mCharaStatus.hp > 1)
		{
			mState = EState::eChase;
		}
		else if (mCharaStatus.hp <= 0)
		{
			mpDamageCol->SetEnable(false);
			mState = EState::eDeth;
		}
	}
}

// �W�����v�J�n
void CSoldier::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	mState = EState::eJump;

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}


// �W�����v��
void CSoldier::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mState = EState::eJumpEnd;
	}
}

// �W�����v�I��
void CSoldier::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
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
		mState = EState::eDethEnd;
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
		mState = EState::eChase;
	}
	else
	{
		if (ShouldTransitionWander())
		{
			mState = EState::eIdle;
		}
	}
}

// �X�V
void CSoldier::Update()
{
	SetParent(mpRideObject);
	mpRideObject = nullptr;

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
		// �ǐՏ��
	case EState::eChase:
		UpdateChase();
		break;
		// �v���C���[�̍U��Hit
	case EState::eHit:
		UpdateHit();
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


	CDebugPrint::Print("Shot%d\n", mTimeShot);
	CDebugPrint::Print("Shotend%d\n", mTimeShotEnd);
	CDebugPrint::Print("FPS:%f\n", Time::FPS());
	

	// HP�Q�[�W�̍��W���X�V (�G�̍��W�̏�����̍��W)
	CVector gaugePos = Position() + CVector(0.0f, 25.0f, 0.0f);
	mpGauge->SetWorldPos(gaugePos);
	CVector framePos = Position() + CVector(0.0f, 25.0f, 0.0f);
	mpFrame->SetWorldPos(framePos);


	// ���݂�Hp��ݒ�
	mpGauge->SetValue(mCharaStatus.hp);

	// CSoldier�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpAttackCol->Update();
	mpGun->UpdateAttachMtx();

	mIsGrounded = false;
	
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

	//// acos�֐����g�p���Ď��ۂ̊p�x���v�Z����
	//float angle = acos(dot) * (180.0f / M_PI);

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

// �Փˏ���
void CSoldier::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
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
		if (other->Layer() == ELayer::eField)
		{
			Position(Position() + hit.adjust);
		}
	}

	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eAttackCol)
		{
			if (mState != EState::eKick)
			{
				mState = EState::eHit;
			}
		}

		if (other->Layer() == ELayer::eDamageCol)
		{
			(other->Tag() == ETag::eEnemy);
			{
				Position(Position() + hit.adjust);
			}
		}
	}


}

// �`��
void CSoldier::Render()
{
	CXCharacter::Render();
}

// ��_���[�W����
void CSoldier::TakeDamage(int damage)
{
	// ���S���Ă�����_���[�W�͎󂯂Ȃ�
	//if (mCharaStatus.hp <= 0) return;

	// HP����_���[�W������
	//mCharaStatus.hp = std::max(mCharaStatus.hp - damage, 0);
	mCharaStatus.hp -= damage;
	// HP��0�ɂȂ�����
	if (mCharaStatus.hp == 0)
	{
		mState = EState::eDeth;
	}
}

int CSoldier::GetEnemyCount()
{
	return enemyCount;
}


// �p�j�ɑJ�ڂ������
bool CSoldier::ShouldTransitionWander()
{
	float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return randomValue < 0.01f;  // 1%�̊m���Ŝp�j�ɑJ��
}

bool CSoldier::ShouldTransition()
{
	float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return randomValue < 0.01f;  // 0.1%�̊m���Ŝp�j�ɑJ��
}


// 1%�̊m���ňڍs����ׂ̏���
void CSoldier::ChangeDerection()
{
	// �����_���ȕ����ɕύX
	float randomAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 360.0f;
	mTargetDir = CalculateDirection(randomAngle);
}


// 360�x�̊p�x�����߂āAx����y������v�Z����
CVector CSoldier::CalculateDirection(float angleDegrees)
{
	// �p�x���烉�W�A���ɕϊ�
	float angleRadians = angleDegrees * M_PI / 180.0f;

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
	// mMoveSpeed �͓G�̑��x�x�N�g����mMoveSpeed.X() �� X �������̑��x��\���܂��B
	// �K�؂ȑ��x��ݒ肵�AmMoveSpeed��mTargetDir�ɃX�P�[�����O���Ĉړ��B

	// ���x��ݒ�
	float moveSpeed = RUN_SPEED;

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime ���l�����Ĉړ��ʂ��v�Z
	moveVector *= Time::DeltaTime();

	// ���݂̍��W���X�V
	Position(Position() + moveVector + mMoveSpeed);
}
