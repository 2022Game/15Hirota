#ifndef CFINALSTAGEFALLCOL_H
#define CFINALSTAGEFALLCOL_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

// �u�ŏI�X�e�[�W�v�̗����R���C�_�[
class CFinalStageFallCol : public CObjectBase
{
public:
	// �R���X�g���N�^
	CFinalStageFallCol();
	// �f�X�g���N�^
	~CFinalStageFallCol();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
private:
	// �����R���C�_�[
	CColliderMesh* mpFallCol;
};
#endif