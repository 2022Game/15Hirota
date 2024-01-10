#ifndef CFALLINGOBJECTS_H
#define CFALLINGOBJECTS_H


#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderMesh.h"

// �����鏰
class CFallingObjects : public CRideableObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="scale">���̃X�P�[���l</param>
	/// <param name="reactionTag">�G���Ɣ�������I�u�W�F�N�g�̃^�O</param>
	/// <param name="reactionLayer">�G���Ɣ�������R���C�_�[�̃��C���[</param>
	CFallingObjects(const CVector& pos, const CVector& scale,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CFallingObjects();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	void SetStartPosition(const CVector& pos);

	// �X�V
	void Update() override;

	// �`��
	void Render() override;

private:
	// �����鏰�̏��
	enum class EState
	{
		Idle,		// �ҋ@���
		Falling,	// �������
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// ����Ă����Ԃ̍X�V����
	void UpdateFalling();

	CModel* mpModel;	// �����鏰�̃��f��
	CColliderMesh* mpColliderMesh;	// �����鏰�̃R���C�_�[

	EState mState;	// ���݂̏��
	int mStateStep;	// ��ԓ��̃X�e�b�v

	ETag mReactionTag;	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ELayer mReactionLayer;	// �G�ꂽ���ɔ������郌�C���[

	float mFadeTime;	// �t�F�[�h����
	float mWaitTime;	// �҂�����
	bool mIsCollision;	// �Փ˂��Ă��邩

	CVector mMoveSpeed;
	CVector mPosition;
	CVector mStartPos;
};
#endif