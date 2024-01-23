#ifndef CVANGUAD_H
#define CVANGUAD_H

#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CRideableObject.h"

class CExclamationMark;

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

	//// �t���[����HP�Q�[�W�̕\���̊m�F�����鏈��
	//void UpdateGaugeAndFrame();

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

	// ���@���K�[�h������Ɉړ������鏈��
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
	static CVanguard* spInstance;


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

	// �r�b�N���}�[�N
	CExclamationMark* mpExclamationMark;

	///////////////////////////////////////////////////////


	//// ��Ԋ֘A /////////////////////////////////////////

	// �ҋ@���
	void UpdateIdle();
	// �U��
	void UpdateAttack();
	//// �U���I���҂�
	//void UpdateAttackWait();
	//// �W�����v�J�n
	//void UpdateJumpStart();
	//// �W�����v��
	//void UpdateJump();
	//// �W�����v�I��
	//void UpdateJumpEnd();
	//// �v���C���[����
	//void UpdateDiscovery();
	//// �ǐ�
	//void UpdateChase();
	//// �L�b�N
	//void UpdateKick();
	//// �L�b�N�I��
	//void UpdateKickWait();
	//// �G�C������
	//void UpdateDisarmament();
	//// �v���C���[�̍U��Hit
	//void UpdateHit();
	//// ���S
	//void UpdateDeth();
	//// ���S�����I��
	//void UpdateDethEnd();
	//// �p�j����
	//void UpdateWander();
	//// �o�b�N�X�e�b�v
	//void UpdateBackStep();

	// ���
	enum class EState
	{
		eIdle,			// �ҋ@
		eWalk,			// ����
		eDash,			// �_�b�V��
		eChase,			// �ǐ�
		eAttack,		// �U��
		eAttackEnd,		// �U���I��
		eDiscovery,		// �v���C���[����
		eKick,			// �L�b�N
		eKickEnd,		// �L�b�N�I��
		eDisarmament,	// ��������
		eHit,			// �_���[�W���󂯂�
		eAvoidance,		// ����s��
		eDeth,			// ���S
		eDethEnd,		// ���S�I��
		eWander,		// �p�j����
		eBackStep,		// �o�b�N�X�e�b�v
		eJumpStart,		// �W�����v�J�n
		eJump,			// �W�����v��
		eJumpEnd,		// �W�����v�I��
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
		eIdle,				// �ҋ@���1
		eIdle1,				// �ҋ@���2
		eMove1,				// �ړ����1
		eMoveBack1,			// ���ړ�1
		eMoveShield1,		// ������1
		eMoveBackShield1,	// ��������1
		eDash1,				// ����1
		eAttackSpin,		// �X�s���U��1
		eAAttackKick,		// �L�b�N�U��1
		eGutsPose,			// �K�b�c�|�[�Y1
		eJumpStart,			// �W�����v�J�n
		eJump,				// �W�����v��
		eJumpEnd,			// �W�����v�I��

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
	// �ݒu���Ă��邩�ǂ���
	bool mIsGrounded;
	// �L�b�N�̑҂����Ԃ��I���������ǂ���
	bool mKickTimeEnd;
	// �v���C���𔭌����Ĉ�莞�Ԍo�������ǂ���
	bool mDiscovery;
	// �v���C���[�𔭌����I�������̎��Ԃ����q��������
	bool mDiscoveryEnd;

	// �v���C���[�����������ǂ���
	bool IsFoundPlayer() const;

	///////////////////////////////////////////////////////
};
#endif