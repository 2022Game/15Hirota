#ifndef CITEM1_H
#define CITEM1_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CInput.h"
#include "CColliderLine.h"

/*
�A�C�e���N���X1(�v���C���[�N���X�̗��p)
�L�����N�^�N���X���p��
*/
class CItem1 : public CCharacter3 {
public:
	//�C���X�^���X�̃|�C���^�̎擾
	static CItem1* Instance();
	//�Փˏ���
	void Collision();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//CBullet bullet;
	CItem1();
	//CPlayer(�ʒu, ��], �X�P�[��)
	CItem1(const CVector& pos, const CVector& rot, const CVector& scale);

	static int Hp();
	//�X�V����
	void Update();

private:
	//�v���C���[�̃C���X�^���X
	static CItem1* spInstance;

	static int sHp;

	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2; //�����R���C�_
	CColliderLine mLine3; //�����R���C�_
	CInput mInput;

};

#endif