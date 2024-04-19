#ifndef CNUMBERFLOORONCE_H
#define CNUMBERFLOORONCE_H

#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderMesh.h"

// ���ŏ��ł��鏰�N���X
class CNumberFloorOnce : public CRideableObject
{
public:

	CNumberFloorOnce(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CNumberFloorOnce();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// �X�V
	void Update();
	// �`��
	void Render();

private:
	// ���f���E�f�ފ֘A
	CModel* mpModel;
	// 1��ŏ��ł��鏰�̃��f��
	CModel* mpNumberOnce;
	// 1��ŏ��ł��鏰�̃��f��
	CColliderMesh* mpColliderMesh;

	
	// �ҋ@���
	// 1��ŏ��ł��鏰�̃��f��
	enum class EState
	{
		Idle,
		Waiting,
		Falling,
	};
	void ChangeState(EState state);
	void UpdateIdle();
	void UpdateWaiting();
	void UpdateFalling();
	EState mState;


	// �x�N�g���֘A
	// �ړ����x
	CVector mMoveSpeed;
	// �����ʒu
	CVector mStartPos;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �_�ŉ�
	int mSwitchCount;
	// ������Ԃ̃X�e�b�v
	int mFallingSwitch;
	// �t�F�[�h����
	float mFadeTime;
	// �҂�����
	float mWaitTime;
	// �v������
	float mElapsedTime;
	// �Փ˂��Ă��邩
	bool mIsCollision;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃��C���[
	ELayer mReactionLayer;
};
#endif