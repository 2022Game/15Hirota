#ifndef CMeat1_H
#define CMeat1_H

#include "CObjectBase.h"
#include "CMeatObjectBase.h"
#include "CColliderSphere.h"
#include "CModel.h"
class CMeat1Event;

// ���t�����N���X
class CMeat1 : public CMeatObjectBase
{
public:
	// �R���X�g���N�^
	CMeat1(const CVector& pos, const CVector& rot, const CVector& scale);
	// �f�X�g���N�^
	~CMeat1();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փˏ��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	//�C���X�^���X�̃|�C���^�̎擾
	static CMeat1* Instance();

	// �����擾������
	bool IsMeat1();

	// �X�R�A��ݒ�
	static void SetScore(int score);
	// �X�R�A���擾
	static int GetScore();

	// �Ǘ�����Ă���C�x���g��ݒ�
	void SetEvent(CMeat1Event* ev);

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �C���X�^���X
	static CMeat1* spInstance;
	// �X�R�A
	static int sScore;

	// �C�x���g�̃|�C���^�[
	CMeat1Event* mpEvent;

	// ���f���֘A
	// ���̃��f��
	CModel* mpMeat;
	// ���̃R���C�_�[���f��
	CColliderSphere* mpMeatSphere;

	// ��Ԋ֘A
	// ���̏��
	enum class EState
	{
		eIdle,	// �ҋ@���
		eGet,	// �擾���
	};
	EState mState;
	// ��Ԃ�ω������鏈��
	void ChangeState(EState state);
	// �ҋ@��ԍX�V����
	void UpdateIdle();
	// �擾��ԍX�V����
	void UpdateGet();

	// �x�N�g���֘A
	// �擾�J�n���̃A�C�e���̍��W
	CVector mGetStartPos;
	// �擾���̃A�C�e���̈ړ���̍��W
	CVector mGetTargetPos;
	// �����ʒu
	CVector mStartPos;

	// �ϐ�
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �v������
	float mElapsedTime;
	// �擾���̃J��������̋���
	float mGetCameraDist;
	// ��ڂ̓�
	bool mMeat1;
	// ���ɐڒn���Ă��邩
	bool mIsGround;
};
#endif