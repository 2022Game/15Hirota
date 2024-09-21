#ifndef CSOLDIER_H
#define CSOLDIER_H

//�L�����N�^�N���X�̃C���N���[�h
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderCapsule.h"
#include "CRideableObject.h"

class CGun;
class CBullet;
class CPlayer;
class CSoldierFrame;
class CSoldierGauge;
class CExclamationMark;
class CEffect;

// �\���W���[�N���X(�e�^�C�v)
class CSoldier : public CXCharacter
{
public:

	//�C���X�^���X�̃|�C���^�̎擾
	CSoldier* Instance();

	// �R���X�g���N�^
	CSoldier();
	// �f�X�g���N�^
	~CSoldier();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փˏ��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	/// <summary>
	/// ��_���[�W����
	/// </summary>
	/// <param name="damage">�󂯂�_���[�W��</param>
	void TakeDamage(int damage) override;

	// ���x���A�b�v
	void LevelUp();
	/// <summary>
	/// ���x���ύX����
	/// </summary>
	/// <param name="level">���x���ύX��</param>
	void ChangeLevel(int level);

	// �����ݒ�
	// �J�n���̒��S���W�Ɣ͈͂�ݒ�
	void SetCenterPoint(CVector& center, const float radius);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	
	// �\���W���[�̃C���X�^���X
	static CSoldier* spInstance;

	// �ړ�����
	// �\���W���[������Ɉړ������鏈��
	void Move();
	/// <summary>
	/// 360�x�̊p�x�����߂āAx����y������v�Z����
	/// </summary>
	/// <param name="angleDegrees">�p�x</param>
	/// <returns></returns>
	CVector CalculateDirection(float angleDegrees);
	// �\���W���[�̕����������_���ɕύX���鏈��
	void ChangeDerection();

	// �ړ��̏�������
	// �ҋ@��ԂɑJ�ڂ������
	bool WaitingCondition();
	// �p�j��ԂɑJ�ڂ������
	bool WanderingConditions();
	// �v���C���[�ǐՏ���
	bool IsFoundPlayer() const;

	// UI����
	// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
	void UpdateGaugeAndFrame();
	// �r�b�N���}�[�N�̕\���̊m�F�����鏈��
	void UpdateExclamation();

	// ���ԏ���
	// �L�b�N�̑҂�����
	void KickWaitTime();
	// �o�b�N�X�e�b�v�̑҂�����
	void BackStepWaitTime();
	// �v���C���[�𔭌�������̑҂�����
	void DiscoveryWaitTime();

	// �c�̐����R���C�_�[
	CColliderLine* mpColliderLine;
	// �ǂ�I�u�W�F�N�g�Ƃ̓����蔻������R���C�_�[
	CColliderCapsule* mpColliderCapsule;
	// �_���[�W��^����R���C�_�[
	CColliderSphere* mpAttackCol;
	// �_���[�W���󂯂�R���C�_�[
	CColliderSphere* mpDamageCol;

	// �e���f��
	CGun* mpGun;

	// �t���[��
	CSoldierFrame* mpFrame;
	// �Q�[�W
	CSoldierGauge* mpGauge;
	// �r�b�N���}�[�N
	CExclamationMark* mpExclamationMark;

	// �������̏��
	void UpdateReady();
	// �ҋ@���
	void UpdateIdle();

	// �U�����
	void UpdateAttack();
	// �U���I���҂����
	void UpdateAttackWait();
	// �L�b�N���
	void UpdateKick();
	// �L�b�N�I�����
	void UpdateKickWait();
	// �G�C���������
	void UpdateAimDwon();

	// �v���C���[�������
	void UpdateDiscovery();
	// �ǐՏ��
	void UpdateChase();
	// �p�j���
	void UpdateWander();
	// �o�b�N�X�e�b�v���
	void UpdateBackStep();
	
	// �v���C���[�̍U��Hit���
	void UpdateHit();
	// ���S���
	void UpdateDeth();
	// ���S�����I�����
	void UpdateDethEnd();
	
	// ���
	enum class EState
	{
		eReady,		// ������
		eIdle,		// �ҋ@
		eAttack,	// �U��
		eAttackWait,// �U���I���҂�
		eKick,		// �L�b�N
		eKickWait,	// �L�b�N�I��
		eAimDwon,	// �G�C������
		eDiscovery,	// �v���C���[����
		eChase,		// �ǐ�
		eWander,	// �p�j����
		eBackStep,	// �o�b�N�X�e�b�v
		eHit,		// �v���C���[�̍U��Hit
		eDeth,		// ���S
		eDethEnd,	// ���S�I��
	};
	// ��ԕύX
	void ChangeState(EState state);
	// �v���C���[�̏��
	EState mState;
	// ����I�u�W�F�N�g�ɏ���Ă��邩
	CTransform* mpRideObject;

	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		None = -1,

		eTpose,		// T�|�[�Y
		eIdle,		// Idle��
		eRifleIdle,	// ���C�t��Idle��
		eWalk,		// �ړ�
		eAlert,		// �x��
		eAttack,	// �v���C���[�������U��
		eKick,		// �i��
		eReload,	// �����[�h
		eAimDwou,	// �G�C������
		eHit,		// �_���[�WHit
		eDeth,		// ���S
		eBackStep,	// �o�b�N�X�e�b�v

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

	// �\���W���[�̌������
	CVector mTargetDir;
	// �ړ����x
	CVector mMoveSpeed;
	// �����ʒu�̕ۑ�
	CVector mInitialPosition;
	// �J�n���̒��S�_
	CVector mCenterPoint;

	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �e�̒e�̊J�n�l
	int mTimeShot;
	// �e�̒e�̏I���l
	int mTimeShotEnd;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �������Ԍv���p
	float mElapsedTime_End;
	// �����]�����Ԍv���p
	float mChangeTime;
	// �����_�����Ԍv���p
	float mRandomCalculationTime;
	// �L�b�N�̎��Ԍv���p
	float mKickTime;
	// �o�b�N�X�e�b�v�̎��Ԍv���p
	float mBackStepTime;
	// �v���C���[�������̎��Ԍv���p
	float mDiscoveryTime;
	// �v���C���[�������̏I�����Ԍv���p
	float mDiscoveryTimeEnd;
	// �J�n���̔��a�̐ݒ�p
	float mMaxRadius;
	// �ڒn���Ă��邩�ǂ���
	bool mIsGrounded;
	// �L�b�N�̑҂����Ԃ��I��������ǂ���
	bool mKickWaitingEnd;
	// �v���C���[�𔭌����Ĉ�莞�Ԍo�������ǂ���
	bool mDiscovery;
	// �v���C���[�𔭌����I�������̎��Ԃ��ǂꂭ�炢�o�������ǂ���
	bool mDiscoveryEnd;
	// �o�b�N�X�e�b�v�����邩�ǂ���
	bool mBackStep;
	// �J�n���͈͓̔��ɓ��������ǂ���
	bool mEnteredTheRange;

};
#endif