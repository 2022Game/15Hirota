#pragma once
//�L�����N�^�N���X�̃C���N���[�h
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CRideableObject.h"
#include "CImage.h"

class CUIGauge;

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

	// �ҋ@���
	void UpdateIdle();
	// �U��
	void UpdateAttack();
	// ���U��
	void UpdateAttackStrong();
	// �U���I���҂�
	void UpdateAttackWait();
	// �W�����v�J�n
	void UpdateJumpStart();
	// �W�����v��
	void UpdateJump();
	// �W�����v�I��
	void UpdateJumpEnd();
	//�_�b�V���J�n
	void UpdateDashStart();
	//�_�b�V����
	void UpdateDash();
	//�_�b�V���I��
	void UpdateDashEnd();
	//����J�n
	void UpdateRotate();
	//����I��
	void UpdateRotateEnd();

	// �X�V
	void Update();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �`��
	void Render();

	// ���x������
	void LevelUp();
	void ChangeLevel(int level);

private:
	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		None = -1,

		eTPose,			// T�|�[�Y
		eIdle,			// �ҋ@
		eWalk,			// ���s
		eAttack,		// �U��
		eAttackStrong,	// ���U��
		eJumpStart,		// �W�����v�J�n
		eJump,			// �W�����v��
		eJumpEnd,		// �W�����v�I��
		eDash,			// �_�b�V��
		eDashStop,		// �_�b�V���I��
		eRotate,		// ���

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
		eIdle,			// �ҋ@
		eAttack,		// �U��
		eAttackStrong,	// ���U��
		eAttackWait,	// �U���I���҂�
		eJumpStart,		// �W�����v�J�n
		eJump,			// �W�����v��
		eJumpEnd,		// �W�����v�I��
		eDashStart,		// �_�b�V���J�n
		eDash,			// �_�b�V����
		eDashEnd,		// �_�b�V���I��
		eRotate,		// ����J�n
		eRotateEnd,		// ����I���҂�
		eClear,			// �N���A���
		eDeth,			// ���S
	};
	EState mState;		// �v���C���[�̏��

	CVector mMoveSpeed;	// �ړ����x
	CImage* image;
	bool mIsGrounded;	// �ڒn���Ă��邩�ǂ���

	CColliderLine* mpColliderLine;
	CTransform* mpRideObject;
	int mRemainTime;			// �c�莞��
	int mInvincible;			// ���G�J�E���^

	CUIGauge* mpHpGauge;		// HP�Q�[�W
};
