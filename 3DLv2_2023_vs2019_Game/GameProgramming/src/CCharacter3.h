#ifndef CCHARACTER3_H
#define CCHARACTER3_H
//�ϊ��s��N���X�̃C���N���[�h
#include "CTransform.h"
//���f���N���X�̃C���N���[�h
#include "CModel.h"
#include "CTask.h"

//�R���C�_�N���X�̐錾
class CCollider;

/*
�L�����N�^�[�N���X
�Q�[���L�����N�^�̊�{�I�ȋ@�\���`����
*/

class CCharacter3 :public CTransform,public CTask {
public:
	//���f���̐ݒ�
	//Model(���f���N���X�̃|�C���^)
	void Model(CModel* m);
	//�`�揈��
	void Render();
	//�f�X�g���N�^
	~CCharacter3();
	//�R���X�g���N�^
	CCharacter3();
	//�R���X�g���N�^
	CCharacter3(int priority);
	//�Փˏ���
	virtual void Collision(CCollider *m,CCollider *o){}
	enum ETag
	{
		EZERO,			//�����l
		EPLAYER,		//�v���C���[
		EENEMY,			//�G
		EBULLETPLAYER,	//�v���C���[�e
		EBULLETENEMY,	//�G�e
	};
	//�^�O�̎擾
	ETag Tag();	//�^�O
protected:
	CModel* mpModel;//���f���̃|�C���^
	ETag mTag;	//�^�O
};

#endif