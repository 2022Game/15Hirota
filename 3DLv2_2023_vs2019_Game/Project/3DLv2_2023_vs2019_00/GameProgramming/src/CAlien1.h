#ifndef CALIEN1_H
#define CALIEN1_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CAlien1 : public CCharacter3 {
public:
	//�R���X�g���N�^
	CAlien1();
	//CEnemy3(�ʒu, ��], �g�k)
	CAlien1(const CVector& position, const CVector& rotation,
		const CVector& scale);
	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void Collision();
private:
	CVector mPoint;	//�ڕW�n�_
	int mHp;	//�q�b�g�|�C���g
	//���f���f�[�^
	static CModel sModel;
	//�R���C�_
	CCollider mCollider;
};

#endif