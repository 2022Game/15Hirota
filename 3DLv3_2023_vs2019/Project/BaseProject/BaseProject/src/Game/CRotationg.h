#ifndef CROTATIONG_H
#define CROTATIONG_H

#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderMesh.h"

class CRotationg : public CRideableObject
{
public: 
	CRotationg(const CVector& pos, const CVector& scale,
	float rotateSpeedY);
	  ~CRotationg();

	  void Update();
	  void Render();
private:
	CModel* mpRotationgModel;
	CColliderMesh* mpRotationgCol;

	float mRotateSpeedY;
};
#endif