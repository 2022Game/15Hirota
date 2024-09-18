#ifndef CNEEDLEUPDOWN_H
#define CNEEDLEUPDOWN_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderMesh.h"


// �㉺�̐j�M�~�b�N
// �j�[�h�����f���̐j�̕���
class CNeedleUpDown : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�X�P�[��</param>
	/// <param name="rot">��]</param>
	/// <param name="reactionTag">��������I�u�W�F�N�g�^�O</param>
	/// <param name="reactionLayer">��������I�u�W�F�N�g���C���[</param>
	CNeedleUpDown(const CVector& pos, const CVector& scale, const CVector& rot, const float endPos,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CNeedleUpDown();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�e�[�W�J�n���̈ʒu��ݒ�
	void SetStartPosition(const CVector& pos);

	// �U���J�n
	void AttackStart() override;

	// �U���I��
	void AttackEnd() override;

	// �X�V
	void Update() override;

	// �`��
	void Render();

private:

	// ���f���E�f�ފ֘A
	// �j�̃��f��
	CModel* mpNeedle;

	// �j���f���̃R���C�_�[
	CColliderMesh* mpColliderMesh;
	// �j���f���̃x�[�X�R���C�_�[
	CColliderMesh* mpColliderBaseMesh;

	// ��Ԋ֘A
	// �j���f���̏��
	enum class EState
	{
		Idle,		// �ҋ@���
		Attack,		// �U�����
		AttackEnd,	// �U���I�����
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// �U�����
	void UpdateAttack();
	// �U���I�����
	void UpdateAttackEnd();

	// ���݂̏��
	EState mState;


	// �x�N�g���֘A
	// �j���f���̏����ʒu
	CVector mStartPos;


	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �����ʒu
	float mStartPosition;
	// �Ō�̈ʒu
	float mEndPosition;


	// �҂�����
	float mWait;
	// �U����̑҂�����
	float mAttackWait;
	// �U����̍ċN����
	float mWaitAttackTime;
	// �Փ˂��Ă��邩
	bool mIsCollision;
	// �v���C���[���U��������
	bool mIsAttack;
	// �G�ꂽ���ɔ������邨�I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃��C���[
	ELayer mReactionLayer;
};

class CNeedleUpDownBase : public CObjectBase
{
public:
	CNeedleUpDownBase(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CNeedleUpDownBase();

	// �X�e�[�W�J�n���̈ʒu��ݒ�
	void SetStartPosition(const CVector& pos);
	
	void Update();
	void Render();
private:
	// �j�̃x�[�X���f��
	CModel* mpNeedleBase;
	// �j���f���̏����ʒu
	CVector mStartPos;

	// �G�ꂽ���ɔ������邨�I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃��C���[
	ELayer mReactionLayer;
};

#endif