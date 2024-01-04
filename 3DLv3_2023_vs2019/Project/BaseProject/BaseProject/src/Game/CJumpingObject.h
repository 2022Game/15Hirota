#ifndef CJUMPINGOBJECT_H
#define CJUMPINGOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CJumpingBase.h"

class CJumpingObject : public CJumpingBase
{
public:
	CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot);
	~CJumpingObject();

	void Update();
	void Render();

private:
	CModel* mpModel;

	CColliderMesh* mpColliderMesh;
};
#endif