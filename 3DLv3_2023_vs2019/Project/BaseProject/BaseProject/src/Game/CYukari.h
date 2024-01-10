#ifndef CYUKARI_H
#define CYUKARI_H

//�L�����N�^�N���X�̃C���N���[�h
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CRideableObject.h"
#include "CEffect.h"

class CGun;
class CBullet;
class CPlayer;
class CYukariFrame;
class CYukariGauge;

/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/

class CYukari : public CXCharacter
{
public:
	//�C���X�^���X�̃|�C���^�̎擾
	static CYukari* Instance();

	// �R���X�g���N�^
	CYukari();
	// �f�X�g���N�^
	~CYukari();

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

	// �X�V
	void Update();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �`��
	void Render();

	// ��_���[�W����
	// damage == �󂯂�_���[�W
	void TakeDamage(int damage) override;

	// ���x������
	void LevelUp();	//	���x���A�b�v
	void ChangeLevel(int level);	// ���x���ύX

private:
	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		None = -1,

		eIdle,		// �ҋ@
		eWalk,		// ���s
		eAttack,	// �U��
		eReload,	// �����[�h
		eJumpStart,	// �W�����v�J�n
		eJump,		// �W�����v��
		eJumpEnd,	// �W�����v�I��

		Num
	};
	// �A�j���[�V�����؂�ւ�
	void ChangeAnimation(EAnimType type);

	// �v���C���[�̃C���X�^���X
	static CYukari* spInstance;

	// �A�j���[�V�����f�[�^
	struct AnimData
	{
		std::string path;	// �A�j���[�V�����f�[�^�̃p�X
		bool loop;			// ���[�v���邩�ǂ���
		float frameLength;	// �A�j���[�V�����̃t���[����
	};
	// �A�j���[�V�����f�[�^�̃e�[�u��
	static const AnimData ANIM_DATA[];

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
	};
	EState mState;	// �v���C���[�̏��

	CVector mTargetDir;	// �L�����N�^�[�̌������
	CVector mMoveSpeed;	// �ړ����x
	bool mIsGrounded;	// �ڒn���Ă��邩�ǂ���
	bool IsFoundPlayer() const;	//�v���C���[����������

	CVector mPoint;

	CColliderLine* mpColliderLine;
	CTransform* mpRideObject;
	CColliderSphere* mpDamageCol;	//�_���[�W���󂯂�R���C�_

	CVector playerPosition;		// �ڕW�n�_
	CVector yukariPosition;		// �����̒n�_

	CGun* mpGun;	// �e�̃��f��


	int mTimeShot;
	int mTimeShotEnd;
	float mElapsedTime;	// �o�ߎ��Ԍv���p

	CYukariFrame* mpFrame;
	CYukariGauge* mpGauge;

};
#endif