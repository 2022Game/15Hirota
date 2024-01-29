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
#include "CYukariFrame.h"
#include "CYukariGauge.h"
#include "CStageManager.h"

#define _USE_MATH_DEFINES


// Yukari�̃C���X�^���X
CYukari* CYukari::spInstance = nullptr;


#define EFFECT	 "Effect\\exp.tga"

// Yukari�̃A�j���[�V�����f�[�^�̃e�[�u��
const CYukari::AnimData CYukari::ANIM_DATA[] =
{
	//{ "",													true,	0.0f	},	// T�|�[�Y
	{ "Character\\Yukari\\anim\\Yukari_GunIdle463.x",		true,	463.0f	},	// Idle��
	{ "Character\\Yukari\\anim\\Yukari_GunWorlk79.x",		true,	79.0f	},	// �ړ�
	{ "Character\\Yukari\\anim\\Yukari_GunPlay13.x",		true,	13.0f	},	// �v���C���[�������U��
	{ "Character\\Yukari\\anim\\Yukari1_Reload199.x",		true,	199.0f	},	// �����[�h
};

#define ENEMY_HEIGHT 8.0f
#define ENEMY_HEIGHT2 20.0f
#define MOVE_SPEED 0.5f
#define JUMP_SPEED 1.5f
#define GRAVITY 0.0625f
#define JUMP_END_Y 1.0f

//�ړ����x
#define FOV_ANGLE 90.0f		// ����̊p�x(�[�p�x+�p�x���o)
#define ATTACK_RANGE 50.0f	// �v���C���[�܂ł̋���

// HP�֘A
#define HP 5

// ���x���֘A
#define LEVEL 1

// �U���͊֘A
#define ATTACK 10

// �e�ۂ̔��ˊԊu
#define ATTACK 10

// �e�ۂ̔��ˊԊu
#define SHOT_INTERVAL 0.5f

// �R���X�g���N�^
CYukari::CYukari()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eIdle)
	, mTargetDir(0.0f,0.0f,1.0f)
	, mpRideObject(nullptr)
	, mTimeShot(0)
	, mTimeShotEnd(10)
	, mElapsedTime(0.0f)
{
	mpFrame = new CYukariFrame();
	mpFrame->SetCenterRatio(CVector2(0.5f, 0.0f));
	mpGauge = new CYukariGauge();
	mpGauge->SetCenterRatio(CVector2(0.3f, 0.0f));

	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Yukari");

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
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol, ELayer::eDamageCol,ELayer::eEnemy, ELayer::eFieldWall });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon, ETag::eEnemy });
	// �_���[�W���󂯂�R���C�_�[��������ւ��炷
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);

	// �e���쐬���Ď�������
	mpGun = new CGun();
	const CMatrix* gun = GetFrameMtx("Armature_mixamorig_RightHand");
	mpGun->AttachMtx(gun);


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

	// �_���[�W���󂯂�R���C�_�[���폜
	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
	}
	mpGun->Kill();

	mpGauge->Kill();
	mpFrame->Kill();
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

	// �ő�HP�ƌ���HP��HP�Q�[�W�ɔ��f
	mpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpGauge->SetValue(mCharaStatus.hp);

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
	else
	{
		ChangeAnimation(EAnimType::eIdle);
	}
}

void CYukari::UpdateChase()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	if (!IsFoundPlayer())
	{
		ChangeAnimation(EAnimType::eIdle);
	}
	else
	{
		CPlayer* player = CPlayer::Instance();
		CVector playerPos = player->Position();
		playerPos.Y(Position().Y());
		
		CVector toPlayer = (playerPos - Position()).Normalized();
		mMoveSpeed += toPlayer * MOVE_SPEED;
		mTargetDir = toPlayer;

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
		}
	}
	else
	{
		mState = EState::eChase;
		mTimeShot = 0;
		mElapsedTime = 0.0f;
	}
}

// �U���I���҂�
void CYukari::UpdateAttackWait()
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
			mState = EState::eChase;
		}
	}
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

	//// Yukari�̃f�o�b�O�\��
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

	// �ړ�
	Position(Position() + mMoveSpeed);

	CVector PlayerPosition;

	// Yukari���ړ������֌�����
	CVector current = VectorZ();
	CVector target = mTargetDir;
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));


	//CDebugPrint::Print("Shot%d\n", mTimeShot);
	//CDebugPrint::Print("Shotend%d\n", mTimeShotEnd);
	//CDebugPrint::Print("FPS:%f\n", Time::FPS());


	// HP�Q�[�W�̍��W���X�V (�G�̍��W�̏�����̍��W)
	CVector gaugePos = Position() + CVector(0.0f, 25.0f, 0.0f);
	mpGauge->SetWorldPos(gaugePos);
	CVector framePos = Position() + CVector(0.0f, 25.0f, 0.0f);
	mpFrame->SetWorldPos(framePos);


	// ���݂�HP��ݒ�
	mpGauge->SetValue(mCharaStatus.hp);

	mIsGrounded = false;

	// Yukari�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpGun->UpdateAttachMtx();
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