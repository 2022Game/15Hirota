#ifndef CFIELD_WORLDS_1_FALLCOL
#define CFIELD_WORLDS_1_FALLCOL

#include "CObjectBase.h"
#include "CColliderMesh.h"

// �u�A���W�����v�X�e�[�W�v�̗����R���C�_�[
class CField_Worlds_1_FallCol : public CObjectBase
{
public:
	CField_Worlds_1_FallCol();
	~CField_Worlds_1_FallCol();

	void Update() override;
	void Render() override;
private:
	CColliderMesh* mpFallCol;
};
#endif