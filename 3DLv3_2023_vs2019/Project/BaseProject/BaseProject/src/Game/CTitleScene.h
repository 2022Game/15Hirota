#pragma once
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"
#include "CImage.h"

class CSound;
class CTitleMenu;
class CTitleUI;
class CTitleStage;
class CStageSky;

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
	/*CImage* mTitle;
	CTitleMenu* mpTitleMenu;*/
	CTitleUI* mpTitleUI;
	CTitleStage* mpTitleStage;
	CStageSky* mpStageSky;
};