#ifndef CSTAGE4MENUOBJECT_H
#define CSTAGE4MENUOBJECT_H

#include "CObjectBase.h"
#include "CColliderSphere.h"
#include "CModel.h"

// �X�e�[�W���j���[�I�u�W�F�N�g
class CStage4MenuObject : public CObjectBase
{
public:
	// �R���X�g���N�^
	CStage4MenuObject(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// �f�X�g���N�^
	~CStage4MenuObject();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
private:
	enum class EState
	{
		eIdle,
		eReaction,
	};
	EState mState;
	int mStateStep;
	bool mIsCollisionPlayer;
	float mElapsedTime;
	CVector mStartScale;
	CVector mShrinkScale;

	void ChangeState(EState state);
	void UpdateIdle();
	void UpdateReaction();

	// �V�[�\�[���f��
	CModel* mpSeesawModel;
	// �V�[�\�[�̃R���C�_�[
	CColliderSphere* mpColliderSphere;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

};
#endif