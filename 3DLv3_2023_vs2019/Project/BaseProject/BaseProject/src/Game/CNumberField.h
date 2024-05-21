#ifndef CNUMBERFIELD_H
#define CNUMBERFIELD_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

// �u�A���W�����v�X�e�[�W�v
class CNumberField : public CObjectBase
{
public: 
	CNumberField();
	~CNumberField();

	  // �ǂ̃R���C�_�[�擾
	 // CColliderMesh* GetWallCol() const;

	  void Update();
	  void Render();

private:

	CModel* mpStageModel;
	CModel* mpStageSkyModel;

	CColliderMesh* mpFallCol;
};
#endif