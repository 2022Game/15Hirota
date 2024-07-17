#include "COperationInstructionsUI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CSignboard.h"
#include "CPlayer.h"
#include "CStageManager.h"

// UIデータ
const COperationInstructionsUI::UIData COperationInstructionsUI::UI_DATA[] =
{
	// 画像名
	{"TUI"},
	{"EnterUI"},
};

// コンストラクタ
COperationInstructionsUI::COperationInstructionsUI(std::string path)
	: mPath(path)
	, mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
{
	//// UI画像データ
	//int datasize = ARRAY_SIZE(UI_DATA);
	//for (int i = 0; i < datasize; i++)
	//{
	//	const UIData& data = UI_DATA[i];
	//	CImage* ui = new CImage
	//	(
	//		data.UIName.c_str(), // UIDataの画像名を使用
	//		ETaskPriority::eUI,
	//		0,
	//		ETaskPauseType::eGame,
	//		false, false
	//	);
	//	CVector2 size(150.0f, 150.0f);
	//	mUIimages[i]->SetSize(size);
	//	mUIimages[i]->SetCenter(size * 0.5f);
	//	mUIimages.push_back(ui);
	//}

	// バックグラウンド画像
	mpUI = new CImage
	(
		"TUI",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eGame,
		false, false
	);
	CVector2 size(150.0f, 150.0f);
	mpUI->SetSize(size);
	mpUI->SetCenter(size * 0.5f);

	// バックグラウンド画像
	mpBG = new CImage
	(
		"PBarImage",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eGame,
		false, false
	);
	mpBG->SetSize(size);
	mpBG->SetCenter(size * 0.5f);
}

// デストラクタ
COperationInstructionsUI::~COperationInstructionsUI()
{
	SAFE_DELETE(mpBG);
	SAFE_DELETE(mpUI);
	/*CStageManager::RemoveTask(this);
	int size = mUIimages.size();
	for (int i = 0; i < size; i++)
	{
		CImage* img = mUIimages[i];
		mUIimages[i] = nullptr;
		SAFE_DELETE(img);
	}
	mUIimages.clear();*/
}

// 削除
void COperationInstructionsUI::Kill()
{
	CTask::Kill();
}

// 画像のセンターサイズを設定
void COperationInstructionsUI::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ワールド座標を設定
void COperationInstructionsUI::SetWorldPos(const CVector& worldPos)
{
	// 現在のカメラを取得
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// 設定されたワールド座標をスクリーン座標に変換
	CVector screenPos = cam->WorldToScreenPos(worldPos);

	// 設定されたワールド座標がカメラの背後であれば、
	// ゲージを表示しない
	if (screenPos.Z() < 0.0f)
	{
		SetShow(false);
		return;
	}

	// スクリーン座標をUIの位置として設定
	mPosition = screenPos;
}

// 更新処理
void COperationInstructionsUI::Update()
{
	// ゲージの位置を設定
	CVector2 pos = mPosition;

	/*for (CImage* img : mUIimages)
	{
		img->SetPos(pos);
		img->SetShow(IsShow());
		img->Update();
	}*/

	mpBG->SetPos(pos);
	mpBG->SetShow(IsShow());
	mpUI->SetPos(pos);
	mpUI->SetShow(IsShow());
}

// 描画処理
void COperationInstructionsUI::Render()
{
	mpBG->Render();
	mpUI->Render();

	/*int size = ARRAY_SIZE(UI_DATA);
	for (int i = 0; i < size; i++)
	{
		mUIimages[i]->Render();
	}*/
}