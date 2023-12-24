#include "CStage1.h"
#include "CMoveFloor.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CField.h"

// コンストラクタ
CStage1::CStage1()
{
	mStageNo = 0;
}

// デストラクタ
CStage1::~CStage1()
{
	
}

// ステージ読み込み
void CStage1::Load()
{
	// フィールド
	CField* field = new CField();
	AddTask(field);


	// 四角モデル
	CModel* FloorModel = new CModel();
	CMoveFloor* floor = new CMoveFloor(floor, 
		CVector(-20.0f, -20.0f, -340.0f), 
		CVector(5.5f, 1.0f, 3.25f), 
		CVector(0.0f, 0.0f, 0.0f), 
		5.0f);
	AddTask(floor);

	// ゴールオブジェクト
	CGoalObject* goal = new CGoalObject(goal,
		CVector(0.0f, 0.0f, -100.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f));
	AddTask(goal);

	// 岩1
	CStone1* stone1 = new CStone1(stone1,
		CVector(-80.0f, 0.0f, -200.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(stone1);
}

// ステージ破棄
void CStage1::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();
}