#ifndef CHEALINGUPBUFFS_H
#define CHEALINGUPBUFFS_H

#include "CObjectBase.h"
#include "CModel.h"

// �񕜃A�b�v�G�t�F�N�g
class CHealingUpBuffs : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">effect�𔭐��������I�u�W�F�N�g</param>
	/// <param name="pos">�����ʒu</param>
	/// <param name="dir">�ړ�����</param>
	/// <param name="speed">�ړ����x</param>
	/// <param name="dist">�ړ�����������鋗��</param>
	CHealingUpBuffs(CObjectBase* owner, const CVector& pos, const CVector& dir, float speed, float dist);
	// �f�X�g���N�^
	~CHealingUpBuffs();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	CObjectBase* mpOwner;	// effect�̎�����
	CModel* mpModel;			// effect�̃��f��
	CVector mMoveSpeed;		// �ړ����x
	float mKillMoveDist;	// �ړ�����������鋗��
	float mMovedDist;		// ���݈ړ���������
};
#endif