#include "CTitleMenu.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CStageManager.h"
#include "CGameManager.h"

#define MENU_ALPHA 0.75f

// コンストラクタ
CTitleMenu::CTitleMenu()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mSelectIndex(0)
	, mIsOpened(false)
{
	mpTitleMenu = new CImage
	(
		"UI/menu_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpTitleMenu->SetCenter(mpTitleMenu->GetSize() * 0.5f);
	mpTitleMenu->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpTitleMenu->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);

	int stageMenuCount = 3;
	float spaceX = (float)WINDOW_WIDTH / (stageMenuCount + 1);
	for (int i = 0; i < stageMenuCount; i++)
	{
		CImage* item = new CImage
		(
			"UI/menu_item.png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		item->SetSize(200.0f, 150.0f);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = spaceX * (i + 1) - item->GetSize().X() / 2.0f + 100.0f;
		float posY = (float)WINDOW_HEIGHT / 2.0f;
		item->SetPos(posX, posY);
		item->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mTitleMenuItems.push_back(item);
	}

	mpTitleMenuFrame = new CImage
	(
		"UI/menu_item_select.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpTitleMenuFrame->SetSize(200.0f, 150.0f);
	mpTitleMenuFrame->SetCenter(mpTitleMenuFrame->GetSize() * 0.5f);
	mpTitleMenuFrame->SetColor(1.0f, 0.1f, 0.0f, MENU_ALPHA);

	SetEnable(false);
	SetShow(false);
}

// デストラクタ
CTitleMenu::~CTitleMenu()
{
	// 削除されるときにメニューが開いたままであれば、
	// メニューを閉じる
	if (mIsOpened)
	{
		Close();
	}
}

// 開く
void CTitleMenu::Open()
{
	// 既に開いていたら、処理しない
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
void CTitleMenu::Close()
{
	// すでに閉じていたら、処理しない
	if (!mIsOpened) return;

	SetEnable(false);
	SetShow(false);
	CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
	// メニューを開いたフラグを下す
	mIsOpened = false;
}

void CTitleMenu::HandleMouseInput()
{
	// マウスがクリックされたかどうかをチェック
	if (CInput::PushKey(VK_LBUTTON))
	{
		// マウスの座標を取得
		CVector2 mousePos = CInput::GetMousePos();

		// マウスがクリックされた位置をチェックし、該当するメニュー項目を特定
		for (int i = 0; i < mTitleMenuItems.size(); i++)
		{
			CImage* item = mTitleMenuItems[i];
			// メニュー項目の左上の座標と右下の座標を取得
			CVector2 itemPos = item->GetPos();
			CVector2 itemSize = item->GetSize();
			float left = itemPos.X() - itemSize.X() / 2.2f;		// 左端の座標
			float right = itemPos.X() + itemSize.X() / 2.2f;	// 右端の座標
			float top = itemPos.Y() - itemSize.Y() / 3.5f;		// 上端の座標
			float bottom = itemPos.Y() + itemSize.Y() / 3.5f;	// 下端の座標

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

bool CTitleMenu::IsOpened() const
{
	return mIsOpened;
}

// どのメニューにするか
void CTitleMenu::Decide(int select)
{
	switch (select)
	{
	case 0:
		break;
	case 1:
		CTitleMenu::Close();
		CSceneManager::Instance()->LoadScene(EScene::eGame);
		/*CStageManager::LoadStage(0);
		CGameManager::SetStageNo(0);*/
		break;
	case 2:
		break;
	}
}

// 更新処理
void CTitleMenu::Update()
{
	HandleMouseInput(); // マウス入力を処理
	if (IsOpened())
	{
		CInput::ShowCursor(true);
	}
	else
	{
		CInput::ShowCursor(false);
	}
	/*int itemCount = mTitleMenuItems.size();
	if (CInput::PushKey(VK_LEFT))
	{
		mSelectIndex = (mSelectIndex + itemCount - 1) % itemCount;
	}
	else if (CInput::PushKey(VK_RIGHT))
	{
		mSelectIndex = (mSelectIndex + 1) % itemCount;
	}
	else if (CInput::PushKey(VK_RETURN))
	{
		Decide(mSelectIndex);
	}*/

	mpTitleMenu->Update();
	for (CImage* item : mTitleMenuItems)
	{
		item->Update();
	}
	mpTitleMenuFrame->Update();
}

// 描画処理
void CTitleMenu::Render()
{
	mpTitleMenu->Render();
	for (int i = 0; i < mTitleMenuItems.size(); i++)
	{
		CImage* item = mTitleMenuItems[i];
		item->Render();

		if (i == mSelectIndex)
		{
			mpTitleMenuFrame->SetPos(item->GetPos());
			mpTitleMenuFrame->Render();
		}
	}
}