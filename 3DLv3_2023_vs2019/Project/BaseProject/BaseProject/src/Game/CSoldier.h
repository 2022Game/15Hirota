#ifndef CSOLDIER_H
#define CSOLDIER_H

//�L�����N�^�N���X�̃C���N���[�h
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CRideableObject.h"
#include "CEffect.h"

class CGun;
class CBullet;
class CPlayer;
class CSoldierFrame;
class CSoldierGauge;
class CExclamationMark;

/*
�\���W���[�N���X
�L�����N�^�N���X���p��
*/

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

	// �\���W���[�̕����������_���ɕύX���鏈��
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

	// �\���W���[������Ɉړ������鏈��
	void Move();

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
	static CSoldier* spInstance;


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

	// �e���f��
	CGun* mpGun;

	// �t���[��
	CSoldierFrame* mpFrame;
	// �Q�[�W
	CSoldierGauge* mpGauge;
	// �r�b�N���}�[�N
	CExclamationMark* mpExclamationMark;

	///////////////////////////////////////////////////////


	//// ��Ԋ֘A /////////////////////////////////////////
	
	// �ҋ@���
	void UpdateIdle();
	// �U��
	void UpdateAttack();
	// �U���I���҂�
	void UpdateAttackWait();
	// �W�����v�J�n
	void UpdateJumpStart();
	// �W�����v��
	void UpdateJump();
	// �W�����v�I��
	void UpdateJumpEnd();
	// �v���C���[����
	void UpdateDiscovery();
	// �ǐ�
	void UpdateChase();
	// �L�b�N
	void UpdateKick();
	// �L�b�N�I��
	void UpdateKickWait();
	// �G�C������
	void UpdateAimDwon();
	// �v���C���[�̍U��Hit
	void UpdateHit();
	// ���S
	void UpdateDeth();
	// ���S�����I��
	void UpdateDethEnd();
	// �p�j����
	void UpdateWander();
	// �o�b�N�X�e�b�v
	void UpdateBackStep();

	// ���
	enum class EState
	{
		eIdle,		// �ҋ@
		eAttack,	// �U��
		eAttackWait,// �U���I���҂�
		eDiscovery,	// �v���C���[����
		eChase,		// �ǐ�
		eKick,		// �L�b�N
		eKickWait,	// �L�b�N�I��
		eAimDwon,	// �G�C������
		eHit,		// �_���[�WHit
		eDeth,		// ���S
		eDethEnd,	// ���S�I��
		eWander,	// �p�j����
		eBackStep,	// �o�b�N�X�e�b�v
		eJumpStart,	// �W�����v�J�n
		eJump,		// �W�����v��
		eJumpEnd,	// �W�����v�I��
	};
	// ��ԕύX
	void ChangeState(EState state);
	// �v���C���[�̏��
	EState mState;
	// ����I�u�W�F�N�g�ɏ���Ă��邩
	CTransform* mpRideObject;

	//////////////////////////////////////////////////////////


	//// �A�j���[�V�����֘A //////////////////////////////////
	
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
		eJumpEnd,	// �W�����v�I��
		eJumpStart,	// �W�����v�J�n
		eJump,		// �W�����v��

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

	//////////////////////////////////////////////////////////


	//// �x�N�g���֘A ////////////////////////////////////////

	// �\���W���[�̌������
	CVector mTargetDir;
	// �ړ����x
	CVector mMoveSpeed;
	// �����ʒu�̕ۑ�
	CVector mInitialPosition;

	//////////////////////////////////////////////////////////
	

	//// �ϐ��֘A ////////////////////////////////////////////
	
	// �e�̒e�̊J�n�l
	int mTimeShot;
	// �e�̒e�̏I���l
	int mTimeShotEnd;
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �������Ԍv���p
	float mElapsedTime_End;
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

	// �v���C���[����������
	bool IsFoundPlayer() const;

	//////////////////////////////////////////////////////////
};
#endif