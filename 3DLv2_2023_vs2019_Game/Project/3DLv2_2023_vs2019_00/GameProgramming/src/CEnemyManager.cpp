#include "CEnemyManager.h"

//CEnemyManagerのインスタンスを定義
CEnemyManager* CEnemyManager::mpInstance = nullptr;

//コンストラクタ
CEnemyManager::CEnemyManager()
{
}

//デストラクタ
CEnemyManager::~CEnemyManager()
{
	//CEnemyManagerで管理していたエネミーも全て破棄
	for (int i = 0; i < mEnemyList.size(); i++)
	{
		delete mEnemyList[i];
	}
	//念のためリストもクリアしておく
	mEnemyList.clear();
	//念のためインスタンスも空にしておく
	mpInstance = nullptr;
}

//CEnemyManagerのインスタンスを取得
CEnemyManager* CEnemyManager::Instance()
{
	//インスタンスが生成されていなければ、生成する
	if (mpInstance == nullptr)
	{
		mpInstance = new CEnemyManager();
	}
	return mpInstance;
}

//エネミーをリストに追加
void CEnemyManager::Add(CEnemy* enemy)
{
	//リストの最後尾に追加
	mEnemyList.push_back(enemy);
}

//エネミーをリストから取り除く
void CEnemyManager::Remove(CEnemy* enemy)
{
	//指定されたエネミーをリストから検索
	auto find = std::find
	(
		mEnemyList.begin(),
		mEnemyList.end(),
		enemy
	);
	//指定されたエネミーがリスト内に存在すれば
	if (find != mEnemyList.end())
	{
		//リストから取り除く
		mEnemyList.erase(find);
	}
}

//エネミーのリストを取得
const std::vector<CEnemy*>& CEnemyManager::GetEnemyList() const
{
	return mEnemyList;
}
