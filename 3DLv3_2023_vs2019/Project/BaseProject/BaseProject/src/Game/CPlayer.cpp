//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CInput.h"
#include "CCamera.h"
#include "CUiGauge.h"
#include "CStaminaGauge.h"
#include "Maths.h"
#include "CSceneManager.h"
#include "CMajicSword.h"
#include "CBullet.h"
#include "CGameManager.h"
#include "CRecoveryObject.h"

// �v���C���[�֘A
// ����
#define PLAYER_HEIGHT 16.0f
// �X�s�[�h
#define MOVE_SPEED 0.9f
// �ړ��X�s�[�h
#define RUN_SPEED 1.3f
// �W�����v
#define JUMP_SPEED 1.5f
// ��W�����v
#define JUMP_BOUNCE 2.0f
// �d��
#define GRAVITY 0.0625f
// �W�����v�I����
#define JUMP_END_Y 1.0f


//����̊p�x(�[�p�x+�p�x���o)
#define FOV_ANGLE 45.0f
//����̊p�x
#define FOV_LENGTH 5.0f


// HP�֘A
#define HP 100
// ���x���֘A
#define LEVEL 1
// �X�^�~�i�֘A
#define STAMINA 109


// ���̑�
// �F��`�悷�鎞��
#define COLORSET 0.5f
// �_���[�W�R���C�_�[�̌v������
#define DAMAGECOL 2.0f

// �v���C���[�̃C���X�^���X
CPlayer* CPlayer::spInstance = nullptr;

CPlayer* CPlayer::Instance()
{
	return spInstance;
}

// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",															true,	0.0f	},	// T�|�[�Y
	{ "Character\\Monster1\\anim\\Warrok_Idle.x",					true,	854.0f	},	// �ҋ@
	{ "Character\\Monster1\\anim\\Warrok_Walking.x",				true,	86.0f	},	// �_�b�V��
	{ "Character\\Monster1\\anim\\Warrok_Punchi.x",				false,	67.0f	},		// �U��
	{ "Character\\Monster1\\anim\\Warrok_StrongAttack.x",		false,	161.0f	},		// ���U��
	{ "Character\\Monster1\\anim\\jump_start.x",				false,	25.0f	},		// �W�����v�J�n
	{ "Character\\Monster1\\anim\\jump.x",							true,	1.0f	},	// �W�����v��
	{ "Character\\Monster1\\anim\\jump_end.x",					false,	26.0f	},		// �W�����v�I��
	{ "Character\\Monster1\\anim\\Warrok_Run.x",					true,	53.0f	},	// ���s
	{ "Character\\Monster1\\anim\\Warrok_RunStop.x",			false,	90.0f	},		// �_�b�V���I��
	{ "Character\\Monster1\\anim\\Rotate.x",					false,	71.0f	},		// ���
	{ "Character\\Monster1\\anim\\Guts pose_325.x",				false,	325.0f	},		// �K�b�c�|�[�Y
	{ "Character\\Monster1\\anim\\Hit_63.x",					false,	63.0f	},		// �G�̍U��Hit
	{ "Character\\Monster1\\anim\\Death_276.x",					false,	276.0f	},		// ���SHit_107
	{ "Character\\Monster1\\anim\\Hit_107.x",					false,	107.0f	},		// �G�̒eHit

};

