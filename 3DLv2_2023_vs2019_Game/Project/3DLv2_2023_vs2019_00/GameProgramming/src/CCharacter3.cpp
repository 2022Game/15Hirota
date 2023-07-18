#include "CCharacter3.h"
#include "CApplication.h"

CCharacter3::CCharacter3()
	:mpModel(nullptr)
	, mTag(EZERO)
{
	SetPauseType(TaskPauseType::eGame);

	//タスクリストに追加
//	CApplication::TaskManager()->Add(this);
	CTaskManager::Instance()->Add(this);
}

CCharacter3::CCharacter3(int priority)
	:mpModel(nullptr)
	, mTag(EZERO)
{
	SetPauseType(TaskPauseType::eGame);

	mPriority = priority;
	CTaskManager::Instance()->Add(this);
}

CCharacter3::ETag CCharacter3::Tag()
{
	return mTag;
}

CCharacter3::~CCharacter3()
{
	//タスクリストから削除
//	CApplication::TaskManager()->Remove(this);
	CTaskManager::Instance()->Remove(this);
}

void CCharacter3::Model(CModel* m)
{
	mpModel = m;
}

//描画処理
void CCharacter3::Render()
{
	mpModel->Render(mMatrix);
}

void CCharacter3::TakeDamage(int damege)
{
	//与えられたダメージ分、HPを減らす
	mHp -= damege;
	{
		//キャラクターを殺す処理
		mEnabled = false;
	}
}

bool CCharacter3::IsDeath()
{
	//HPが0以下なら死んでいる
	return mHp <= 0;;
}