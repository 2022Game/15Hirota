#include "CGameOverScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CTitleScene.h"
#include "CCamera.h"

#define GAMEOVER_IMAGE "\\UI\\GameOver.png"

CGameOverScene::CGameOverScene()
	:CSceneBase(EScene::eOver)
	,mpImage(nullptr)
{
}

CGameOverScene::~CGameOverScene()
{
	if (mpImage != nullptr)
	{
		delete mpImage;
		mpImage = nullptr;
	}
}

void CGameOverScene::Load()
{
	mpImage = new CImage(GAMEOVER_IMAGE);
	mpImage->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);
}

void CGameOverScene::Update()
{
	if (CInput::PushKey('T'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}
}