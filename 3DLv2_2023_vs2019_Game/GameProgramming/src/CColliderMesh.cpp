#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
	: mpColliderTriangles(nullptr)
{
}

CColliderMesh::~CColliderMesh()
{
	if(mpColliderTriangles != nullptr)
	{	//△コライダ配列の削除
		delete[]mpColliderTriangles;
	}
}

//Set(親、親行列、モデル)
//モデルから△コライダの生成
void CColliderMesh::Set(CCharacter3* parent, CMatrix* matrix, CModel* model)
{
	//モデルの△ポリゴン出△コライダの配列作成
	mpColliderTriangles = new
		CColliderTriangle[model->Triangles().size()];
	for (size_t i = 0 ; i < model->Triangles().size(); i++)
	{
		//△コライダの設定
		mpColliderTriangles[i].Set(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2());
		mpColliderTriangles[i].ChangePriority();
	}
}