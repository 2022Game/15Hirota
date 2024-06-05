#ifndef CBIRIBIRI_H
#define CBIRIBIRI_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderMesh.h"

// �r���r���G�t�F�N�g
class CBiribiri : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">�G�t�F�N�g�𔭐��������I�u�W�F�N�g</param>
	/// <param name="pos">�����ʒu</param>
	CBiribiri(CObjectBase* owner, const CVector& pos);
	// �f�X�g���N�^
	~CBiribiri();

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	CObjectBase* mpOwner;	// ���̃G�t�F�N�g�̎�����
	CModel* mpModel;		// �G�t�F�N�g�̃��f���f�[�^
	CVector mMoveSpeed;		// �ړ����x
	float mKillMoveDist;	// �ړ�����������鋗��
	float mMovedDist;		// ���݈ړ���������
	float mElapsedTime;

	float mInitialRingSize; // ���������O�T�C�Y
	float mCurrentRingSize; // ���݂̃����O�T�C�Y
	float mMaxRingSize;     // �ő僊���O�T�C�Y
	
	CColliderMesh* mpMesh;
};
#endif