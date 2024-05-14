#pragma once
#include "CSceneBase.h"
class CGameMenu;
class CInventoryMenu;
class CSound;
class CPlayer;
class CSoldier;
class CStageTime;
class CScore;
class CResult;

// �Q�[���V�[��
class CGameScene : public CSceneBase
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
	//CInventoryMenu* mpInventoryMenu;

	CStageTime* mpTime;
	CScore* mpScore;
	CResult* mpResult;
};
