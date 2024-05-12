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
#include "CClimbWall.h"
#include "CWireMeshClimbWall.h"
#include "CWireMeshMoveClimbWall.h"
#include "CVanguard.h"
#include "CFlamethrower.h"
#include "CSlash.h"
#include "CSound.h"
#include "CImage.h"
#include "CStageManager.h"

// �v���C���[�֘A
// ����
#define PLAYER_HEIGHT 16.0f
// �X�s�[�h
#define MOVE_SPEED 0.9f
// �ړ��X�s�[�h
#define RUN_SPEED 1.3f
// �_�b�V���X�s�[�h
#define DASH_SPEED 2.0f
// �W�����v
#define JUMP_SPEED 1.5f
// ��W�����v
#define JUMP_BOUNCE 2.0f
// �d��
#define GRAVITY 0.0625f
// �W�����v�I����
#define JUMP_END_Y 1.0f

// �ǂ�o�鑬�x
#define CLIMB_SPEED 0.5f
// �ǂ̒���֏��̂ɂ����鎞��
#define CLIMBED_TOP_TIME 1.0f
// ���Ԃ̒���֏��̂ɂ����鎞��
#define WIREMESH_TOP_TIEM 0.2f


//����̊p�x(�[�p�x+�p�x���o)
#define FOV_ANGLE 45.0f
//����̊p�x
#define FOV_LENGTH 5.0f


// HP�֘A
#define HP 100
// ���x���֘A
#define LEVEL 1
// �X�^�~�i�֘A
#define STAMINA 150


// ���̑�
// �F��`�悷�鎞��
#define COLORSET 0.5f
// �_���[�W�R���C�_�[�̌v������
#define DAMAGECOL 0.9f

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
	{ "Character\\Monster1\\anim\\Warrok_Walking.x",				true,	86.0f	},	// ���s
	{ "Character\\Monster1\\anim\\Warrok_Punchi.x",				false,	50.0f	},		// �U��
	{ "Character\\Monster1\\anim\\Warrok_StrongAttack.x",		false,	161.0f	},		// ���U��
	{ "Character\\Monster1\\anim\\Warrok_SpinAttack(1)_79.x",	false,	79.0f	},		// �_�b�V���A�^�b�N
	{ "Character\\Monster1\\anim\\jump_start1.x",				false,	25.0f	},		// �W�����v�J�n
	{ "Character\\Monster1\\anim\\jump1.x",							true,	1.0f	},	// �W�����v��
	{ "Character\\Monster1\\anim\\jump_end1.x",					false,	26.0f	},		// �W�����v�I��
	{ "Character\\Monster1\\anim\\Dash1_53.x",						true,	53.0f	},	// �_�b�V��
	{ "Character\\Monster1\\anim\\Warrok_RunStop.x",			false,	40.0f	},		// �_�b�V���I��
	{ "Character\\Monster1\\anim\\Rotate.x",					false,	50.0f	},		// ���
	{ "Character\\Monster1\\anim\\Guts pose_325.x",				false,	325.0f	},		// �K�b�c�|�[�Y
	{ "Character\\Monster1\\anim\\Hit_63.x",					false,	63.0f	},		// �G�̍U��Hit
	{ "Character\\Monster1\\anim\\Hit_107.x",					false,	107.0f	},		// �G�̒eHit
	{ "Character\\Monster1\\anim\\Death_276.x",					false,	276.0f	},		// ���S
	{ "Character\\Monster1\\anim\\Climb_121.x",						true,	121.0f	},	// �ǂ�o��
	{ "Character\\Monster1\\anim\\Climb_to Top_241.x",				true,	241.0f	},	// ����֓o����
	{ "Character\\Monster1\\anim\\Warrok_Falling_643.x",			true,	643.0f	},	// �������
	{ "Character\\Monster1\\anim\\Warrok_Falling Flat_93.x",	false,	93.0f	},		// ������Ԃ��璅�n����
	{ "Character\\Monster1\\anim\\Warrok_Stand Up_141.x",		false,	141.0f	},		// �����オ��

};

// �R���X�g���N�^
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer, 0,
		ETaskPauseType::ePlayer)
	, mState(EState::eReady)
	, mInventory(std::map<ItemType, int>())
	, mStateStep(0)
	, mWeaponTime(0.0f)
	, mMoveSpeedY(0.0f)
	, mElapsedTime(0.0f)
	, mStartDashTime(0.0f)
	, mElapsedTimeEnd(0.0f)
	, mElapsedTimeCol(0.0f)
	, mClimbStaminaTime(0.0f)
	, mInvincibleStartTime(10.0f)
	, mStartPos(CVector::zero)
	, mMoveSpeed(CVector::zero)
	, mGroundNormal(CVector::up)
	, mClimbNormal(CVector::zero)
	, mClimbedStartPos(CVector::zero)
	, mClimbedMovedPos(CVector::zero)
	, mClimbedMovedUpPos(CVector::zero)
	, mDash(false)
	, mClimb(false)
	, mHpHit(false)
	, mIsAttack(false)
	, mSavePoint(false)
	, mIsJumping(false)
	, mClimbWall(false)
	, mInvincible(false)
	, mFallDamage(false)
	, mStage1Clear(false)
	, mStage2Clear(false)
	, mStage3Clear(false)
	, mDamageEnemy(false)
	, mClimbWallTop(false)
	, mDamageObject(false)
	, mStaminaDepleted(false)
	, mIsPlayedSlashSE(false)
	, mStaminaLowerLimit(false)
	, mIsPlayedHitDamageSE(false)
	, mIsSpawnedSlashEffect(false)
	, mpRideObject(nullptr)
{
	ClearItems();
	//, mInventory(std::vector<ItemType>())
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// �a��SE�̍Đ��ς݃t���O��������
	mIsPlayedSlashSE = false;
	// �a���G�t�F�N�g�̐����ς݃t���O��������
	mIsSpawnedSlashEffect = false;

	Position(0.0f, 0.0f, 0.0f);
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
	mpColliderLine->SetCollisionLayers({ ELayer::eField,ELayer::eDamageObject, ELayer::eJumpingCol,
		ELayer::eBlockCol });


	// �ꎞ�I�ȓ����蔻������R���C�_�[
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::ePlayer,
		0.8f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField, ELayer::eRecoverCol, 
		ELayer::eInvincbleCol, ELayer::eEnemy, ELayer::eClimb, ELayer::eMedalCol,
		ELayer::eSavePoint, ELayer::eAttackCol,ELayer::eGoalCol });
	mpColliderSphere->SetCollisionTags({ ETag::eGoalObject,ETag::eMedal, ETag::eField,ETag::eAttackObject,
		ETag::eItemInvincible,ETag::eItemRecover,ETag::eSavePoint, ETag::eObstacle});
	//mpColliderSphere->Position(0.0f, 5.0f, 1.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpColliderSphere->SetAttachMtx(spineMtx);

	// �_���[�W���󂯂�R���C�_�[���쐬
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.9f
	);
	// �_���[�W���󂯂�R���C�_�[��
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol, 
		ELayer::eKickCol, ELayer::eBulletCol,ELayer::eNeedleCol,
		ELayer::eFlame,ELayer::eFall});
	mpDamageCol->SetCollisionTags({ ETag::eEnemyWeapon, 
		ETag::eEnemy, ETag::eBullet,ETag::eRideableObject, ETag::eFlame,
		ETag::eFall});
	// �_���[�W���󂯂�R���C�_�[��������ւ��炷
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx1 = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx1);


	// �o���R���C�_�[�Ƃ̓����蔻������R���C�_�[
	mpClimbCol = new CColliderLine
	(
		this, ELayer::ePlayer,
		CVector(0.0f, PLAYER_HEIGHT, 12.5f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	mpClimbCol->SetCollisionLayers({ ELayer::eClimb,ELayer::eClimbedTop,
		ELayer::eWireClimb,ELayer::eWireClimbedTop,
		ELayer::eWireMoveClimb, ELayer::eWireMoveClimbedTop});


	// �}�W�b�N�\�[�h�쐬
	mpSword = new CMajicSword();
	//mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
	mpSword->SetOwner(this);
	CStageManager::AddTask(mpSword);


	mpFlamethrower = new CFlamethrower
	(
		this, nullptr,
		CVector(0.0f, 14.0f, -1.0f),
		CQuaternion(0.0f, 90.0f, 0.0f).Matrix()
	);
	CStageManager::AddTask(mpFlamethrower);

	mpCutInDeath = new CCutInDeath();
	mpCutInClear = new CCutInClear();


	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}

CPlayer::~CPlayer()
{
	CStageManager::RemoveTask(mpSword);
	CStageManager::RemoveTask(mpFlamethrower);

	spInstance = nullptr;
	// �R���C�_�[�֘A�̔j��
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderSphere);
	SAFE_DELETE(mpDamageCol);
	SAFE_DELETE(mpClimbCol);

	// �}�W�b�N�\�[�h��j��
	mpSword->Kill();

	mpCutInDeath->Kill();
	mpCutInClear->Kill();
}

