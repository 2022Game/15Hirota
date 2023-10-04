#pragma once
#include "CEnemy.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CModel.h"
#include "CModelX.h"

class CApplication
{
private:
	CPlayer* mpPlayer;

	CSound mSoundBgm;	        //BGM
	CSound mSoundOver;	        //�Q�[���I�[�o�[
public:
	~CApplication();

	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};