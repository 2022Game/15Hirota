#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
	: mpColliderTriangles(nullptr)
{
}

CColliderMesh::~CColliderMesh()
{
	if(mpColliderTriangles != nullptr)
	{	//���R���C�_�z��̍폜
		delete[]mpColliderTriangles;
	}
}

//Set(�e�A�e�s��A���f��)
//���f�����灢�R���C�_�̐���
void CColliderMesh::Set(CCharacter3* parent, CMatrix* matrix, CModel* model)
{
	//���f���́��|���S���o���R���C�_�̔z��쐬
	mpColliderTriangles = new
		CColliderTriangle[model->Triangles().size()];
	for (size_t i = 0 ; i < model->Triangles().size(); i++)
	{
		//���R���C�_�̐ݒ�
		mpColliderTriangles[i].Set(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2());
		mpColliderTriangles[i].ChangePriority();
	}
}