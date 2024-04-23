#pragma once
#include "CSceneBase.h"
class CGameMenu;
class CInventoryMenu;
class CSound;
class CPlayer;
class CSoldier;
class CStageTime;
class CScore;

// �Q�[���V�[��
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
	CGameMenu* mpGameMenu;
	CInventoryMenu* mpInventoryMenu;

	CStageTime* mpTime;
	int mTime;
	bool mIsStage1;
	bool mIsStage2;
	bool mIsStage3;

	CScore* mpScore;
	int mScore;
};
