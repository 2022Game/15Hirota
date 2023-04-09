#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
/*
モデルデータから△コライダの生成
*/
class CColliderMesh
{
public:
	CColliderMesh();
	~CColliderMesh();
	//Set(親、親行列、モデル)
	//モデルから△コライダの生成
	void Set(CCharacter3* parent, CMatrix* matrix, CModel* model);
private:
	//△コライダの配列作成
	CColliderTriangle* mpColliderTriangles;
};
#endif
