#ifndef CGAMEOVERSCENE_H
#define CGAMEOVERSCENE_H
#include "CSceneBase.h"
#include "CImage.h"
#include "CInput.h"

class CImage;

class CGameOverScene :public CSceneBase
{
public:
	// �R���X�g���N�^
	CGameOverScene();
	// �f�X�g���N�^
	~CGameOverScene();

	//�V�[���ǂݍ���
	void Load();
	//�V�[���̍X�V����
	void Update();
private:
	CImage* mpOverImage;
};
#endif