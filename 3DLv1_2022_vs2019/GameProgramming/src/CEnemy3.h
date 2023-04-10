#ifndef CENEMY3_H
#define CENEMY3_H

//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"

#include "CPlayer.h"
/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CEnemy3 : CCharacter3 {
public:
	//�R���X�g���N�^
	CEnemy3();
	//CEnemy3(�ʒu�A��]�A�g�k)
	CEnemy3(const CVector& position, const CVector& rotation,
		const CVector& scale);
	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1�A�R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void Collision();
private:
	//���f���f�[�^
	static CModel sModel;
	//�R���C�_
	CCollider mCollider;
};
#endif