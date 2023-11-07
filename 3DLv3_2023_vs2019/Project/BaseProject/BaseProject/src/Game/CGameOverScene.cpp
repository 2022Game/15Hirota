#include "CGameOverScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CTitleScene.h"

#define GAMEOVER_IMAGE "UI\\GameOver.png"

CGameOverScene::CGameOverScene()
	:CSceneBase(EScene::eOver)
	, mpOverImage(nullptr)
{
}

CGameOverScene::~CGameOverScene()
{
	if (mpOverImage != nullptr)
	{
		delete mpOverImage;
		mpOverImage = nullptr;
	}
}

void CGameOverScene::Load()
{
	mpOverImage = new CImage(GAMEOVER_IMAGE);
	mpOverImage->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mpOverImage->SetUV(120, 313, 1074, 873);//Œã‚Ådefine
}

void CGameOverScene::Update()
{
	if (CInput::PushKey('T'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}
}