// �R���X�g���N�^
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mElapsedTimeEnd(0.0f)
	, mElapsedTimeCol(0.0f)
	, mInvincibleStartTime(10.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mHpHit(false)
	, damageEnemy(false)
	, mInvincible(false)
	, damageObject(false)
	, staminaDepleted(false)
	, mIsPlayedSlashSE(false)
	, staminaLowerLimit(false)
	, mIsPlayedHitDamageSE(false)
	, mpRideObject(nullptr)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;
	Position(0.0f, 60.0f, -30.0f);
	mStartPos = Position();

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Player");

	// �X���b�V��SE�擾
	mpSlashSE = CResourceManager::Get<CSound>("SlashSound");
	// �_���[�W���̃{�C�X�擾
	mpHitDamageSE = CResourceManager::Get<CSound>("CreatureGrowl1");

	// HP�Q�[�W���쐬
	mpHpGauge = new CUIGauge();
	mpHpGauge->SetShow(true);
	// �X�^�~�i�Q�[�W���쐬
	mpStaminaGauge = new CStaminaGauge();
	mpStaminaGauge->SetShow(true);

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
		this, ELayer::ePlayer,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField,ELayer::eDamageObject, ELayer::eJumpingCol, ELayer::eBlockCol });
	

	// �ꎞ�I�ȓ����蔻������R���C�_�[
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::ePlayer,
		9.0f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField, ELayer::eRecoverCol, ELayer::eInvincbleCol, ELayer::eEnemy});
	mpColliderSphere->Position(0.0f, 5.0f, 1.0f);

	// �_���[�W���󂯂�R���C�_�[���쐬
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f
	);
	// �_���[�W���󂯂�R���C�_�[��
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol,ELayer::eGoalCol, ELayer::eKickCol, ELayer::eBulletCol });
	mpDamageCol->SetCollisionTags({ ETag::eEnemyWeapon,ETag::eGoalObject, ETag::eEnemy, ETag::eBullet});
	// �_���[�W���󂯂�R���C�_�[��������ւ��炷
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);

	// �}�W�b�N�\�[�h�쐬
	mpSword = new CMajicSword();
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpSword->SetOwner(this);

	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}

CPlayer::~CPlayer()
{
	// �R���C�_�[�֘A�̔j��
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderSphere);
	SAFE_DELETE(mpDamageCol);
	
	// �}�W�b�N�\�[�h��j��
	mpSword->Kill();
}

// �Փˏ���
void CPlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// ����R���C�_�[
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust * hit.weight);
			mIsGrounded = true;

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
		// �v���C���[�Ƀ_���[�W��^����R���C�_�[
		else if (other->Layer() == ELayer::eDamageObject)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
			mIsGrounded = true;

			if (other->Tag() == ETag::eRideableObject)
			{
				if (!damageObject)
				{
					TakeDamage(1);

					if (mCharaStatus.hp > 0)
					{
						damageObject = true;
						ChangeAnimation(EAnimType::eHit);
						ChangeState(EState::eReStart);
					}
					else
					{
						damageObject = true;
						ChangeState(EState::eDeath);
					}
				}
				mpRideObject = other->Owner();
			}
		}
		// �v���C���[���G�ꂽ��W�����v����R���C�_�[
		else if (other->Layer() == ELayer::eJumpingCol)
		{
			if (mState == EState::eJumpEnd)
			{
				mMoveSpeed.Y(0.0f);
				Position(Position() + hit.adjust);
				mpRideObject = other->Owner();
			}
			else
			{
				Position(Position() + hit.adjust);
			}
		}
		// �u���b�N�̃R���C�_�[
		else if (other->Layer() == ELayer::eBlockCol)
		{
			if (mState == EState::eJump)
			{
				mMoveSpeed.Y(0.0f);
				Position(Position() + hit.adjust);
				mpRideObject = other->Owner();
			}
			else
			{
				Position(Position() + hit.adjust);
			}
		}
	}

	// �ꎞ�I�ȓ����蔻������R���C�_�[
	// �J�v�Z���R���C�_�[������������ύX
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
		// �񕜃A�C�e��
		else if (other->Layer() == ELayer::eRecoverCol)
		{
			if (other->Tag() == ETag::eItemRecover)
			{
				TakeRecovery(1);
			}
		}
		// ���G�A�C�e��
		else if (other->Layer() == ELayer::eInvincbleCol)
		{
			if (other->Tag() == ETag::eItemInvincible)
			{
				TakeInvincible();
			}
		}
		else if (other->Layer() == ELayer::eEnemy)
		{
			Position(Position() + hit.adjust);
		}
	}

	// �_���[�W���󂯂�R���C�_�[
	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eGoalCol)
		{
			/*CDebugPrint::Print("Player hit GoalObject!\n");*/
			mpDamageCol->SetEnable(false);
			if (CGameManager::StageNo() == 0 || CGameManager::StageNo() == 1 || CGameManager::StageNo() == 2)
			{
				ChangeState(EState::eClear);
			}
		}
		// �G�̃L�b�N�R���C�_�[
		else if (other->Layer() == ELayer::eKickCol)
		{
			ChangeState(EState::eHit);
		}
		// �G�̒e�̃R���C�_�[
		else if (other->Layer() == ELayer::eBulletCol)
		{
			ChangeState(EState::eHitBullet);
		}
		else if (other->Layer() == ELayer::eAttackCol)
		{
			ChangeState(EState::eHitBullet);
		}
	}
}

