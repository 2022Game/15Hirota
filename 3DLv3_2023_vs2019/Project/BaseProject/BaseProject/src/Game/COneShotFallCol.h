#ifndef CONESHOTFALLCOL_H
#define CONESHOTFALLCOL_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

// �u�A���W�����v�X�e�[�W�v�̗����R���C�_�[
class COneShotFallCol : public CObjectBase
{
public:
	// �R���X�g���N�^
	COneShotFallCol();
	// �f�X�g���N�^
	~COneShotFallCol();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
private:
	// �����R���C�_�[
	CColliderMesh* mpFallCol;
};
#endif