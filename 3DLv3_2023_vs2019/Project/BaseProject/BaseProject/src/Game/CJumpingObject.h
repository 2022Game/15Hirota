#ifndef CJUMPINGOBJECT_H
#define CJUMPINGOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CJumpingBase.h"

class CJumpingObject : public CJumpingBase
{
public:
	CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CJumpingObject();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;


	void Update();
	void Render();

private:
	// ���˂鏰�̏��
	enum class EState
	{
		Idle,		// �ҋ@���
		Bounce,		// ���˂���
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// ����Ă����Ԃ̍X�V����
	void UpdateBounce();

	EState mState;	// ���݂̏��
	int mStateStep;	// ��ԓ��̃X�e�b�v

	ETag mReactionTag;	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ELayer mReactionLayer;	// �G�ꂽ���ɔ������郌�C���[

	float mFadeTime;	// �t�F�[�h����
	float mWaitTime;	// �҂�����
	bool mIsCollision;	// �Փ˂��Ă��邩


	CModel* mpModel;

	CColliderMesh* mpColliderMesh;
};
#endif