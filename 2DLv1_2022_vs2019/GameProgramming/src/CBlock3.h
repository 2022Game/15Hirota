#pragma once
#include "CCharacter.h"
#include "CApplication.h"
/*
* CBlock
* �u���b�N�N���X
* �}�b�v�̃u���b�N�Ɏg�p����
*/
class CBlock3 : public CCharacter
{
public:
	//CBlock(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CBlock3(float x, float y, float w, float h, CTexture* pt);
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
public:
	bool flag_B;

	//Update�ł͉������Ȃ�
	void Update() {}
};
