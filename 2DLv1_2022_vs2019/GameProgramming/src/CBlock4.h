#pragma once
#include "CCharacter.h"
#include "CApplication.h"
/*
* CBlock
* �u���b�N�N���X
* �}�b�v�̃u���b�N�Ɏg�p����
*/
class CBlock4 : public CCharacter
{
public:
	//CBlock(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CBlock4(float x, float y, float w, float h, CTexture* pt);
	//�G�̃X�R�A��ݒ�
	static void Score(int score);
	//�G�̃X�R�A���擾
	static int Score();
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	void Update();
private:
	static int sScore;	//�X�R�A
};