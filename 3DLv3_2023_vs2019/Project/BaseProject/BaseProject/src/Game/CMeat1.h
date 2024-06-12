#ifndef CMeat1_H
#define CMeat1_H

#include "CObjectBase.h"
#include "CMeatObjectBase.h"
#include "CColliderSphere.h"
#include "CModel.h"

// ���t�����N���X
class CMeat1 : public CMeatObjectBase
{
public:
	CMeat1(const CVector& pos, const CVector& rot, const CVector& scale);
	~CMeat1();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	//�C���X�^���X�̃|�C���^�̎擾
	static CMeat1* Instance();

	bool IsMeat1();

	void Update() override;
	void Render() override;

private:
	// �C���X�^���X
	static CMeat1* spInstance;

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
	// �ړ�����
	CVector mMoveVector;
	// �������
	CVector mTargetDir;
	CVector mMoveSpeed;
	CVector mStartPos;
	CVector mTotalMovement;

	CVector2 mPosition;

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