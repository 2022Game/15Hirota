#ifndef CMEAT2_H
#define CMEAT2_H

#include "CObjectBase.h"
#include "CMeatObjectBase.h"
#include "CColliderSphere.h"
#include "CModel.h"

// ���t�����N���X
class CMeat2 : public CMeatObjectBase
{
public:
	// �R���X�g���N�^
	CMeat2(const CVector& pos, const CVector& rot, const CVector& scale);
	// �f�X�g���N�^
	~CMeat2();

	// �Փˏ���
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	//�C���X�^���X�̃|�C���^�̎擾
	static CMeat2* Instance();

	// �����擾������
	bool IsMeat2() const;

	// �X�R�A��ݒ�
	static void SetScore(int score);
	// �X�R�A���擾
	static int GetScore();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �C���X�^���X
	static CMeat2* spInstance;
	// �X�R�A
	static int sScore;

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

	CVector2 mPosition;

	// �ϐ�
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �v������
	float mElapsedTime;
	// �擾���̃J��������̋���
	float mGetCameraDist;
	// ��ڂ̓�
	bool mMeat2;
	// ���ɐڒn���Ă��邩
	bool mIsGround;
};
#endif