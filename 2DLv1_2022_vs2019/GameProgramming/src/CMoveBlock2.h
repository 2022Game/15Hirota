#pragma once
#include "CCharacter.h"
#include "CPlayer2.h"
/*
* CMoveBlock
* �ړ��u���b�N�N���X
* �}�b�v�̃u���b�N�Ɏg�p����
*/
class CMoveBlock2 : public CCharacter
{
public:
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	//CMoveBlock(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CMoveBlock2(float x, float y, float w, float h, CTexture* pt);
	//Update�ł͉������Ȃ�
	void Update();
	static CMoveBlock2* Instance();
private:
	static CMoveBlock2* spInstance;
};
