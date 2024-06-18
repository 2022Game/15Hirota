#ifndef CHOPSANDHOOPSFALLCOL_H
#define CHOPSANDHOOPSFALLCOL_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

// �u�z�b�v���t�[�v�X�v�̗����R���C�_�[
class CHopsAndHoopsFallCol : public CObjectBase
{
public:
	CHopsAndHoopsFallCol();
	~CHopsAndHoopsFallCol();

	void Update() override;
	void Render() override;
private:
	CColliderMesh* mpFallCol;
};
#endif