#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
/*
���f���f�[�^���灢�R���C�_�̐���
*/
class CColliderMesh
{
public:
	CColliderMesh();
	~CColliderMesh();
	//Set(�e�A�e�s��A���f��)
	//���f�����灢�R���C�_�̐���
	void Set(CCharacter3* parent, CMatrix* matrix, CModel* model);
private:
	//���R���C�_�̔z��쐬
	CColliderTriangle* mpColliderTriangles;
};
#endif
