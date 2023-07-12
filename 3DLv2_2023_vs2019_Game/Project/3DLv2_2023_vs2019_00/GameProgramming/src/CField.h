#ifndef CFIELD_H
#define CFIELD_H

#include "CTask.h"
#include "CModel.h"
#include "CColliderMesh.h"

//Field�N���X
class CField :public CTask
{
public:
	//�R���X�g���N�^
	CField();
	//�f�X�g���N�^
	~CField();

	//�X�V����
	void Update();
	//�`�揈��
	void Render();

private:
	CModel* mModel;	//Field�̃��f���f�[�^	
	CColliderMesh mColliderMesh;	//Field�̓����蔻��p�R���C�_
};
#endif