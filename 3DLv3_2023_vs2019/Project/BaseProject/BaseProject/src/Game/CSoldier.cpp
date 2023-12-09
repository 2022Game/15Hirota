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

#define _USE_MATH_DEFINES


// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)


// �o�[�̉��T�C�Y
#define NEW_BAR_SIZE_X	(139.0f)
// �o�[�̏c�T�C�Y
#define NEW_BAR_SIZE_Y	(11.5f)

// �o�[�̉��T�C�Y * ���̕�
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// �o�[�̏c�T�C�Y * ���̕�
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)


// CSoldier�̃C���X�^���X
CSoldier* CSoldier::spInstance = nullptr;

//// CSoldier�̃��f���f�[�^�̃p�X
//#define MODEL_PATH	"Character\\Gas mask soldier\\GasMask_Soldier_Model.x"

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

};

#define ENEMY_HEIGHT 8.0f
#define ENEMY_HEIGHT2 20.0f
#define MOVE_SPEED 0.5f
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
#define SHOT_INTERVAL 0.1f

// �G������������̎���
#define PLAYER_LOST 10.0f

// �R���X�g���N�^
CSoldier::CSoldier()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eIdle)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mpRideObject(nullptr)
	, mTimeShot(0)
	, mTimeShotEnd(20)
	, mElapsedTime(0.0f)
	, mElapsedTime_End(0.0f)
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Soldier");

	mpFrame = new CSoldierFrame();
	mpGauge = new CSoldierGauge();

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

	// �_���[�W���󂯂�R���C�_�[���쐬
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f //��ŕύX
	);
	// �_���[�W���󂯂�R���C�_�[��
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon });
	// �_���[�W���󂯂�R���C�_�[���������ւ��炷
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);


	// �E���Ƀ_���[�W�R���C�_�[��ݒ�
	mpKick = new CKick();
	mpKick->AttachMtx(GetFrameMtx("Armature_mixamorig_RightToeBase"));
	mpKick->SetOwner(this);


	// �e���쐬���Ď�������
	mpGun = new CGun();
	mpGun->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpGun->SetOwner(this);

	//const CMatrix* bodyMtx = GetFrameMtx("Armature_")

	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}


CSoldier::~CSoldier()
{
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	// �_���[�W���󂯂�R���C�_�[���폜
	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
	}

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

			// �e�ۂ𔭎�
			CBullet* bullet = new CBullet();
			bullet->Position(CVector(0.0f, 10.0f, 10.0f) * Matrix());
			bullet->Rotation(Rotation());

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
	if (mAnimationFrame >= 45.0f && mAnimationFrame < 60.0f)
	{
		mpKick->AttackStart();
		mState = EState::eKickWait;
	}
}

// �L�b�N�I��
void CSoldier::UpdateKickWait()
{
	if (IsAnimationFinished())
	{
		mState = EState::eChase;
		ChangeAnimation(EAnimType::eIdle);

		mpKick->AttackEnd();
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
		mState = EState::eIdle;
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

	// CSoldier�̍X�V
	CXCharacter::Update();

	mIsGrounded = false;

	
	// �J�����̎擾
	CCamera* cam = CCamera::CurrentCamera();
	// �t���[���̈ʒu�𓪏�ɌŒ�
	CVector gaugeWorldPos = Position() + CVector(-5.0f, 30.0f, 0.0f);
	// �J�����Ń��[���h���W���X�N���[�����W�֕ϊ�
	CVector gp = cam->WorldToScreenPos(gaugeWorldPos);

	// �v���C���[�̍��W
	CVector playerPos = CPlayer::Instance()->Position();
	// �v���C���[�ƓG�̋������v�Z
	float distance = (playerPos - Position()).Length();

	// ���͈͓̔��ɋ���ꍇ�͕\��
	float displayRange = 100.0f;
	if (distance < displayRange)
	{
		// �t���[�����W
		mpFrame->SetPos(gp.X(), gp.Y());

		// �Q�[�W�̍��W��2D�Őݒ�i�E�ɂ��炷�j
		float GaugeOffsetX = 20.0f;
		// �Q�[�W�̍��W��2D�Őݒ�
		mpGauge->SetPos(gp.X() + GaugeOffsetX, gp.Y());
	}
	else
	{
		// ��������\��
		mpFrame->SetPos(-1000, -1000);
		mpGauge->SetPos(-1000, -1000);
	}

	//// �t���[���̍��W��2D�Őݒ�
	//mpFrame->SetPos(gp.X(), gp.Y());

	//// �Q�[�W�̍��W��2D�Őݒ�i�E�ɂ��炷�j
	//float GaugeOffsetX = 20.0f;
	//// �Q�[�W�̍��W��2D�Őݒ�
	//mpGauge->SetPos(gp.X() + GaugeOffsetX, gp.Y());

	// ���݂�Hp��ݒ�
	mpGauge->SetValue(mCharaStatus.hp);
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
	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eAttackCol)
		{
			mState = EState::eHit;
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
		//���S���� ���
	}
}
