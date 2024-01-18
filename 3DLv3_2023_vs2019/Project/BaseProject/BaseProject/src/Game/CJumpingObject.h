#ifndef CJUMPINGOBJECT_H
#define CJUMPINGOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CRideableObject.h"

// ���˂����鏰�N���X
class CJumpingObject : public CRideableObject
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

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:

	// ���f���E�f�ފ֘A
	CModel* mpModel;
	// ���˂郂�f���̃R���C�_�[
	CColliderMesh* mpColliderMesh;


	// ��Ԋ֘A
	// ���˂����鏰�̏��
	enum class EState
	{
		Idle,		// �ҋ@���
		Bounce,		// ���˂�������
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// ���˂������Ԃ̍X�V����
	void UpdateBounce();
	EState mState;	// ���݂̏��


	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �t�F�[�h����
	float mFadeTime;
	// �҂�����
	float mWaitTime;
	// �Փ˂��Ă��邩
	bool mIsCollision;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;
};
#endif