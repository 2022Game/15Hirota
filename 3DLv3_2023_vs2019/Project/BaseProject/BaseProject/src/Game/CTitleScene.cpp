#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CBGMManager.h"

#define TITLE_IMAGE "UI\\Title.png"

//コンストラクタ
CTitleScene::CTitleScene()
	: CSceneBase(EScene::eTitle)
{
}

//デストラクタ
CTitleScene::~CTitleScene()
{
}

//シーン読み込み
void CTitleScene::Load()
{
	// 背景色設定
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// タイトルBGMを再生
	CBGMManager::Instance()->Play(EBGMType::eTitle);

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
