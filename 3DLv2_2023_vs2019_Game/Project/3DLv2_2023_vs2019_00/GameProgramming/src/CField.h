#ifndef CFIELD_H
#define CFIELD_H

#include "CTask.h"
#include "CModel.h"
#include "CColliderMesh.h"
#include"CCharacter3.h"

//Field�N���X
class CField :public CCharacter3
{
public:
	//�R���X�g���N�^
	CField();
	//�f�X�g���N�^
	~CField();

	//�X�V����
	void Update();

private:
	CColliderMesh mColliderMesh;	//Field�̓����蔻��p�R���C�_
};
#endif