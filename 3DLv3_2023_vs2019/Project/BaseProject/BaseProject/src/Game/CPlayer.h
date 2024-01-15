#pragma once
//�L�����N�^�N���X�̃C���N���[�h
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CRideableObject.h"
#include "CColliderSphere.h"
#include "CImage.h"

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

	//	��邱�Ƃ��ł���I�u�W�F�N�g���폜���ꂽ�Ƃ��̏���
	void DeleteRideableObject(CTransform* rideObj);

	// �X�e�[�W�J�n���̈ʒu��ݒ�
	void SetStartPosition(const CVector& pos);

	// �������̏��
	void UpdateReady();
	// �ҋ@���
	void UpdateIdle();
	// �U��
	void UpdateAttack();
	// ���U��
	void UpdateAttackStrong();
	// �U���I���҂�1
	void UpdateAttackWait();
	// �U���I���҂�2
	void UpdateAttackWait2();
	// �W�����v�J�n
	void UpdateJumpStart();
	// �W�����v��
	void UpdateJump();
	// �W�����v�I��
	void UpdateJumpEnd();
	//�_�b�V���I��
	void UpdateDashEnd();
	// ���˂�
	void UpdateJumpingStart();
	// ���˂Ă�r��
	void UpdateJumping();
	// ���˂�̏I��
	void UpdateJumpingEnd();
	//����J�n
	void UpdateRotate();
	//����I��
	void UpdateRotateEnd();
	// �N���A
	void UpdateClear();
	// �N���A�I��
	void UpdateClearEnd();
	// ���S
	void UpdateDeth();
	// ���S�����I��
	void UpdateDethEnd();
	// �ċN
	void UpdateReStart();
	// �G�̍U��Hit
	void UpdateHit();
	// �G�̒eHit
	void UpdateHitJ();


	bool CanEvade();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// ���x������
	void LevelUp();	//	���x���A�b�v
	void ChangeLevel(int level);	// ���x���ύX

	// hp�擾
	int GetHp();
	int GetMaxHp();

	// damage == �󂯂�_���[�W
	void TakeDamage(int damage) override;

	// recovery == ��
	void TakeRecovery(int recovery) override;

	// �X�V
	void Update();

	// �`��
	void Render();

private:
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
		eDeth,			// ���S
		eHitJ,			// �G�̒eHit

		Num
	};

	// �A�j���[�V�����؂�ւ�
	void ChangeAnimation(EAnimType type);

	// �v���C���[�̃C���X�^���X
	static CPlayer* spInstance;

	// �A�j���[�V�����f�[�^
	struct AnimData
	{
		std::string path;	// �A�j���[�V�����f�[�^�̃p�X
		bool loop;			// ���[�v���邩�ǂ���
		float frameLength;	// �A�j���[�V�����̃t���[����
	};
	// �A�j���[�V�����f�[�^�̃e�[�u��
	static const AnimData ANIM_DATA[];

	// �v���C���[�̏��
	enum class EState
	{
		eReady,			// ������
		eIdle,			// �ҋ@
		eAttack,		// �U��
		eAttackStrong,	// ���U��
		eAttackWait,	// �U���I���҂�
		eAttackWait2,	// �U���I���҂�2
		eJumpStart,		// �W�����v�J�n
		eJump,			// �W�����v��
		eJumpEnd,		// �W�����v�I��
		eJumpingStart,	// ���˂�J�n
		eJumping,		// ���˂�
		eJumpingEnd,	// ���˂�I��
		eRotate,		// ����J�n
		eRotateEnd,		// ����I���҂�
		eDashEnd,		// �_�b�V���I��
		eClear,			// �N���A���
		eClearEnd,		// �N���A�I��
		eDeth,			// ���S
		eDethEnd,		// ���S�I��
		eReStart,		// �ċN
		eHit,			// �_���[�W�q�b�g
		eHitJ,			// �G�̒e�q�b�g

	};
	// ���݂̏�Ԃ�؂�ւ�
	void ChangeState(EState state);
	EState mState;		// �v���C���[�̏��
	int mStateStep;		// ��ԓ��̃X�e�b�v

	CVector mMoveSpeed;	// �ړ����x
	CVector mPosition;
	CVector mStartPos;	// �v���C���[�̈ʒu
	CImage* image;
	bool mIsGrounded;	// �ڒn���Ă��邩�ǂ���

	// �R���C�_�[���C��
	CColliderLine* mpColliderLine;
	/*CColliderLine* mpColliderLine_2;
	CColliderLine* mpColliderLine_3;*/

	CColliderSphere* mpColliderSphere;

	CTransform* mpRideObject;

	int mInvincible;			// ���G�J�E���^
	bool staminaDepleted;		// �X�^�~�i������l�ɓ��B�����ꍇ�̃t���O
	bool staminaLowerLimit;		// �X�^�~�i�������l�ɓ��B�����ꍇ�̃t���O
	bool damageObject;			// �_���[�W��^����t���O
	bool damageEnemy;			// �_���[�W��^����t���O(�G)
	bool JumpObject;			// �W�����v�I�u�W�F�N�g�̃t���O


	CColliderSphere* mpDamageCol;	//�_���[�W���󂯂�R���C�_
	CMajicSword* mpSword;
	CBullet* mpBullet;

	// �e��������
	int mLife;

	CUIGauge* mpHpGauge;			// HP�Q�[�W
	CStaminaGauge* mpStaminaGauge;	// �X�^�~�i�Q�[�W


	float mElapsedTime;	// �v������
	float mElapsedTimeEnd;	// �v�����ԏI��
	float mElapsedTimeCol;	// �R���C�_�[�̌v������
	float JumpCoolDownTime;
};
