#ifndef CEXSTAGEFIELD_H
#define CEXSTAGEFIELD_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

class CEXStageField : public CObjectBase
{
public:
	CEXStageField();
	~CEXStageField();

	// �ǂ̃R���C�_�[���擾
	CColliderMesh* GetWallCol() const;

	void Update() override;
	void Render() override;

private:

	CModel* mpStageModel;

	CColliderMesh* mpFloorCol;
	CColliderMesh* mpWallCol;
};
#endif