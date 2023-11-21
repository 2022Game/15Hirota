#include "CYukari.h"
#include "CCamera.h"
#include "CBillBoard.h"
#include "CImage.h"
#include "CPlayer.h"
#include <algorithm>
#include "Maths.h"
#include <BaseSystem/CInput.h>
#include "CGun.h"
#include "CBullet.h"

#define _USE_MATH_DEFINES


// Yukari�̃C���X�^���X
CYukari* CYukari::spInstance = nullptr;

// Yukari�̃��f���f�[�^�̃p�X
#define MODEL_PATH "Character\\Yukari\\Yukari_Model.x"

// Yukari�̃A�j���[�V�����f�[�^�̃e�[�u��
const CYukari::AnimData CYukari::ANIM_DATA[] =
{
	{ "",													true,	0.0f	},	// T�|�[�Y
	{ "Character\\Yukari\\anim\\Yukari_GunIdle463.x",		true,	463.0f	},	// Idle��
	{ "Character\\Yukari\\anim\\Yukari_GunWorlk79.x",		true,	79.0f	},	// �ړ�
	{ "Character\\Yukari\\anim\\Yukari_GunPlay13.x",		true,	13.0f	},	// �v���C���[�������U��
	{ "Character\\Yukari\\anim\\Yukari1_Reload199.fbx.x",	false,	199.0f	},	// �����[�h

};

#define PLAYER_HEIGHT 8.0f
#define MOVE_SPEED 1.0f
#define JUMP_SPEED 1.5f
#define GRAVITY 0.0625f
#define JUMP_END_Y 1.0f

//�ړ����x
#define FOV_ANGLE 55.0f		// ����̊p�x(�[�p�x+�p�x���o)
#define ATTACK_RANGE 50.0f	// �v���C���[�܂ł̋���

// HP�֘A
#define HP 5

// ���x���֘A
#define LEVEL 1

// �U���͊֘A
#define ATTACK 10

// �R���X�g���N�^
CYukari::CYukari()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eIdle)
	, mpRideObject(nullptr)
	, mShot(false)
	, mLife(50)
	, mTimeShot(0)
	, mTimeShotEnd(5)
{

	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// ���f���f�[�^�ǂݍ���
	CModelX* model = new CModelX();
	model->Load(MODEL_PATH);

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
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField });

	// �_���[�W���󂯂�R���C�_�[���쐬
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		10.0f //��ŕύX
	);
	// �_���[�W���󂯂�R���C�_�[��
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon });
	// �_���[�W���󂯂�R���C�_�[��������ւ��炷
	mpDamageCol->Position(0.0f, 5.0f, 0.0f);

	// �e���쐬���Ď�������
	mpGun = new CGun();
	mpGun->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpGun->SetOwner(this);

	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);

}

CYukari::~CYukari()
{
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	if (mpModel != nullptr)
	{
		delete mpModel;
		mpModel = nullptr;
	}

	// �_���[�W���󂯂�R���C�_�[���폜
	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
	}
}

CYukari* CYukari::Instance()
{
	return spInstance;
}

// ���x���A�b�v
void CYukari::LevelUp()
{
	int level = mCharaStatus.level;
	ChangeLevel(level + 1);
}

// ���x����ύX
void CYukari::ChangeLevel(int level)
{
	// �X�e�[�^�X�̃e�[�u���̃C���f�b�N�X�n�ɕϊ�
	int index = Math::Clamp(level - 1, 0, ENEMY_LEVEL_MAX);
	// �ő�X�e�[�^�X�ɐݒ�
	mCharaMaxStatus = ENEMY_STATUS[index];
	// ���݂̃X�e�[�^�X���ő�l�ɂ��邱�ƂŁAHP��
	mCharaStatus = mCharaMaxStatus;

}

// �A�j���[�V�����؂�ւ�
void CYukari::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �ҋ@
void CYukari::UpdateIdle()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	ChangeAnimation(EAnimType::eIdle);
	//�v���C���[����������A�ǐՏ�Ԃֈڍs
	if (IsFoundPlayer())
	{
		mState = EState::eChase;
	}
}

