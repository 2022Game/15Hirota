#pragma once
#include "CCharacter.h"
#include "CPlayer2.h"
/*
* CMoveBlock
* �ړ��u���b�N�N���X
* �}�b�v�̃u���b�N�Ɏg�p����
*/
class CMoveBlock : public CCharacter
{
public:
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	//CMoveBlock(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CMoveBlock(float x, float y, float w, float h, CTexture* pt);
	//Update�ł͉������Ȃ�
	void Update();
	static CMoveBlock* Instance();
private:
	static CMoveBlock* spInstance;
};