#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
//�O�p�`�̃C���N���[�h
#include "CTriangle.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"

/*
�e�N���X
�O�p�`���΂�
*/
class CBullet : public CCharacter3 {
public:
	//���Ɖ��s���̐ݒ�
	//Set(���A���s��)
	void Set(float w, float d);

	CBullet();

	//�X�V
	void Update();
	//�`��
	void Render();

private:
	//�O�p�`
	CTriangle mT;
	//��������
	int mLife;
private:
	//�R���C�_
	CCollider mCollider;
};

#endif