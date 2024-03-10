#ifndef CFIELD1_H
#define CFIELD1_H
#include "CObjectBase.h"
#include "CColliderMesh.h"

class CField1 : public CObjectBase
{
public:
	// �R���X�g���N�^
	CField1();
	// �f�X�g���N�^
	~CField1();

	// �ǂ̃R���C�_�[�擾
	CColliderMesh* GetWallCol() const;

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	void CreateFieldObjects();

	CModel* mpModel;
	CModel* mpTree;
	CColliderMesh* mpColliderMesh;
	CColliderMesh* mpWallCol;
	//CColliderMesh* mpEnemyWallCol;
};
#endif