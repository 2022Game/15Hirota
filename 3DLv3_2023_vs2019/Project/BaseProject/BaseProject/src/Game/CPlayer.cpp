//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CInput.h"
#include "CColliderCapsule.h"
#include "CCamera.h"
#include "CFade.h"
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
#include "CMetalLadder.h"
#include "CVanguard.h"
#include "CFlamethrower.h"
#include "CSlash.h"
#include "CSound.h"
#include "CImage.h"
#include "CStageManager.h"
#include "CCutInResult.h"
#include "CCutInClear.h"
#include "CCutInDeath.h"
#include "CCutInResult.h"
#include "CCutInDeathJump.h"
#include "CResultAnnouncement.h"
#include "CScreenItem.h"
#include "CSpikyBallUI.h"
#include "Easing.h"
#include "CStageMenu.h"
#include "CStage1Button.h"
#include "CStage3Button.h"
#include "CBiribiri.h"
#include "CSmoke.h"
#include "CHealingUpBuffs.h"
#include "CInvincibleBuffs.h"
#include "CAttackUpBuffs.h"
#include "CTrailEffect.h"
#include "CMeatUI.h"
#include "CInsideCircleEffect.h"
#include "COutsideCircleEffect.h"
#include "COperationUI.h"
#include "CBullet.h"
#include "CSpikyBall.h"

// �v���C���[�֘A
// ����
#define PLAYER_HEIGHT 16.0f
// �X�s�[�h
#define MOVE_SPEED 1.1f
// �_�b�V���W�����v�X�s�[�h
#define DASH_JUMP_SPEED 2.0f
// �ړ��X�s�[�h
#define RUN_SPEED 1.4f
// �_�b�V���X�s�[�h
#define DASH_SPEED 2.1f
// �W�����v
#define JUMP_SPEED 1.5f
// ��W�����v
#define JUMP_BOUNCE 2.0f
// ����W�����v
#define JUMP_HIGH_BOUNCE 2.5f
// �_�b�V���W�����v
#define JUMP_DASH 1.7f
// �N���A�W�����v
#define JUMP_CLEAR 2.0f;
// ���S�W�����v
#define JUMP_DEATH 2.0f
// �X�^�[�g�W�����v
#define JUMP_START_STAGE 2.0f
// �ړI�ʒu�܂ŃW�����v
#define JUMP_TARGET 15.0f
// �d��
#define GRAVITY 0.0625f
// �W�����v�I����
#define JUMP_END_Y 1.0f

// �w��ʒu�܂ł̈ړ�����
#define MOVE_TO_TIME 1.0f

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
#define DAMAGECOL 3.0f

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
	{ "Character\\Monster1\\anim\\Warrok_DashJumpStart_54.x",	false,	54.0f	},		// �_�b�V���W�����v�J�n
	{ "Character\\Monster1\\anim\\Warrok_DashJump_1.x",				true,	1.0f	},	// �_�b�V���W�����v
	{ "Character\\Monster1\\anim\\Warrok_DashJumpLoop_22.x",		true,	22.0f	},	// �_�b�V���W�����v���[�v
	{ "Character\\Monster1\\anim\\Warrok_DashJumpEnd_13.x",		false,	13.0f	},		// �_�b�V���W�����v�I��
	{ "Character\\Monster1\\anim\\Dash1_53.x",						true,	53.0f	},	// �_�b�V��
	{ "Character\\Monster1\\anim\\Warrok_RunStop.x",			false,	40.0f	},		// �_�b�V���I��
	{ "Character\\Monster1\\anim\\Rotate.x",					false,	50.0f	},		// ���
	{ "Character\\Monster1\\anim\\Guts pose_325.x",				false,	325.0f	},		// �K�b�c�|�[�Y
	{ "Character\\Monster1\\anim\\Hit_63.x",					false,	63.0f	},		// �G�̍U��Hit
	{ "Character\\Monster1\\anim\\Hit_107.x",					false,	107.0f	},		// �G�̎�U��Hit
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
	, mClimbTime(0.0f)
	, mScaleTime(0.0f)
	, mAttackTime(0.0f)
	, mWeaponTime(0.0f)
	, mMoveSpeedY(0.0f)
	, mElapsedTime(0.0f)
	, mSpikTime(0.0f)
	, mHealingTime(0.0f)
	, mReflectTime(0.0f)
	, mMoveDistance(0.0f)
	, mStartDashTime(0.0f)
	, mElapsedTimeEnd(0.0f)
	, mColElapsedTime(0.0f)
	, mInvincibleTime(0.0f)
	, mBlinkElapsedTime(0.0f)
	, mClimbStaminaTime(0.0f)
	, mStageElapsedTime(0.0f)
	, mResultElapsedTime(0.0f)
	, mInvincibleStartTime(10.0f)
	, mSpikRechargeTime(0.0f)
	, mLastPos(CVector::zero)
	, mStartPos(CVector::zero)
	, mMoveSpeed(CVector::zero)
	, mGroundNormal(CVector::up)
	, mClimbNormal(CVector::zero)
	, mReflectionNormal(CVector::zero)
	, mMoveStartPos(CVector::zero)
	, mMoveTargetPos(CVector::zero)
	, mClimbedStartPos(CVector::zero)
	, mClimbedMovedPos(CVector::zero)
	, mClimbedMovedUpPos(CVector::zero)
	, mAttackStrongPos(CVector::zero)
	, mDash(false)
	, mClimb(false)
	, mHpHit(false)
	, mDeath(false)
	, mDamaged(false)
	, mIsDeath(false)
	, mIsAttack(false)
	, mIsJumping(false)
	, mClimbWall(false)
	, mIsDashJump(false)
	, mInvincible(false)
	, mFallDamage(false)
	, mSavePoint1(false)
	, mSavePoint2(false)
	, mStage1Clear(false)
	, mStage2Clear(false)
	, mStage3Clear(false)
	, mStage4Clear(false)
	, mDamageEnemy(false)
	, mStartStage1(false)
	, mStartStage2(false)
	, mStartStage3(false)
	, mStartStage4(false)
	, mClimbWallTop(false)
	, mDamageObject(false)
	, mIsStageClear(false)
	, mIsAttackItem(false)
	, mIsHealingItem(false)
	, mIsStage1Clear(false)
	, mIsStage2Clear(false)
	, mIsStage3Clear(false)
	, mIsStage4Clear(false)
	, mIsStartStage2(false)
	, mIsStartStage3(false)
	, mIsStartStage4(false)
	, mStaminaDepleted(false)
	, mIsPlayedSlashSE(false)
	, mStaminaLowerLimit(false)
	, mIsPlayedHitDamageSE(false)
	, mIsSpawnedSlashEffect(false)
	, mSpikyBall(false)
	, mSpik1(false)
	, mSpik2(false)
	, mpRideObject(nullptr)
	, mpUnderFootObject(nullptr)
	, mpScreenItem(nullptr)
	, mpSpikyBallUI(nullptr)
	, mpMeat(nullptr)
	, mpSpiky1(nullptr)
	, mpSpiky2(nullptr)
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

	// T�L�[�̉摜�\��
	mpClimbUI = new COperationUI("EUI");
	mpClimbUI->SetSize(100.0f, 100.0f);
	mpClimbUI->SetShow(false);

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
	mpColliderCapsule = new CColliderCapsule
	(
		this, ELayer::ePlayer,
		CVector(0.0f, 8.0f, 2.0f),
		CVector(0.0f, PLAYER_HEIGHT, 2.0f),
		4.0f,
		true,
		1.0f
	);
	mpColliderCapsule->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField,
		ELayer::eRecoverCol,ELayer::eInvincbleCol, ELayer::eEnemy, ELayer::eClimb,
		ELayer::eMedalCol,ELayer::eSavePoint1, ELayer::eSavePoint2, ELayer::eAttackCol,
		ELayer::eGoalCol, ELayer::eJumpingCol,ELayer::eFlameWall,ELayer::eMedalCol,
		ELayer::eMeatCol,ELayer::eFall, ELayer::eMetalLadder, ELayer::eReflection,
		ELayer::eReflectionJump});
	mpColliderCapsule->SetCollisionTags({ ETag::eGoalObject,ETag::eMedal, ETag::eField,ETag::eAttackObject,
		ETag::eItemInvincible,ETag::eItemRecover,ETag::eSavePoint1, ETag::eSavePoint2, ETag::eObstacle,ETag::eJumpingObject,
		ETag::eNeedleObject, ETag::eMeat, ETag::eSeesaw, ETag::eFall,ETag::ePropeller, ETag::eReflection});
	//mpColliderCapsule->Position(0.0f, 5.0f, 1.0f);
	

	// �v���C���[�̃��O�ɕt���邩�ǂ����l����
	//const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	//mpColliderCapsule->SetAttachMtx(spineMtx);

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
		ELayer::eFlame, ELayer::eStageMenuObject, ELayer::eBiribiri,
		ELayer::eElectricCol});
	mpDamageCol->SetCollisionTags({ ETag::eEnemyWeapon, 
		ETag::eEnemy, ETag::eBullet,ETag::eRideableObject, ETag::eFlame,
		ETag::eStageMenuObject,ETag::eNeedleObject, ETag::eBiribiri,
		ETag::eEffect});
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
		ELayer::eWireClimb,ELayer::eWireClimbedTop,ELayer::eWireMoveClimb,
		ELayer::eWireMoveClimbedTop,ELayer::eMetalLadder, ELayer::eMetalLadderTop});


	// �}�W�b�N�\�[�h�쐬
	mpSword = new CMajicSword();
	//mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
	mpSword->SetOwner(this);
	//CStageManager::AddTask(mpSword);

	/*mpFlamethrower = new CFlamethrower
	(
		this, nullptr,
		CVector(0.0f, 14.0f, -1.0f),
		CQuaternion(0.0f, 90.0f, 0.0f).Matrix()
	);
	CStageManager::AddTask(mpFlamethrower);*/

	mpCutInDeath = new CCutInDeath();
	mpCutInClear = new CCutInClear();
	mpCutInResult = new CCutInResult();
	mpCutInDeathJump = new CCutInDeathJump();

	mpScreenItem = new CScreenItem();
	mpMeat = new CMeatUI();
	
	mpSpikyBallUI = new CSpikyBallUI();

	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
}

CPlayer::~CPlayer()
{
	//CStageManager::RemoveTask(mpSword);
	//CStageManager::RemoveTask(mpFlamethrower);
	//CStageManager::RemoveTask(mpSmoke);
	//CStageManager::RemoveTask(mpScreenItem);

	spInstance = nullptr;
	// �R���C�_�[�֘A�̔j��
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderCapsule);
	SAFE_DELETE(mpDamageCol);
	SAFE_DELETE(mpClimbCol);

	// �}�W�b�N�\�[�h��j��
	mpSword->Kill();
	mpClimbUI->Kill();

	mpCutInDeath->Kill();
	mpCutInClear->Kill();
	mpCutInResult->Kill();
	mpCutInDeathJump->Kill();
}