// ��_���[�W����
void CPlayer::TakeDamage(int damage)
{
	// SE���Đ�����Ƃ��܂ɃG���[����������
	// ��U�ۗ�
	mIsPlayedHitDamageSE = false;
	if (!mIsPlayedHitDamageSE)
	{
		mpHitDamageSE->Play(1.0f, false, 0.0f);
		mIsPlayedHitDamageSE = true;
	}
	//// ���S���Ă�����A�_���[�W�͎󂯂Ȃ�
	//if (mCharaStatus.hp <= 0)return;

	//// HP����_���[�W������
	//mCharaStatus.hp = max(mCharaStatus.hp - damage, 0);
	mCharaStatus.hp -= damage;
	// HP��0�ɂȂ�����
	if (mCharaStatus.hp <= 0)
	{
		ChangeState(EState::eDeath);
	}
}

// �񕜏���
void CPlayer::TakeRecovery(int recovery)
{
	// ���艟���A�������̕��@������
	if (mCharaStatus.hp < mCharaMaxStatus.hp && !mHpHit)
	{
		mHpHit = true;
		mCharaStatus.hp += recovery;
	}
}

// ���G��ԏ���(�R���C�_�[����莞�ԃI�t�ɂ���)
void CPlayer::TakeInvincible()
{
	mInvincibleStartTime = 10.0f;
	if (!mInvincible)
	{
		mpDamageCol->SetEnable(false);
		mInvincible = true;
	}
}

// ���x���A�b�v
void CPlayer::LevelUp()
{
	int level = mCharaStatus.level;
	ChangeLevel(level + 1);
}

// ���x����ύX
void CPlayer::ChangeLevel(int level)
{
	// �X�e�[�^�X�̃e�[�u���̃C���f�b�N�X�l�ɕϊ�
	int index = Math::Clamp(level - 1, 0, PLAYER_LEVEL_MAX);
	// �ő�X�e�[�^�X�ɐݒ�
	mCharaMaxStatus = PLAYER_STATUS[index];
	// ���݂̃X�e�[�^�X���ő�l�ɂ��邱�ƂŁAHP����
	mCharaStatus = mCharaMaxStatus;

	// �ő�HP�ƌ���HP��HP�Q�[�W�ɔ��f
	mpHpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpHpGauge->SetValue(mCharaStatus.hp);

	// �ő�X�^�~�i�ƌ��݃X�^�~�i���X�^�~�i�Q�[�W�ɔ��f
	mpStaminaGauge->SetSutaminaMaxValue(mCharaMaxStatus.stamina);
	mpStaminaGauge->SetSutaminaValue(mCharaStatus.stamina);
}

// ��邱�Ƃ��ł���I�u�W�F�N�g���폜���ꂽ�Ƃ��̏���
void CPlayer::DeleteRideableObject(CTransform* rideObj)
{
	// �폜�����̂����ݏ���Ă���I�u�W�F�N�g�ł���΁A
	// ����Ă���I�u�W�F�N�g���폜
	if (mpRideObject == rideObj)
	{
		mpRideObject = nullptr;
	}
}

