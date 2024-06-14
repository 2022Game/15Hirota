#ifndef CONESHOTFLOORFIELD_H
#define CONESHOTFLOORFIELD_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

// �u�A���W�����v�X�e�[�W�v
class COneShotFloorField : public CObjectBase
{
public: 
	COneShotFloorField();
	~COneShotFloorField();

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