#pragma once
#include "CCharacter.h"

class CEnemy3 : public CCharacter
{
public:
	//�G�̐���ݒ�
	static void Num(int num);
	//�G�̐����擾
	static int Num();
	//�G�̃X�R�A��ݒ�
	static void Score(int score);
	//�G�̃X�R�A���擾
	static int Score();
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	//CEnemy3(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CEnemy3(float x, float y, float w, float h, CTexture* pt);
	//�X�V����

	void Update();
private:
	static int sNum;	//�G�̐�
	static int sScore;	//�X�R�A
};