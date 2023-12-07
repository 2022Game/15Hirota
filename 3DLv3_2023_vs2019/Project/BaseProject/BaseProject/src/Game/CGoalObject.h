#ifndef CGOALOBJECT_H
#define CGOALOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderMesh.h"
#include "CObjectBase.h"

class CGoalObject : CObjectBase
{
public:
	CGoalObject(CModel* model, const CVector& pos, const CVector& scale, const CVector&rot);
	~CGoalObject();

	void Update();
	void Render();

private:
	CModel* mpModel;
	CColliderLine* mpColliderLine;
	CColliderMesh* mpColliderMesh;
};
#endif