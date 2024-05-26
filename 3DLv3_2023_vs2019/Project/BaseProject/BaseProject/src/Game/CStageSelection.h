#ifndef CSTAGESELECTION_H
#define CSTAGESELECTION_H
#include "CObjectBase.h"
#include "CColliderMesh.h"

class CStageSelection : public CObjectBase
{
public:
	// �R���X�g���N�^
	CStageSelection();
	// �f�X�g���N�^
	~CStageSelection();

	// �ǂ̃R���C�_�[�擾
	//CColliderMesh* GetWallCol() const;

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	void CreateFieldObjects();

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;
	//CColliderMesh* mpWallCol;
};
#endif