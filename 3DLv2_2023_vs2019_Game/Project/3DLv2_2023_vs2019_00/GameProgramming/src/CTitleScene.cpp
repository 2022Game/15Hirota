#include "CTitleScene.h"
#include "main.h"
#include "CSceneManager.h"

//コンストラクタ
CTitleScene::CTitleScene()
	:CSceneBase(EScene::eTitle)
	,mBgImage(nullptr)
{
}

//デストラクタ
CTitleScene::~CTitleScene()
{
}

//シーン読み込み
void CTitleScene::Load()
{
	//ここでタイトル画面に必要な
	//リソースの読み込みやクラスの生成を行う
	//フェード背景用の白イメージを読み込み
	//mBgImage = new CImage("White.png");
	////背景の色設定
	//mBgImage->SetColor(1.0f,0.0f, 0.0f, 1.0f);
	//mBgImage->SetPos(0.0f, 0.0f);
	//mBgImage->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// 新しい画像を読み込む
	mBgImage1 = new CImage("Title.png");	//後で決める
	// 画像の設定（位置やサイズなど）
	mBgImage1->SetPos(200.0f, 150.0f);
	mBgImage1->SetSize(400, 300);
}

//シーンの更新処理
void CTitleScene::Update()
{
	if (mInput.PushKey('T'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eGame);
	}
	else
	{
		if (mBgImage != nullptr)
		{
			mBgImage->Render();
		}
		if (mBgImage1 != nullptr)
		{
			mBgImage1->Render();
		}
	}
}