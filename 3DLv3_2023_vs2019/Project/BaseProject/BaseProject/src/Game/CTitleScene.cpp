#include "CTitleScene.h"
#include "CTitleMenu.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CBGMManager.h"
#include "CTitleUI.h"

#define TITLE_IMAGE "UI\\Title.png"

//コンストラクタ
CTitleScene::CTitleScene()
	: CSceneBase(EScene::eTitle)
	/*, mTitle(nullptr)
	, mpTitleMenu(nullptr)*/
{
}

//デストラクタ
CTitleScene::~CTitleScene()
{
	//mpTitleMenu->Kill();
}

//シーン読み込み
void CTitleScene::Load()
{
	// タイトルメニューを作成
	//mpTitleMenu = new CTitleMenu();
	// タイトル画面はカーソル表示
	CInput::ShowCursor(true);
	// 背景色設定
	System::SetClearColor(0.2f, 0.2f, 0.2f, 0.9f);

	// タイトルBGMを再生
	CBGMManager::Instance()->Play(EBGMType::eTitle);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);

	mpTitleUI = new CTitleUI();
	AddTask(mpTitleUI);
}

//シーンの更新処理
void CTitleScene::Update()
{
	//mpTitleMenu->Open();

	// タイトル画面が
	if (mpTitleUI->IsEnd())
	{
		// ゲーム開始ならば、ゲームシーンを読み込む
		if (mpTitleUI->IsStartGame())
		{
			CSceneManager::Instance()->LoadScene(EScene::eGame);
		}
		// ゲーム終了ならば、アプリを閉じる
		else if (mpTitleUI->IsExitGame())
		{
			System::ExitGame();
		}
	}
}
