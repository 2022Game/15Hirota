#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include <list>
#include "CModel.h"
#include "CCollider.h"
/*
���f���f�[�^����O�p�R���C�_�̐���
*/
class CColliderMesh : public CCollider
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="model">���f���f�[�^</param>
	CColliderMesh(CObjectBase* owner, ELayer layer, CModel* model);
	// �f�X�g���N�^
	~CColliderMesh();

	void Set(CModel* model);
	void Get(std::list<STVertex>* tris) const;

	// �R���C�_�[�`��
	void Render();

private:
	//�O�p�R���C�_�̔z��쐬
	std::list<STVertex> mVertices;
};
#endif
