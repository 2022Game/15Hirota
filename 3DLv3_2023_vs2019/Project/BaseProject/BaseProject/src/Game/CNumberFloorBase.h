#ifndef CNUMBERFLOORBASE_H
#define CNUMBERFLOORBASE_H

#include "CModel.h"
#include "CCollider.h"
#include "CObjectBase.h"

// �񐔂ŏ��ł��鏰Base
class CNumberFloorBase : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CNumberFloorBase(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	virtual ~CNumberFloorBase();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

protected:

	// ���I�u�W�F�N�g���f���f�[�^
	CModel* mpModel;
	// ���I�u�W�F�N�g�̃R���C�_�[
	CCollider* mpCollider;

	// �ҋ@���
	void UpdateIdle();
	// �v���C���[�ҋ@���
	virtual void UpdateWaiting();
	// �������
	void UpdateFalling();

	// ���̈ʒu�ɖ߂�ۂ̃��f���p�X�ݒ�
	virtual void SetModelPath(const std::string& path);
	std::string mModelPath;

	// ���
	enum class EState
	{
		Idle,	// �ҋ@���
		Waiting,// �v���C���[�ҋ@���
		Falling,// �������
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// ���݂̏��
	EState mState;

	// �ړ����x
	CVector mMoveSpeed;
	// �����ʒu
	CVector mStartPos;

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
	// case 0���I�������
	bool mCase0End;
	// case 1���I�������
	bool mCase1End;
};
#endif