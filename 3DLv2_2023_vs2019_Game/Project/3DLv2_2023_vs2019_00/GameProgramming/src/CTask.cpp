#include "CTask.h"

//コンストラクタ
CTask::CTask(EScene scene)
	: mpNext(nullptr)
	, mpPrev(nullptr)
	, mPriority((int)TaskPriority::eDefault)
	, mEnabled(true)
	, mPauseType(TaskPauseType::eDefault)
	, mSceneType(scene)
{
}

//デストラクタ
CTask::~CTask()
{
}

//更新
void CTask::Update()
{
}

//描画
void CTask::Render()
{
}

//ポーズの種類を設定
void CTask::SetPauseType(TaskPauseType type)
{
	mPauseType = type;
}

//ポーズの種類を取得
TaskPauseType CTask::GetPauseType() const
{
	return mPauseType;
}

//所属するシーンを設定
void CTask::SetSceneType(EScene scene)
{
	mSceneType = scene;
}

//所属するシーンを取得
EScene CTask::GetSceneType() const
{
	return mSceneType;
}