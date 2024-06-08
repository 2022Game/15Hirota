#ifndef CINVINCIBLEBUFFS_H
#define CINVINCIBLEBUFFS_H

#include "CObjectBase.h"
#include "CModel.h"

// ���G�G�t�F�N�g
class CInvincibleBuffs : public CObjectBase
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
	CInvincibleBuffs(CObjectBase* owner, const CVector& pos, const CVector& dir, float speed, float dist);
	// �f�X�g���N�^
	~CInvincibleBuffs();

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