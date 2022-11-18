#pragma once
#include "CCharacter.h"
#include "CInput.h"
#include "CSound.h"

class CPlayer2 : public CCharacter
{
public:
	//HP���擾
	static int Hp();
	//GOAL1���擾
	static int Goal1();
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	//CPlayer2(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CPlayer2(float x, float y, float w, float h, CTexture* pt);
	//�X�V����
	void Update();
	static CPlayer2* Instance();
private:
	CSound mSoundJump;	//�W�����vSE
	static int sHp;	//HP
	static int sGoal1; //�S�[��
	int mInvincible; //���G�J�E���^
	CInput mInput;
	static CPlayer2* spInstance;
};