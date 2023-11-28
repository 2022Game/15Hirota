#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CPlayer.h"

#define TITLE_IMAGE "UI\\Title.png"

//コンストラクタ
CTitleScene::CTitleScene()
	: CSceneBase(EScene::eTitle)
	, mpTitle(nullptr)
{
}

//デストラクタ
CTitleScene::~CTitleScene()
{
	if (mpTitle != nullptr)
	{
		delete mpTitle;
		mpTitle = nullptr;
	}
}

//シーン読み込み
void CTitleScene::Load()
{
	// 背景色設定
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mpTitle = new CImage(TITLE_IMAGE);
	mpTitle->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mpTitle->SetUV(0, 1, 1, 0);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);
}

//シーンの更新処理
void CTitleScene::Update()
{
	if (CInput::PushKey('T'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eGame);
	}
}