// �Փˏ���
void CPlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (mState == EState::eReady) return;

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
			else if (other->Tag() == ETag::eSeesaw)
			{
				mpUnderFootObject = other->Owner();
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
						mDeath = true;
						ChangeState(EState::eDeath);
					}
				}
				mpRideObject = other->Owner();
			}
		}
		// �v���C���[���G�ꂽ��W�����v����R���C�_�[
		else if (other->Layer() == ELayer::eJumpingCol)
		{
			if (mState == EState::eFalling)
			{
				ChangeState(EState::eJumpingStart);
			}
			//// ���]���������߂��x�N�g���Ə�����̃x�N�g���̓���(�p�x)�����߂�
			//float dot = CVector::Dot(-hit.adjust.Normalized(), CVector::up);
			//// ��ɏ�����Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
			//float cosAngle = cosf(Math::DegreeToRadian(10.0f));
			//// ���߂��p�x���w�肵���p�x�͈͓̔��ł���΁A
			//if (dot >= cosAngle)
			//{
			//	Position(Position() + hit.adjust);
			//}
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
	if (self == mpColliderCapsule)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
			else if (other->Tag() == ETag::eNeedleObject)
			{
				Position(Position() + hit.adjust);
			}
		}
		// ��������p�̃R���C�_�[�ɐG�ꂽ��
		else if (other->Layer() == ELayer::eFall)
		{
			// �X�e�[�W�ԍ�
			int currentStage = CGameManager::StageNo();

			// �X�e�[�W�ԍ���1��������
			if (currentStage == 1)
			{
				// 1�ʂ̃Z�[�u�|�C���g
				if (mSavePoint1 && mSavePoint2 ||
					!mSavePoint1 && mSavePoint2)
				{
					ChangeState(EState::eFallDamege);
					Position(26.0f, 10.0f, 673.0f);
				}
				else if (mSavePoint1)
				{
					ChangeState(EState::eFallDamege);
					Position(26.0f, 10.0f, 390.0f);
				}
				else
				{
					// �����l�_�ɖ߂�
					Position(26.0f, 6.5f, -28.0f);
					ChangeState(EState::eFallDamege);
				}
			}
			// �X�e�[�W�ԍ���2��������
			else if (currentStage == 2)
			{
				// �����l�_�ɖ߂�
				Position(0.0f, 20.0f, 50.0f);
				ChangeState(EState::eFallDamege);
				// 2�ʂ̃Z�[�u�|�C���g
				if (mSavePoint1 && mSavePoint2 ||
					!mSavePoint1 && mSavePoint2)
				{
					ChangeState(EState::eFallDamege);
					Position(0.0f, 56.0f, 994.0f);
				}
				else if (mSavePoint1)
				{
					ChangeState(EState::eFallDamege);
					Position(0.0f, 20.0f, 480.0f);
				}
			}
			// �X�e�[�W�ԍ���3��������
			else if (currentStage == 3)
			{
				// 3�ʂ̃Z�[�u�|�C���g1��2�̃`�F�b�N
				if (mSavePoint1 && mSavePoint2 ||
					!mSavePoint1 && mSavePoint2)
				{
					// SavePoint2��true�Ȃ�Z�[�u�|�C���g2�̃|�W�V������K�p
					ChangeState(EState::eFallDamege);
					Position(0.0f, 10.0f, 1550.0f);
				}
				else if (mSavePoint1)
				{
					// �Z�[�u�|�C���g1������true�Ȃ�Z�[�u�|�C���g1�̃|�W�V������K�p
					ChangeState(EState::eFallDamege);
					Position(0.0f, 10.0f, 453.0f);
				}
				else
				{
					// �����l�_�ɖ߂�
					Position(0.0f, 10.0f, 0.0f);
					ChangeState(EState::eFallDamege);
				}
			}
			// �X�e�[�W�ԍ���4��������
			else if (currentStage == 4)
			{
				// 4�ʂ̃Z�[�u�|�C���g1��2�̃`�F�b�N
				if (mSavePoint1 && mSavePoint2 ||
					!mSavePoint1 && mSavePoint2)
				{
					// SavePoint2��true�Ȃ�Z�[�u�|�C���g2�̃|�W�V������K�p
					Position(0.0f, 440.0f, -1890.0f);
				}
				else if (mSavePoint1)
				{
					// �Z�[�u�|�C���g1������true�Ȃ�Z�[�u�|�C���g1�̃|�W�V������K�p
					Position(328.0f, -190.0f, -546.0f);
				}
				else
				{
					// �����l�_�ɖ߂�
					Position(328.0f, -277.0f, -958.0f);
					ChangeState(EState::eFallDamege);
				}
			}
		}
		else if (other->Layer() == ELayer::eReflection)
		{
			mReflectTime = 0.0f;
			ChangeState(EState::eReflection);
			// ���˂���I�u�W�F�N�g�̖@�����擾
			mReflectionNormal = hit.adjust.Normalized();
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eReflectionJump)
		{
			ChangeState(EState::eJumpingStart);
			Position(Position() + hit.adjust);
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
		// ��
		else if (other->Layer() == ELayer::eMeatCol)
		{

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
		else if (other->Layer() == ELayer::eMetalLadder)
		{
		Position(Position() + hit.adjust);
 }
		// �Z�[�u�|�C���g1
		else if (other->Layer() == ELayer::eSavePoint1)
		{
			if (other->Tag() == ETag::eSavePoint1)
			{
				mSavePoint1 = true;
			}
		}
		// �Z�[�u�|�C���g2
		else if (other->Layer() == ELayer::eSavePoint2)
		{
			if (other->Tag() == ETag::eSavePoint2)
			{
				mSavePoint2 = true;
			}
		}
		// �S�[���|�X�g
		else if (other->Layer() == ELayer::eGoalCol)
		{
			mIsStageClear = true;
			mpColliderCapsule->SetEnable(false);
			if (CGameManager::StageNo() == 1 ||
				CGameManager::StageNo() == 2 ||
				CGameManager::StageNo() == 3)
			{
				if (mIsGrounded && !mIsJumping)
				{
					ChangeState(EState::eClear);
				}
				else
				{
					ChangeState(EState::eStop);
				}
			}
		}
		// ���˂�u���b�N
		else if (other->Layer() == ELayer::eJumpingCol)
		{
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFlameWall)
		{
			Position(Position() + hit.adjust);
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
		else if (other->Layer() == ELayer::eBiribiri)
		{
			ChangeState(EState::eHitBullet);
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
		}
		// ���ɓ���������
		else if (other->Layer() == ELayer::eFlame)
		{
			ChangeState(EState::eHit);
		}
		// �X�e�[�W�I���X�e�[�W�̃I�u�W�F�N�g�ɓ���������
		else if (other->Layer() == ELayer::eStageMenuObject)
		{
			
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

		// ������q�̃R���C�_�[
		if (other->Layer() == ELayer::eMetalLadder)
		{
			mClimbWall = true;
			if (mState == EState::eIdle && mIsGrounded)
			{
				if (CInput::PushKey('E'))
				{
					CVector mSpd = mMoveSpeed;
					mSpd = CVector(0.0f, 0.5f, 0.0f);
					Position(Position() + mSpd);

					// Climb��ԂɈڍs����
					ChangeState(EState::eMetalLadder);
					// ������o��ǂ��L�����Ă���
					mpMetalLadder = dynamic_cast<CMetalLadder*>(other->Owner());
				}
			}

			// ���ݕǂ�o���Ă���Œ��ł���΁A
			if (mState == EState::eMetalLadder)
			{
				// �o���Ă���ǂ̖@�����擾
				mClimbNormal = hit.adjust.Normalized();
			}
		}
		// �o���ǂ̒���R���C�_�[
		else if (other->Layer() == ELayer::eMetalLadderTop)
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

// �R���C�_�[�̎��Ԍv���p
void CPlayer::CColliderTime()
{
	if (mColElapsedTime <= DAMAGECOL)
	{
		mColElapsedTime += Time::DeltaTime();
		if (mColElapsedTime >= DAMAGECOL && !mInvincible)
		{
			mColElapsedTime = DAMAGECOL;
			mDamaged = false;
			mpDamageCol->SetEnable(true);
			return;
		}
	}
}

// �_�ł��鎞�Ԍv���p
void CPlayer::CDamageColorTime()
{
	if (mColElapsedTime <= DAMAGECOL && !mInvincible)
	{
		// �_�ł̑��x�𒲐����邽�߂̒萔
		const float blinkSpeed = 16.5f;

		// sin�֐����g���ē_�ł���F�̃A���t�@�l���v�Z
		// 0.0�`1.0�̊Ԃ���������
		float alpha = 0.5f + 0.5f * sin(mBlinkElapsedTime * blinkSpeed);

		// �F���Z�b�g (���F��alpha�l���w��)
		SetColor(CColor(1.0f, 1.0f, 1.0f, alpha));

		mColElapsedTime += Time::DeltaTime();
		mBlinkElapsedTime += Time::DeltaTime();
	}
	else
	{
		if (!mInvincible)
		{
			mBlinkElapsedTime = 0.0f;
			mColElapsedTime = 0.0f;
			mDamaged = false;
			mpDamageCol->SetEnable(true);
		}
	}
}

// // �A�j���[�V�����I���̗͔̑��菈��
void CPlayer::CHPJudgment()
{
	if (IsAnimationFinished())
	{
		if (mCharaStatus.hp > 0)
		{
			mDamageEnemy = false;
			mIsPlayedHitDamageSE = false;
			ChangeState(EState::eIdle);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mDeath = true;
			mFallDamage = false;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}
}

// �W�����v���ɑ̗͂�0�ȉ��ɂȂ����ꍇ�̏���
void CPlayer::JumpingHpJudgment()
{
	if (mCharaStatus.hp <= 0)
	{
		mDeath = true;
		ChangeState(EState::eDeath);
	}
}

// �X�e�[�W�N���A���̃A�C�e���폜����
void CPlayer::ItemDeletion()
{
	// ���G�A�C�e���폜
	RemoveItem(ItemType::INVINCIBLE);
	// �U���̓A�b�v�|�[�V�����폜
	RemoveItem(ItemType::ATTACK_UP);
	// �񕜃|�[�V�����폜
	RemoveItem(ItemType::HEALING);
	// �h��̓A�b�v�|�[�V�����폜
	RemoveItem(ItemType::DEFENSE);
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
		mDeath = true;
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

	mIsHealingItem = true;
	mHealingTime = 3.0f;

	// �o�t1�𐶐�
	float dist = 0.1f;
	CInsideCircleEffect* circle1 = new CInsideCircleEffect
	(
		0.0f, dist
	);
	// �o�t2�𐶐�
	COutsideCircleEffect* circle2 = new COutsideCircleEffect
	(
		0.0f, dist
	);

	// �_�ł̑��x�𒲐����邽�߂̒萔
	const float blinkSpeed = 1.0f;

	// sin�֐����g���ē_�ł���F���v�Z
	// 0.0�`1.0�̊Ԃ���������
	float green = 0.5f + 0.5f * sin(mHealingTime * blinkSpeed);
	// �o�t�̐F�ݒ�
	circle1->SetColor(CColor(0.0f, green, 0.0f, 1.0f));
	circle1->Scale(5.0f, 5.0f, 5.0f);
	circle1->SetOwner(this);

	circle2->SetColor(CColor(0.0f, green, 0.0f, 1.0f));
	circle2->Scale(5.0f, 5.0f, 5.0f);
	circle2->SetOwner(this);
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
	mIsAttackItem = true;
	mAttackTime = 3.0;
	mCharaStatus.power += attack;

	// �o�t1�𐶐�
	float dist = 0.1f;
	CInsideCircleEffect* circle1 = new CInsideCircleEffect
	(
		0.0f, dist
	);
	// �o�t2�𐶐�
	COutsideCircleEffect* circle2 = new COutsideCircleEffect
	(
		0.0f, dist
	);

	// �_�ł̑��x�𒲐����邽�߂̒萔
	const float blinkSpeed = 1.0f;

	// sin�֐����g���ē_�ł���F���v�Z
	// 0.0�`1.0�̊Ԃ���������
	float red = 0.5f + 0.5f * sin(mAttackTime * blinkSpeed);
	// �o�t�̐F�ݒ�
	circle1->SetColor(CColor(red, 0.0f, 0.0f, 1.0f));
	circle1->Scale(5.0f, 5.0f, 5.0f);
	circle1->SetOwner(this);

	circle2->SetColor(CColor(red, 0.0f, 0.0f, 1.0f));
	circle2->Scale(5.0f, 5.0f, 5.0f);
	circle2->SetOwner(this);
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

// ���S�������ǂ���
bool CPlayer::IsDeath()
{
	return mIsDeath;
}

// ���S�������ǂ���(mDeath)
bool CPlayer::IsMDeath()
{
	return mDeath;
}

// �X�e�[�W1���N���A������
bool CPlayer::IsStage1Clear()
{
	return mIsStage1Clear;
}

// �X�e�[�W2���N���A������
bool CPlayer::IsStage2Clear()
{
	return mIsStage2Clear;
}

// �X�e�[�W3���N���A������
bool CPlayer::IsStage3Clear()
{
	return mIsStage3Clear;
}

// �X�e�[�W4���N���A������
bool CPlayer::IsStage4Clear()
{
	return mIsStage4Clear;
}

// �X�e�[�W���N���A������
bool CPlayer::IsStageClear()
{
	return mIsStageClear;
}

// �X�e�[�W2�ɓ���邩�ǂ���
bool CPlayer::IsStartStage2()
{
	return mIsStartStage2;
}

// �X�e�[�W3�ɓ���邩�ǂ���
bool CPlayer::IsStartStage3()
{
	return mIsStartStage3;
}

// �X�e�[�W4�ɓ���邩�ǂ���
bool CPlayer::IsStartStage4()
{
	return mIsStartStage4;
}

// �U���̓A�b�v�A�C�e�����g�p������
bool CPlayer::IsAttackItem()
{
	return mIsAttackItem;
}

// �U���̓A�b�v�A�C�e�����g�p������
bool CPlayer::IsHealingItem()
{
	return mIsHealingItem;
}

bool CPlayer::IsSpikyBall()
{
	return mSpikyBall;
}

bool CPlayer::IsSpikyBallAppearance()
{
	return mSpik1;
}

float CPlayer::GetSpikyTime() const
{
	return mSpikRechargeTime;
}

#define MAXCHARGETIME 2.0f
#define SPIKYCHARGETIME 5.0f
#define SPIKYBALLVELOCITY_Y 1.4f
#define MAXVELOCITY_Y 3.0f
#define SPIKYSPEED 50.0f
#define SPIKYDISTANCE 50.0f
#define SPIKYMAXSPEED 100.0f
#define MAXDISTANCE 300.0f
#define REDUCEDISTANCE 100.0f

float CPlayer::GetSpikyBallSpeed() const
{
	return SPIKYSPEED + (Math::Clamp01(mSpikTime / MAXCHARGETIME) * SPIKYMAXSPEED);
}

float CPlayer::GetSpikyBallDistance() const
{
	return SPIKYDISTANCE + (Math::Clamp01(mSpikTime / MAXCHARGETIME) * (MAXDISTANCE - REDUCEDISTANCE));
}

float CPlayer::GetSpikyBallInitialVelocityY() const
{
	return SPIKYBALLVELOCITY_Y + (Math::Clamp01(mSpikTime / MAXCHARGETIME) * MAXVELOCITY_Y);
}

// �X�e�[�W�t���O��false�ɂ���֐�
void CPlayer::StageFlagfalse()
{
	mStage1Clear = false;
	mStage2Clear = false;
	mStage3Clear = false;
	mStage4Clear = false;

	mStartStage1 = false;
	mStartStage2 = false;
	mStartStage3 = false;
	mStartStage4 = false;
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

// �L�[�̓��͏�񂩂�ǈړ��x�N�g��(�㉺)�����߂�
CVector CPlayer::ClimbMoveUpVec() const
{
	CVector move = CVector::zero;

	// �L�[�̓��̓x�N�g�����擾
	CVector input = CVector::zero;
	if (CInput::Key('W'))		input.Y(-1.0f);
	else if (CInput::Key('S'))	input.Y(1.0f);

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

// �v���C���[���A�N�V�������N�����邩�ǂ���
bool CPlayer::IsEnableAction() const
{
	return CGameManager::StageNo() > 0;
}

// �������̏��
void CPlayer::UpdateReady()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ���
	switch (mStateStep)
	{
		// �X�e�b�v0 ����������
	case 0:
		//ChangeAnimation(EAnimType::eIdle);
		// �S�Ă̏Փ˔�����I�t�ɂ���
		SetEnableCol(false);
		// �v���C���[�̈ړ����x��0�ɂ���
		mMoveSpeed = CVector::zero;
		mMoveSpeedY = 0.0f;
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
			mStageElapsedTime = 0.0f;
			// �v���C���[�̏Փ˔�����I���ɂ���
			SetEnableCol(true);
			// ���݂̏�Ԃ�ҋ@�ɐ؂�ւ�
			mCharaStatus.hp = mCharaMaxStatus.hp;
			ChangeState(EState::eFirstAction);

			// �X�e�[�W���N���A������
			if (mStage1Clear || mStage2Clear || mStage3Clear || mStage4Clear)
			{
				// �N���A�W�����v�ɑJ��
				ChangeState(EState::eResultJumpStart);
			}

			// ����ł�����
			if (!mIsDeath && mDeath)
			{
				ChangeState(EState::eDeathJumpStart);
			}
		}
		break;
	}
}

// �ŏ��̃A�N�V����
void CPlayer::UpdateFirstAction()
{
	mMoveSpeed =  CVector::zero;
	ChangeAnimation(EAnimType::eDashJumpLoop);
	if (IsAnimationFinished() &&mIsGrounded)
	{
		ChangeAnimation(EAnimType::eIdle);
		ChangeState(EState::eIdle);
	}
}

// �ҋ@
void CPlayer::UpdateIdle()
{
	// �A�N�V�������N�����邩�ǂ���
	if (!IsEnableAction())
	{
		// �X�e�[�W�I����ʂł���΁A���U���g�֐؂�ւ�
		if (mStage1Clear && !mIsStage1Clear)
		{
			ChangeState(EState::eResult);
		}
		else if (mStage2Clear && !mIsStage2Clear)
		{
			ChangeState(EState::eResult);
		}
		else if (mStage3Clear && !mIsStage3Clear)
		{
			ChangeState(EState::eResult);
		}
		else if (mStage4Clear && !mIsStage4Clear)
		{
			ChangeState(EState::eResult);
		}

		if (!mIsDeath && mDeath)
		{
			ChangeState(EState::eRestart);
		}

		// �A�N�V�������N�����Ȃ��ꍇ�́A�ȍ~�̏��������s���Ȃ�
		return;
	}

	SetAlpha(1.0f);
	mpSword->SetAlpha(1.0f);
	mMoveSpeed = CVector::zero;
	// ���ɍU���I����`����
	mpSword->AttackEnd();

	if (mIsAttack)
	{
		mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHandMiddle1"));
	}

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
		// �}�E�X�E�N���b�N�ŋ��U��
		else if (CInput::PushKey(VK_RBUTTON) && mSpikRechargeTime <= 0.0f)
		{
			mMoveSpeed = CVector::zero;
			// �`���[�W���Ԃ����Z�b�g
			mSpikTime = 0.0f;
			ChangeState(EState::eAttackStrongStart);
		}
		// SPACE�L�[�ŃW�����v�J�n�ֈڍs
		else if (CInput::PushKey(VK_SPACE) && !mIsDashJump)
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
			//ChangeAnimation(EAnimType::eDashJumpLoop);
		}
	}
}

// ��~���
void CPlayer::UpdateStop()
{
	mMoveSpeed = CVector::zero;
	if (IsAnimationFinished() && mIsGrounded)
	{
		ChangeState(EState::eClear);
	}
}

// �ړ����
void CPlayer::UpdateMove()
{
	// �A�N�V�������N�����Ȃ��ꍇ�́A�ړ��ł��Ȃ�
	if (!IsEnableAction()) return;

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
						mIsDashJump = true;
						mDash = true;
						mCharaStatus.stamina -= 1;

						// �_�b�V���W�����v�ڍs
						if ((CInput::PushKey(VK_SPACE) && mIsDashJump) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
						{
							// �_�b�V���W�����v�ڍs����
							// �X�^�~�i��0�ȉ��ɂȂ邩�ǂ������m�F
							if (mCharaStatus.stamina - 40 >= 0)
							{
								mMoveSpeed = CVector::zero;
								ChangeState(EState::eDashJumpStart);
								// �X�^�~�i��0�ȉ��ɂȂ�Ȃ��ꍇ�̓_�b�V���W�����v�����s
								mCharaStatus.stamina -= 40;
							}
							else
							{

							}
						}

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
						mIsDashJump = false;
						mCharaStatus.stamina -= 1;
						if (mCharaStatus.stamina <= 0)
						{
							ChangeState(EState::eDashEnd);
							mStaminaLowerLimit = true;
							mDash = false;
						}
					}

					// �_�b�V���A�^�b�N�ڍs
					if (((CInput::PushKey(VK_MBUTTON))) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
					{
						// �_�b�V���A�^�b�N�ڍs���ɁA
						// �X�^�~�i��0�ȉ��ɂȂ邩�ǂ������m�F
						if (mCharaStatus.stamina - 20 >= 0)
						{
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
				// �X�^�~�i��0�ȉ����A�X�^�~�i�̉����l�t���O��true��������
				else
				{
					// ����
					mStartDashTime = 0.0f;
					mIsDashJump = false;
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
				mIsDashJump = false;
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
		if (mState == EState::eDashJump)
		{
			speed = DASH_JUMP_SPEED;
			//mMoveSpeed += move * speed * mCharaStatus.moveSpeed;
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
			mIsDashJump = false;
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

// ���U���J�n
void CPlayer::UpdateAttackStrongStart()
{
	mAttackStrongPos = Position();
	ChangeState(EState::eAttackStrong);
}

// ���U��
void CPlayer::UpdateAttackStrong()
{
	mSpikyBall = false;
	mIsAttack = false;
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
	mWeaponTime = 0.0f;

	// ���U���A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttackStrong);

	CVector forward = VectorZ();
	forward.Normalize();

	if (!mSpik1)
	{
		mSpik1 = true;
		mpSpiky1 = new CSpikyBall
		(
			Position(),
			forward,
			GetSpikyBallSpeed(),
			GetSpikyBallDistance(),
			SPIKYBALLVELOCITY_Y
		);
		mpSpiky1->AttachMtx(GetFrameMtx("Armature_mixamorig_LeftHandMiddle1"));
	}

	if (GetAnimationFrame() >= 50.0f)
	{
		SetAnimationSpeed(0.0f);
		if (CInput::Key(VK_RBUTTON))
		{
			mSpikTime += Time::DeltaTime();
			if (mSpikTime >= MAXCHARGETIME)
			{
				ChangeState(EState::eAttackStrongWait);
			}
		}
		else if (CInput::PullKey(VK_RBUTTON))
		{
			ChangeState(EState::eAttackStrongWait);
		}
	}
	else if (GetAnimationFrame() <= 50.0f && CInput::PullKey(VK_RBUTTON))
	{
		mpSpiky1->Kill();
		mSpik1 = false;
		ChangeState(EState::eIdle);
	}

	if (mpSpiky1 != nullptr)
	{
		mpSpiky1->UpdateAttachMtx();
	}
}

// ���U���I���҂�
void CPlayer::UpdateAttackStrongWait()
{
	SetAnimationSpeed(1.0f);

	CVector forward = VectorZ();
	forward.Normalize();

	if (GetAnimationFrame() >= 74.0f && mSpik1 && mpSpiky1 != nullptr)
	{
		mSpik1 = false;
		mpSpiky1->DetachMtx();
		mpSpiky1->Kill();
	}
	else if (GetAnimationFrame() >= 50.0f && GetAnimationFrame() <= 75.0f)
	{
		if (mpSpiky1 != nullptr && mSpik1)
		{
			mpSpiky1->UpdateAttachMtx();
		}
	}

	if (GetAnimationFrame() >= 75.0f && !mSpik2)
	{
		if (mpSpiky2 == nullptr)
		{
			mSpik2 = true;
			mpSpiky2 = new CSpikyBall
			(
				Position() + CVector(0.0f, 10.0f, 0.0f) + forward * 5.0f,
				forward,
				GetSpikyBallSpeed(),
				GetSpikyBallDistance(),
				SPIKYBALLVELOCITY_Y
			);
			mpSpiky2->SetAlpha(1.0f);
			mpSpiky2->AttachMtx(GetFrameMtx("Armature_mixamorig_LeftHandMiddle1"));
			mpSpiky2->AttackStart();
			mpSpiky2->DetachMtx();
			mpSpiky2->PlayerVectorZ(*spInstance);
		}
		mSpikyBall = true;

		if (mpSpiky2 != nullptr && mSpik2)
		{
			mpSpiky2->UpdateAttachMtx();
		}
	}

	if (IsAnimationFinished())
	{
		mSpikRechargeTime = SPIKYCHARGETIME;
		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
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
				mIsSpawnedSlashEffect = false;
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
			//// �a���G�t�F�N�g�𐶐����āA���ʕ����֔�΂�
			//CSlash* slash = new CSlash
			//(
			//	this,
			//	Position() + CVector(0.0f, 10.0f, 0.0f),
			//	VectorZ(),
			//	300.0f,
			//	100.0f
			//);
			//// �a���G�t�F�N�g�̐F�ݒ�
			//slash->SetColor(CColor(0.15f, 0.5f, 0.5f));

			// �a���G�t�F�N�g�𐶐����āA���ʕ����֔�΂�
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

// �_�b�V���A�^�b�N�I���҂�
void CPlayer::UpdateDashAttackWait()
{
	// ���ɍU���I����`����
	mpSword->AttackEnd();
	mMoveSpeed = CVector::zero;
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

		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �N���A
void CPlayer::UpdateClear()
{	
	mpHpGauge->SetShow(false);
	mpStaminaGauge->SetShow(false);
	mpScreenItem->SetShow(false);
	mpSpikyBallUI->SetShow(false);
	mpColliderCapsule->SetEnable(false);

	mpMeat->SetShow(false);
	mMoveSpeed = CVector::zero;
	mElapsedTime = 0.0f;
	mMoveDistance = 0.0f;

	ItemDeletion();

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
				// �X�e�[�W1�u�����V���b�g�E�t���A�v
				if (CGameManager::StageNo() == 1)
				{
					mSavePoint1 = false;
					mSavePoint2 = false;

					mStage1Clear = true;
					mIsStage1Clear = false;

					mIsStartStage2 = true;

					if (mStage2Clear)
					{
						mIsStage2Clear = false;
						mStage2Clear = false;
					}
					else if (mStage3Clear)
					{
						mIsStage3Clear = false;
						mStage3Clear = false;
					}

					mElapsedTime = 0.0f;
					mpCutInClear->End();

					// �X�e�[�W���N���A
					CGameManager::StageClear();
					// �X�e�[�W���N���A������A���̃X�e�[�W�J�n�܂ŏ������̏�ԂɕύX
					ChangeState(EState::eReady);
					Position(mStartPos);
					mpColliderCapsule->SetEnable(true);
				}
				// �X�e�[�W2�N���A
				else if (CGameManager::StageNo() == 2)
				{
					mSavePoint1 = false;
					mSavePoint2 = false;

					mStage2Clear = true;
					mIsStage2Clear = false;

					mIsStartStage3 = true;

					if (mStage1Clear)
					{
						mIsStage1Clear = false;
						mStage1Clear = false;
					}
					else if (mStage3Clear)
					{
						mIsStage3Clear = false;
						mStage3Clear = false;
					}

					mElapsedTime = 0.0f;
					mpCutInClear->End();
					// �X�e�[�W���N���A
					CGameManager::StageClear();
					// �X�e�[�W���N���A������A���̃X�e�[�W�J�n�܂ŏ������̏�ԂɕύX
					ChangeState(EState::eReady);
					Position(mStartPos);
					mpColliderCapsule->SetEnable(true);
				}
				// �X�e�[�W3�u�����v
				else if (CGameManager::StageNo() == 3)
				{
					mSavePoint1 = false;
					mSavePoint2 = false;

					mStage3Clear = true;
					mIsStage3Clear = false;

					if (mStage1Clear)
					{
						mIsStage1Clear = false;
						mStage1Clear = false;
					}
					else if (mStage2Clear)
					{
						mIsStage2Clear = false;
						mStage2Clear = false;
					}

					mElapsedTime = 0.0f;
					mpCutInClear->End();
					// �X�e�[�W���N���A
					CGameManager::GameClear();
					// �X�e�[�W���N���A
					//CGameManager::StageClear();
					// �X�e�[�W���N���A������A���̃X�e�[�W�J�n�܂ŏ������̏�ԂɕύX
					ChangeState(EState::eReady);
					mIsStartStage2 = false;
					mIsStartStage3 = false;
					// �����Ȃ��悤��
					// ��������s�
					//Position(mStartPos);
					mpColliderCapsule->SetEnable(true);
				}
				// �X�e�[�W4�N���A
				else if (CGameManager::StageNo() == 2)
				{
					mSavePoint1 = false;
					mSavePoint2 = false;

					mStage4Clear = true;
					mIsStage4Clear = false;

					mIsStartStage4 = true;

					if (mStage1Clear)
					{
						mIsStage1Clear = false;
						mStage1Clear = false;
					}
					else if (mStage2Clear)
					{
						mIsStage2Clear = false;
						mStage2Clear = false;
					}
					else if (mStage3Clear)
					{
						mIsStage3Clear = false;
						mStage3Clear = false;
					}

					mElapsedTime = 0.0f;
					mpCutInClear->End();
					// �X�e�[�W���N���A
					CGameManager::GameClear();
					// �X�e�[�W���N���A������A���̃X�e�[�W�J�n�܂ŏ������̏�ԂɕύX
					ChangeState(EState::eReady);
					mIsStartStage2 = false;
					mIsStartStage3 = false;
					Position(mStartPos);
					mpColliderCapsule->SetEnable(true);
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

// ���U���g���̃W�����v�J�n
void CPlayer::UpdateResultJumpStart()
{
	mDash = false;
	Scale(CVector(0.0f, 0.0f, 0.0f));
	if (mpCutInResult->IsPlaying())
	{

	}
	else
	{
		mpCutInResult->Setup(this);
		mpCutInResult->Start();
	}
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eResultJump);

	mMoveDistance = 0.0f;
	mMoveSpeedY = JUMP_CLEAR;
	mIsGrounded = false;
}

// ���U���g���̃W�����v
void CPlayer::UpdateResultJump()
{
	// �ڕW�n�_�܂ňړ������鏈��
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = player->Position();
	CVector current = VectorZ();
	CVector targetPos = playerPos + current * 0.5f;
	float per = mResultElapsedTime / 1.5f;
	CVector pos = CVector::Lerp(playerPos, targetPos, per);
	Position(pos);

	// �ڕW�̑傫���ɂ��鏈��
	float perscale = mScaleTime / 1.0f;
	CVector scale = CVector(0.0f, 0.0f, 0.0f);
	CVector targetscale = CVector(1.0f, 1.0f, 1.0f);
	CVector ScaleCur = CVector::Lerp(scale, targetscale, perscale);
	Scale(ScaleCur);

	mResultElapsedTime += Time::DeltaTime();
	mScaleTime += Time::DeltaTime();

	if (mResultElapsedTime > 1.5f)
	{
		mMoveDistance = 0.0f;
		if (mMoveSpeedY <= 0.0f)
		{
			mResultElapsedTime = 0.0f;
			Scale(CVector(1.0f, 1.0f, 1.0f));
			ChangeAnimation(EAnimType::eJumpEnd);
			ChangeState(EState::eResultJumpEnd);
		}
	}
}

// ���U���g���̃W�����v�I��
void CPlayer::UpdateResultJumpEnd()
{
	if (mIsGrounded)
	{
		mMoveDistance = 0.0f;
		ChangeState(EState::eIdle);
	}
}

// ���U���g���
void CPlayer::UpdateResult()
{
	mMoveSpeed = CVector::zero;
	mElapsedTime += Time::DeltaTime();
	if (mElapsedTime > 1.0f)
	{
		mElapsedTime = 0.0f;
		mScaleTime = 0.0f;
		ChangeAnimation(EAnimType::eGuts);
		ChangeState(EState::eResultEnd);
	}
}

// ���U���g�I�����
void CPlayer::UpdateResultEnd()
{
	if (IsAnimationFinished())
	{
		if (mStage1Clear)
		{
			mIsStage1Clear = true;
			CResultAnnouncement* result = CResultAnnouncement::Instance();
			bool resultEnd = result->IsResultOpened();
			if (resultEnd)
			{
				mMoveDistance = 0.0f;
				mpCutInResult->End();
				mpHpGauge->SetShow(true);
				mpStaminaGauge->SetShow(true);
				mpScreenItem->SetShow(true);
				mpSpikyBallUI->SetShow(true);
				mpMeat->SetShow(true);
				mIsStageClear = false;

				mIsStage1Clear = false;
				StageFlagfalse();
				ChangeState(EState::eIdle);
			}
		}
		else if (mStage2Clear)
		{
			mIsStage2Clear = true;
			CResultAnnouncement* result = CResultAnnouncement::Instance();
			bool resultEnd = result->IsResultOpened();
			if (resultEnd)
			{
				mMoveDistance = 0.0f;
				mpCutInResult->End();
				mpHpGauge->SetShow(true);
				mpStaminaGauge->SetShow(true);
				mpScreenItem->SetShow(true);
				mpSpikyBallUI->SetShow(true);
				mpMeat->SetShow(true);
				mIsStageClear = false;

				mIsStage2Clear = false;
				StageFlagfalse();
				ChangeState(EState::eIdle);
			}
		}
		else if (mStage3Clear)
		{
			mIsStage3Clear = true;
			CResultAnnouncement* result = CResultAnnouncement::Instance();
			bool resultEnd = result->IsResultOpened();
			if (resultEnd)
			{
				mMoveDistance = 0.0f;
				mpCutInResult->End();
				mpHpGauge->SetShow(true);
				mpStaminaGauge->SetShow(true);
				mpScreenItem->SetShow(true);
				mpSpikyBallUI->SetShow(true);
				mpMeat->SetShow(true);
				mIsStageClear = false;

				mIsStage3Clear = false;
				StageFlagfalse();
				ChangeState(EState::eIdle);
			}
		}
	}
}

// restart���
void CPlayer::UpdateRestart()
{
	mMoveSpeed = CVector::zero;
	//mElapsedTime += Time::DeltaTime();
	ChangeAnimation(EAnimType::eStandUp);
	if (IsAnimationFinished())
	{
		mElapsedTime = 0.0f;
		mScaleTime = 0.0f;
		ChangeState(EState::eRestartEnd);
		/*if (mElapsedTime > 1.0f)
		{
			mElapsedTime = 0.0f;
			mScaleTime = 0.0f;
			ChangeState(EState::eRestartEnd);
		}*/
	}
}

// restart�I�����
void CPlayer::UpdateRestartEnd()
{
	CResultAnnouncement* result = CResultAnnouncement::Instance();
	bool resultEnd = result->IsResultOpened();
	mIsDeath = true;
	if (resultEnd)
	{
		mDeath = false;
		mIsDeath = false;
		mpCutInDeathJump->End();
		mpHpGauge->SetShow(true);
		mpStaminaGauge->SetShow(true);
		mpScreenItem->SetShow(true);
		mpMeat->SetShow(true);

		StageFlagfalse();
		ChangeAnimation(EAnimType::eIdle);
		ChangeState(EState::eIdle);
	}
}

// �X�e�[�W�J�n���̃W�����v�J�n
void CPlayer::UpdateStartStageJumpStart()
{
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;

	// �����ɉ��̃G�t�F�N�g�𔭐�������
	PlayStepSmoke();

	mpColliderCapsule->SetEnable(false);
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eStartStageJump);

	mMoveSpeedY = JUMP_START_STAGE;
	mIsGrounded = false;
}

// �X�e�[�W�J�n���̃W�����v
void CPlayer::UpdateStartStageJump()
{
	// �ڕW�n�_�܂ňړ������鏈��
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = player->Position();
	CVector zDirection(-1.0f, 0.0f, 0.0f); // Z�������̃x�N�g��
	CVector targetPos = playerPos + zDirection * 1.1f;
	float per = mElapsedTime / 1.0f;
	CVector pos = CVector::Lerp(playerPos, targetPos, per);
	Position(pos);

	// �v���C���[�̌����𒲐�
	CVector current = VectorZ();
	CVector target = zDirection; // �ړ������ɍ��킹��Z����������������

	// �ڕW�̑傫���ɂ��鏈��
	float perscale = mScaleTime / 1.0f;
	CVector scale =  CVector(1.0f, 1.0f, 1.0f);
	CVector targetscale = CVector(0.0f, 0.0f, 0.0f);
	CVector ScaleCur = CVector::Lerp(scale, targetscale, perscale);
	Scale(ScaleCur);

	//// Slerp�ŃX���[�Y�Ɍ�����ς���
	//CVector forward = CVector::Slerp(current, target, 0.125f);
	//Rotation(CQuaternion::LookRotation(forward));
	// �v���C���[�̌����𒲐�
	Rotation(CQuaternion::LookRotation(target)); // ��u�ŐV���������Ɍ�����

	mElapsedTime += Time::DeltaTime();
	mScaleTime += Time::DeltaTime();
	
	if (mElapsedTime > 0.8f && mScaleTime > 1.0f)
	{
		if (mMoveSpeedY <= 0.0f)
		{
			ChangeAnimation(EAnimType::eJumpEnd);
			ChangeState(EState::eStartStageJumpEnd);
		}
	}
}

// �X�e�[�W�J�n���̃W�����v�I��
void CPlayer::UpdateStartStageJumpEnd()
{
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = -0.01f;
	mpSword->SetAlpha(0.0f);
	if (IsAnimationFinished())
	{
		mElapsedTime = 0.0f;
		mpColliderCapsule->SetEnable(true);
		ChangeState(EState::eReady);
		if (mStartStage1)
		{
			mScaleTime = 0.0f;
			mMoveSpeedY = 0.0f;
			Scale(CVector(1.0f, 1.0f, 1.0f));
			SetAlpha(0.0f);
			CFade::FadeIn();
			ChangeState(EState::eReady);
			CGameManager::Stage1();
		}
		else if (mStartStage2)
		{
			mScaleTime = 0.0f;
			mMoveSpeedY = 0.0f;
			Scale(CVector(1.0f, 1.0f, 1.0f));
			SetAlpha(0.0f);
			CFade::FadeIn();
			ChangeState(EState::eReady);
			CGameManager::Stage2();
		}
		else if (mStartStage3)
		{
			mScaleTime = 0.0f;
			mMoveSpeedY = 0.0f;
			Scale(CVector(1.0f, 1.0f, 1.0f));
			SetAlpha(0.0f);
			CFade::FadeIn();
			ChangeState(EState::eReady);
			CGameManager::Stage3();
		}
		else if (mStartStage4)
		{
			mScaleTime = 0.0f;
			mMoveSpeedY = 0.0f;
			Scale(CVector(1.0f, 1.0f, 1.0f));
			SetAlpha(0.0f);
			CFade::FadeIn();
			ChangeState(EState::eReady);
			CGameManager::Stage4();
		}
	}
}

// ���S
void CPlayer::UpdateDeath()
{
	mMoveSpeed = CVector::zero;
	mMoveSpeedY += GRAVITY;

	mDeath = true;

	if (mState == EState::eIdle || IsAnimationFinished())
	{
		mpDamageCol->SetEnable(false);
		mpSword->AttackEnd();
		mMoveSpeed = CVector::zero;
		mMoveSpeedY = 0.0f;
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
	mMoveSpeed = CVector::zero;
	mMoveSpeedY += GRAVITY;
	if (IsAnimationFinished())
	{
		mpCutInDeath->End();
		mDamaged = false;
		mDamageObject = false;
		mDamageEnemy = false;
		mCharaStatus = mCharaMaxStatus;
		mpHpGauge->SetMaxValue(mCharaMaxStatus.hp);
		mpDamageCol->SetEnable(true);
		// ���S
		CGameManager::StageOver();
		// ���S������A���̃X�e�[�W�J�n�܂ŏ������̏�ԂɕύX
		ChangeState(EState::eReady);
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
	mClimb = false;
	mDamaged = true;

	mMoveSpeed = CVector::zero;

	if (!mDamageEnemy)
	{
		TakeDamage(3);
		mDamageEnemy = true;
	}

	if (mSpik1)
	{
		mSpik1 = false;
		if (mpSpiky1 != nullptr)
		{
			mpSpiky1->Kill();
		}
	}

	mpDamageCol->SetEnable(false);
	ChangeAnimation(EAnimType::eHitJ);

	CHPJudgment();
}

// �G�̒e�̍U�����󂯂���
void CPlayer::UpdateHitBullet()
{
	mClimb = false;
	mDamaged = true;

	mMoveSpeed = CVector::zero;

	if (!mDamageEnemy)
	{
		TakeDamage(1);
		mDamageEnemy = true;
	}

	if (mSpik1)
	{
		mSpik1 = false;
		if (mpSpiky1 != nullptr)
		{
			mpSpiky1->Kill();
		}
	}

	mpDamageCol->SetEnable(false);
	ChangeAnimation(EAnimType::eHit);

	CHPJudgment();
}

// �G�̌��̍U�����󂯂���
void CPlayer::UpdateHitSword()
{
	mClimb = false;
	mDamaged = true;
	mMoveSpeed = CVector::zero;

	if (!mDamageEnemy)
	{
		mDamageEnemy = true;
	}

	if (mSpik1)
	{
		mSpik1 = false;
		if (mpSpiky1 != nullptr)
		{
			mpSpiky1->Kill();
		}
	}

	mpDamageCol->SetEnable(false);
	ChangeAnimation(EAnimType::eHit);

	CHPJudgment();
}

// �_���[�W���󂯂�(�I�u�W�F�N�g)
void CPlayer::UpdateHitObj()
{
	mClimb = false;
	mDamaged = true;
	mMoveSpeed = CVector::zero;

	if (!mDamageEnemy)
	{
		mDamageEnemy = true;
	}

	if (mSpik1)
	{
		mSpik1 = false;
		if (mpSpiky1 != nullptr)
		{
			mpSpiky1->Kill();
		}
	}

	mpDamageCol->SetEnable(false);
	ChangeAnimation(EAnimType::eHit);

	CHPJudgment();
}

// �����_���[�W
void CPlayer::UpdateFallDamage()
{
	mDamaged = true;
	mMoveSpeed = CVector::zero;

	if (!mFallDamage)
	{
		mFallDamage = true;
		TakeDamage(1);
	}

	if (mSpik1)
	{
		mSpik1 = false;
		if (mpSpiky1 != nullptr)
		{
			mpSpiky1->Kill();
		}
	}

	mpDamageCol->SetEnable(false);

	ChangeAnimation(EAnimType::eFallingFlat);
	if (IsAnimationFinished())
	{
		if (mCharaStatus.hp > 0)
		{
			mFallDamage = false;
			mIsPlayedHitDamageSE = false;
			ChangeState(EState::eStandUp);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mDeath = true;
			mFallDamage = false;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
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
		mpMetalLadder->GetClimbedMoveVec(&moveUp, &moveForward);
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

// ������q�ɓo����
void CPlayer::UpdateMetalLadder()
{
	mClimb = true;
	mIsAttack = false;
	mWeaponTime = 0.0f;
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_Spine1"));
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;
	// �v���C���[�̈ړ��x�N�g�������߂�
	CVector move = ClimbMoveUpVec();

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
		mClimbTime = 0.0f;
		ChangeState(EState::eJumpStart);
	}

	if (mClimbTime >= 0.5f)
	{
		if (mIsGrounded)
		{
			mClimb = false;
			mClimbTime = 0.0f;
			ChangeState(EState::eIdle);
		}
	}
	else
	{
		mClimbTime += Time::DeltaTime();
	}

	// �o���ǂ͈̔͊O�ɏo���ꍇ
	if (!mClimbWall)
	{
		// �o���ǂ̒���ɐG��Ă����ꍇ
		if (mClimbWallTop)
		{
			// ����֏���Ԃֈڍs
			ChangeState(EState::eMetalLadderTop);
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

// ������q�̒���ɓo�������
void CPlayer::UpdateMetalLaddertop()
{
	mClimb = true;
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;
	mClimbTime = 0.0f;

	// �X�e�b�v�Ǘ�
	switch (mStateStep)
	{
		// �X�e�b�v0: ����������
	case 0:
	{
		// ����֏��؂������̈ړ��O�̍��W�ƈړ���̍��W��ݒ�
		mClimbedStartPos = Position();
		CVector  moveUp, moveForward;
		mpMetalLadder->GetClimbedMoveVec(&moveUp, &moveForward);
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
			ChangeState(EState::eFallDamege);
		}
		else if (mCharaStatus.hp <= 0)
		{
			ChangeState(EState::eFallDamege);
		}
	}
}

// �����オ��
void CPlayer::UpdateStandUp()
{
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;
	ChangeAnimation(EAnimType::eStandUp);
	if (IsAnimationFinished())
	{
		mDamageEnemy = false;
		mDamaged = false;
		mDamageObject = false;
		ChangeState(EState::eIdle);
	}
}

// �W�����v�J�n
void CPlayer::UpdateJumpStart()
{
	// �����ɉ��̃G�t�F�N�g�𔭐�������
	PlayStepSmoke();

	mMoveSpeedY += JUMP_SPEED;
	mIsJumping = true;
	mIsGrounded = false;

	JumpingHpJudgment();
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eJump);
}

// �W�����v��
void CPlayer::UpdateJump()
{
	if (mMoveSpeedY <= 0.0f)
	{
		mIsJumping = false;
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpEnd);
	}

	JumpingHpJudgment();
}

// �W�����v�I��
void CPlayer::UpdateJumpEnd()
{
	mMoveSpeed = CVector::zero;

	if (IsAnimationFinished() && mIsGrounded)
	{
		ChangeState(EState::eIdle);
	}

	JumpingHpJudgment();
	mpClimbCol->SetEnable(true);
}

// �_�b�V���W�����v�J�n
void CPlayer::UpdateDashJumpStart()
{
	// �����ɉ��̃G�t�F�N�g�𔭐�������
	PlayStepSmoke();
	mDash = false;

	mMoveSpeedY += JUMP_DASH;
	mIsJumping = true;
	mIsGrounded = false;

	JumpingHpJudgment();
	ChangeAnimation(EAnimType::eDashJumpStart);
	ChangeState(EState::eDashJump);
}

// �_�b�V���W�����v��
void CPlayer::UpdateDashJump()
{
	mIsJumping = false;

	if (mIsGrounded)
	{
		// �����������炢�邩������Ȃ��̂Ŏc���Ă���
		//mIsJumping = false;
		ChangeAnimation(EAnimType::eDashJumpEnd);
		ChangeState(EState::eDashJumpEnd);
	}

	JumpingHpJudgment();
}

// �_�b�V���W�����v�I��
void CPlayer::UpdateDashJumpEnd()
{
	mMoveSpeed = CVector::zero;

	if (IsAnimationFinished() && mIsGrounded)
	{
		ChangeState(EState::eIdle);
	}

	JumpingHpJudgment();
	mpClimbCol->SetEnable(true);
}

// ���˂鏈���J�n
void CPlayer::UpdateJumpingStart()
{
	mMoveSpeedY = JUMP_BOUNCE;
	mIsGrounded = false;
	mDamageEnemy = false;

	JumpingHpJudgment();
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eJumping);
}

// ���˂鏈��
void CPlayer::UpdateJumping()
{
	if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
	{
		mCharaStatus.stamina += 1;
	}

	if (mMoveSpeedY <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpingEnd);
	}

	JumpingHpJudgment();
}

// ���˂鏈���I��
void CPlayer::UpdateJumpingEnd()
{
	mMoveSpeed = CVector::zero;

	if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
	{
		mCharaStatus.stamina += 1;
	}

	if (IsAnimationFinished() && mIsGrounded)
	{
		ChangeState(EState::eIdle);
	}

	JumpingHpJudgment();
	mpClimbCol->SetEnable(true);
}

// ���ђ��˂�J�n
void CPlayer::UpdateHighJumpingStart()
{
	mMoveSpeedY = JUMP_HIGH_BOUNCE;
	mIsGrounded = false;

	JumpingHpJudgment();
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eHighJumping);
}

// ���ђ��˂�
void CPlayer::UpdateHighJumping()
{
	if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
	{
		mCharaStatus.stamina += 1;
	}

	if (mMoveSpeedY <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eHighJumpingEnd);
	}

	JumpingHpJudgment();
}

// ���ђ��˂�I��
void CPlayer::UpdateHighJumpingEnd()
{
	mMoveSpeed = CVector::zero;

	if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
	{
		mCharaStatus.stamina += 1;
	}

	if (IsAnimationFinished() && mIsGrounded)
	{
		ChangeState(EState::eIdle);
	}

	JumpingHpJudgment();
}

// �ړI�ʒu�܂ŃW�����v�J�n
void CPlayer::UpdateTargetPositionStart()
{
	mMoveSpeedY = JUMP_TARGET;
	mIsGrounded = false;

	JumpingHpJudgment();
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eTarget);
}

// �ړI�ʒu�܂ŃW�����v
void CPlayer::UpdateTargetPosition()
{
	if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
	{
		mCharaStatus.stamina += 1;
	}

	if (IsAnimationFinished())
	{
		ChangeAnimation(EAnimType::eDashJumpLoop);
	}

	// �ڕW�n�_�܂ňړ������鏈��
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = player->Position();
	CVector targetPos = CVector(0.0f, 10.0f, 480.0f); // �X�̏����͕ύX�\��
	float duration = 25.0f;
	float stopDistance = 3.0f; // �v���C���[���ڕW�ɓ��B�Ƃ݂Ȃ�������臒l

	if (mElapsedTime < duration) 
	{
		float per = mElapsedTime / duration;
		CVector pos = CVector::Lerp(playerPos, targetPos, per);
		player->Position(pos);

		// �v���C���[�̌����𒲐��i���E�̉�]�̂݁j
		CVector direction = targetPos - playerPos;
		direction.Y(0.0f); //CVector(direction.X(), 0.0f, direction.Z()); // �㉺�̉�]�𖳎�
		direction.Normalize(); // �ړ��x�N�g���𐳋K��

		player->Rotation(CQuaternion::LookRotation(direction)); // �V����������ݒ�

		 // �v���C���[�ƖڕW�ʒu�Ƃ̋������v�Z���A����臒l�ȉ��Ȃ�I��
		float distanceToTarget = (targetPos - playerPos).Length();
		if (distanceToTarget <= stopDistance) {
			Position(targetPos); // �m���ɍŏI�ʒu�ɐݒ�
			// �K�v�ɉ�����mElapsedTime�����Z�b�g
			mElapsedTime = 0.0f;
		}
		else 
		{
			mElapsedTime += Time::DeltaTime();
		}
	}
	else 
	{
		Position(targetPos); // �m���ɍŏI�ʒu�ɐݒ�
		// �K�v�ɉ�����mElapsedTime�����Z�b�g
		mElapsedTime = 0.0f;
	}

	if (mMoveSpeedY <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eTargetEnd);
	}

	JumpingHpJudgment();
}

// �ړI�ʒu�܂ŃW�����v�I��
void CPlayer::UpdateTargetPositionEnd()
{
	mMoveSpeed = CVector::zero;

	if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
	{
		mCharaStatus.stamina += 1;
	}

	if (IsAnimationFinished() && mIsGrounded)
	{
		ChangeState(EState::eIdle);
	}

	JumpingHpJudgment();
	mpClimbCol->SetEnable(true);
}

#define REFLECTION 0.4f
// ���˕Ԃ����鏈��
void CPlayer::UpdateReflection()
{
	ChangeAnimation(EAnimType::eHitJ);
	switch (mStateStep)
	{
	case 0:
		if (mReflectTime < REFLECTION)
		{
			mMoveSpeed = mReflectionNormal * 1.5f;
			mReflectTime += Time::DeltaTime();
		}
		else
		{
			mStateStep++;
		}
		break;
	case 1:
		if (mCharaStatus.hp > 0)
		{
			mDamageEnemy = false;
			mIsPlayedHitDamageSE = false;
			mStateStep = 0;
			mReflectTime = 0.0f;
			ChangeState(EState::eIdle);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mDeath = true;
			mFallDamage = false;
			mpDamageCol->SetEnable(false);
			mStateStep = 0;
			mReflectTime = 0.0f;
			ChangeState(EState::eDeath);
		}
		break;
	}
	//CDebugPrint::Print("mStateStep:%d\n", mStateStep);
}

// ���S�W�����v�J�n
void CPlayer::UpdateDeathJumpStart()
{
	mSavePoint1 = false;
	mSavePoint2 = false;
	mFallDamage = false;

	Scale(CVector(0.0f, 0.0f, 0.0f));
	if (mpCutInDeathJump->IsPlaying())
	{

	}
	else
	{
		mpCutInDeathJump->Setup(this);
		mpCutInDeathJump->Start();
	}
	ChangeAnimation(EAnimType::eFalling);
	ChangeState(EState::eDeathJump);

	mMoveSpeedY = JUMP_DEATH;
	mIsGrounded = false;
}

// ���S�W�����v
void CPlayer::UpdateDeathJump()
{
	// �ڕW�n�_�܂ňړ������鏈��
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = player->Position();
	CVector current = VectorZ();
	CVector targetPos = playerPos + current * 0.5f;
	float per = mResultElapsedTime / 1.5f;
	CVector pos = CVector::Lerp(playerPos, targetPos, per);
	Position(pos);

	// �ڕW�̑傫���ɂ��鏈��
	float perscale = mScaleTime / 1.0f;
	CVector scale = CVector(0.0f, 0.0f, 0.0f);
	CVector targetscale = CVector(1.0f, 1.0f, 1.0f);
	CVector ScaleCur = CVector::Lerp(scale, targetscale, perscale);
	Scale(ScaleCur);

	mResultElapsedTime += Time::DeltaTime();
	mScaleTime += Time::DeltaTime();

	if (mResultElapsedTime > 1.5f)
	{
		if (mIsGrounded)
		{
			mResultElapsedTime = 0.0f;
			Scale(CVector(1.0f, 1.0f, 1.0f));
			ChangeAnimation(EAnimType::eFallingFlat);
			ChangeState(EState::eDeathJumpEnd);
		}
	}
}

// ���S�W�����v�I��
void CPlayer::UpdateDeathJumpEnd()
{
	if (mIsGrounded)
	{
		ChangeState(EState::eIdle);
	}
}

// �w�肳�ꂽ�ʒu�܂ňړ�����
void CPlayer::UpdateMoveTo()
{
	mMoveSpeed = CVector::zero;

	switch (mStateStep)
	{
		// �X�e�b�v0 �v���C���[���ړ������֌�����
	case 0:
	{
		// �ړ��J�n�O�͑ҋ@���[�V����
		ChangeAnimation(EAnimType::eIdle);
		// �ړ��J�n�ʒu����ړ��I���ʒu�̕����x�N�g�������߂�
		CVector v = mMoveTargetPos - mMoveStartPos;
		v.Y(0.0f);
		// ���߂������x�N�g���̌����փv���C���[��������
		Rotation(CQuaternion::LookRotation(v.Normalized()));
		mStateStep++;
		break;
	}
		// �X�e�b�v1 �v���C���[���ړ�
	case 1:
		// �v���C���[���_�b�V�����[�V�����֕ύX
		ChangeAnimation(EAnimType::eDash);
		// �ړ����Ԃ��o�߂��Ă��Ȃ�
		if (mElapsedTime < MOVE_TO_TIME)
		{
			// �o�ߎ��Ԃ̊��������߁A���̊����ɉ��������݈ʒu�����߂Đݒ�
			float percent = mElapsedTime / MOVE_TO_TIME;
			CVector pos = CVector::Lerp(mMoveStartPos, mMoveTargetPos, percent);
			pos.Y(Position().Y());
			Position(pos);

			// �o�ߎ��Ԃ�i�s
			mElapsedTime += Time::DeltaTime();
		}
		// �ړ����Ԃ��o�߂���
		else
		{
			// �ړ��I���ʒu�Ɉړ�
			CVector pos = mMoveTargetPos;
			pos.Y(Position().Y());
			Position(pos);
			mStateStep++;
		}
		break;
		 // �X�e�b�v2 �ړ��I��
	case 2:
		// �ړ��I��������A�ҋ@���[�V�����֐؂�ւ�
		ChangeAnimation(EAnimType::eIdle);
		break;
	}
}

// �w�肳�ꂽ�ʒu�܂ňړ��J�n
void CPlayer::MoveTo(const CVector& pos)
{
	// �w�肳�ꂽ�ʒu�܂ňړ��ł��Ȃ���Ԃł���΁A�������Ȃ�
	if (!CanMoveTo()) return;

	mElapsedTime = 0.0f;
	// �ړ��O�̍��W�ƈړ���̍��W��ݒ�
	mMoveStartPos = Position();
	mMoveTargetPos = pos;

	// �w�肳�ꂽ�ʒu�܂ł̈ړ���Ԃ֑J��
	ChangeState(EState::eMoveTo);
}

// �w�肳�ꂽ�ʒu�܂ł̈ړ����o���邩�ǂ���
bool CPlayer::CanMoveTo() const
{
	// �X�e�[�W�I����ʈȊO�̃X�e�[�W�ł���΁A�ړ��ł��Ȃ�
	if (CGameManager::StageNo() != 0) return false;
	// �ҋ@��Ԃ������́A�w��ʒu�܂ňړ����Ă����ԂŖ�����΁A�ړ��ł��Ȃ�
	if (mState != EState::eIdle && mState != EState::eMoveTo) return false;
	// �ړ��I���X�e�b�v�܂Ői�s���Ă��Ȃ���΁A�ړ��ł��Ȃ�
	if (mState == EState::eMoveTo && mStateStep < 2) return false;

	// �S�Ă̏����𖞂�������ړ��\
	return true;
}

// �w�肳�ꂽ�ԍ��̃X�e�[�W���J�n
void CPlayer::StartStage(int stageNo)
{
	// �X�e�[�W1�ɓ�����ԂŁA�X�e�[�W1���J�n������
	if (stageNo == 1)
	{
		// �X�e�[�W1�̃t���O���I��
		mStartStage1 = true;
	}
	else if (stageNo == 2 && mIsStartStage2)
	{
		mStartStage2 = true;
	}
	// �X�e�[�W3���J�n������A�X�e�[�W3�̃t���O���I��
	else if (stageNo == 3 && mIsStartStage3)
	{
		mStartStage3 = true;
	}
	// �X�e�[�W4���J�n������A�X�e�[�W4�̃t���O���I��
	else if (stageNo == 4 && mIsStartStage4)
	{
		mStartStage4 = true;
	}
	// ����ȊO�́A�X�e�[�W�ړ���Ԃ֐i�s���Ȃ�
	else return;

	// �X�e�[�W�ڍs�W�����v�Ɉړ�����
	ChangeState(EState::eStartStageJumpStart);
}

// �����ɉ��̃G�t�F�N�g�𔭐�
void CPlayer::PlayStepSmoke()
{
	CVector pos = Position() + CVector(0.0f, 2.0f, 0.0f);
	CSmoke* smoke = new CSmoke(ETag::eSmoke, ETaskPriority::eEffect);
	smoke->Position((pos));

	mSmokeList.push_back(smoke);
}

// �����̉��G�t�F�N�g�̍X�V
void CPlayer::UpdateStepSmoke()
{
	// �Ō�܂ōĐ��������G�t�F�N�g��
	// ���X�g�����菜���A�폜����
	auto itr = mSmokeList.begin();
	auto itr_end = mSmokeList.end();
	while (itr != itr_end)
	{
		CSmoke* smoke = *itr;
		if (smoke->IsDeath())
		{
			smoke->Kill();
			itr = mSmokeList.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	if (IsEnableStepSmoke())
	{
		mMoveDistance += (Position() - mLastPos).Length();
		if (mMoveDistance >= 20.0f)
		{
			PlayStepSmoke();
			mMoveDistance -= 20.0f;
		}
	}
	else
	{
		mMoveDistance = 0.0f;
	}
}

// �����̉��G�t�F�N�g��\�������Ԃ��ǂ���
bool CPlayer::IsEnableStepSmoke() const
{
	// �_�b�V�����͉��G�t�F�N�g���o��
	if (mDash) return true;
	// �X�e�[�W�I����ʂ̈ړ����͉��G�t�F�N�g���o��
	if (mState == EState::eMoveTo && mStateStep < 2) return true;
	return false;
}

void CPlayer::CheckUnderFootObject()
{
	if (mpUnderFootObject == nullptr) return;

	if (mState != EState::eJumpStart &&
		mState != EState::eJump &&
		mState != EState::eJumpEnd)
	{
		CVector start = Position() + CVector::up * 1.0f;
		CVector end = start + CVector::down * 20.0f;
		CHitInfo hit;
		if (mpUnderFootObject->CollisionRay(start, end, &hit))
		{
			Position(hit.cross + CVector::down * 1.0f);
			mMoveSpeedY = 0.0f;
			mIsGrounded = true;
			mGroundNormal = hit.adjust.Normalized();
		}
		else
		{
			mpUnderFootObject = nullptr;
		}
	}
}

// �ړ����x���擾
CVector CPlayer::Velocity() const
{
	return mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f);
}

// �X�V
void CPlayer::Update()
{
	//CDebugPrint::Print("speed:%f:\n", GetSpikyBallSpeed());
	//CDebugPrint::Print("mSpik2:%s\n", mSpik2 ? "true" : "false");
	//CDebugPrint::Print("strongpos:%f %f %f\n", mAttackStrongPos.X(), mAttackStrongPos.Y(), mAttackStrongPos.Z());
	mIsStartStage2 = true;
	mIsStartStage3 = true;

	SetParent(mpRideObject);
	SetColor(CColor(1.0, 1.0, 1.0, 1.0));
	mpRideObject = nullptr;
	mHpHit = false;

	if (mIsAttackItem)
	{
		mAttackTime -= Time::DeltaTime();
		if (mAttackTime <= 0.0f)
		{
			mIsAttackItem = false;
		}
	}
	else if (mIsHealingItem)
	{
		mHealingTime -= Time::DeltaTime();
		if (mHealingTime <= 0.0f)
		{
			mIsHealingItem = false;
		}
	}

	if (mDamaged)
	{
		CDamageColorTime();
	}

	if (mSpikyBall)
	{
		if (mState != EState::eAttackStrongWait && mpSpiky2 != nullptr)
		{
			mSpikRechargeTime -= Time::DeltaTime();
			if (mSpikRechargeTime <= 0.0f)
			{
				mSpik1 = false;
				mSpik2 = false;
				mpSpiky2 = nullptr;
				mSpikRechargeTime = 0.0f;
			}
		}
	}
	//SCDebugPrint::Print("mTime:%f\n", mSpikRechargeTime);
	// �Ƃ��{�[�����`���[�W
	//CDebugPrint::Print("spiktime:%f\n", mSpikRechargeTime);

	////////////////////////////////////////////////////////////////////////////////////////


	if (CGameManager::GameState() == EGameState::eStage1)
	{
		ChangeState(EState::eReady);
	}
	else if (CGameManager::GameState() == EGameState::eStage2)
	{
		ChangeState(EState::eReady);
	}
	else if (CGameManager::GameState() == EGameState::eStage3)
	{
		ChangeState(EState::eReady);
	}

	/*if (mState != EState::eJumpStart &&
		mState != EState::eJump &&
		mState != EState::eJumpEnd)
	{
		if (mMoveSpeedY <= -3.5f)
		{
			ChangeState(EState::eFalling);
		}
	}*/

	if (mMoveSpeedY <= -4.0f)
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
	case EState::eFirstAction:
		UpdateFirstAction();
		break;
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// ��~���
	case EState::eStop:
		UpdateStop();
		break;
		// �_�b�V���I��
	case EState::eDashEnd:
		UpdateDashEnd();
		break;
		// �U��
	case EState::eAttack:
		UpdateAttack();
		break;
		// ���U���J�n
	case EState::eAttackStrongStart:
		UpdateAttackStrongStart();
		break;
		// ���U��
	case EState::eAttackStrong:
		UpdateAttackStrong();
		break;
		// ���U���I���҂�
	case EState::eAttackStrongWait:
		UpdateAttackStrongWait();
		break;
		// �_�b�V���A�^�b�N
	case EState::eAttackDash:
		UpdateDashAttack();
		break;
		// �U���I���҂�
	case EState::eAttackWait:
		UpdateAttackWait();
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
		// ������q�ɓo����
	case EState::eMetalLadder:
		UpdateMetalLadder();
		break;
		// ������q�̒���ɓo�������
	case EState::eMetalLadderTop:
		UpdateMetalLaddertop();
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
		// ���U���g���
	case EState::eResult:
		UpdateResult();
		break;
		// ���U���g���
	case EState::eResultEnd:
		UpdateResultEnd();
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
		// ��ђ��˂�J�n
	case EState::eHighJumpingStart:
		UpdateHighJumpingStart();
		break;
		// ��ђ��˂�
	case EState::eHighJumping:
		UpdateHighJumping();
		break;
		// ��ђ��˂�I��
	case EState::eHighJumpingEnd:
		UpdateHighJumpingEnd();
		break;
	case EState::eResultJumpStart:
		UpdateResultJumpStart();
		break;
	case EState::eResultJump:
		UpdateResultJump();
		break;
	case EState::eResultJumpEnd:
		UpdateResultJumpEnd();
		break;
	case EState::eStartStageJumpStart:
		UpdateStartStageJumpStart();
		break;
	case EState::eStartStageJump:
		UpdateStartStageJump();
		break;
	case EState::eStartStageJumpEnd:
		UpdateStartStageJumpEnd();
		break;
	case EState::eDashJumpStart:
		UpdateDashJumpStart();
		break;
	case EState::eDashJump:
		UpdateDashJump();
		break;
	case EState::eDashJumpEnd:
		UpdateDashJumpEnd();
		break;
	case EState::eMoveTo:
		UpdateMoveTo();
		break;
	case EState::eTargetStart:
		UpdateTargetPositionStart();
		break;
	case EState::eTarget:
		UpdateTargetPosition();
		break;
	case EState::eTargetEnd:
		UpdateTargetPositionEnd();
		break;
	case EState::eDeathJumpStart:
		UpdateDeathJumpStart();
		break;
	case EState::eDeathJump:
		UpdateDeathJump();
		break;
	case EState::eDeathJumpEnd:
		UpdateDeathJumpEnd();
		break;
	case EState::eRestart:
		UpdateRestart();
		break;
	case EState::eRestartEnd:
		UpdateRestartEnd();
		break;
	case EState::eReflection:
		UpdateReflection();
		break;
	}

	// �ҋ@���ƃW�����v���́A�ړ��������s��
	if ((mState == EState::eIdle/* && mIsGrounded*/)
		|| mState == EState::eJumpStart
		|| mState == EState::eJump
		|| mState == EState::eJumpEnd
		|| mState == EState::eJumpingStart
		|| mState == EState::eJumping
		|| mState == EState::eJumpingEnd
		|| mState == EState::eHighJumpingStart
		|| mState == EState::eHighJumping
		|| mState == EState::eHighJumpingEnd
		|| mState == EState::eDashJumpStart
		|| mState == EState::eDashJump
		|| mState == EState::eDashJumpEnd
		|| mState == EState::eFalling)
	{
		UpdateMove();
	}

	// �������łȂ���΁A�ړ������Ȃǂ��s��
	if (mState != EState::eReady)
	{
		if (!mClimb)
		{
			mMoveSpeedY -= GRAVITY;
		}
		else if (mState != EState::eDeath || mState != EState::eDeathEnd)
		{
			mMoveSpeedY = 0.0f;
		}

		CVector moveSpeed = mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f);

		// �ړ�
		Position(Position() + moveSpeed * 60.0f * Time::DeltaTime());

		// �A�N�V�������N�������Ԃł����
		if (IsEnableAction())
		{
			// �v���C���[�̌����𒲐�
			CVector current = VectorZ();
			CVector target = moveSpeed;
			float rotationSpeed = 0.125f;

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
			else if (mState == EState::eMetalLadder)
			{
				target = -mClimbNormal;
			}
			else if (mState == EState::eReflection)
			{
				target = -mReflectionNormal;
			}
			else if (mState == EState::eAttackStrong)
			{
				if (CInput::Key('A'))
				{
					target = CVector::Cross(CVector::up, current);
					target.Normalize();
					rotationSpeed = 0.005f;
				}
				else if (CInput::Key('D'))
				{
					target = CVector::Cross(current, CVector::up);
					target.Normalize();
					rotationSpeed = 0.005f;
				}
				else
				{
					target = current;
				}
			}
			// ����ȊO�̎��́A�v���C���[�̈ړ������֌�����
			else
			{
				target = moveSpeed;
				target.Y(0.0f);
				target.Normalize();
			}
			CVector forward = CVector::Slerp(current, target, rotationSpeed);
			Rotation(CQuaternion::LookRotation(forward));
		}
	}

	// ���G��Ԃ������ꍇ�̏���
	if (mInvincible)
	{
		float PosZ = Math::Rand(-10.0f, 10.0f);
		float PosX = Math::Rand(-10.0f, 10.0f);

		mInvincibleTime += Time::DeltaTime();

		// �G�t�F�N�g�����̏�������
		if (mInvincibleTime >= 0.25f && !mIsStageClear)
		{
			mInvincibleTime = 0.0f;
			// ���G�G�t�F�N�g�𐶐����āA������֔�΂�
			CInvincibleBuffs* invincible = new CInvincibleBuffs
			(
				this,
				Position() + CVector(PosX, 1.0f, PosZ),
				CVector::up, // ������ɐݒ�
				50.0f,
				20.0f
			);
			// ���G�G�t�F�N�g�̐F�ݒ�
			invincible->SetColor(CColor(0.8f, 0.8f, 0.0f, 0.5f));
			invincible->Rotation(0.0f, 90.0f, 0.0f);
			invincible->Scale(0.3f, 0.3f, 0.3f);
			invincible->SetParent(this);
		}

		SetColor(CColor(1.0, 1.0, 0.0, 1.0));
		mInvincibleStartTime -= Time::DeltaTime();

		if (mInvincibleStartTime <= 0.0f)
		{
			mpDamageCol->SetEnable(true);
			mInvincibleStartTime = 10.0f;
			mElapsedTime = 0.0f;
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
		if (CInput::PushKey(VK_UP))
		{
			mIsStartStage2 = true;
			mIsStartStage3 = true;
			//mIsStartStage4 = true;
		}
		else if (CInput::PushKey(VK_DOWN))
		{
			mIsStartStage2 = false;
			mIsStartStage3 = false;
			mIsStartStage4 = false;
		}
	}

	// ���݂�HP��ݒ�
	mpHpGauge->SetValue(mCharaStatus.hp);
	// ���݂̃X�^�~�i��ݒ�
	mpStaminaGauge->SetSutaminaValue(mCharaStatus.stamina);

	if (mClimbWall && !mClimb && mIsGrounded)
	{
		// E�L�[�e�L�X�g�摜��\��
		CVector EkeyPos = Position() + CVector(20.0f, 20.0f, 0.0f);
		mpClimbUI->SetWorldPos(EkeyPos);
		mpClimbUI->SetShow(true);
	}
	else
	{
		mpClimbUI->SetShow(false);
	}

	// �L�����N�^�[�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();
	mpColliderCapsule->Update();
	mpSword->UpdateAttachMtx();
	
	if (CGameManager::StageNo() == 1 ||
		CGameManager::StageNo() == 2 ||
		CGameManager::StageNo() == 3 ||
		CGameManager::StageNo() == 4)
	{
		mpHpGauge->SetShow(true);
		mpStaminaGauge->SetShow(true);
		mpScreenItem->SetShow(true);
		mpScreenItem->Open();
		mpSpikyBallUI->SetShow(true);
		mpSpikyBallUI->Open();
		mpMeat->SetShow(true);
		mpMeat->Open();
	}
	else if (CGameManager::StageNo() == 0)
	{
		mpHpGauge->SetShow(false);
		mpStaminaGauge->SetShow(false);
		mpScreenItem->SetShow(false);
		mpScreenItem->Close();
		mpSpikyBallUI->SetShow(false);
		mpSpikyBallUI->Close();
		mpMeat->SetShow(false);
		mpMeat->Close();
	}

	mIsGrounded = false;
	mClimbWall = false;
	mClimbWallTop = false;

	// �����̃I�u�W�F�N�g�Ƃ̏Փ˔���
	CheckUnderFootObject();

	// �����̉��̃G�t�F�N�g�X�V
	UpdateStepSmoke();

	// �O��̃v���C���[�̍��W���X�V
	mLastPos = Position();
	
	//CDebugPrint::Print("mIStartStage2:%s\n", mIsStartStage2 ? "true" : "false");
	//CDebugPrint::Print("mIStartStage3:%s\n", mIsStartStage3 ? "true" : "false");
	//CDebugPrint::Print("mMoveDistance:%f\n", mMoveDistance);
	//CDebugPrint::Print("mIsGrounded:%s\n", mIsGrounded ? "true" : "false");
	/*CDebugPrint::Print("mIsGrounded:%s\n", mIsGrounded ? "true" : "false");*/
	//CDebugPrint::Print("mSpeedY:%f\n", mMoveSpeedY);
	//CDebugPrint::Print("Position: %f %f %f\n", Position().X(), Position().Y(), Position().Z());
}

// �A�C�e�����擾
void CPlayer::AddItem(ItemType item)
{
	// �A�C�e����3�����Ă��Ȃ�������A
	// �ǉ�
	if (mInventory[item] <= 3)
	{
		mInventory[item]++;
	}
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

// �Ƃ��{�[���̎g�p
void CPlayer::UseSpikyBall()
{
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
	else if (CGameManager::StageNo() == 0)
	{
		mInventory.erase(item);
	}
}

// �`��
void CPlayer::Render()
{
	// �L�����`��
	CXCharacter::Render();
}