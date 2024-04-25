#ifndef CINVINCIBLE_H
#define CINVINCIBLE_H

#include "CObjectBase.h"
#include "CInvincibleObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"
class CSound;
class CPlayer;

// ���G�A�C�e��
class CInvincible : public CInvincibleObjectBase
{
public:
	CInvincible();
	~CInvincible();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂����Ƃ��̏��</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// �ړ�����
	// ��O
	void MoveFront();
	// ��
	void MoveBack();
	// �E
	void MoveRight();
	// ��
	void MoveLeft();

	void OnTouch(CPlayer* player);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();


	// ���G�I�u�W�F�̍s����擾
	//CMatrix Matrix() const override;

private:

	enum class EState
	{
		Idle,	// �ҋ@���
		Get,	// �擾���
	};
	EState mState;
	int mStateStep;
	void ChangeState(EState state);
	void UpdateIdle();
	void UpdateGet();

	// �擾�����ɕK�v�ȃ����o�ϐ�
	CVector mGetStartPos;	// �擾�J�n���̃A�C�e���̍��W
	CVector mGetTargetPos;	// �擾���̃A�C�e���̈ړ���̍��W
	float mGetCameraDist;	// ��ƈ玙�̃J��������̋���
	
	// ���f���E�f�ފ֘A
	// ���G�A�C�e���̃��f��
	CModel* mpInvincibleModel;
	// ���G�A�C�e���̃R���C�_�[
	CColliderSphere* mpInvincibleCol;
	CColliderSphere* mpFieldCol;

	// ���G�A�C�e�������������SE
	CSound* mpInvincibleSE;


	// �x�N�g���֘A
	// �ړ�����
	CVector mMoveVector;
	// �ړ����x
	CVector mMoveSpeed;
	// �������
	CVector mTargetDir;
	CVector mStartPos;
	CVector mTotalMovement;

	CVector2 mPosition;


	// �ϐ��֘A
	// �J�E���g
	int mSwitchCounter;
	// �v�����ԏ���
	float mElapsedTime;
	// ���ɐڒn���Ă��邩
	bool mIsGround;
	// ���G�ɂȂ������ǂ���
	bool mInvincibleUsed;
	// �ێ�����Ă��邩
	bool mIsHeld;
};
#endif