// �Փˏ���
void CPlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// ����R���C�_�[
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			CVector adjust = hit.adjust;
			mMoveSpeedY = 0.0f;
			adjust.X(0.0f);
			adjust.Z(0.0f);
			Position(Position() + adjust * hit.weight);

			// �ڒn����
			mIsGrounded = true;
			// �ڒn�����n�ʂ̖@�����L�����Ă���
			mGroundNormal = hit.adjust.Normalized();

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
		// �v���C���[�Ƀ_���[�W��^����R���C�_�[
		else if (other->Layer() == ELayer::eDamageObject)
		{
			mMoveSpeedY = 0.0f;
			Position(Position() + hit.adjust);

			// �ڒn����
			mIsGrounded = true;
			// �ڒn�����n�ʂ̖@�����L�����Ă���
			mGroundNormal = hit.adjust.Normalized();

			if (other->Tag() == ETag::eRideableObject)
			{
				if (!mDamageObject)
				{
					TakeDamage(1);

					if (mCharaStatus.hp > 0)
					{
						mDamageObject = true;
						ChangeAnimation(EAnimType::eHit);
						ChangeState(EState::eReStart);
					}
					else
					{
						mDamageObject = true;
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
				//mMoveSpeedY = 0.0f;
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
				mMoveSpeedY = 0.0f;
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
		// �U���̓A�b�v�|�[�V����
		else if (other->Layer() == ELayer::eAttackCol)
		{
			if (other->Tag() == ETag::eAttackObject)
			{
				//AddItem(ItemType::ATTACK_UP);
			}
		}
		// �񕜃A�C�e��
		else if (other->Layer() == ELayer::eRecoverCol)
		{
			if (other->Tag() == ETag::eItemRecover)
			{
				//AddItem(ItemType::HEALING);
			}
		}
		// ���G�A�C�e��
		else if (other->Layer() == ELayer::eInvincbleCol)
		{
			if (other->Tag() == ETag::eItemInvincible)
			{
				//AddItem(ItemType::INVINCIBLE);
			}
		}
		// ���_���A�C�e��
		else if (other->Layer() == ELayer::eMedalCol)
		{
			if (other->Tag() == ETag::eMedal)
			{

			}
		}
		else if (other->Layer() == ELayer::eEnemy)
		{
			Position(Position() + hit.adjust);
		}
		// �o���I�u�W�F�N�g
		else if (other->Layer() == ELayer::eClimb)
		{
			// Climb��Ԃ̏ꍇ�͈ʒu�𒲐�����
			Position(Position() + hit.adjust);
		}
		// �Z�[�u�|�C���g
		else if (other->Layer() == ELayer::eSavePoint)
		{
			if (other->Tag() == ETag::eSavePoint)
			{
				mSavePoint = true;
			}
		}
		// �S�[���|�X�g
		else if (other->Layer() == ELayer::eGoalCol)
		{
			/*CDebugPrint::Print("Player hit GoalObject!\n");*/
			mpColliderSphere->SetEnable(false);
			if (CGameManager::StageNo() == 0 ||
				CGameManager::StageNo() == 1 ||
				CGameManager::StageNo() == 2 ||
				CGameManager::StageNo() == 3)
			{
				ChangeState(EState::eClear);
			}
		}
	}

	// �_���[�W���󂯂�R���C�_�[
	if (self == mpDamageCol)
	{
		// �G�̃L�b�N�R���C�_�[
		if (other->Layer() == ELayer::eKickCol)
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
			ChangeState(EState::eHitSword);
		}
		// �j�u���b�N�̃R���C�_�[
		else if (other->Layer() == ELayer::eNeedleCol)
		{
			ChangeState(EState::eHitObj);
			mpRideObject = other->Owner();
		}
		// ��������p�̃R���C�_�[�ɐG�ꂽ��
		else if (other->Layer() == ELayer::eFall)
		{
			// �����_���[�W����
			int currentStage = CGameManager::StageNo();
			if (currentStage == 3)
			{
				ChangeState(EState::eFallDamege);
				Position(0.0f, 17.0f, -70.0f);
				// 3�ʂ̃Z�[�u�|�C���g
				if (mSavePoint)
				{
					ChangeState(EState::eFallDamege);
					Position(0.0f, 15.0f, 325.0f);
				}
			}
			//CDebugPrint::Print("mSavePoint: %s\n", mSavePoint ? "true" : "false");
		}
		// ���ɓ���������
		else if (other->Layer() == ELayer::eFlame)
		{
			ChangeState(EState::eHit);
		}
	}

	// �o���R���C�_�[�Ƃ̓����蔻������R���C�_�[
	if (self == mpClimbCol)
	{
		// �o���ǂ̃R���C�_�[
		if (other->Layer() == ELayer::eClimb)
		{
			mClimbWall = true;
			if (mState == EState::eIdle && mIsGrounded)
			{
				if (CInput::PushKey('E'))
				{
					// Climb��ԂɈڍs����
					ChangeState(EState::eClimb);
					// ������o��ǂ��L�����Ă���
					mpClimbWall = dynamic_cast<CClimbWall*>(other->Owner());
				}
			}

			// ���ݕǂ�o���Ă���Œ��ł���΁A
			if (mState == EState::eClimb)
			{
				// �o���Ă���ǂ̖@�����擾
				mClimbNormal = hit.adjust.Normalized();
			}
		}
		// �o���ǂ̒���R���C�_�[
		else if (other->Layer() == ELayer::eClimbedTop)
		{
			mClimbWallTop = true;
		}

		// �o�����Ԃ̃R���C�_�[
		if (other->Layer() == ELayer::eWireClimb)
		{
			mClimbWall = true;

			if (mState == EState::eIdle && mIsGrounded)
			{
				if (CInput::PushKey('E'))
				{
					// Climib��ԂɈڍs����
					ChangeState(EState::eWireClimb);
					// ������o��ǂ��L�����Ă���
					mpWireWall = dynamic_cast<CWireMeshClimbWall*>(other->Owner());
				}

				// ���݋��Ԃ�o���Ă���Œ��ł���΁A
				if (mState == EState::eWireClimb)
				{
					// �o���Ă���ǂ̖@�����擾
					mClimbNormal = hit.adjust.Normalized();
				}
			}
		}
		if (other->Layer() == ELayer::eWireMoveClimb && mState == EState::eWireClimb)
		{
			mClimbWall = true;

			// Climib��ԂɈڍs����
			ChangeState(EState::eWireClimb);
			// ������o��ǂ��L�����Ă���
			mpRideObject = other->Owner();
			mpWireMoveWall = dynamic_cast<CWireMeshMoveClimbWall*>(other->Owner());

			// ���݋��Ԃ�o���Ă���Œ��ł���΁A
			if (mState == EState::eWireClimb)
			{
				// �o���Ă���ǂ̖@�����擾
				mClimbNormal = hit.adjust.Normalized();
			}
		}
		// �o���ǂ̒���R���C�_�[
		else if (other->Layer() == ELayer::eWireClimbedTop)
		{
			mClimbWallTop = true;
		}
		// �o��铮���ǂ̒���R���C�_�[
		else if (other->Layer() == ELayer::eWireMoveClimbedTop)
		{
			mClimbWallTop = true;
		}
	}
}

// �A�C�e�����擾
void CPlayer::AddItem(ItemType item)
{
	mInventory[item]++;
}

// �擾�����A�C�e���𔻒�
bool CPlayer::HasItem(ItemType item)
{	
	if (mInventory.empty()) {
		return ItemType::NONE == item;
	}
	return mInventory.find(item) != mInventory.end() && mInventory[item] > 0;
}

// �擾�����A�C�e���𔻒�
void CPlayer::ClearItems()
{
	mInventory.clear();
	//AddItem(ItemType::NONE);
}

// �A�C�e���̎擾�̏����t��������s�����߂̏���
void CPlayer::PickUpItem(ItemType item)
{
	AddItem(item);
}

// ���G�A�C�e���̎g�p
void CPlayer::UseInvincibleItem()
{
	if (HasItem(ItemType::INVINCIBLE)) {
		TakeInvincible();
		RemoveItem(ItemType::INVINCIBLE);
	}
}

// �񕜖�̎g�p
void CPlayer::UseHealingItem()
{
	if (HasItem(ItemType::HEALING)) {
		TakeRecovery(1);
		RemoveItem(ItemType::HEALING);
	}
}

// �U���̓A�b�v�A�C�e���̎g�p
void CPlayer::UseAttackPotion()
{
	if (HasItem(ItemType::ATTACK_UP)) {
		TakeAttackPotion(1);
		RemoveItem(ItemType::ATTACK_UP);
	}
}

// �C���x���g���������̃A�C�e�����폜
void CPlayer::RemoveItem(ItemType item)
{
	if (mInventory[item] > 0) {
		mInventory[item]--;
		if (mInventory[item] == 0) {
			mInventory.erase(item);	 // �A�C�e����0�ɂȂ�����C���x���g������폜����
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

// �U���͂��㏸������
void CPlayer::TakeAttackPotion(int attack)
{
	mCharaStatus.power += attack;
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
	// �A�j���[�V�����̍Đ����x�����Ƃɖ߂�
	SetAnimationSpeed(1.0f);
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

// �W�����v���������ǂ����擾
bool CPlayer::IsJumping()
{
	return mIsJumping;
}

// �U�������ǂ���
bool CPlayer::IsAttack()
{
	return mIsAttack;
}

// �X�e�[�W1���N���A������
bool CPlayer::IsStage1Clear()
{
	return mStage1Clear;
}

// �X�e�[�W2���N���A������
bool CPlayer::IsStage2Clear()
{
	return mStage2Clear;
}

// �X�e�[�W3���N���A������
bool CPlayer::IsStage3Clear()
{
	return mStage3Clear;
}

// �A�j���[�V�����؂�ւ�
void CPlayer::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �L�[�̓��͏�񂩂�ړ��x�N�g�������߂�
CVector CPlayer::CalcMoveVec() const
{
	CVector move = CVector::zero;

	// �L�[�̓��̓x�N�g�����擾
	CVector input = CVector::zero;
	if (CInput::Key('W'))		input.Z(-1.0f);
	else if (CInput::Key('S'))	input.Z(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// ���̓x�N�g���̒����œ��͂���Ă��邩����
	if (input.LengthSqr() > 0.0f)
	{
		// ������x�N�g��(�ݒu���Ă���ꍇ�́A�n�ʂ̖@��)
		CVector up = mIsGrounded ? mGroundNormal : CVector::up;
		// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
		CCamera* mainCamera = CCamera::MainCamera();
		CVector camForward = mainCamera->VectorZ();
		camForward.Y(0.0f);
		camForward.Normalize();
		// �J�����̐��ʕ����x�N�g���Ə�����x�N�g���̊O�ς���
		// �������̈ړ��x�N�g�������߂�
		CVector moveSide = CVector::Cross(up, camForward);
		// �������̈ړ��x�N�g���Ə�����x�N�g���̊O�ς���
		// ���ʕ����̈ړ��x�N�g�������߂�
		CVector moveForward = CVector::Cross(moveSide, up);

		// ���߂��e�����̈ړ��x�N�g������A
		// �ŏI�I�ȃv���C���[�̈ړ��x�N�g�������߂�
		move = moveForward * input.Z() + moveSide * input.X();
		move.Normalize();
	}
	return move;
}

// �L�[�̓��͏�񂩂�ړ��x�N�g�������߂�
CVector CPlayer::ClimbMoveVec() const
{
	CVector move = CVector::zero;

	// �L�[�̓��̓x�N�g�����擾
	CVector input = CVector::zero;
	if (CInput::Key('W'))		input.Y(-1.0f);
	else if (CInput::Key('S'))	input.Y(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// ���͂���Ă���ꍇ�̂݁A���E�����̈ړ��x�N�g����ݒ�
	if (input.LengthSqr() > 0.0f)
	{
		// ���[���h�̏�����x�N�g���Ɠo���Ă���ǂ̖@���̊O�ς���A
		// �������̈ړ��x�N�g�������߂�
		CVector moveSide = CVector::Cross(CVector::up, mClimbNormal);
		// ���߂��������̈ړ��x�N�g���Ɠo���Ă���ǂ̖@���̊O�ς���A
		// �㉺�ړ��x�N�g�������߂�
		CVector moveUp = CVector::Cross(moveSide, mClimbNormal);

		// �v���C���[�̈ړ��x�N�g�� =
		// ���ړ��x�N�g���~�����́@�{�@�㉺�ړ��x�N�g���~�㉺����
		move = moveSide * input.X() + moveUp * input.Y();
		move.Normalize();
	}

	return move;
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
		mMoveSpeedY = 0.0f;
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
	mMoveSpeed = CVector::zero;
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

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHandMiddle1"));
	}

	mDamageEnemy = false;

	mMoveSpeed = CVector::zero;

	if (mIsGrounded)
	{
		mStateStep = 0;

		// J�L�[�ōU����Ԃֈڍs
		if (CInput::PushKey(VK_LBUTTON))
		{
			mMoveSpeed = CVector::zero;
			ChangeState(EState::eAttack);
		}
		// K�L�[�ŋ��U��
		else if (CInput::PushKey(VK_RBUTTON))
		{
			mMoveSpeed = CVector::zero;
			ChangeState(EState::eAttackStrong);
		}
		// SPACE�L�[�ŃW�����v�J�n�ֈڍs
		// ���������Ƒ�W�����v
		// �Z�������Ə��W�����v
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
	}
	// �v���C���[���ڒn���Ă��Ȃ�
	else
	{
		// �󒆂ɔ�яo�����Ƃ��ɑҋ@���[�V�����֐؂�ւ���̂�
		// ���t���[���҂�
		if (mStateStep <= 5)
		{
			mStateStep++;
		}
		else
		{
			// �ҋ@�A�j���[�V�����ɐ؂�ւ�
			ChangeAnimation(EAnimType::eIdle);
		}
	}
}

// �ړ����
void CPlayer::UpdateMove()
{
	mDamageEnemy = false;
	mMoveSpeed = CVector::zero;

	// �v���C���[�̈ړ��x�N�g�������߂�
	CVector move = CalcMoveVec();
	// ���߂��ړ��x�N�g���̒����œ��͂���Ă��邩����
	if (move.LengthSqr() > 0.0f)
	{
		float speed = MOVE_SPEED;
		// �ҋ@��Ԃł���΁A���s���[�V�����ɐ؂�ւ�
		if (mState == EState::eIdle)
		{
			if (CInput::Key(VK_SHIFT) && mIsGrounded)
			{
				// �X�^�~�i��0�ȏォ�A�X�^�~�i�̉����l�t���O��false��������
				if (mCharaStatus.stamina >= 0 && !mStaminaLowerLimit)
				{
					// �_�b�V���J�n
					ChangeAnimation(EAnimType::eDash);
					// �X�^�[�g�_�b�V��
					if (mStartDashTime <= 0.5f)
					{
						speed = DASH_SPEED;
						mDash = true;
						mCharaStatus.stamina -= 1;
						if (mCharaStatus.stamina <= 0)
						{
							ChangeState(EState::eDashEnd);
							mStartDashTime = 0.0f;
							mStaminaLowerLimit = true;
							mDash = false;
						}
						mStartDashTime += Time::DeltaTime();
					}
					// �_�b�V��
					else
					{
						speed = RUN_SPEED;
						mDash = true;
						mCharaStatus.stamina -= 1;
						if (mCharaStatus.stamina <= 0)
						{
							ChangeState(EState::eDashEnd);
							mStaminaLowerLimit = true;
							mDash = false;
						}

						// �_�b�V���A�^�b�N�ڍs
						if (((CInput::PushKey(VK_MBUTTON))) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
						{
							// �_�b�V���A�^�b�N�ڍs���ɁA
							// �X�^�~�i��0�ȉ��ɂȂ邩�ǂ������m�F
							if (mCharaStatus.stamina - 20 >= 0) {
								mMoveSpeed = CVector::zero;
								ChangeState(EState::eAttackDash);
								// �X�^�~�i��0�ȉ��ɂȂ�Ȃ��ꍇ�̓_�b�V���A�^�b�N�����s
								mCharaStatus.stamina -= 20;
							}
							else
							{
							}
						}
					}
				}
				// �X�^�~�i��0�ȉ����A�X�^�~�i�̉����l�t���O��true��������
				else
				{
					// ����
					mStartDashTime = 0.0f;
					mDash = false;
					ChangeAnimation(EAnimType::eWalk);
					if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
					{
						mCharaStatus.stamina += 1;
						if (mCharaStatus.stamina >= mCharaMaxStatus.stamina)
						{
							mStaminaLowerLimit = false;
						}
					}
				}
			}
			else
			{
				mStartDashTime = 0.0f;
				mDash = false;
				ChangeAnimation(EAnimType::eWalk);
				if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
				{
					mCharaStatus.stamina += 1;
				}
			}

			if (mStaminaLowerLimit)
			{
				if (mCharaStatus.stamina >= mCharaMaxStatus.stamina)
				{
					mStaminaLowerLimit = false;
				}
			}

			// CTRL�L�[�ŉ���ֈڍs
			if (((CInput::PushKey(VK_CONTROL))) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
			{
				// ����s���O�ɃX�^�~�i��0�ȉ��ɂȂ邩�ǂ������m�F
				if (mCharaStatus.stamina - 50 >= 0) {
					mMoveSpeed = CVector::zero;
					ChangeState(EState::eRotate);
					// �X�^�~�i��0�ȉ��ɂȂ�Ȃ��ꍇ�͉���s�������s
					mCharaStatus.stamina -= 50;
				}
				else
				{
				}
			}
		}
		mMoveSpeed += move * speed * mCharaStatus.moveSpeed;
	}
	// �ړ��L�[����͂��Ă��Ȃ�
	else
	{
		if (mState == EState::eIdle)
		{
			// �ҋ@�A�j���[�V�����ɐ؂�ւ�
			ChangeAnimation(EAnimType::eIdle);
			mStartDashTime = 0.0f;
			mDash = false;
			if (mCharaStatus.stamina < mCharaMaxStatus.stamina && !mDash)
			{
				mCharaStatus.stamina += 1;
			}
		}
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

	mMoveSpeed = CVector::zero;
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
	mIsAttack = true;
	mWeaponTime = 0.0f;
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHandMiddle1"));

	// �U���A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttack);
	if (GetAnimationFrame() >= 10.0f)
	{
		// ���ɍU���J�n��`����
		mpSword->AttackStart();
		ChangeState(EState::eAttackWait);
	}

	// �a��SE�̍Đ��ς݃t���O��������
	mIsPlayedSlashSE = false;
}

// ���U��
void CPlayer::UpdateAttackStrong()
{
	mIsAttack = false;
	mWeaponTime = 0.0f;
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
	mWeaponTime = 0.0f;
	// ���U���A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttackStrong);
	// �U���I���҂���Ԃֈڍs
	ChangeState(EState::eAttackStrongWait);
}

// �_�b�V���A�^�b�N
void CPlayer::UpdateDashAttack()
{
	// �_�b�V���A�^�b�N�A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttackDash);
	mMoveSpeed = CVector::zero;
	mIsAttack = true;
	mWeaponTime = 0.0f;
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHandMiddle1"));

	if (GetAnimationFrame() >= 20.0f)
	{
		// ���ɍU���J�n��`����
		mpSword->AttackStart();
	}

	if (GetAnimationFrame() <= 69.0f)
	{
		// �ړ�����
		CVector move = CalcMoveVec();

		// ���̓x�N�g���̒����œ��͂���Ă��邩����
		if (move.LengthSqr() > 0.0f)
		{
			mMoveSpeed += move;
		}
		mMoveSpeed = move * MOVE_SPEED;
	}
	else
	{
		// �_�b�V���A�^�b�N�I���҂���Ԃֈڍs
		ChangeState(EState::eAttackDashWait);
	}
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

		// SE
		if (!mIsPlayedSlashSE && GetAnimationFrame() >= 10.0f)
		{
			// �a��SE���Đ�
			mpSlashSE->Play(1.0f, false, 0.0f);
			mIsPlayedSlashSE = true;
		}

		// �a���G�t�F�N�g�𐶐����Ă��Ȃ����A�A�j���[�V������35%�ȏ�i�s������A
		if (!mIsSpawnedSlashEffect && GetAnimationFrameRatio() >= 0.15f)
		{
			// �a���G�t�F�N�g�𐶐����āA���ʕ����֔�΂�
			CSlash* slash = new CSlash
			(
				this,
				Position() + CVector(0.0f, 10.0f, 0.0f),
				VectorZ(),
				300.0f,
				100.0f
			);
			// �a���G�t�F�N�g�̐F�ݒ�
			slash->SetColor(CColor(0.15f, 0.5f, 0.5f));

			mIsSpawnedSlashEffect = true;
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
		mIsSpawnedSlashEffect = false;
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

// �_�b�V���A�^�b�N�I���҂�
void CPlayer::UpdateDashAttackWait()
{
	// ���ɍU���I����`����
	mpSword->AttackEnd();
	mMoveSpeed = CVector::zero;
	// ���ɍU���I����`����
	mpSword->AttackEnd();
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
	mIsAttack = false;
	mWeaponTime = 0.0f;
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
	mMoveSpeed = CVector::zero;

	// �ړ�����
	CVector move = CalcMoveVec();

	// ���̓x�N�g���̒����œ��͂���Ă��邩����
	if (move.LengthSqr() > 0.0f)
	{
		mMoveSpeed += move;
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
	mMoveSpeed = CVector::zero;
	mElapsedTime = 0.0f;

	mpColliderSphere->SetEnable(false);
	mpSword->AttackEnd();
	ChangeState(EState::eClearEnd);
}

// �N���A�I��
void CPlayer::UpdateClearEnd()
{
	ChangeAnimation(EAnimType::eGuts);

	if (mpCutInClear->IsPlaying())
	{
		// �L�����N�^�[�̍X�V
		if (IsAnimationFinished())
		{
			if (mElapsedTime < 2.0f)
			{
				mElapsedTime += Time::DeltaTime();
			}
			else
			{
				mElapsedTime = 0.0f;
				mpCutInClear->End();
				if (CGameManager::StageNo() == 0)
				{
					mSavePoint = false;
					// �X�e�[�W���N���A
					CGameManager::StageClear();
					// �X�e�[�W���N���A������A���̃X�e�[�W�J�n�܂ŏ������̏�ԂɕύX
					ChangeState(EState::eReady);
					Position(mStartPos);
					mpColliderSphere->SetEnable(true);
				}

				// �u�����V���b�g�E�t���A�v
				if (CGameManager::StageNo() == 3)
				{
					mSavePoint = false;
					mStage3Clear = true;
					// �X�e�[�W���N���A
					CGameManager::StageClear();
					// �X�e�[�W���N���A������A���̃X�e�[�W�J�n�܂ŏ������̏�ԂɕύX
					ChangeState(EState::eReady);
					Position(mStartPos);
					mpColliderSphere->SetEnable(true);
				}
			}
		}
		//CXCharacter::Update();
		return;
	}
	else
	{
		mpCutInClear->Setup(this);
		mpCutInClear->Start();
	}
}

// ���S
void CPlayer::UpdateDeath()
{
	if (IsAnimationFinished())
	{
		mpDamageCol->SetEnable(false);
		mpSword->AttackEnd();
		mMoveSpeed = CVector::zero;
		if (mpCutInDeath->IsPlaying())
		{
			// �L�����N�^�[�̍X�V
			CXCharacter::Update();
			return;
		}
		else
		{
			mpCutInDeath->Setup(this);
			mpCutInDeath->Start();
		}
		ChangeAnimation(EAnimType::eDeath);
		ChangeState(EState::eDeathEnd);
	}
}

// ���S�����I��
void CPlayer::UpdateDeathEnd()
{
	if (IsAnimationFinished())
	{
		mpCutInDeath->End();
		mSavePoint = false;
		mDamageObject = false;
		mCharaStatus = mCharaMaxStatus;
		mpHpGauge->SetMaxValue(mCharaMaxStatus.hp);
		CGameManager::StageOver();
		Position(-245.0f, 60.0f, 0.0f);
		ChangeState(EState::eIdle);
	}
}

// �ċN
void CPlayer::UpdateReStart()
{
	if (IsAnimationFinished())
	{
		mDamageObject = false;
		Position(-195.0f, 200.0f, 9.0f);
		ChangeState(EState::eIdle);
	}
}

// �G�̍U�����󂯂���
void CPlayer::UpdateHit()
{
	mMoveSpeed = CVector::zero;
	if (!mDamageEnemy)
	{
		TakeDamage(3);
		mDamageEnemy = true;
	}

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		// �_�ł̑��x�𒲐����邽�߂̒萔
		const float blinkSpeed = 16.5f;

		// �o�ߎ��Ԃ��X�V
		mElapsedTime += Time::DeltaTime();

		// sin�֐����g���ē_�ł���F�̃A���t�@�l���v�Z
		// 0.0�`1.0�̊Ԃ���������
		float alpha = 0.5f + 0.5f * sin(mElapsedTime * blinkSpeed);

		// �F���Z�b�g (���F��alpha�l���w��)
		SetColor(CColor(1.0f, 1.0f, 1.0f, alpha));

		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	ChangeAnimation(EAnimType::eHitJ);
	if (IsAnimationFinished())
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			mDamageEnemy = false;
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
	mMoveSpeed = CVector::zero;
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

	mElapsedTime += Time::DeltaTime();
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));

	if (!mDamageEnemy)
	{
		TakeDamage(1);
		mDamageEnemy = true;
		mpDamageCol->SetEnable(true);
	}

	if (mElapsedTime >= COLORSET)
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			mDamageEnemy = true;
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

// �G�̌��̍U�����󂯂���
void CPlayer::UpdateHitSword()
{
	mMoveSpeed = CVector::zero;
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

	mElapsedTime += Time::DeltaTime();
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));

	if (!mDamageEnemy)
	{
		mDamageEnemy = true;
		mpDamageCol->SetEnable(false);
	}

	if (mElapsedTime >= COLORSET)
	{
		if (IsAnimationFinished())
		{
			if (mCharaStatus.hp > 0)
			{
				mIsPlayedHitDamageSE = false;
				mDamageEnemy = true;
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
	}

	//CDebugPrint::Print("Time%f\n", mElapsedTime);
}

// �_���[�W���󂯂�(�I�u�W�F�N�g)
void CPlayer::UpdateHitObj()
{
	mMoveSpeed = CVector::zero;
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

	mElapsedTime += Time::DeltaTime();
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));

	if (!mDamageEnemy)
	{
		mDamageEnemy = true;
		mpDamageCol->SetEnable(true);
	}

	if (mElapsedTime >= COLORSET)
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			mDamageEnemy = true;
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
}

// �����_���[�W
void CPlayer::UpdateFallDamage()
{
	mMoveSpeed = CVector::zero;
	ChangeAnimation(EAnimType::eFallingFlat);

	if (!mFallDamage)
	{
		mFallDamage = true;
		TakeDamage(1);
		mpDamageCol->SetEnable(false);
	}

	if (mElapsedTime >= COLORSET)
	{
		if (IsAnimationFinished())
		{
			if (mCharaStatus.hp > 0)
			{
				mIsPlayedHitDamageSE = false;
				mFallDamage = false;
				mElapsedTime = 0.0f;
				mElapsedTimeCol = 0.0f;
				mpDamageCol->SetEnable(false);
				ChangeAnimation(EAnimType::eStandUp);
				ChangeState(EState::eStandUp);
			}
			else if (mCharaStatus.hp <= 0)
			{
				mElapsedTime = 0.0f;
				mElapsedTimeCol = 0.0f;
				mpDamageCol->SetEnable(false);
				ChangeState(EState::eDeath);
			}
		}
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

	mElapsedTime += Time::DeltaTime();
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		// �_�ł̑��x�𒲐����邽�߂̒萔
		const float blinkSpeed = 16.5f;

		// �o�ߎ��Ԃ��X�V
		mElapsedTime += Time::DeltaTime();

		// sin�֐����g���ē_�ł���F�̃A���t�@�l���v�Z
		// 0.0�`1.0�̊Ԃ���������
		float alpha = 0.5f + 0.5f * sin(mElapsedTime * blinkSpeed);

		// �F���Z�b�g (���F��alpha�l���w��)
		SetColor(CColor(1.0f, 1.0f, 1.0f, alpha));

		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}
}

// �o����
void CPlayer::UpdateClimb()
{
	mClimb = true;
	mIsAttack = false;
	mWeaponTime = 0.0f;
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;
	// �v���C���[�̈ړ��x�N�g�������߂�
	CVector move = ClimbMoveVec();

	ChangeAnimation(EAnimType::eClimb);

	// ���߂��ړ��x�N�g���̒����œ��͂���Ă��邩����
	if (move.LengthSqr() > 0.0f)
	{
		// �㉺�L�[�����͂���Ă���ꍇ
		if (move.Y() != 0.0f)
		{
			// �ǂ�o���Ă��鎞�́A�A�j���[�V������ʏ�Đ����A
			// �ǂ��~��Ă���Ƃ��̓A�j���[�V�������t�Đ�����
			SetAnimationSpeed(move.Y() > 0.0f ? 1.0f : -1.0f);
		}
		// ���E�L�[�݂̂����͂���Ă���ꍇ
		else
		{
			SetAnimationSpeed(1.0f);
		}
	}
	// �ړ��L�[�����͂���Ă��Ȃ��ꍇ
	else
	{
		// �A�j���[�V�������~����
		SetAnimationSpeed(0.0f);
	}
	mMoveSpeed = move * CLIMB_SPEED;

	if (CInput::PushKey('E'))
	{
		mClimb = false;
		ChangeState(EState::eJumpStart);
	}

	// �o���ǂ͈̔͊O�ɏo���ꍇ
	if (!mClimbWall)
	{
		// �o���ǂ̒���ɐG��Ă����ꍇ
		if (mClimbWallTop)
		{
			// ����֏���Ԃֈڍs
			ChangeState(EState::eClimbedTop);
		}
		// �o���ǂ̒���ɐG��Ă��Ȃ������ꍇ
		else
		{
			// �o���Ă����Ԃ��������āA�ҋ@��Ԃֈڍs
			mClimb = false;
			ChangeState(EState::eIdle);
		}
	}
	//CDebugPrint::Print("mClimbWall: %s\n", mClimbWall ? "true" : "false");
	//CDebugPrint::Print("mClimbWallTop: %s\n", mClimbWallTop ? "true" : "false");
}

// ����܂œo����
void CPlayer::UpdateClimbedTop()
{
	mClimb = true;
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;

	// �X�e�b�v�Ǘ�
	switch (mStateStep)
	{
		// �X�e�b�v0: ����������
	case 0:
	{
		// ����֏��؂������̈ړ��O�̍��W�ƈړ���̍��W��ݒ�
		mClimbedStartPos = Position();
		CVector  moveUp, moveForward;
		mpClimbWall->GetClimbedMoveVec(&moveUp, &moveForward);
		mClimbedMovedUpPos = mClimbedStartPos + Rotation() * moveUp;
		mClimbedMovedPos = mClimbedMovedUpPos + Rotation() * moveForward;

		mElapsedTime = 0.0f;
		// ����֏��؂������̃A�j���[�V�������Đ�
		ChangeAnimation(EAnimType::eClimbedTop);

		// ���̃X�e�b�v��
		mStateStep++;
		break;
	}
	// �X�e�b�v1: �o��؂������̃A�j���[�V�����̌o�ߑ҂�
	case 1:
	{
		float ratio = GetAnimationFrameRatio();
		// �o��؂������̃A�j���[�V�����̔����܂ł�
		// �v���C���[��������Ɉړ�����
		if (ratio < 0.5f)
		{
			float per = ratio / 0.5f;
			CVector pos = CVector::Lerp(mClimbedStartPos, mClimbedMovedUpPos, per);
			Position(pos);
		}
		// �o��؂������̃A�j���[�V�����̔����𒴂�����A���̃X�e�b�v��
		else
		{
			Position(mClimbedMovedUpPos);
			mStateStep++;
		}
		break;
	}
		// �X�e�b�v2: ����֏��؂�����̈ړ�����
	case 2:
		// �o�ߎ��Ԃɍ��킹�Ĉړ�
		if (mElapsedTime < CLIMBED_TOP_TIME)
		{
			float per = mElapsedTime / CLIMBED_TOP_TIME;
			CVector pos = CVector::Lerp(mClimbedMovedUpPos, mClimbedMovedPos, per);
			Position(pos);
			mElapsedTime += Time::DeltaTime();
		}
		// �ړ����I�����
		else
		{
			Position(mClimbedMovedPos);
			// �ǂ�o���Ă����Ԃ�����
			mClimb = false;
			ChangeState(EState::eIdle);
		}
		break;
	}
}

// ���Ԃɓo����
void CPlayer::UpdateWireClimb()
{
	mClimb = true;
	mIsAttack = false;
	mWeaponTime = 0.0f;
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;
	// �v���C���[�̈ړ��x�N�g�������߂�
	CVector move = ClimbMoveVec();

	ChangeAnimation(EAnimType::eClimb);

	// ���߂��ړ��x�N�g���̒����œ��͂���Ă��邩����
	if (move.LengthSqr() > 0.0f)
	{
		// �㉺�L�[�����͂���Ă���ꍇ
		if (move.Y() != 0.0f)
		{
			// �ǂ�o���Ă��鎞�́A�A�j���[�V������ʏ�Đ����A
			// �ǂ��~��Ă���Ƃ��̓A�j���[�V�������t�Đ�����
			SetAnimationSpeed(move.Y() > 0.0f ? 1.0f : -1.0f);
		}
		// ���E�L�[�݂̂����͂���Ă���ꍇ
		else
		{
			SetAnimationSpeed(1.0f);
		}
	}
	// �ړ��L�[�����͂���Ă��Ȃ��ꍇ
	else
	{
		// �A�j���[�V�������~����
		SetAnimationSpeed(0.0f);
	}
	mMoveSpeed = move * CLIMB_SPEED;

	if (CInput::PushKey('E'))
	{
		mClimb = false;
		mpClimbCol->SetEnable(false);
		ChangeState(EState::eJumpStart);
		mMoveSpeed = CVector(-0.1f, 0.0f, 0.0f);
	}

	// �o���ǂ͈̔͊O�ɏo���ꍇ
	if (!mClimbWall)
	{
		// �o���ǂ̒���ɐG��Ă����ꍇ
		if (mClimbWallTop)
		{
			// ����֏���Ԃֈڍs
			ChangeState(EState::eWireClimbedTop);
		}
		// �o���ǂ̒���ɐG��Ă��Ȃ������ꍇ
		else
		{
			// �o���Ă����Ԃ��������āA�ҋ@��Ԃֈڍs
			mClimb = false;
			ChangeState(EState::eIdle);
		}
	}

	if (mClimbStaminaTime >= 0.2f)
	{
		mCharaStatus.stamina -= 2;
		mClimbStaminaTime = 0.0f;
	}
	else
	{
		mClimbStaminaTime += Time::DeltaTime();
	}

	if (mCharaStatus.stamina <= 0)
	{
		mClimb = false;
		ChangeState(EState::eIdle);
	}
	//CDebugPrint::Print("stamina:%f\n", mClimbSt);

	//CDebugPrint::Print("mClimbWall: %s\n", mClimbWall ? "true" : "false");
	//CDebugPrint::Print("mClimbWallTop: %s\n", mClimbWallTop ? "true" : "false");
}

// ���Ԃ̒���ɓo�������
void CPlayer::UpdateWireClimbedTop()
{
	mClimb = true;
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;

	// �X�e�b�v�Ǘ�
	switch (mStateStep)
	{
		// �X�e�b�v0: ����������
	case 0:
	{
		// ����֏��؂������̈ړ��O�̍��W�ƈړ���̍��W��ݒ�
		mClimbedStartPos = Position();
		CVector  moveUp, moveForward;
		mpWireWall->GetClimbedMoveVec(&moveUp, &moveForward);
		mClimbedMovedUpPos = mClimbedStartPos + Rotation() * moveUp;
		mClimbedMovedPos = mClimbedMovedUpPos + Rotation() * moveForward;

		mElapsedTime = 0.0f;
		// ����֏��؂������̃A�j���[�V�������Đ�
		ChangeAnimation(EAnimType::eClimbedTop);

		// ���̃X�e�b�v��
		mStateStep++;
		break;
	}
	// �X�e�b�v1: �o��؂������̃A�j���[�V�����̌o�ߑ҂�
	case 1:
	{
		float ratio = GetAnimationFrameRatio();
		// �o��؂������̃A�j���[�V�����̔����܂ł�
		// �v���C���[��������Ɉړ�����
		if (ratio < 0.5f)
		{
			float per = ratio / 0.5f;
			CVector pos = CVector::Lerp(mClimbedStartPos, mClimbedMovedUpPos, per);
			Position(pos);
		}
		// �o��؂������̃A�j���[�V�����̔����𒴂�����A���̃X�e�b�v��
		else
		{
			Position(mClimbedMovedUpPos);
			mStateStep++;
		}
		break;
	}
	// �X�e�b�v2: ����֏��؂�����̈ړ�����
	case 2:
		// �o�ߎ��Ԃɍ��킹�Ĉړ�
		if (mElapsedTime < WIREMESH_TOP_TIEM)
		{
			float per = mElapsedTime / WIREMESH_TOP_TIEM;
			CVector pos = CVector::Lerp(mClimbedMovedUpPos, mClimbedMovedPos, per);
			Position(pos);
			mElapsedTime += Time::DeltaTime();
		}
		// �ړ����I�����
		else
		{
			Position(mClimbedMovedPos);
			// �ǂ�o���Ă����Ԃ�����
			mClimb = false;
			ChangeState(EState::eIdle);
		}
		break;
	}
}

// �������
void CPlayer::UpdateFalling()
{
	mMoveSpeedY = -2.5f;
	ChangeAnimation(EAnimType::eFalling);
	if (mIsGrounded)
	{
		if (mCharaStatus.hp > 0)
		{
			TakeDamage(1);
			ChangeAnimation(EAnimType::eStandUp);
			ChangeState(EState::eStandUp);
		}
		else if (mCharaStatus.hp <= 0)
		{
			ChangeAnimation(EAnimType::eDeath);
			ChangeState(EState::eDeath);
		}
	}
}

// �����オ��
void CPlayer::UpdateStandUp()
{
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
}

// �W�����v�J�n
void CPlayer::UpdateJumpStart()
{
	mIsJumping = true;
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

	mMoveSpeedY += JUMP_SPEED;
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

	if (!CInput::Key(VK_SPACE))
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mMoveSpeedY -= GRAVITY;
	}

	if (mMoveSpeedY <= 0.0f)
	{
		mIsJumping = false;
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpEnd);
	}
}

// �W�����v�I��
void CPlayer::UpdateJumpEnd()
{
	mMoveSpeed = CVector::zero;
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (IsAnimationFinished() && mIsGrounded)
	{
		ChangeState(EState::eIdle);
	}

	mpClimbCol->SetEnable(true);
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
	mMoveSpeedY = JUMP_BOUNCE;
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

	if (mMoveSpeedY <= 0.0f)
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

bool CPlayer::IsFoundVanguard()
{
	CVector vanguardPos = CVanguard::Instance()->Position();
	CVector playerPos = Position();

	CVector toVanguard = (vanguardPos - playerPos).Normalized();
	CVector forward = Matrix().VectorZ().Normalized();

	float dot = forward.Dot(toVanguard);

	// ����p�̔������v�Z����
	float halfFOV = FOV_ANGLE * 0.5f;


	// ����p�̔�����菬���������@���K�[�h�Ƃ̋��������͈͈ȓ��ł���΁A�v���C���[��F������
	if (dot >= cosf(halfFOV * M_PI / 180.0f))
	{
		float distance = (vanguardPos - playerPos).Length();
		const float chaseRange = 100.0f;

		if (distance <= chaseRange)
			return true;
	}

	return false;
}

// �X�V
void CPlayer::Update()
{
	CDebugPrint::Print("mSpeedY:%f\n", mMoveSpeedY);
	SetParent(mpRideObject);
	SetColor(CColor(1.0, 1.0, 1.0, 1.0));
	mpRideObject = nullptr;
	mHpHit = false;

	if (mMoveSpeedY <= -3.0f)
	{
		ChangeState(EState::eFalling);
	}

	if (!(mState == EState::eAttack || mState == EState::eAttackStrong ||
		mState == EState::eAttackWait || mState == EState::eAttackStrongWait))
	{
		if (mIsAttack)
		{
			mWeaponTime += Time::DeltaTime();
			if (mWeaponTime >= 6.0f)
			{
				mIsAttack = false;
				mWeaponTime = 0.0f;
				mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
			}
		}
	}
	/*CDebugPrint::Print("mWeaponTime:%f\n", mWeaponTime);
	CDebugPrint::Print("mIsAttack: %s\n", mIsAttack ? "true" : "false");*/

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
		// �_�b�V���A�^�b�N
	case EState::eAttackDash:
		UpdateDashAttack();
		break;
		// �U���I���҂�
	case EState::eAttackWait:
		UpdateAttackWait();
		break;
		// ���U���I���҂�
	case EState::eAttackStrongWait:
		UpdateAttackStrongWait();
		break;
		// �_�b�V���A�^�b�N�I���҂�
	case EState::eAttackDashWait:
		UpdateDashAttackWait();
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
		// �G�̌�Hit
	case EState::eHitSword:
		UpdateHitSword();
		break;
		// �_���[�W���󂯂�(�I�u�W�F�N�g)
	case EState::eHitObj:
		UpdateHitObj();
		break;
		// �����_���[�W
	case EState::eFallDamege:
		UpdateFallDamage();
		break;
		// �o����
	case EState::eClimb:
		UpdateClimb();
		break;
		// ����܂œo����
	case EState::eClimbedTop:
		UpdateClimbedTop();
		break;
		// ���Ԃɓo����
	case EState::eWireClimb:
		UpdateWireClimb();
		break;
		// ���Ԃ̒���܂œo����
	case EState::eWireClimbedTop:
		UpdateWireClimbedTop();
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
		// �������
	case EState::eFalling:
		UpdateFalling();
		break;
		// �����オ��
	case EState::eStandUp:
		UpdateStandUp();
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

	// �ҋ@���ƃW�����v���́A�ړ��������s��
	if ((mState == EState::eIdle && mIsGrounded)
		|| mState == EState::eJumpStart
		|| mState == EState::eJump
		|| mState == EState::eJumpEnd
		|| mState == EState::eJumpingStart
		|| mState == EState::eJumping
		|| mState == EState::eJumpingEnd
		|| mState == EState::eFalling)
	{
		UpdateMove();
	}

	//// �uE�v�L�[�ŉ��̔��˂��I���I�t����
	//if (CInput::PushKey('F'))
	//{
	//	if (!mpFlamethrower->IsThrowing())
	//	{
	//		mpFlamethrower->Start();
	//	}
	//	else
	//	{
	//		mpFlamethrower->Stop();
	//	}
	//}


	// �������łȂ���΁A�ړ������Ȃǂ��s��
	if (mState != EState::eReady)
	{
		if (!mClimb)
		{
			mMoveSpeedY -= GRAVITY;
		}
		CVector moveSpeed = mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f * Time::DeltaTime());

		// �ړ�
		Position(Position() + moveSpeed * 60.0f * Time::DeltaTime());

		// �v���C���[�̌����𒲐�
		CVector current = VectorZ();
		CVector target = moveSpeed;
		if (mState == EState::eClimb)
		{
			// �ǂ̖@���̔��Ε���������
			target = -mClimbNormal;
		}
		else if (mState == EState::eWireClimb)
		{
			// �ǂ̖@���̔��Ε���������
			target = -mClimbNormal;
		}
		// ����ȊO�̎��́A�v���C���[�̈ړ������֌�����
		else
		{
			target = moveSpeed;
			target.Y(0.0f);
			target.Normalize();
		}
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
		// ���̂��f�o�b�O�łȂ��Ă��̗͂��������邽�ߍ폜
		//LevelUp();
	}

	// ���݂�HP��ݒ�
	mpHpGauge->SetValue(mCharaStatus.hp);
	// ���݂̃X�^�~�i��ݒ�
	mpStaminaGauge->SetSutaminaValue(mCharaStatus.stamina);

	// �L�����N�^�[�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpColliderSphere->Update();
	mpSword->UpdateAttachMtx();

	mIsGrounded = false;
	mClimbWall = false;
	mClimbWallTop = false;

	//// �c�����̈ړ����x�Ď�
	//CDebugPrint::Print("mMoveSpeed%f\n", mMoveSpeed.Y());
	//// ���G���Ԃ̎��ԊĎ�
	//CDebugPrint::Print("mInvincible:%f\n", mInvincibleStartTime);
	//// ���݂̏c�����̃|�W�V�����Ď�
	//CDebugPrint::Print("Position.Y %f\n", Position().Y());
	//// �R���C�_�[�̕������ԊĎ�
	//CDebugPrint::Print("TimeCol%f\n", mElapsedTimeCol);
	//CDebugPrint::Print("mMoveSpeedY%f\n", mMoveSpeedY);
	//CDebugPrint::Print("State:%d\n", mState);
	CDebugPrint::Print("Position: %f %f %f\n", Position().X(), Position().Y(), Position().Z());
}

// �`��
void CPlayer::Render()
{
	// �L�����`��
	CXCharacter::Render();
}