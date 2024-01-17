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
	// �v���C���[�̃C���X�^���X
	static CSoldier* spInstance;


	//// ���f���֘A ///////////////////////////////////////

	// �t�B�[���h�Ƃ̓����蔻������R���C�_�[
	CColliderLine* mpColliderLine;
	// �ꎞ�I�ȓ����蔻������R���C�_�[
	// �J�v�Z���R���C�_������������ύX
	CColliderSphere* mpColliderSphere;
	// �_���[�W���󂯂�R���C�_�[
	CColliderSphere* mpDamageCol;
	// �_���[�W��^����R���C�_�[
	CColliderSphere* mpAttackCol;

	// �e���f���̃|�C���^�[
	CGun* mpGun;

	// UI�̃t���[���̃|�C���^�[
	CSoldierFrame* mpFrame;
	// UI�̃Q�[�W�̃|�C���^�C�[
	CSoldierGauge* mpGauge;

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

	// ���
	enum class EState
	{
		eIdle,		// �ҋ@
		eAttack,	// �U��
		eAttackWait,// �U���I���҂�
		eJumpStart,	// �W�����v�J�n
		eJump,		// �W�����v��
		eJumpEnd,	// �W�����v�I��
		eChase,		// �ǐ�
		eKick,		// �L�b�N
		eKickWait,	// �L�b�N�I��
		eAimDwon,	// �G�C������
		eHit,		// �_���[�WHit
		eDeth,		// ���S
		eDethEnd,	// ���S�I��
		eWander,	// �p�j����
	};
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
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �������Ԍv���p
	float mElapsedTime_End;
	// �����_�����Ԍv�Z
	float mTimeToChange;
	// �ڒn���Ă��邩�ǂ���
	bool mIsGrounded;
	//�v���C���[����������
	bool IsFoundPlayer() const;

	//////////////////////////////////////////////////////////
};
#endif