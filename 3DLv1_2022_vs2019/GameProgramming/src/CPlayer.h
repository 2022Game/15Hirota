#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"
#include "CColliderLine.h"

/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CCharacter3 {
public:
	CPlayer();
	//CPlayer(�ʒu�A��]�A�X�P�[��)
	CPlayer(const CVector& pos, const CVector& rot, const CVector& scale);
	//CBullet bullet;
	//�X�V����
	void Update();

	void Collision();
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
private:
	CInput mInput;
	CColliderLine mLine;	//�����R���C�_
	CColliderLine mLine2;	//�����R���C�_�Q
	CColliderLine mLine3;	//�����R���C�_�R
};

#endif