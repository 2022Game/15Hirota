#pragma once

//�L�����N�^�N���X�̃C���N���[�h
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CRideableObject.h"
#include "CColliderSphere.h"
#include "CImage.h"
#include "CSound.h"

class CUIGauge;
class CStaminaGauge;
class CMajicSword;
class CBullet;

#define DEFOLT_CAMERA CVector(0.0f,50.0f,75.0f);

/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/

class CPlayer : public CXCharacter
{
public:

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

	// ���̃N���X�Ŏg���Ă����public�ɒu���Ă���
	// �W�����v�J�n
	void UpdateJumpStart();
	// �W�����v��
	void UpdateJump();
	// �W�����v�I��
	void UpdateJumpEnd();
	// ���˂�
	void UpdateJumpingStart();
	// ���˂Ă�r��
	void UpdateJumping();
	// ���˂�̏I��
	void UpdateJumpingEnd();

	// �X�V
	void Update();
	// �`��
	void Render();
	
private:
	// ���f���E�f�ފ֘A
	// ��Ԋ֘A
	// �A�j���[�V�����֘A
	// �x�N�g���֘A
	// �ϐ��֘A

	// �v���C���[�̃C���X�^���X
	static CPlayer* spInstance;


	//// ���f���E�f�ފ֘A /////////////////////////////////
	
	// �c�̃R���C�_�[���C��
	CColliderLine* mpColliderLine;
	// �ꎞ�I�ȓ����蔻������R���C�_�[
	// �J�v�Z���R���C�_�[������������ύX
	CColliderSphere* mpColliderSphere;
	//�_���[�W���󂯂�R���C�_
	CColliderSphere* mpDamageCol;

	// �}�W�b�N�\�[�h���f��
	CMajicSword* mpSword;
	
	// HP�Q�[�W
	CUIGauge* mpHpGauge;
	// �X�^�~�i�Q�[�W
	CStaminaGauge* mpStaminaGauge;

	// ���̐U�肩�����U������SE
	CSound* mpSlashSE;
	// �G�̍U����������������SE
	CSound* mpHitDamageSE;

	///////////////////////////////////////////////////////
	

	//// ��Ԋ֘A /////////////////////////////////////////
	
	// �������̏��
	void UpdateReady();
	// �ҋ@���
	void UpdateIdle();
	//�_�b�V���I��
	void UpdateDashEnd();
	// �U��
	void UpdateAttack();
	// ���U��
	void UpdateAttackStrong();
	// �U���I���҂�
	void UpdateAttackWait();
	// ���U���I���҂�
	void UpdateAttackStrongWait();
	//����J�n
	void UpdateRotate();
	//����I���҂�
	void UpdateRotateEnd();
	// �N���A
	void UpdateClear();
	// �N���A�I��
	void UpdateClearEnd();
	// ���S
	void UpdateDeath();
	// ���S�����I��
	void UpdateDeathEnd();
	// �ċN
	void UpdateReStart();
	// �G�̍U��Hit
	void UpdateHit();
	// �G�̒eHit
	void UpdateHitBullet();
	// �G�̌��U��hit
	void UpdateHitSword();
	// �v���C���[�̏��
	enum class EState
	{
		eReady,				// ������
		eIdle,				// �ҋ@
		eAttack,			// �U��
		eAttackStrong,		// ���U��
		eAttackWait,		// �U���I���҂�
		eAttackStrongWait,	// �U���I���҂�2
		eJumpStart,			// �W�����v�J�n
		eJump,				// �W�����v��
		eJumpEnd,			// �W�����v�I��
		eJumpingStart,		// ���˂�J�n
		eJumping,			// ���˂�
		eJumpingEnd,		// ���˂�I��
		eRotate,			// ����J�n
		eRotateEnd,			// ����I���҂�
		eDashEnd,			// �_�b�V���I��
		eClear,				// �N���A���
		eClearEnd,			// �N���A�I��
		eDeath,				// ���S
		eDeathEnd,			// ���S�I��
		eReStart,			// �ċN
		eHit,				// �_���[�W�q�b�g
		eHitBullet,			// �G�̒e�q�b�g
		eHitSword,			// �G�̌��q�b�g
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
		eJumpStart,		// �W�����v�J�n
		eJump,			// �W�����v��
		eJumpEnd,		// �W�����v�I��
		eDash,			// �_�b�V��
		eDashStop,		// �_�b�V���I��
		eRotate,		// ���
		eGuts,			// �K�b�c�|�[�Y
		eHit,			// �G�̍U��Hit
		eDeath,			// ���S
		eHitJ,			// �G�̒eHit

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

	CVector mMoveSpeed;		// �ړ����x(X,Z)
	CVector mStartPos;		// �v���C���[�̏����ʒu
	CVector mGroundNormal;	// �ݒu���Ă���n�ʂ̖@��

	///////////////////////////////////////////////////////


	//// �L�[���͊֘A /////////////////////////////////////

	/// <summary>
	/// �L�[�̓��͏�񂩂�ړ��x�N�g�������߂�
	/// </summary>
	/// <returns></returns>
	CVector CalcMoveVec() const;

	///////////////////////////////////////////////////////


	//// �ϐ��֘A /////////////////////////////////////////

	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �v������
	float mElapsedTime;
	// �v�����ԏI��
	float mElapsedTimeEnd;
	// �R���C�_�[�̌v������
	float mElapsedTimeCol;
	// ���G��ԗp�̌v������
	float mInvincibleStartTime;
	// �d�͂�W�����v�ɂ��Y���̈ړ����x
	float mMoveSpeedY;
	// �ڒn���Ă��邩�ǂ���
	bool mIsGrounded;
	// ���G���ǂ���
	bool mInvincible;
	// �X�^�~�i������l�ɓ��B�����ꍇ�̃t���O
	bool staminaDepleted;
	// �X�^�~�i�������l�ɓ��B�����ꍇ�̃t���O
	bool staminaLowerLimit;
	// �_���[�W��^����t���O
	bool damageObject;
	// �_���[�W��^����t���O(�G)
	bool damageEnemy;
	// �񕜂�����
	bool mHpHit;
	// �X���b�V����SE���Đ�������
	bool mIsPlayedSlashSE;
	// �U��������������
	bool mIsPlayedHitDamageSE;

	///////////////////////////////////////////////////////
};
