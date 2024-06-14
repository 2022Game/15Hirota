#ifndef CPLAINSSTAGEFALLCOL_H
#define CPLAINSSTAGEFALLCOL_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

// �u�A���W�����v�X�e�[�W�v�̗����R���C�_�[
class CPlainsStageFallCol : public CObjectBase
{
public:
	CPlainsStageFallCol();
	~CPlainsStageFallCol();

	void Update() override;
	void Render() override;
private:
	CColliderMesh* mpFallCol;
};
#endif