#pragma once
#include "CSceneBase.h"

class CImage;
class CPlayer;

//�^�C�g���V�[��
class CGameScene :public CSceneBase
{
public:
	//�R���X�g���N�^
	CGameScene();
	//�f�X�g���N�^
	~CGameScene();
	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();

private:
	CImage* image;
};
