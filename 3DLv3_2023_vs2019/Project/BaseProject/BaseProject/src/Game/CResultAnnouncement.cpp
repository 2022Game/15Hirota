#include "CResultAnnouncement.h"
#include "Maths.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CImage.h"
#include "CResult.h"

#define MENU_ALPHA 0.65f

// コンストラクタ
CResultAnnouncement::CResultAnnouncement()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mSelectIndex(0)
	, mElapsedTime(0.0f)
	, mAlpha(0.0f)
	, mIsOpened(false)
{
	/*mpResultsMenu = new CImage
	(
		"UI/menu_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpResultsMenu->SetCenter(mpResultsMenu->GetSize() * 0.5f);
	mpResultsMenu->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpResultsMenu->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);*/

	const char* menuItems[] = { "UI/ResultUI/Continue.png", "UI/ResultUI/End.png" };
	int stageMenuCount = 2;
	float spaceX = (float)WINDOW_WIDTH / (stageMenuCount + 1);
	for (int i = 0; i < stageMenuCount; i++)
	{
		CImage* item = new CImage
		(
			menuItems[i],
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		item->SetSize(400.0f, 300.0f);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = spaceX * (i + 1) - item->GetSize().X() / 2.0f + 200.0f;
		float posY = (float)WINDOW_HEIGHT / 2.0f + 100.0f;
		item->SetPos(posX, posY);
		item->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		mResultsMenuItems.push_back(item);
	}

	// リザルト画像
	int resultCount = 3;
	for (int i = 0; i < resultCount; i++)
	{
		Result Result;
		const char* imagePath;

		// mABCItemsに合わせて画像とアイテムの種類を設定
		switch (i)
		{
		case 0:
			Result = Result::A;
			imagePath = "UI/ResultUI/A.png";
			break;
		case 1:
			Result = Result::B;
			imagePath = "UI/ResultUI/B.png";
			break;
		case 2:
			Result = Result::C;
			imagePath = "UI/ResultUI/C.png";
			break;
		}

		// mABCItemsの画像を描画
		CImage* abc = new CImage
		(
			imagePath,
			ETaskPriority::eUI, 0, ETaskPauseType::eGame,
			false, false
		);
		abc->SetSize(300.0f, 350.0f);
		abc->SetCenter(abc->GetSize() * 0.5f);
		float posX = (float)WINDOW_WIDTH * 0.65f;
		float posY = (float)WINDOW_HEIGHT* 0.4f;
		abc->SetPos(posX, posY);
		abc->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
		mABCItems.push_back(std::make_pair(Result, abc));
	}

	SetEnable(false);
	SetShow(false);
}

// デストラクタ
CResultAnnouncement::~CResultAnnouncement()
{
	// 削除されるときにメニューが開いたままであれば、
	// メニューを閉じる
	if (mIsOpened)
	{
		Close();
	}
}

// 開く
void CResultAnnouncement::Open()
{
	// 既に開いていたら
	if (mIsOpened) return;

	SetEnable(true);
	SetShow(true);
	mSelectIndex = 0;
	CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
	// メニューを開いたフラグを立てる
	mIsOpened = true;
}

// 閉じる
void CResultAnnouncement::Close()
{
	// すでに閉じていたら、処理しない
	if (!mIsOpened) return;

	SetEnable(false);
	SetShow(false);
	CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
	// メニューを開いたフラグをおろす
	mIsOpened = false;
}

// マウス処理
void CResultAnnouncement::HandleMouseInput()
{
	// マウスがクリックされたかどうかをチェック
	if (CInput::PullKey(VK_LBUTTON))
	{
		// マウスの座標を取得
		CVector2 mousePos = CInput::GetMousePos();

		// マウスがクリックされた位置をチェックし、該当するメニュー項目を特定
		for (int i = 0; i < mResultsMenuItems.size(); i++)
		{
			CImage* item = mResultsMenuItems[i];
			// メニュー項目の左上の座標と右下の座標を取得
			CVector2 itemPos = item->GetPos();
			CVector2 itemSize = item->GetSize();
			float left = itemPos.X() - itemSize.X() / 2.6f;		// 左端の座標
			float right = itemPos.X() + itemSize.X() / 2.6f;	// 右端の座標
			float top = itemPos.Y() - itemSize.Y() / 9.0f;		// 上端の座標
			float bottom = itemPos.Y() + itemSize.Y() / 9.0f;	// 下端の座標

			// マウスがメニュー項目の上にあるかどうか
			if (mousePos.X() >= left && mousePos.X() <= right &&
				mousePos.Y() >= top && mousePos.Y() <= bottom)
			{
				// メニュー項目がクリックされた場合の処理
				Decide(i);
				break;
			}
		}
	}
}

bool CResultAnnouncement::IsOpened() const
{
	return mIsOpened;
}

// どのメニューにするか
void CResultAnnouncement::Decide(int select)
{
	switch (select)
	{
	case 0:
		CResultAnnouncement::Close();
		CGameManager::GameStart();
		break;
	case 1:
		System::ExitGame();
		break;
	case 2:
		break;
	}
}

// 更新処理
void CResultAnnouncement::Update()
{
	HandleMouseInput(); // マウス入力を処理
	if (IsOpened())
	{
		CInput::ShowCursor(true);
		for (const auto& itemPair : mABCItems)
		{
			CImage* item = itemPair.second;

			// 表示＆非表示に掛ける時間（秒）
			static const float fadeTime = 4.0f;
			// 最大アルファ値
			static const float fadeAlpha = 1.0f;

			//フェード背景の表示時間が経過していない
			if (mElapsedTime < fadeTime)
			{
				//経過時間に合わせてアルファ値を設定
				float alpha = mElapsedTime / fadeTime;
				item->SetAlpha(fadeAlpha * alpha);
				//1フレームの経過時間を加算（仮）
				mElapsedTime += 0.0016f;
			}
			//フェード背景の表示時間が経過した
			else
			{
				//フェード背景を完全に表示して
				item->SetAlpha(fadeAlpha);
				return;
			}
		}
	}
	else
	{
		CInput::ShowCursor(false);
		for (const auto& itemPair : mABCItems)
		{
			CImage* item = itemPair.second;
			
			item->SetAlpha(0.0f);
			mElapsedTime = 0.0f;
		}
	}

	//mpResultsMenu->Update();
	for (CImage* item : mResultsMenuItems)
	{
		item->Update();
	}
}

// 描画処理
void CResultAnnouncement::Render()
{
	//mpResultsMenu->Render();
	for (int i = 0; i < mResultsMenuItems.size(); i++)
	{
		CImage* item = mResultsMenuItems[i];
		item->Render();
	}

	// 画像パスを更新
	CResult* result = CResult::Instance();
	int score = result->GetTotalScore();

	// mABCItems内の画像を描画
	for (int i = 0; i < mABCItems.size(); i++)
	{
		// スコアに応じた結果を計算
		Result resultType;
		if (score >= 2500)
		{
			resultType = Result::A;
		}
		else if (score < 2500 && score >= 1500)
		{
			resultType = Result::B;
		}
		else
		{
			resultType = Result::C;
		}

		// アイテムの種類を取得
		Result itemResult = mABCItems[i].first;

		// 画像パスが一致するものを描画
		if (itemResult == resultType)
		{
			// 描画
			mABCItems[i].second->Render();
			Update();
		}
	}
}