// �X�e�[�W�J�n���̈ʒu��ݒ�
void CPlayer::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// ���݂̏�Ԃ�؂�ւ�
void CPlayer::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// hp�擾
int CPlayer::GetHp()
{
	return mCharaStatus.hp;
}

// �ő�hp�擾
int CPlayer::GetMaxHp()
{
	return mCharaMaxStatus.hp;
}

// �A�j���[�V�����؂�ւ�
void CPlayer::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �������̏��
void CPlayer::UpdateReady()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ���
	switch (mStateStep)
	{
		// �X�e�b�v0 ����������
	case 0:
		// �S�Ă̏Փ˔�����I�t�ɂ���
		SetEnableCol(false);
		// �v���C���[�̈ړ����x��0�ɂ���
		mMoveSpeed = CVector::zero;
		// ���̃X�e�b�v��
		mStateStep++;
		break;
		// �X�e�b�v1 �X�e�[�W�̓ǂݍ��݂���
	case 1:
		// �Q�[�����J�n������
		if (CGameManager::GameState() == EGameState::eGame)
		{
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
void CPlayer::UpdateIdle()
{
	// ���ɍU���I����`����
	mpSword->AttackEnd();

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	damageEnemy = false;
	bool KeyPush = (CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D'));

	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	
	if (mIsGrounded)
	{
		//// �ړ�����
		//// �L�[�̓��̓x�N�g�����擾
		//CVector input;
		//// ���������̓���
		//if (CInput::Key('W') && !CInput::Key('S'))
		//	input.Z(-1.0f);
		//else if (CInput::Key('S') && !CInput::Key('W'))
		//	input.Z(1.0f);
		//else
		//	input.Z(0.0f);

		//// ���������̓���
		//if (CInput::Key('A') && !CInput::Key('D'))
		//	input.X(-1.0f);
		//else if (CInput::Key('D') && !CInput::Key('A'))
		//	input.X(1.0f);
		//else
		//	input.X(0.0f);

		// �ړ�����
		// �L�[�̓��̓x�N�g�����擾
		CVector input;
		if (CInput::Key('W'))		input.Z(-1.0f);
		else if (CInput::Key('S'))	input.Z(1.0f);
		if (CInput::Key('A'))		input.X(-1.0f);
		else if (CInput::Key('D'))	input.X(1.0f);

		// ���̓x�N�g���̒����œ��͂���Ă��邩����
		if (input.LengthSqr() > 0.0f)
		{
			// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
			CCamera* mainCamera = CCamera::MainCamera();
			CVector camForward = mainCamera->VectorZ();
			CVector camSide = CVector::Cross(CVector::up, camForward);
			CVector move = camForward * input.Z() + camSide * input.X();
			// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
			//CVector move = CCamera::MainCamera()->Rotation() * input;
			move.Y(0.0f);
			move.Normalize();

			float speed = MOVE_SPEED;
			if (CInput::Key(VK_SHIFT) && KeyPush)
			{
				if ((mCharaStatus.stamina > 0 && !staminaLowerLimit))
				{
					// ���x�𑖍s���x�ɕύX
					speed = RUN_SPEED;
					mCharaStatus.stamina -= 1;
					ChangeAnimation(EAnimType::eDash);

					if (mCharaStatus.stamina == 0)
					{
						staminaLowerLimit = true;
						ChangeState(EState::eDashEnd);
					}
				}
				else
				{
					if (staminaLowerLimit && mCharaStatus.stamina == mCharaMaxStatus.stamina)
					{
						staminaLowerLimit = false; // �X�^�~�i���Ă�MAX�ɂȂ����烊�Z�b�g
					}
					mCharaStatus.stamina += 1;
					ChangeAnimation(EAnimType::eWalk);
				}
			}
			else
			{
				if (mCharaStatus.stamina < mCharaMaxStatus.stamina && !staminaDepleted)
				{
					mCharaStatus.stamina += 1;
				}
				else if (mCharaStatus.stamina >= mCharaMaxStatus.stamina)
				{
					staminaDepleted = false;  // �X�^�~�i������l����ɂȂ����烊�Z�b�g
				}

				ChangeAnimation(EAnimType::eWalk);
			}
			mMoveSpeed += move * speed * MOVE_SPEED * mCharaStatus.moveSpeed;
		}
		// �ړ��L�[����͂��Ă��Ȃ�
		else
		{
			// �ҋ@�A�j���[�V�����ɐ؂�ւ�
			ChangeAnimation(EAnimType::eIdle);
			if (mCharaStatus.stamina < mCharaMaxStatus.stamina && !staminaDepleted)
			{
				mCharaStatus.stamina += 1;
			}
			else if (mCharaStatus.stamina >= mCharaMaxStatus.stamina)
			{
				staminaDepleted = false;  //  �X�^�~�i������l����ɂȂ����烊�Z�b�g
			}
		}

		// J�L�[�ōU����Ԃֈڍs
		if (CInput::PushKey(VK_LBUTTON))
		{
			mMoveSpeed.X(0.0f);
			mMoveSpeed.Z(0.0f);
			ChangeState(EState::eAttack);
		}
		// K�L�[�ŋ��U��
		else if (CInput::PushKey(VK_RBUTTON))
		{
			mMoveSpeed.X(0.0f);
			mMoveSpeed.Z(0.0f);
			ChangeState(EState::eAttackStrong);
		}
		// SPACE�L�[�ŃW�����v�J�n�ֈڍs
		else if (CInput::PushKey(VK_SPACE))
		{
			if (mCharaStatus.stamina - 20 >= 0)
			{
				ChangeState(EState::eJumpStart);
				// �X�^�~�i��0�ȉ��ɂȂ�Ȃ��ꍇ�̓W�����v�����s
				mCharaStatus.stamina -= 20;
			}
			else
			{
			}
		}
		// CTRL�L�[�ŉ���ֈڍs
		else if (((CInput::PushKey(VK_CONTROL)) && KeyPush) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
		{
			// ����s���O�ɃX�^�~�i��0�ȉ��ɂȂ邩�ǂ������m�F
			if (mCharaStatus.stamina - 50 >= 0) {
				
				mMoveSpeed.X(0.0f);
				mMoveSpeed.Z(0.0f);
				ChangeState(EState::eRotate);
				// �X�^�~�i��0�ȉ��ɂȂ�Ȃ��ꍇ�͉���s�������s
				mCharaStatus.stamina -= 50;
			}
			else
			{
			}
		}
	}
	else
	{
		if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
		{
			mCharaStatus.stamina += 1;
		}

		// �ҋ@�A�j���[�V�����ɐ؂�ւ�
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �_�b�V���I��
void CPlayer::UpdateDashEnd()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	mMoveSpeed.Z(0.0f);
	mMoveSpeed.X(0.0f);
	ChangeAnimation(EAnimType::eDashStop);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �U��
void CPlayer::UpdateAttack()
{
	// �U���A�j���[�V�������J�n
	// ���ɍU���J�n��`����
	mpSword->AttackStart();
	ChangeAnimation(EAnimType::eAttack);
	ChangeState(EState::eAttackWait);

	// �a��SE�̍Đ��ς݃t���O��������
	mIsPlayedSlashSE = false;
}

// ���U��
void CPlayer::UpdateAttackStrong()
{
	// ���U���A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttackStrong);
	// �U���I���҂���Ԃֈڍs
	ChangeState(EState::eAttackStrongWait);
}

// �U���I���҂�
void CPlayer::UpdateAttackWait()
{
	bool KeyPush = (CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D'));
	if (mAnimationFrame >= 10.0f)
	{
		// �U���I���҂���Ԃֈڍs
		// CTRL�L�[�ŉ���ֈڍs
		if (((CInput::PushKey(VK_CONTROL)) && KeyPush) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
		{
			// ����s���O�ɃX�^�~�i��0�ȉ��ɂȂ邩�ǂ������m�F
			if (mCharaStatus.stamina - 50 >= 0) 
			{
				ChangeState(EState::eRotate);
				// �X�^�~�i��0�ȉ��ɂȂ�Ȃ��ꍇ�͉���s�������s
				mCharaStatus.stamina -= 50;
				mpSword->AttackEnd();

			}
			else
			{
			}
		}

		if (CInput::PushKey(VK_SPACE))
		{
			mpSword->AttackEnd();
			ChangeState(EState::eJumpStart);
		}

		// SE
		if (!mIsPlayedSlashSE && GetAnimationFrame() >= 10.0f)
		{
			// �a��SE���Đ�
			mpSlashSE->Play(1.0f, false, 0.0f);
			mIsPlayedSlashSE = true;
		}

		if (GetAnimationFrame() >= 50.0f)
		{
			// ���ɍU���I����`����
			mpSword->AttackEnd();
		}
	}
	else
	{

	}
	// �U���A�j���[�V�������I��������A
	if (IsAnimationFinished())
	{
		// �ҋ@��Ԃֈڍs
		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

// ���U���I���҂�
void CPlayer::UpdateAttackStrongWait()
{
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

//����J�n
void CPlayer::UpdateRotate()
{
	mpDamageCol->SetEnable(false);

	// �ړ�����
	// �L�[�̓��̓x�N�g�����擾
	CVector input;
	if (CInput::Key('W'))		input.Z(-1.0f);
	else if (CInput::Key('S'))	input.Z(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// ���̓x�N�g���̒����œ��͂���Ă��邩����
	if (input.LengthSqr() > 0.0f)
	{
		// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
		CVector move = CCamera::MainCamera()->Rotation() * input;
		move.Y(0.0f);
		move.Normalize();

		float speed = MOVE_SPEED;
		mMoveSpeed += move * speed * MOVE_SPEED * mCharaStatus.moveSpeed;
	}
	ChangeAnimation(EAnimType::eRotate);
	ChangeState(EState::eRotateEnd);
}

//����I���҂�
void CPlayer::UpdateRotateEnd()
{
	if (IsAnimationFinished())
	{
		mpDamageCol->SetEnable(true);

		if (mElapsedTimeCol <= DAMAGECOL)
		{
			mElapsedTimeCol += Time::DeltaTime();
			if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
			{
				mElapsedTimeCol = DAMAGECOL;
				mpDamageCol->SetEnable(true);
			}
		}

		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �N���A
void CPlayer::UpdateClear()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eGuts);
	ChangeState(EState::eClearEnd);
}

// �N���A�I��
void CPlayer::UpdateClearEnd()
{
	if (IsAnimationFinished())
	{
		// �X�e�[�W���N���A
		CGameManager::StageClear();
		// �X�e�[�W���N���A������A���̃X�e�[�W�J�n�܂ŏ������̏�ԂɕύX
		ChangeState(EState::eReady);
	}
}

// ���S
void CPlayer::UpdateDeath()
{
	mpDamageCol->SetEnable(false);
	mpSword->AttackEnd();
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eDeath);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eDeathEnd);
	}
}

// ���S�����I��
void CPlayer::UpdateDeathEnd()
{
	if (IsAnimationFinished())
	{
		damageObject = false;
		mCharaStatus = mCharaMaxStatus;
		Position(0.0f, 20.0f, -30.0f);
		ChangeState(EState::eIdle);
	}
}

// �ċN
void CPlayer::UpdateReStart()
{
	if (IsAnimationFinished())
	{
		damageObject = false;
		Position(0.0f, 10.0f, -30.0f);
		ChangeState(EState::eIdle);
	}
}

// �G�̍U�����󂯂���
void CPlayer::UpdateHit()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));
	if (!damageEnemy)
	{
		TakeDamage(3);
		damageEnemy = true;
	}

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	// �_���[�W���󂯂����͈ړ����~
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eHitJ);
	if (IsAnimationFinished())
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			damageEnemy = false;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eIdle);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}
}

// �G�̒e�̍U�����󂯂���
void CPlayer::UpdateHitBullet()
{
	ChangeAnimation(EAnimType::eHit);

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	mElapsedTime += Time::DeltaTime();
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));

	if (!damageEnemy)
	{
		TakeDamage(1);
		damageEnemy = true;
	}

	if (mElapsedTime >= COLORSET)
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			damageEnemy = true;
			mElapsedTime = 0.0f;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eIdle);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mElapsedTime = 0.0f;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}

	//CDebugPrint::Print("Time%f\n", mElapsedTime);
}

