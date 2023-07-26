#ifndef CSIKAKU_H
#define CSIKAKU_H

#include "CCharacter3.h"
#include "CCollider.h"
#include "CColliderLine.h"
#include "CColliderMesh.h"
#include "CColliderTriangle.h"
#include "CPlayer.h"

/*
�G�l�~�[�ƃL�����N�^�N���X���p��
*/
class CSikaku :public CCharacter3 {
private:
	//�R���C�_
	CColliderMesh mColliderMesh1;
protected:
	
public:
	//static int mD;
	//�Փˏ���
	//Collision(�R���C�_�P�A�R���C�_�Q�j
	void Collision(CCollider* m, CCollider* o);

	void Collision();
	//�R���X�g���N�^
	//CEnemy(���f��,�ʒu,��],�g�k�j
	CSikaku(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	~CSikaku();

	/*bool IsPlayerOnTop() const;*/

	//�X�V����
	void Update();
};
#endif