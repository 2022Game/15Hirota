#ifndef CSTONE1_H
#define CSTONE1_H

#include "CModel.h"
#include "CColliderSphere.h"
#include "CRideableObject.h"

class CStone1 : public CRideableObject
{
public:
	CStone1(CModel* model, const CVector& pos, const CVector& scale, const CVector& rot);
	~CStone1();

	void Update();
	void Render();

private:
	CModel* mpModel;
	CColliderSphere* mpColliderSphere;
};
#endif