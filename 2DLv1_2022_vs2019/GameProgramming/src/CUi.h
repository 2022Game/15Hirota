#pragma once
#include "CFont.h"
/*
* CUi
* ���[�U�[�C���^�t�F�[�X�N���X
*/
class CUi
{
public:
	//�Q�[���N���A�\��
	void Clear();
	//�Q�[���I�[�o�[�\��
	void Over();
	//�X�^�[�g�\��
	void Start();
	//Enemy(�G�̐�)
	void Enemy(int enemy);
	CUi();
	void Hp(int hp);
	//Time(����)
	void Time(int time);
	//�X�R�A
	void Score(int score);
	void Render();
private:
	int mEnemy;	//�G�̐�
	int mHp;
	int mTime;	//�o�ߎ���
	int mScore;	//�X�R�A
	CFont mFont;
};
