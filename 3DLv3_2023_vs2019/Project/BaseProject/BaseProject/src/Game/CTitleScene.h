#pragma once
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"

//�^�C�g���V�[��
class CTitleScene :public CSceneBase
{
public:
	//�R���X�g���N�^
	CTitleScene();
	//�f�X�g���N�^
	~CTitleScene();
	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();

private:
	CImage* mBgImage;   //�w�i�摜
};