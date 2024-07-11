#include "CStuffedRoll.h"
#include "CText.h"
#include "CImage.h"
#include "CFont.h"
#include "CGameManager.h"
#include "CTaskManager.h"
#include "CPlayer.h"

// スタッフロールクラスのインスタンス
CStuffedRoll* CStuffedRoll::spInstance = nullptr;

CStuffedRoll* CStuffedRoll::Instance()
{
	if (spInstance == nullptr)
	{
		spInstance = new CStuffedRoll();
	}
	return spInstance;
}

const CStuffedRoll::StafData CStuffedRoll::STAFF_DATA[] =
{
	{"Game Title\n \nDemon Adventure", 3.0f},
	{"Producerdirector\n \nTanaka Taro", 7.0f},
	{"Director\n \nTanaka Taro", 11.0f},
	{"Designer\n \nTanaka Taro", 15.0f},
	{"Programmer\n \nTanaka Taro", 19.0f},
	{"Creator\n \nTanaka Taro", 23.0f},
	{"Debugger\n \nTanaka Taro", 27.0f},
	{"Homeroom Teacher\n \nNamizashi Shota\n \nTakahashi Shinobu", 24.0f},
	{"スタッフ4", 31.0f},
	{"スタッフ5", 35.0f},
	{"スタッフ6", 39.0f},
	{"Thank you for playing this game!", 43.0f},
};

// コンストラクタ
CStuffedRoll::CStuffedRoll()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eDefault)
	, mStaffRollTime(0.0f)
{
	spInstance = this;

	// ロゴのフォントデータを生成
	mpFont = new CFont("res\\Font\\toroman.ttf");
	mpFont->SetFontSize(70);
	mpFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpFont->SetLineLength(WINDOW_WIDTH);

	// テキストオブジェクトと初期Y位置の設定
	int size = ARRAY_SIZE(STAFF_DATA);
	for (int i = 0; i < size; i++)
	{
		CText* text = new CText
		(
			mpFont, 70,
			CVector2(0.0f, 720.0f),
			CVector2(600.0f, 600),
			CColor(1.0f, 1.0f, 0.0f, 1.0f),
			ETaskPriority::eUI,
			0,
			ETaskPauseType::eDefault,
			false, false
		);
		mStuffedRolls.push_back(text);
		mTextYPositions.push_back(720.0f);  // 初期Y位置
	}
}

// デストラクタ
CStuffedRoll::~CStuffedRoll()
{
	spInstance = nullptr;
	int size = mStuffedRolls.size();
	for (int i = 0; i < size; i++)
	{
		CText* tex = mStuffedRolls[i];
		mStuffedRolls[i] = nullptr;
		SAFE_DELETE(tex);
	}
	mStuffedRolls.clear();
	mTextYPositions.clear();
}

// 更新処理
void CStuffedRoll::Update()
{
	mStaffRollTime += Time::DeltaTime();

	for (CText* text : mStuffedRolls)
	{
		text->Update();
	}

	CDebugPrint::Print("mTime:%f\n", mStaffRollTime);
}

// テキストを移動させる処理
void CStuffedRoll::ScrollTextUp(CText* pText, float& yPos, float speed)
{
	yPos -= speed;

	pText->SetPos(CVector2(0.0f, yPos));

	CDebugPrint::Print("Text Position: %f, %f\n", pText->GetPos().X(), pText->GetPos().Y());
	CDebugPrint::Print("yPos: %f\n", yPos);
}

// 描画処理
void CStuffedRoll::Render()
{
	int size = ARRAY_SIZE(STAFF_DATA);
	for (int i = 0; i < size; i++)
	{
		const StafData& data = STAFF_DATA[i];
		if (mStaffRollTime < data.startTime) continue;
		if (mStaffRollTime > data.startTime + 13.0f) continue;

		mStuffedRolls[i]->SetText(data.stuffName.c_str());
		// スクロール処理
		ScrollTextUp(mStuffedRolls[i], mTextYPositions[i], 1.0f);
		mStuffedRolls[i]->SetColor(1.0f, 1.0f, 0.0f);
		mStuffedRolls[i]->SetFontSize(42);
		mStuffedRolls[i]->Render();
	}
}