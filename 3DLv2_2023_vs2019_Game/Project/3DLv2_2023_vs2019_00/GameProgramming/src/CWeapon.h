#ifndef CWEAPON_H
#define CWEAPON_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CBullet.h"
#include "CColliderLine.h"

/*
����N���X
�L�����N�^�N���X���p��
*/
class CWeapon : public CCharacter3 {
public:
	CWeapon();
	//CWeapon(�ʒu, ��], �X�P�[��)
	CWeapon(const CVector& pos, const CVector& rot, const CVector& scale);

	//�Փ˔���̍X�V����
	void Collision();
	//�Փ˔���
	void Collision(CCollider* m, CCollider* o);

	//�X�V����
	void Update();
private:

	//�U������p�̃R���C�_�[
	CColliderLine mAttackCollider;
};

#endif