// �W�����v�J�n
void CPlayer::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eJump);

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	// �ړ�����
	// �L�[�̓��̓x�N�g�����擾
	CVector input;
	if (CInput::Key('W'))		input.Z(-1.0f);
	else if (CInput::Key('S'))	input.Z(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// ���̓x�N�g���̒����œ��͂���Ă��邩����
	if (input.LengthSqr() > 0.0f)
	{
		// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
		CVector move = CCamera::MainCamera()->Rotation() * input;
		move.Y(0.0f);
		move.Normalize();

		mMoveSpeed = move;
	}
	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// �W�����v��
void CPlayer::UpdateJump()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpEnd);
	}
}

// �W�����v�I��
void CPlayer::UpdateJumpEnd()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
}

// ���˂鏈���J�n
void CPlayer::UpdateJumpingStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eJumping);

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	// �ړ�����
	// �L�[�̓��̓x�N�g�����擾
	CVector input;
	if (CInput::Key('W'))		input.Z(-1.0f);
	else if (CInput::Key('S'))	input.Z(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// ���̓x�N�g���̒����œ��͂���Ă��邩����
	if (input.LengthSqr() > 0.0f)
	{
		// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
		CVector move = CCamera::MainCamera()->Rotation() * input;
		move.Y(0.0f);
		move.Normalize();

		mMoveSpeed = move;
	}
	mMoveSpeed += CVector(0.0f, JUMP_BOUNCE, 0.0f);
	mIsGrounded = false;
}

