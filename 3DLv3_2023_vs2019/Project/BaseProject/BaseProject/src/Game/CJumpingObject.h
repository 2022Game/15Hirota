#ifndef CJUMPINGOBJECT_H
#define CJUMPINGOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CObjectBase.h"

// �v���C���[�𒵂˂����鏰
class CJumpingObject : public CObjectBase
{
public:
	// �R���X�g���N�^
	CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// �f�X�g���N�^
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
	// ���˂鏰���f��
	CModel* mpModel;
	// ���˂鏰���f���̃R���C�_�[
	CColliderMesh* mpColliderMesh;


	// ��Ԋ֘A
	// ���˂����鏰�̏��
	enum class EState
	{
		eIdle,			// �ҋ@���
		eBounce,		// ���˂�������
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// ���˂������Ԃ̍X�V����
	void UpdateBounce();
	// ���݂̏��
	EState mState;

	// �x�N�g���֘A
	// �����̑傫��
	CVector mStartScale;
	// �k�ޑ傫��
	CVector mShrinkScale;


	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �t�F�[�h����
	float mFadeTime;
	// �҂�����
	float mWaitTime;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �Փ˂��Ă��邩
	bool mIsCollisionPlayer;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;
};
#endif