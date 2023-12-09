#ifndef CGOALOBJECT_H
#define CGOALOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CGoalBase.h"

class CGoalObject : public CGoalBase
{
public:
	CGoalObject(CModel* model, const CVector& pos, const CVector& scale, const CVector&rot);
	~CGoalObject();

	void Update();
	void Render();

private:
	CModel* mpModel;
	//CColliderLine* mpColliderLine;
	CColliderSphere* mpColliderSphere;
	CColliderMesh* mpColliderMesh;
};
#endif