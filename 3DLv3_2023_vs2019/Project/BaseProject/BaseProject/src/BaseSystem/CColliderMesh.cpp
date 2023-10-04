#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
	: mpColliderTriangles(nullptr)
{
}

CColliderMesh::~CColliderMesh()
{
	if (mpColliderTriangles != nullptr)
	{	//�O�p�R���C�_�z��̍폜
		delete[] mpColliderTriangles;
	}
}

//Set(�e, �e�s��, ���f��)
//���f������O�p�R���C�_�̐���
void CColliderMesh::Set(CObjectBase* owner, ELayer layer, CModel* model)
{
	auto triangles = model->Triangles();
	mColliderTriangleCount = triangles.size();
	//���f���̎O�p�|���S���ŎO�p�R���C�_�̔z��쐬
	mpColliderTriangles = new CColliderTriangle[mColliderTriangleCount];
	for (int i = 0; i < mColliderTriangleCount; i++)
	{
		auto& tri = triangles[i];
		//�O�p�R���C�_�̐ݒ�
		mpColliderTriangles[i].Set
		(
			owner, layer,
			tri.V0(), tri.V1(), tri.V2()
		);
	}
}