void CYukari::UpdateChase()
{
	if (!IsFoundPlayer())
	{
		
	}
	else
	{
		CPlayer* player = CPlayer::Instance();

		CVector toPlayer = (player->Position() - Position()).Normalized();
		CVector newPosition = Position() + toPlayer * MOVE_SPEED;
		Position(newPosition);

		// �v���C���[�Ƃ̋��������͈͈ȓ��ł���΍U�����[�h�ɐ؂�ւ���
		float distanceToPlayer = (player->Position() - Position()).Length();

		ChangeAnimation(EAnimType::eWalk);

		if (distanceToPlayer <= ATTACK_RANGE)
		{
			mState = EState::eAttack;
		}
	}
}


// �U��
void CYukari::UpdateAttack()
{
	mShot = true;
	//�v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - Position();

		float distancePlayer = vp.Length();

		if (distancePlayer <= ATTACK_RANGE)
		{
			mTimeShot++;
			if (mTimeShot < mTimeShotEnd && mShot)
			{
				mpBullet = new CBullet();
				mpBullet->SetOwner(this);
				mpBullet->Position(CVector(0.0f, 10.0f, 10.0f) * Matrix());
				mpBullet->Rotation(Rotation());
				mpBullet->AttackStart();
				mpBullet->Update();
				ChangeAnimation(EAnimType::eAttack);
				if (mTimeShot >= mTimeShotEnd && mShot)
				{
					ChangeAnimation(EAnimType::eReload);
					if (IsAnimationFinished())
					{
						// �U���I����̑ҋ@��ԂɑJ��
						mState = EState::eAttackWait;
						mShot = false;
						mTimeShot = 0;
					}
				}
			}
		}
		else
		{
			mState = EState::eChase;
			mShot = false;
			mTimeShot = 0;
		}
	}
	else
	{
		mState = EState::eIdle;
		mShot = true;
		mTimeShot = 0;
	}

	CDebugPrint::Print("Shot%d\n", mTimeShot);
	CDebugPrint::Print("Shot: %s\n", mShot ? "true" : "false");
}

// �U���I���҂�
void CYukari::UpdateAttackWait()
{
	ChangeAnimation(EAnimType::eReload);
	// �ҋ@��Ԃֈڍs
	mState = EState::eIdle;
	mpBullet->AttackEnd();
}

// �W�����v�J�n
void CYukari::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	mState = EState::eJump;

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// �W�����v��
void CYukari::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mState = EState::eJumpEnd;
	}
}

// �W�����v�I��
void CYukari::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

// �X�V
void CYukari::Update()
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
		// �U���I���҂�
	case EState::eAttackWait:
		UpdateAttackWait();
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
	case EState::eChase:
		UpdateChase();
		break;
	}

	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// Yukari�̃f�o�b�O�\��
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
	Position(Position() + mMoveSpeed);

	CVector PlayerPosition;

	// Yukari���ړ������֌�����
	CVector current = VectorZ();
	CVector target = mMoveSpeed;
	target.Y(0.0f);
	target.Normalize();
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	// Yukari�̍X�V
	CXCharacter::Update();

	mIsGrounded = false;
}

bool CYukari::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector enemyPos = Position();

	CVector toPlayer = (playerPos - enemyPos).Normalized();
	CVector forward = Matrix().VectorZ().Normalized();

	float dot = forward.Dot(toPlayer);

	// ����p�̔������v�Z����
	float halfFOV = FOV_ANGLE * 0.5f;

	// acos�֐����g�p���Ď��ۂ̊p�x���v�Z����
	float angle = acos(dot) * (180.0f / M_PI);

	// ����p�̔�����菬�������v���C���[�Ƃ̋��������͈͈ȓ��ł���΁A�v���C���[��F������
	if (angle < halfFOV && dot >= cosf(halfFOV * M_PI / 180.0f))
	{
		float distance = (playerPos - enemyPos).Length();
		const float chaseRange = 100.0f;

		if (distance <= chaseRange)
			return true;
	}

	return false;

	/*CVector playerPos = CPlayer::Instance()->Position();
	CVector enemyPos = Position();

	CVector EP = (playerPos - enemyPos).Normalized();

	CVector forwrd = Matrix().VectorZ().Normalized();

	float dot = forwrd.Dot(EP);

	if (dot < cosf(FOV_ANGLE * M_PI / 180.0f)) return false;

	float distance = (playerPos - enemyPos).Length();

	const float chaseRenge = 100.0f;

	if (distance > chaseRenge)
		return false;

	return true;*/

}


// �Փˏ���
void CYukari::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
}

// �`��
void CYukari::Render()
{
	CXCharacter::Render();
}

// ��_���[�W����
void CYukari::TakeDamage(int damage)
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