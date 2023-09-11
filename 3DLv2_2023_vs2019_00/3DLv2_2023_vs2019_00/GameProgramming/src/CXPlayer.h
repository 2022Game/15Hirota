#ifndef CXPLAYER_H
#define CXCPLAYER_H

#include "CXCharacter.h"
#include "CInput.h"
#include "CCollider.h"
#include "CActionCamera.h"

class CXPlayer :public CXCharacter {
public:
	//�X�V����
	void Update();
	//�f�t�H���g�R���X�g���N�^
	CXPlayer();

	void Init(CModelX* model);
private:
	CInput mInput;
	//�R���C�_�錾
	CCollider mColSpherBody;	//��
	CCollider mColSpherHead;	//��
	CCollider mColspherSword;	//��
};
#endif