#ifndef CGAMESCENE_H
#define CGAMESCENE_H

#include "CSceneBase.h"

//�Q�[���V�[��
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
};
#endif