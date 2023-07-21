#include "CField.h"
#include "CTaskManager.h"

//コンストラクタ
CField::CField()
{
	//ポーズの種類を設定
	SetPauseType(TaskPauseType::eGame);
	//タスクの優先度を設定
	mPriority = (int)TaskPriority::eBackground;
}

//デストラクタ
CField::~CField()
{
}

//更新処理
void CField::Update()
{
	CTransform::Update();
}