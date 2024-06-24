#ifndef CELECTRICLASER_H
#define CELECTRICLASER_H

#include "CObjectBase.h"
#include "CTexture.h"
#include "CColliderLine.h"

class CLineEffect;

// �d���M�~�b�N
class CElectricLaser : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="move">�ړ���</param>
	/// <param name="moveTime">�ړ�����</param>
	/// <param name="laserStartPos">���[�U�[�̊J�n�ʒu</param>
	/// <param name="laserEndPos">���[�U�[�̏I���ʒu</param>
	/// <param name="colliderPos1">�R���C�_�[�̊J�n�ʒu</param>
	/// <param name="colliderPos2">�R���C�_�[�̏I���ʒu</param>
	CElectricLaser(const CVector& pos, const CVector& move, float moveTime,
		const CVector& laserStartPos, const CVector& laserEndPos,
		const CVector& colliderPos1, const CVector& colliderPos2);
	// �f�X�g���N�^
	~CElectricLaser();

	// �I�u�W�F�N�g�폜����
	void DeleteObject(CObjectBase* obj) override;

	// �X�V����
	void Update() override;

private:
	// ���C���G�t�F�N�g
	CLineEffect* mpLineEffect;
	// �d���̃A�j���f�[�^
	TexAnimData mEffectAnimData;

	// �R���C�_�[���C��
	CColliderLine* mpLine;

	// �����ʒu
	CVector mStartPos;
	// �ړ���
	CVector mMoveVec;
	// �ړ�����
	float mMoveTime;
	// �v������
	float mElapsedTime;
};
#endif