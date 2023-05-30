#ifndef CSHOUGAIBUTUA_H
#define CSHOUGAIBUTUA_H
#include "CCharacter3.h"
#include "CCollider.h"
#include "CColliderMesh.h"
#include "CColliderTriangle.h"
#include "CColliderLine.h"
/*
�O�p�`�R���C�_�̒�`
*/
class CShougaibutuA : public CCharacter3
{
public:
	int a;
	//Collision(�R���C�_�P�A�R���C�_�Q�j
	void Collision(CCollider* m, CCollider* o);
	void Collision();
	//�R���X�g���N�^
	//CEnemy(���f��,�ʒu,��],�g�k�j
	CShougaibutuA(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	//�X�V����
	void Update();
private:
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
	CColliderMesh mColliderMesh1;
};

#endif