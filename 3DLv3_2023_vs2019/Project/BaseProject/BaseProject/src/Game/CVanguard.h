#ifndef CVANGUAD_H
#define CVANGUAD_H

#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CRideableObject.h"

class CExclamationMark;
class CVanguardGauge;
class CMajicSwordEnemy;

/*
���@���K�[�h�N���X
�L�����N�^�N���X���p��
*/

class CVanguard : public CXCharacter
{
public:

	// �C���X�^���X�̃|�C���^�擾
	static CVanguard* Instance();

	// �R���X�g���N�^
	CVanguard();
	// �f�X�g���N�^
	~CVanguard();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂������</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="damage">�󂯂�_���[�W</param>
	void TakeDamage(int damage) override;

	// ���x������
	// ���x���A�b�v
	void LevelUp();
	/// <summary>
	/// ���x���ύX
	/// </summary>
	/// <param name="level">���@���K�[�h���x��</param>
	void ChangeLevel(int level);

	// ���@���K�[�h�̕����������_���ɕύX���鏈��
	void ChangeDerection();

	// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
	void UpdateGaugeAndFrame();

	// �r�b�N���}�[�N�̕\���̊m�F�����鏈��
	void UpdateExclamation();

	// 1%�̊m�������߂鏈��
	bool ShouldTransitionWander();
	// ��L�Ɠ��l
	bool ShouldTransition();

	/// <summary>
	/// 360�x�̊p�x�����߂āAx����y������v�Z����
	/// </summary>
	/// <param name="angleDegrees">�p�x</param>
	/// <returns></returns>
	CVector CalculateDirection(float angleDegrees);

	// ���@���K�[�h������Ɉړ������鏈��
	void Move();

	//�G�̃X�R�A��ݒ�
	static void SetScore(int score);
	//�G�̃X�R�A���擾
	static int GetScore();


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

	// ���@���K�[�h�̃C���X�^���X
	static CVanguard* spInstance;
	// ���@���K�[�h�̃X�R�A
	static int sScore;


	//// ���f���E�f�ފ֘A /////////////////////////////////

	// �t�B�[���h�Ƃ̓����蔻������R���C�_�[
	CColliderLine* mpColliderLine;
	// �ꎞ�I�ȓ����蔻������R���C�_�[
	// �J�v�Z���R���C�_������������ύX
	CColliderSphere* mpColliderSphere;
	// �_���[�W���󂯂�R���C�_�[
	CColliderSphere* mpDamageCol;
	// �_���[�W��^����R���C�_�[
	CColliderSphere* mpAttackCol;

	// �}�W�b�N�\�[�h���f��
	CMajicSwordEnemy* mpSword;

	// �Q�[�W
	CVanguardGauge* mpGauge;
	// �r�b�N���}�[�N
	CExclamationMark* mpExclamationMark;

	///////////////////////////////////////////////////////


	//// ��Ԋ֘A /////////////////////////////////////////

	// �������̏��
	void UpdateReady();
	// �ҋ@���1
	void UpdateIdle();
	// �ړ����
	void UpdateWalk();
	// �ړ����(Mutant)
	void UpdateWalkMutant();
	// �ړ����(���펝�����)
	void UpdateWalkWeapon();
	// �ړ����(���������)
	void UpdateWalkShield();
	// �ړ����1(�����������)
	void UpdateWalkBackShield1();
	// �ړ����2(�����������)
	void UpdateWalkBackShield2();
	// �_�b�V�����
	void UpdateDash();
	// ��������
	void UpdateDashBrisk();
	// ��������
	void UpdateDashShield();
	// �_�b�V���I��
	void UpdateDashEnd();
	// ����s��
	void UpdateRolling();
	// �W�����v�J�n���
	void UpdateJumpStart();
	// �W�����v��
	void UpdateJump();
	// ����W�����v�J�n���
	void UpdateRunJumpStart();
	// ����W�����v�����
	void UpdateRunJump();
	// �_�b�V���W�����v�J�n���
	void UpdateRunDashJumpStart();
	// �_�b�V���W�����v�����
	void UpdateRunDashJump();
	// �W�����v�I��
	void UpdateJumpEnd();
	// �����オ����
	void UpdateStandUp();
	// ���펝���ҋ@���
	void UpdateIdleWeapon();
	// �U�����
	void UpdateAttack();
	// �X�s���U��1
	void UpdateAttackSpin1();
	// �X�s���U��2
	void UpdateAttackSpin2();
	// �U��グ�U��
	void UpdateAttackSwing();
	// 3�A�U��
	void UpdateAttacks3();
	// �E���L�b�N
	void UpdateAttackKick();
	// �E���L�b�N�I��
	void UpdateAttackKickEnd();
	// �W�����v�U��1
	void UpdateAttackJump1();
	// �W�����v�U��2
	void UpdateAttackJump2();
	// �U���I���҂�
	void UpdateAttackEnd();
	// ��������ɂ��܂�1
	void UpdateSwordSheathing1();
	// ��������ɂ��܂�2
	void UpdateSwordSheathing2();
	// ���\��
	void UpdateShield();
	// ����h��
	void UpdateSwordGuard();
	// ��������o��1
	void UpdateSwordDrawn1();
	// ��������o��2
	void UpdateSwordDrawn2();
	// �������납����o��
	void UpdateSwordBackDrawn();
	// ���_���[�W1
	void UpdateHitSlight1();
	// ���_���[�W2
	void UpdateHitSlight2();
	// ���_���[�W3
	void UpdateHitSlight3();
	// �K�b�c�|�[�Y1
	void UpdateGutsPose1();
	// �K�b�c�|�[�Y2
	void UpdateGutsPose2();
	// �v���C���[����
	void UpdateDiscovery();
	// �ǐ�
	void UpdateChase();
	// �p�j����
	void UpdateWander();
	// ���������
	void UpdateLoseSight();
	// �w����
	void UpdatePointing();
	// ���S���
	void UpdateDeath();
	// ���S��ԏI��
	void UpdateDeathEnd();

	// ���
	enum class EState
	{
		eReady,				// ������
		eIdle,				// �ҋ@���1
		eWalk,				// �ړ����
		eWalkMutant,		// ��������
		eWalkWeapon,		// �������
		eWalkShield1,		// ������
		eWalkBackShield1,	// ��������1
		eWalkBackShield2,	// ��������2
		eDash,				// ����
		eDashBrisk,			// ������
		eDashShield,		// ������
		eDashEnd,			// ����~��
		eRolling,			// ����s��
		eJumpStart,			// �W�����v�J�n
		eJump,				// �W�����v��
		eRunDashJumpStart,	// ����W�����v�J�n
		eRunDashJump,		// ����W�����v��
		eDashJumpStart,		// �_�b�V���W�����v�J�n
		eDashJump,			// �_�b�V���W�����v��
		eJumpEnd,			// �W�����v�I��
		eStandUp,			// �����オ��
		eIdleWeapon,		// ���펝���ҋ@
		eAttack,			// �U�����
		eAttackSpin1,		// �X�s���U��1
		eAttackSpin2,		// �X�s���U��2
		eAttackSwing,		// �U��グ�U��
		eAttacks3,			// 3�A�U��
		eAttackKick,		// �E���L�b�N
		eAttackKickEnd,		// �E���L�b�N�I��
		eAttackJump1,		// �W�����v�U��1
		eAttackJump2,		// �W�����v�U��2
		eAttackEnd,			// �U���I���҂�
		eSwordSheathing1,	// ��������ɂ��܂�1
		eSwordSheathing2,	// ��������ɂ��܂�2
		eShield,			// ���\��
		eSwordGuard,		// ����h��
		eSwordDrawn1,		// ��������o��1
		eSwordDrawn2,		// ��������o��2
		eSwordBackDrawn,	// �������납����o��
		eHitSlight1,		// ���_���[�W1
		eHitSlight2,		// ���_���[�W2
		eHitSlight3,		// ���_���[�W3
		eGutsPose1,			// �K�b�c�|�[�Y1
		eGutsPose2,			// �K�b�c�|�[�Y2
		eDiscovery,			// �v���C���[�𔭌�
		eChase,				// �ǐՏ��
		eWander,			// �p�j���
		eLoseSight,			// ���������
		ePointing,			// �w����
		eDeath,				// ���S
		eDeathEnd,			// ���S�I��
	};
	// ��ԕύX
	void ChangeState(EState state);
	// ���@���K�[�h�̏��
	EState mState;
	// ����I�u�W�F�N�g�ɏ���Ă��邩
	CTransform* mpRideObject;

	///////////////////////////////////////////////////////


	//// �A�j���[�V�����֘A ///////////////////////////////

	enum class EAnimType
	{
		None = -1,

		eTpose,				// T�|�[�Y
		eIdle1,				// �ҋ@���1
		eIdle2,				// �ҋ@���2
		eWalk1,				// �ړ����1
		//eWalkBack1,			// ���ړ�1
		eWalkMutant,		// ��������
		eWalkWeapon,		// �������
		eWalkShield1,		// ������
		eWalkBackShield1,	// ��������1
		eWalkBackShield2,	// ��������2
		eDash,				// ����
		eDashBrisk,			// ������
		eDashShield,		// ������
		eJump,				// �W�����v
		eRunDashJump,		// ����W�����v
		eDashJump,			// �_�b�V���W�����v
		eStandUp,			// �����オ��
		eIdleWeapon,		// ���펝���ҋ@
		eAttackSpin1,		// �X�s���U��1
		eAttackSpin2,		// �X�s���U��2
		eAttackSwing,		// �U��グ�U��
		eAttacks3,			// 3�A�U��
		eAttackKick,		// �E���L�b�N
		eAttackJump1,		// �W�����v�U��1
		eAttackJump2,		// �W�����v�U��2
		eSwordSheathing1,	// ��������ɂ��܂�1
		eSwordSheathing2,	// ��������ɂ��܂�2
		eShield,			// ���\��
		eSwordGuard,		// ����h��
		eSwordDrawn1,		// ��������o��
		eSwordDrawn2,		// ��������o��2
		eSwordBackDrawn,	// �������납����o��
		eRolling,			// ����s��
		eHitSlight1,		// ���_���[�W1
		eHitSlight2,		// ���_���[�W2
		eHitSlight3,		// ���_���[�W3
		eGutsPose1,			// �K�b�c�|�[�Y1
		eGutsPose2,			// �K�b�c�|�[�Y2
		eLoseSight,			// ���������
		ePointing,			// �w����
		eDeath,				// ���S


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

	// ���@���K�[�h�̌������
	CVector mTargetDir;
	// �ړ�����
	CVector mMoveVector;
	// �ړ����x
	CVector mMoveSpeed;
	// �����ʒu�̕ۑ�
	CVector mInitialPosition;

	///////////////////////////////////////////////////////


	//// �ϐ��֘A /////////////////////////////////////////

	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �o�ߎ��Ԋϑ��p
	float mElapsedTime;
	// �������Ԍv���p
	float mElapsedTime_End;
	// �L�b�N�̎��Ԍv��
	float mKickTime;
	// �o�b�N�X�e�b�v�̎��Ԍv��
	float mBackStepTime;
	// �v���C���[�������̎��Ԍv��
	float mDiscoveryTime;
	// �v���C���[�������̏I�����Ԍv��
	float mDiscoveryTime_End;
	// �����_�����Ԍv�Z
	float mTimeToChange;
	// ����̎��Ԍv��
	float mTimeRolling;
	// �ݒu���Ă��邩�ǂ���
	bool mIsGrounded;
	// �L�b�N�̑҂����Ԃ��I���������ǂ���
	bool mKickTimeEnd;
	// �v���C���𔭌����Ĉ�莞�Ԍo�������ǂ���
	bool mDiscovery;
	// �v���C���[�𔭌����I�������̎��Ԃ����q��������
	bool mDiscoveryEnd;
	// ������Ԃ��I������k
	bool mRollingEnd;
	// �_���[�W���󂯂���
	bool mDamage;

	// �v���C���[�����������ǂ���
	bool IsFoundPlayer() const;

	///////////////////////////////////////////////////////
};
#endif