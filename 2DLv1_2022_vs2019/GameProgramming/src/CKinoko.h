#pragma once
#include "CCharacter.h"

class CKinoko :public CCharacter
{
public:
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	//CKinoko(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CKinoko(float x, float y, float w, float h, CTexture* pt);
	//�X�V����
	void Update();
};