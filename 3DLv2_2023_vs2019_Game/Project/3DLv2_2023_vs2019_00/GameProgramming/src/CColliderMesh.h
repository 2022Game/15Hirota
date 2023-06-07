#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
#include "CColliderTriangle.h"
#include "CCollider.h"
/*
���f���f�[�^����O�p�R���C�_�̐���
*/
class CColliderMesh
{
public:
	void ChangePriority();
	CColliderMesh();
	~CColliderMesh();
	//Set(�e, �e�s��, ���f��)
	//���f������O�p�R���C�_�̐���
	void Set(CCharacter3* parent, CMatrix* matrix, CModel* model);
private:
	//�O�p�R���C�_�̔z��쐬
	CColliderTriangle* mpColliderTriangles;
	//�O�p�R���C�_�̔z��̗v�f��
	int mTrianglesCount;
};
#endif