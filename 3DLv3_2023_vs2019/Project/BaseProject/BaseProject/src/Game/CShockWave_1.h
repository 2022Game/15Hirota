#ifndef CSHOCKWAVE_1
#define CSHOCKWAVE_1

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderCapsule.h"

// �n�ʂ̏Ռ��g�N���X
class CShockWave_1 : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">�G�t�F�N�g�𔭐��������I�u�W�F�N�g</param>
	/// <param name="pos">�����ʒu</param>
	/// <param name="dir">�ړ�����</param>
	/// <param name="speed">�ړ����x</param>
	/// <param name="dist">�ړ�����������鋗��</param>
	CShockWave_1(CObjectBase* owner, const CVector& pos, const CVector& startscale, const CVector& endscale, 
		const CVector& dir, float speed, float dist);
	// �R���X�g���N�^
	~CShockWave_1();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �G�t�F�N�g�̎�����
	CObjectBase* mpOwner;
	// �G�t�F�N�g�̃��f��
	CModel* mpModel;
	// ���f���̃R���C�_�[1
	CColliderCapsule* mpCapsule1;
	// ���f���̃R���C�_�[2
	CColliderCapsule* mpCapsule2;
	// �ړ����x
	CVector mMoveSpeed;
	// �ړ�����������鋗��
	float mKillMoveDist;
	// ���݈ړ���������
	float mMovedDist;

	// ���Ԍv���p
	float mElapsedTime;
	// �����̑傫��
	CVector mStartScale;
	// �ő�̑傫��
	CVector mEndScale;
	// �傫���Ȃ鎞�Ԍv���p
	float mScaleTime;
};
#endif