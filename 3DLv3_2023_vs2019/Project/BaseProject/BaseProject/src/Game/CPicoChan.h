#ifndef CPICOCHAN_H
#define CPICOCHAN_H

#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderCapsule.h"
#include "CRideableObject.h"
#include "CEffect.h"

class CPicoSword;
class CPicoChanUI;

// �s�R�����N���X
class CPicoChan : public CXCharacter
{
public:

	//�C���X�^���X�̃|�C���^�̎擾
	CPicoChan* Instance();

	// �R���X�g���N�^
	CPicoChan();
	// �f�X�g���N�^
	~CPicoChan();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
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
	/// <param name="level">�\���W���[���x��</param>
	void ChangeLevel(int level);

	// �s�R�����̕����������_���ɕύX���鏈��
	void ChangeDerection();

	// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
	void UpdateGaugeAndFrame();

	//// �r�b�N���}�[�N�̕\���̊m�F�����鏈��
	//void UpdateExclamation();

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

	// ���S���W�Ɣ͈͂�ݒ�
	void SetCenterPoint(CVector& center, const float radius);

	// �s�R����������Ɉړ������鏈��
	void Move();

	// �U�����J�n���āA����������ǂ���
	bool IsAttack();

	// �X�V
	void Update();
	// �`��
	void Render();

private:

	// �s�R�����̃C���X�^���X
	static CPicoChan* spInstance;

	// �t�B�[���h�Ƃ̓����蔻������R���C�_�[
	CColliderLine* mpLine;
	// �ǂƂ̓����蔻������R���C�_�[
	CColliderCapsule* mpCapsule;
	// �_���[�W���󂯂�R���C�_�[
	CColliderSphere* mpDamageCol;
	// �_���[�W��^����R���C�_�[
	CColliderSphere* mpAttackCol;

	// �}�W�b�N�\�[�h���f��
	CPicoSword* mpSword;

	// UI
	CPicoChanUI* mpUI;


	// �������̏��
	void UpdateReady();
	// �ҋ@���
	void UpdateIdle();
	// �_�b�V�����
	//void UpdateDash();
	// �U�����
	void UpdateAttack();
	// �U���I���҂�
	void UpdateAttackEnd();
	// ��U�����
	void UpdateWeakAttack();
	// ��]�U�����
	void UpdateSpinAttack();
	// ��������o�����
	void UpdateDrawn();
	// ��������܂����
	void UpdatePutAway();
	// �W�����v�J�n
	//void UpdateJumpStart();
	// �W�����v��
	//void UpdateJump();
	// �W�����v�I��
	//void UpdateJumpEnd();
	// �v���C���[����
	void UpdateDiscovery();
	// �ǐ�
	void UpdateChase();
	// �L�b�N
	void UpdateKick();
	// �L�b�N�I��
	void UpdateKickEnd();
	// �v���C���[�̍U��hit
	void UpdateHit();
	// ���S
	void UpdateDeath();
	// ���S�����I��
	void UpdateDeathEnd();
	// �p�j����
	void UpdateWander();
	// �o�b�N�X�e�b�v
	//void UpdateBackStep();

	// ���
	enum class EState
	{
		eReady,		// ������
		eIdle,		// �ҋ@
		eDash,		// ����
		eAttack,	// �U��
		eAttackEnd,	// �U���I��
		eWeakAttack,// ��U��
		eSpinAttack,// ��]�U��
		eAttackWait,// �U���I���҂�
		eDrawn,		// ��������o��
		ePutAway,	// ��������܂�
		eDiscovery,	// �v���C���[����
		eChase,		// �ǐ�
		eKick,		// �L�b�N
		eKickEnd,	// �L�b�N�I��
		eHit,		// �_���[�WHit
		eDeath,		// ���S
		eDeathEnd,	// ���S�I��
		eWander,	// �p�j����
		eBackStep,	// �o�b�N�X�e�b�v
		eJumpStart,	// �W�����v�J�n
		eJump,		// �W�����v��
		eJumpEnd,	// �W�����v�I��
	};
	// ��ԕύX
	void ChangeState(EState state);
	// �s�R�����̏��
	EState mState;
	// ����I�u�W�F�N�g�ɏ���Ă��邩
	CTransform* mpRideObject;

	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		None = -1,

		eTpose,		// T�|�[�Y
		eIdle1,		// Idle1
		eIdle2,		// Idle2
		eWalk,		// ����
		eWeaponWalk,// ���펝������
		eRun,		// ����
		eWeaponDash,// ���펝������
		eBackJump,	// �o�b�N�W�����v
		eDashJump,	// �_�b�V���W�����v
		eDeath1,	// ���S1
		eDeath2,	// ���S2
		eKick,		// �L�b�N
		ePutAway,	// ��������܂�
		eWeaponDraw,// ������o��(��납��)
		eWeakAttack,// ��U��
		eSpinAttack,// ��]�U��
		eTurn180,	// �U��Ԃ�
		eAlert1,	// �x��1(���펝��)
		eAlert2,	// �x��2
		eHit,		// ��e

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

	// �s�R�����̌������
	CVector mTargetDir;
	// �ړ����x
	CVector mMoveSpeed;
	// �����ʒu�̕ۑ�
	CVector mInitialPosition;
	// ���S�_
	CVector mCenterPoint;

	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �������Ԍv���p
	float mElapsedTimeEnd;
	// �����_�����Ԍv�Z
	float mTimeToChange;
	// �L�b�N�̎��Ԍv���p
	float mKickTime;
	// �o�b�N�X�e�b�v�̎��Ԍv��
	float mBackStepTime;
	// �v���C���[�������̎��Ԍv��
	float mDiscoveryTime;
	// �v���C���[�������̏I�����Ԍv��
	float mDiscoveryTimeEnd;
	// ���a
	float mMaxRadius;
	// �ڒn���Ă��邩�ǂ���
	bool mIsGrounded;
	// �L�b�N�̑҂����Ԃ��I��������ǂ���
	bool mKickTimeEnd;
	// �v���C���[�𔭌����Ĉ�莞�Ԍo�������ǂ���
	bool mDiscovery;
	// �v���C���[�𔭌����I�������̎��Ԃ��ǂꂭ�炢�o������
	bool mDiscoveryEnd;
	// �o�b�N�X�e�b�v�����邩
	bool mBackStep;
	// ���a�ɓ�������
	bool mIsLerping;

	bool mDash;
	float mDashTime;
	bool mIsAttack;

	// �v���C���[����������
	bool IsFoundPlayer() const;
};
#endif