//#ifndef CNUMBERFLOOR1_H
//#define CNUMBERFLOOR1_H
//
//#include "CRideableObject.h"
//#include "CModel.h"
//#include "CColliderMesh.h"
//
//// �񐔂ŗ����鏰(3��)�N���X
//class CNumberFloor1 : public CRideableObject
//{
//public:
//	/// <summary>
//	/// �R���X�g���N�^
//	/// </summary>
//	/// <param name="pos">�����ʒu</param>
//	/// <param name="scale">�X�P�[���l</param>
//	/// <param name="reactionTag">�G���Ɣ�������I�u�W�F�N�g�̃^�O</param>
//	/// <param name="reactionLayer">�G���Ɣ�������I�u�W�F�N�g�̃��C���[</param>
//	CNumberFloor1(const CVector& pos, const CVector& scale,
//		ETag reactionTag, ELayer reactionLayer);
//
//	// �f�X�g���N�^
//	~CNumberFloor1();
//
//	/// <summary>
//	/// �Փˏ���
//	/// </summary>
//	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
//	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
//	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
//	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
//
//	// �X�V
//	void Update();
//	// �`��
//	void Render();
//
//private:
//	// ���f���E�f�ފ֘A
//	// �񐔂ŗ����鏰(3��)�̃��f��
//	CModel* mpModel;
//	// �񐔂ŗ����鏰(3��)�̃R���C�_�[
//	CColliderMesh* mpColliderMesh;
//
//
//	// ��Ԋ֘A
//	// �񐔂ŗ����鏰(3��)�̏��
//	enum class EState
//	{
//		Idle,		// �ҋ@���
//		Waiting,	// �҂����
//		Falling,	// �������
//	};
//	// ��Ԃ�؂�ւ���
//	void ChangeState(EState state);
//	// �ҋ@��Ԃ̍X�V����
//	void UpdateIdle();
//	// �҂���Ԃ̍X�V����
//	void UpdateWaiting();
//	// ������Ԃ̍X�V����
//	void UpdateFalling();
//	// ���݂̏��
//	EState mState;
//
//	// �ϐ��֘A
//	// ��ԓ��̃X�e�b�v
//	int mStateStep;
//	// �񐔂̊Ď�
//	int mNumberStep;
//	// �t�F�[�h����
//	float mFadeTime;
//	// �҂�����
//	float mWaitTime;
//	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
//	ETag mReactionTag;
//	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃��C���[
//	ELayer mReactionLayer;
//};
//#endif