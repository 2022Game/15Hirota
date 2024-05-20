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
class CResultAnnouncement;

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
	// �Q�[�����j���[(���̃��j���[�Ȃ̂Ōォ������\��)
	CGameMenu* mpGameMenu;
	//CInventoryMenu* mpInventoryMenu;

	// �X�e�[�W�̎���
	CStageTime* mpTime;
	// �X�R�A
	CScore* mpScore;
	// ���U���g��UI
	CResultAnnouncement* mpResultUI;
};
