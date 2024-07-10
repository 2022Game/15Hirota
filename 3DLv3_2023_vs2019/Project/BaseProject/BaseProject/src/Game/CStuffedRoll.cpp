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
	{"Creator\ntanakataro", 3.0f},
	{"Programmer\ntanakataro", 6.5f},
	{"Debugger\ntanakataro", 9.5f},
	{"Homeroom Teacher\nabcdefg\nhijklmn", 12.5f},
	{"スタッフ4", 15.5f},
	{"スタッフ5", 18.5f},
	{"スタッフ6", 21.5f},
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