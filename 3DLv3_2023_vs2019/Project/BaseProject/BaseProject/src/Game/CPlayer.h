#pragma once

//�L�����N�^�N���X�̃C���N���[�h
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CRideableObject.h"
#include "CColliderSphere.h"
#include "CColliderCapsule.h"
#include "CCutInDeath.h"
#include "CCutInClear.h"
#include <list>
#include <map>

class CUIGauge;
class CStaminaGauge;
class CMajicSword;
class CBullet;
class CClimbWall;
class CWireMeshClimbWall;
class CWireMeshMoveClimbWall;
class CFlamethrower;
class CStage3;
class CImage;
class CSound;
class CCutInDeath;
class CCutInClear;
class CCutInResult;
class CCutInDeathJump;
class CScreenItem;
class CSpikyBallUI;
class CSmoke;
class CHealingUpBuffs;
class CSeesaw;
class CMeatUI;
class CMetalLadder;
class COperationUI;
class CSpikyBall;

#define DEFOLT_CAMERA CVector(0.0f,50.0f,75.0f);

/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CXCharacter
{
public:
	// �v���C���[�������Ă���A�C�e���̃��X�g
	enum class ItemType
	{
		NONE,		// �Ȃɂ��ێ����Ă��Ȃ�

		INVINCIBLE,	// ���G�A�C�e��
		HEALING,	// �񕜃A�C�e��
		ATTACK_UP,	// �U���̓A�b�v�A�C�e��
		DEFENSE,	// �h��̓A�b�v�A�C�e��
		ESPIKYBALL,	// �Ƃ��{�[���A�C�e��
	};
	// �C���x���g�����Ǘ�
	std::map<ItemType, int> mInventory;
	// �A�C�e�����擾
	void AddItem(ItemType item);
	// �擾�����A�C�e���𔻒�
	bool HasItem(ItemType item);
	// �v���C���[�̃A�C�e�����ꊇ�폜
	void ClearItems();
	// �A�C�e���̎擾�̏����t��������s�����߂̏���
	void PickUpItem(ItemType item);
	// ���G�A�C�e���̎g�p
	void UseInvincibleItem();
	// �񕜖�A�C�e���̎g�p
	void UseHealingItem();
	// �U���̓A�b�v�A�C�e���̎g�p
	void UseAttackPotion();
	// �Ƃ��{�[���̎g�p
	void UseSpikyBall();
	// �C���x���g���������̃A�C�e�����폜
	void RemoveItem(ItemType item);

	//�C���X�^���X�̃|�C���^�̎擾
	static CPlayer* Instance();

	// �R���X�g���N�^
	CPlayer();
	// �f�X�g���N�^
	~CPlayer();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// damage == �󂯂�_���[�W
	void TakeDamage(int damage) override;

	// recovery == ��
	void TakeRecovery(int recovery) override;

	// ���G��Ԃɂ���(�R���C�_�[���I�t�ɂ���)
	void TakeInvincible() override;

	// attack == �U����
	void TakeAttackPotion(int attack) override;


	// ���x������
	// ���x���A�b�v
	void LevelUp();
	// ���x���ύX
	void ChangeLevel(int level);

	//	��邱�Ƃ��ł���I�u�W�F�N�g���폜���ꂽ�Ƃ��̏���
	void DeleteRideableObject(CTransform* rideObj);

	// �X�e�[�W�J�n���̈ʒu��ݒ�
	void SetStartPosition(const CVector& pos);

	// hp�擾
	int GetHp();
	int GetMaxHp();

	// �W�����v���������ǂ���
	bool IsJumping();
	// �U���������ǂ���
	bool IsAttack();
	// ���S�������ǂ���(mIsDeath)
	bool IsDeath();
	// ���S�������ǂ���(mDeath)
	bool IsMDeath();

	// �X�e�[�W1���N���A�������ǂ���
	bool IsStage1Clear();
	// �X�e�[�W2���N���A�������ǂ���
	bool IsStage2Clear();
	// �X�e�[�W3���N���A�������ǂ���
	bool IsStage3Clear();
	// �X�e�[�W4���N���A�������ǂ���
	bool IsStage4Clear();
	// �X�e�[�W���N���A�������ǂ���
	bool IsStageClear();

	// �X�e�[�W�t���O��false�ɂ���֐�
	void StageFlagfalse();

	// �X�e�[�W�ɓ����悤�ɂ���t���O
	// �X�e�[�W2�ɓ���邩�ǂ����̃t���O
	bool IsStartStage2();
	// �X�e�[�W3�ɓ���邩�ǂ����̃t���O
	bool IsStartStage3();
	// �X�e�[�W4�ɓ���邩�ǂ����̃t���O
	bool IsStartStage4();

	// �U���̓A�b�v�A�C�e�����g�p�������ǂ���
	bool IsAttackItem();
	// �񕜃A�b�v�A�C�e�����g�p�������ǂ���
	bool IsHealingItem();

	// �Ƃ��{�[�����g�p���邩�ǂ���
	bool IsSpikyBall();
	// �Ƃ��{�[�����o�������Ă��邩�ǂ���
	bool IsSpikyBallAppearance();
	// �Ƃ��{�[���̃��`���[�W����
	float GetSpikyTime() const;
	float GetSpikyBallSpeed() const;
	float GetSpikyBallDistance() const;
	float GetSpikyBallInitialVelocityY() const;


	// ���̃N���X�Ŏg���Ă����public�ɒu���Ă���
	// �W�����v�J�n1
	void UpdateJumpStart();
	// �W�����v��1
	void UpdateJump();
	// �W�����v�I��1
	void UpdateJumpEnd();
	// ���˂�J�n
	void UpdateJumpingStart();
	// ���˂�
	void UpdateJumping();
	// ���˂�I��
	void UpdateJumpingEnd();
	// ��ђ��˂�J�n
	void UpdateHighJumpingStart();
	// ��ђ��˂�
	void UpdateHighJumping();
	// ��ђ��˂�I��
	void UpdateHighJumpingEnd();
	// �ړI�ʒu�܂ŃW�����v�J�n
	void UpdateTargetPositionStart();
	// �ړI�ʒu�܂ŃW�����v
	void UpdateTargetPosition();
	// �ړI�ʒu�܂ŃW�����v�I��
	void UpdateTargetPositionEnd();
	// ���˕Ԃ����鏈��
	void UpdateReflection();

	// ���S
	void UpdateDeath();
	// ���S�����I��
	void UpdateDeathEnd();

	// �w�肳�ꂽ�ʒu�܂ňړ��J�n
	void MoveTo(const CVector& pos);
	// �w�肳�ꂽ�ʒu�܂ł̈ړ����o���邩�ǂ���
	bool CanMoveTo() const;
	// �w�肳�ꂽ�ԍ��̃X�e�[�W���J�n
	void StartStage(int stageNo);

	// �ړ����x���擾
	CVector Velocity() const;

	// �X�V
	void Update();
	// �`��
	void Render();
	
private:
	// ���f���E�|�C���^�[�E�f�ފ֘A
	// �J�����֘A
	// ��Ԋ֘A
	// �A�j���[�V�����֘A
	// �x�N�g���֘A
	// �L�[���͊֘A
	// �ϐ��֘A

	// �v���C���[�̃C���X�^���X
	static CPlayer* spInstance;

	//// ���f���E�|�C���^�[�E�f�ފ֘A /////////////////////////////////
	
	// �R���C�_�[
	// �c�̃R���C�_�[���C��
	CColliderLine* mpColliderLine;
	// �ꎞ�I�ȓ����蔻������R���C�_�[
	// �J�v�Z���R���C�_�[������������ύX
	CColliderCapsule* mpColliderCapsule;
	//�_���[�W���󂯂�R���C�_
	CColliderSphere* mpDamageCol;
	// �o���R���C�_�[�Ƃ̓����蔻������R���C�_�[
	CColliderLine* mpClimbCol;

	// �I�u�W�F�N�g�A�C�e��
	// �}�W�b�N�\�[�h���f��
	CMajicSword* mpSword;

	// �Ƃ��Ƃ��{�[��
	CSpikyBall* mpSpiky1;
	CSpikyBall* mpSpiky2;
	
	// UI
	// HP�Q�[�W
	CUIGauge* mpHpGauge;
	// �X�^�~�i�Q�[�W
	CStaminaGauge* mpStaminaGauge;
	// �X�N���[���A�C�e���摜
	CScreenItem* mpScreenItem;
	// �Ƃ��{�[���摜
	CSpikyBallUI* mpSpikyBallUI;
	// ���A�C�e���摜
	CMeatUI* mpMeat;

	COperationUI* mpClimbUI;

	// SE
	// ���̐U�肩�����U������SE
	CSound* mpSlashSE;
	// �G�̍U����������������SE
	CSound* mpHitDamageSE;

	// �G�t�F�N�g
	// �Ή����˃G�t�F�N�g
	CFlamethrower* mpFlamethrower;
	// �񕜃o�teffect
	CHealingUpBuffs* mpHealingUpBuffs;
	
	// �ǂ̃|�C���^�[
	// �o���Ă���ǂ̃|�C���^�[
	CClimbWall* mpClimbWall;
	// �o���Ă�����Ԃ̃|�C���^�[
	CWireMeshClimbWall* mpWireWall;
	// �o���Ă��铮�����Ԃ̃|�C���^�[
	CWireMeshMoveClimbWall* mpWireMoveWall;
	// �o���Ă�������̒�q�̃|�C���^�[
	CMetalLadder* mpMetalLadder;

	///////////////////////////////////////////////////////

	//// �I�u�W�F�N�g�֘A /////////////////////////////////

	// �����̃I�u�W�F�N�g�̃|�C���^�[
	CObjectBase* mpUnderFootObject;

	void CheckUnderFootObject();

	///////////////////////////////////////////////////////

	//// �v���C���[�̃G�t�F�N�g�֘A ///////////////////////

	/// <summary>
	/// �����ɉ��̃G�t�F�N�g�𔭐�
	/// </summary>
	void PlayStepSmoke();
	/// <summary>
	/// �����̉��G�t�F�N�g�̍X�V
	/// </summary>
	void UpdateStepSmoke();
	/// <summary>
	/// �����̉��G�t�F�N�g��\�������Ԃ��ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsEnableStepSmoke() const;

	// ���̃��X�g
	std::list<CSmoke*> mSmokeList;

	///////////////////////////////////////////////////////

	//// �J�����֘A ///////////////////////////////////////

	// ���S���̃J����
	CCutInDeath* mpCutInDeath;
	// �X�e�[�W�N���A���̃J����
	CCutInClear* mpCutInClear;
	// ���U���g���̃J����
	CCutInResult* mpCutInResult;
	// ���S�W�����v���̃J����
	CCutInDeathJump* mpCutInDeathJump;

	///////////////////////////////////////////////////////
	

	//// ��Ԋ֘A /////////////////////////////////////////
	
	// �������̏��
	void UpdateReady();
	// �ŏ��̃A�N�V����
	void UpdateFirstAction();
	// �ҋ@���
	void UpdateIdle();
	// ��~���
	void UpdateStop();
	// �ړ����
	void UpdateMove();
	// �_�b�V���I��
	void UpdateDashEnd();
	// �U��
	void UpdateAttack();
	// �U���I���҂�
	void UpdateAttackWait();
	// ���U���J�n
	void UpdateAttackStrongStart();
	// ���U��
	void UpdateAttackStrong();
	// ���U���I���҂�
	void UpdateAttackStrongWait();
	// �_�b�V���A�^�b�N
	void UpdateDashAttack();
	// �_�b�V���A�^�b�N�I��
	void UpdateDashAttackWait();
	//����J�n
	void UpdateRotate();
	//����I���҂�
	void UpdateRotateEnd();
	// �N���A
	void UpdateClear();
	// �N���A�I��
	void UpdateClearEnd();
	// ���U���g���
	void UpdateResult();
	// ���U���g�I�����
	void UpdateResultEnd();
	// �ċN
	void UpdateReStart();
	// �G�̍U��Hit
	void UpdateHit();
	// �G�̒eHit
	void UpdateHitBullet();
	// �G�̌��U��hit
	void UpdateHitSword();
	// �_���[�W���󂯂�(�I�u�W�F�N�g)
	void UpdateHitObj();
	// �����_���[�W�I�u�W�F�N�g
	void UpdateFallDamage();
	// �o����
	void UpdateClimb();
	// ����܂œo����
	void UpdateClimbedTop();
	// ������q�ɓo����
	void UpdateMetalLadder();
	// ������q�̒���ɓo�������
	void UpdateMetalLaddertop();
	// ���Ԃɓo����
	void UpdateWireClimb();
	// ���Ԃ̒���ɓo�������
	void UpdateWireClimbedTop();
	// �������
	void UpdateFalling();
	// �����オ��
	void UpdateStandUp();
	// �X�e�[�W�J�n���̃W�����v�J�n
	void UpdateStartStageJumpStart();
	// �X�e�[�W�J�n���̃W�����v
	void UpdateStartStageJump();
	// �X�e�[�W�J�n���̃W�����v�I��
	void UpdateStartStageJumpEnd();
	// ���U���g�O�̃W�����v�J�n
	void UpdateResultJumpStart();
	// ���U���g�O�̃W�����v
	void UpdateResultJump();
	// ���U���g�O�̃W�����v�I��
	void UpdateResultJumpEnd();
	// �_�b�V���W�����v�X�^�[�g
	void UpdateDashJumpStart();
	// �_�b�V���W�����v
	void UpdateDashJump();
	// �_�b�V���W�����v�I��
	void UpdateDashJumpEnd();
	// �w�肵���ʒu�܂ňړ�����
	void UpdateMoveTo();
	// ���S�W�����v�J�n
	void UpdateDeathJumpStart();
	// ���S�W�����v
	void UpdateDeathJump();
	// ���S�W�����v�I��
	void UpdateDeathJumpEnd();
	// restart���
	void UpdateRestart();
	// restart
	void UpdateRestartEnd();

	// �R���C�_�[�̎��Ԍv��
	void CColliderTime();
	// �_�ł��鎞�Ԍv���p
	void CDamageColorTime();
	// �A�j���[�V�����I���̗͔̑��菈��
	void CHPJudgment();
	// �W�����v���ɑ̗͂�0�ȉ��ɂȂ����ꍇ�̏���
	void JumpingHpJudgment();
	// �X�e�[�W�N���A���̃A�C�e���폜����
	void ItemDeletion();

	// �v���C���[�̏��
	enum class EState
	{
		eReady,				 // ������
		eFirstAction,		 // �ŏ��̃A�N�V����
		eIdle,				 // �ҋ@
		eStop,				 // ��~
		eClearJump,			 // ���U���g�O�̃A�j���[�V����
		eAttack,			 // �U��
		eAttackStrongStart,	 // ���U���J�n
		eAttackStrong,		 // ���U��
		eAttackDash,		 // �_�b�V���A�^�b�N
		eAttackWait,		 // �U���I���҂�
		eAttackStrongWait,	 // ���U���I���҂�
		eAttackDashWait,	 // �_�b�V���A�^�b�N�I���҂�
		eJumpStart,			 // �W�����v�J�n
		eJump,				 // �W�����v��
		eJumpEnd,			 // �W�����v�I��
		eJumpingStart,		 // ���˂�J�n
		eJumping,			 // ���˂�
		eJumpingEnd,		 // ���˂�I��
		eHighJumpingStart,	 // ��ђ��˂�J�n
		eHighJumping,		 // ��ђ��˂�
		eHighJumpingEnd,	 // ��ђ��˂�I��
		eRotate,			 // ����J�n
		eRotateEnd,			 // ����I���҂�
		eDashEnd,			 // �_�b�V���I��
		eClear,				 // �N���A���
		eClearEnd,			 // �N���A�I��
		eResult,			 // ���U���g���	
		eResultEnd,			 // ���U���g�I�����
		eDeath,				 // ���S
		eDeathEnd,			 // ���S�I��
		eReStart,			 // �ċN
		eHit,				 // �_���[�W�q�b�g
		eHitBullet,			 // �G�̒e�q�b�g
		eHitSword,			 // �G�̌��q�b�g
		eHitObj,			 // �_���[�W���󂯂�(�I�u�W�F�N�g)
		eFallDamege,		 // �����_���[�W
		eClimb,				 // �o����
		eClimbedTop,		 // ����܂œo����
		eMetalLadder,		 // ������q�ɓo����
		eMetalLadderTop,	 // ������q�̒���܂œo����
		eWireClimb,			 // ���Ԃɓo����
		eWireClimbedTop,	 // ���Ԃ̒���܂œo����
		eFalling,			 // �������
		eStandUp,			 // �����オ��
		eStartStageJumpStart,// �X�e�[�W�J�n���̃W�����v�J�n
		eStartStageJump,	 // �X�e�[�W�J�n���̃W�����v
		eStartStageJumpEnd,	 // �X�e�[�W�J�n���̃W�����v�I��
		eResultJumpStart,	 // ���U���g�O�̃W�����v�J�n
		eResultJump,		 // ���U���g�O�̃W�����v
		eResultJumpEnd,		 // ���U���g�O�̃W�����v�I��
		eDashJumpStart,		 // �_�b�V���W�����v�J�n
		eDashJump,			 // �_�b�V���W�����v
		eDashJumpEnd,		 // �_�b�V���W�����v�I��
		eMoveTo,			 // �w�肵���ʒu�܂ňړ�����
		eTargetStart,		 // �ړI�ʒu�܂ŃW�����v�J�n
		eTarget,			 // �ړI�ʒu�܂ŃW�����v
		eTargetEnd,			 // �ړI�ʒu�܂ŃW�����v�I��
		eDeathJumpStart,	 // ���S�W�����v�J�n
		eDeathJump,			 // ���S�W�����v
		eDeathJumpEnd,		 // ���S�W�����v�I��
		eRestart,			 // restart���
		eRestartEnd,		 // restart�I�����
		eReflection,		 // ���˕Ԃ��Ă�����
	};
	// ���݂̏�Ԃ�؂�ւ�
	void ChangeState(EState state);
	// �v���C���[�̏��
	EState mState;
	CTransform* mpRideObject;

	///////////////////////////////////////////////////////
	
	
	//// �A�j���[�V�����֘A ///////////////////////////////

	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		None = -1,

		eTPose,			// T�|�[�Y
		eIdle,			// �x�e
		eWalk,			// ���s
		eAttack,		// �U��
		eAttackStrong,	// ���U��
		eAttackDash,	// �_�b�V���A�^�b�N
		eJumpStart,		// �W�����v�J�n
		eJump,			// �W�����v��
		eJumpEnd,		// �W�����v�I��
		eDashJumpStart,	// �_�b�V���W�����v�J�n
		eDashJump,		// �_�b�V���W�����v
		eDashJumpLoop,	// �_�b�V���W�����v���[�v
		eDashJumpEnd,	// �_�b�V���W�����v�I��
		eDash,			// �_�b�V��
		eDashStop,		// �_�b�V���I��
		eRotate,		// ���
		eGuts,			// �K�b�c�|�[�Y
		eHit,			// �G�̍U��Hit
		eHitJ,			// �G�̎�U��Hit
		eDeath,			// ���S
		eClimb,			// �ǂ�o��
		eClimbedTop,	// �ǂ�o��؂�����
		eFalling,		// �������
		eFallingFlat,	// ������Ԃ��璅�n����
		eStandUp,		// �����オ��

		Num
	};

	// �A�j���[�V�����؂�ւ�
	void ChangeAnimation(EAnimType type);

	// �A�j���[�V�����f�[�^
	struct AnimData
	{
		std::string path;	// �A�j���[�V�����f�[�^�̃p�X
		bool loop;			// ���[�v���邩�ǂ���
		float frameLength;	// �A�j���[�V�����̃t���[����
	};
	// �A�j���[�V�����f�[�^�̃e�[�u��
	static const AnimData ANIM_DATA[];

	///////////////////////////////////////////////////////


	//// �x�N�g���֘A /////////////////////////////////////

	CVector mMoveSpeed;			// �ړ����x(X,Z)
	CVector mStartPos;			// �v���C���[�̏����ʒu
	CVector mGroundNormal;		// �ݒu���Ă���n�ʂ̖@��
	CVector mClimbNormal;		// �o���Ă���ǂ̖@��
	CVector mReflectionNormal;	// ���˂���ǂ̖@��
	CVector mClimbedStartPos;	// ����܂œo��؂������̍��W
	CVector mClimbedMovedUpPos;	// ����܂œo��؂�����̏�����ړ���̍��W
	CVector mClimbedMovedPos;	// ����܂œo��؂�����̈ړ���̍��W
	CVector mMoveStartPos;		// �w�肳�ꂽ�ʒu�܂ňړ�����Ƃ��̈ړ��J�n�ʒu
	CVector mMoveTargetPos;		// �w�肳�ꂽ�ʒu�܂ňړ�����Ƃ��̈ړ��I���ʒu
	CVector mLastPos;			// �v���C���[�̑O��̈ʒu
	CVector mAttackStrongPos;	// ���U���J�n�ʒu

	///////////////////////////////////////////////////////


	//// �L�[���͊֘A /////////////////////////////////////

	/// <summary>
	/// �L�[�̓��͏�񂩂�ړ��x�N�g�������߂�
	/// </summary>
	/// <returns></returns>
	CVector CalcMoveVec() const;
	/// <summary>
	/// �L�[�̓��͏�񂩂�ǈړ��x�N�g�������߂�
	/// </summary>
	/// <returns></returns>
	CVector ClimbMoveVec() const;
	/// <summary>
	/// �L�[�̓��͏�񂩂�ǈړ��x�N�g��(�㉺)�����߂�
	/// </summary>
	/// <returns></returns>
	CVector ClimbMoveUpVec() const;
	/// <summary>
	/// �v���C���[���A�N�V�������N�����邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsEnableAction() const;

	///////////////////////////////////////////////////////


	//// �ϐ��֘A /////////////////////////////////////////

	// ��ԓ��̃X�e�b�v
	int mStateStep;

	// �v������
	float mElapsedTime;
	// �v�����ԏI��
	float mElapsedTimeEnd;
	// �Ƃ��{�[���v������
	float mSpikTime;
	// �Ƃ��{�[�����`���[�W����
	float mSpikRechargeTime;
	// �_�Ŏ��Ԍv���p
	float mBlinkElapsedTime;
	// �R���C�_�[�̌v������
	float mColElapsedTime;
	// ���G��ԊJ�n����
	float mInvincibleStartTime;
	// �Ǔo�蒆�̃X�^�~�i�v������
	float mClimbStaminaTime;
	// �ŏ��̃_�b�V���̌v������
	float mStartDashTime;
	// ��������܂�����
	float mWeaponTime;
	// �d�͂�W�����v�ɂ��Y���̈ړ����x
	float mMoveSpeedY;
	// �v���C���[�̑傫���ύX�v������
	float mScaleTime;
	// �������I�������̌o�ߎ���
	float mStageElapsedTime;
	// ���U���g�W�����v�̌o�ߎ���
	float mResultElapsedTime;
	// �v���C���[���ړ���������
	float mMoveDistance;
	// ���G�G�t�F�N�g�̌v������
	float mInvincibleTime;
	// �U���G�t�F�N�g�̌v������
	float mAttackTime;
	// �񕜃G�t�F�N�g�̌v������
	float mHealingTime;
	// �o���Ă����ԂŒ��n���Ă��邩�ǂ����̌v���p
	float mClimbTime;
	// ���ˈړ�����
	float mReflectTime;

	// �ڒn���Ă��邩�ǂ���
	bool mIsGrounded;
	// ���G���ǂ���
	bool mInvincible;
	// �X�^�~�i������l�ɓ��B�����ꍇ�̃t���O
	bool mStaminaDepleted;
	// �X�^�~�i�������l�ɓ��B�����ꍇ�̃t���O
	bool mStaminaLowerLimit;
	// �_���[�W��^����t���O
	bool mDamageObject;
	// �_���[�W��^����t���O(�G)
	bool mDamageEnemy;
	// �񕜂�����
	bool mHpHit;
	// �X���b�V����SE���Đ�������
	bool mIsPlayedSlashSE;
	// �U��������������
	bool mIsPlayedHitDamageSE;
	// �U������
	bool mIsAttack;
	// �_�b�V����Ԃ�
	bool mDash;
	// �ǂ�o���Ă��邩
	bool mClimb;
	// �o���ǂɐG��Ă��邩
	bool mClimbWall;
	// �o���ǂ̒���ɐG��Ă��邩
	bool mClimbWallTop;
	// �W�����v��������
	bool mIsJumping;
	// ���Ԓn�_
	bool mSavePoint1;
	// ���Ԓn�_2
	bool mSavePoint2;
	// �X���b�V���G�t�F�N�g��炵����
	bool mIsSpawnedSlashEffect;
	// �����_���[�W���󂯂���
	bool mFallDamage;
	// �_�b�V���W�����v�Ɉڍs�ł��邩�ǂ���
	bool mIsDashJump;
	// ���S������
	bool mDeath;
	// ���N���X�Ɏ��S�����ǂ�����`����悤
	bool mIsDeath;
	// �U���̓A�b�v�A�C�e�����d�l������
	bool mIsAttackItem;
	// �̗͉񕜃A�C�e�����g�p������
	bool mIsHealingItem;
	// ���G�A�C�e�����g�p������


	// �_���[�W���󂯂����ǂ���
	bool mDamaged;
	// �Ƃ��Ƃ��{�[�����g�p���邩�ǂ���
	bool mSpikyBall;
	// �Ƃ��Ƃ��{�[�����o�������Ă��邩
	bool mSpik1;
	bool mSpik2;


	// ���N���X
	// �X�e�[�W1���N���A������
	bool mStage1Clear;
	// �}�l�[�W���[�N���X�ɓ`����p
	bool mIsStage1Clear;
	// �X�e�[�W2���N���A������
	bool mStage2Clear;
	// �}�l�[�W���[�N���X�ɓ`����p
	bool mIsStage2Clear;
	// �X�e�[�W3���N���A������
	bool mStage3Clear;
	// �}�l�[�W���[�N���X�ɓ`����p
	bool mIsStage3Clear;
	// �X�e�[�W4���N���A������
	bool mStage4Clear;
	// �}�l�[�W���[�N���X�ɓ`����p
	bool mIsStage4Clear;
	// (�S�ẴX�e�[�W)�N���A�������}�l�[�W���[�N���X�ɓ`����悤
	bool mIsStageClear;

	// �X�e�[�W1�ɓ��邩�ǂ���
	bool mStartStage1;
	// �X�e�[�W2�ɓ��邩�ǂ���
	bool mStartStage2;
	// �X�e�[�W3�ɓ��邩�ǂ���
	bool mStartStage3;
	// �X�e�[�W4�ɓ��邩�ǂ���
	bool mStartStage4;

	// ���N���X�Ŋm�F�p
	// �X�e�[�W2�ɓ���邩(�ʃN���X�p)
	bool mIsStartStage2;
	// �X�e�[�W3�ɓ���邩(�ʃN���X�p)
	bool mIsStartStage3;
	// �X�e�[�W4�ɓ���邩(�ʃN���X�p)
	bool mIsStartStage4;

	///////////////////////////////////////////////////////
};