// ���˂鏈��
void CPlayer::UpdateJumping()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpingEnd);
	}
}

// ���˂鏈���J�n
void CPlayer::UpdateJumpingEnd()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
}

// �X�V
void CPlayer::Update()
{
	SetParent(mpRideObject);
	SetColor(CColor(1.0, 1.0, 1.0, 1.0));
	mpRideObject = nullptr;
	mHpHit = false;

	// ��Ԃɍ��킹�āA�X�V������؂�ւ���
	switch (mState)
	{
		// �������̏��
	case EState::eReady:
		UpdateReady();
		break;
		// �ҋ@���
		case EState::eIdle:
			UpdateIdle();
			break;
		// �_�b�V���I��
		case EState::eDashEnd:
			UpdateDashEnd();
			break;
		// �U��
		case EState::eAttack:
			UpdateAttack();
			break;
		// ���U��
		case EState::eAttackStrong:
			UpdateAttackStrong();
			break;
		// �U���I���҂�
		case EState::eAttackWait:
			UpdateAttackWait();
			break;
		// ���U���I���҂�
		case EState::eAttackStrongWait:
			UpdateAttackStrongWait();
			break;
		// ����J�n
		case EState::eRotate:
			UpdateRotate();
			break;
		// ����I��
		case EState::eRotateEnd:
			UpdateRotateEnd();
			break;
		// �G�̃_���[�WHit
		case EState::eHit:
			UpdateHit();
			break;
		// �G�̒eHit
		case EState::eHitBullet:
			UpdateHitBullet();
			break;
		// �N���A
		case EState::eClear:
			UpdateClear();
			break;
		// �N���A�I��
		case EState::eClearEnd:
			UpdateClearEnd();
			break;
		// ���S
		case EState::eDeath:
			UpdateDeath();
			break;
		// ���S�����I��
		case EState::eDeathEnd:
			UpdateDeathEnd();
			break;
		// �ċN
		case EState::eReStart:
			UpdateReStart();
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
		// ���˂�J�n
		case EState::eJumpingStart:
			UpdateJumpingStart();
			break;
		// ���˂�
		case EState::eJumping:
			UpdateJumping();
			break;
		// ���˂�I��
		case EState::eJumpingEnd:
			UpdateJumpingEnd();
			break;
	}

	// �������łȂ���΁A�ړ������Ȃǂ��s��
	if (mState != EState::eReady)
	{
		mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

		// �ړ�
		Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());

		// �v���C���[���ړ������֌�����
		CVector current = VectorZ();
		CVector target = mMoveSpeed;
		target.Y(0.0f);
		target.Normalize();
		CVector forward = CVector::Slerp(current, target, 0.125f);
		Rotation(CQuaternion::LookRotation(forward));
	}

	// ���G��Ԃ������ꍇ�̏���
	if (mInvincible)
	{
		SetColor(CColor(1.0, 1.0, 0.0, 1.0));
		mInvincibleStartTime -= Time::DeltaTime();

		if (mInvincibleStartTime <= 0.0f)
		{
			mpDamageCol->SetEnable(true);
			mInvincibleStartTime = 10.0f;
			mInvincible = false;
		}
	}

	// �Ȃ�̏������Y�ꂽ���A�����Ă���肪������������
	// �R�����g�A�E�g
	// ���炭�W�����v�R���C�_�[�֘A
	/*if (JumpObject)
	{
		JumpCoolDownTime -= Time::DeltaTime();

		if (JumpCoolDownTime <= 0.0f)
		{
			JumpObject = false;
		}
	}*/

	// �L�����N�^�[�̃f�o�b�O�\��
	static bool debug = false;
	if (CInput::PushKey('R'))
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
	if (CInput::Key('1'))
	{
		if (CInput::PushKey(VK_UP)) mCharaStatus.hp++;
		else if (CInput::PushKey(VK_DOWN)) mCharaStatus.hp--;
	}
	else if (CInput::Key('2'))
	{
		LevelUp();
	}

	// ���݂�HP��ݒ�
	mpHpGauge->SetValue(mCharaStatus.hp);
	// ���݂̃X�^�~�i��ݒ�
	mpStaminaGauge->SetSutaminaValue(mCharaStatus.stamina);


	///////////////////////////////////////////
	// ���̗����_���[�W����
	// �ύX�\��
	float minHeaight = -100.0f;
	if (Position().Y() < minHeaight)
	{
		ChangeAnimation(EAnimType::eHitJ);
		TakeDamage(1);
		Position(0.0f, 20.0f, -30.0f);
	}
	///////////////////////////////////////////
	
	// �L�����N�^�[�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpSword->UpdateAttachMtx();

	mIsGrounded = false;

	//// �c�����̈ړ����x�Ď�
	//CDebugPrint::Print("mMoveSpeed%f\n", mMoveSpeed.Y());
	//// ���G���Ԃ̎��ԊĎ�
	//CDebugPrint::Print("mInvincible:%f\n", mInvincibleStartTime);
	//// ���݂̏c�����̃|�W�V�����Ď�
	//CDebugPrint::Print("Position.Y %f\n", Position().Y());
	//// �R���C�_�[�̕������ԊĎ�
	//CDebugPrint::Print("TimeCol%f\n", mElapsedTimeCol);
}

// �`��
void CPlayer::Render()
{
	// �L�����`��
	CXCharacter::Render();
}