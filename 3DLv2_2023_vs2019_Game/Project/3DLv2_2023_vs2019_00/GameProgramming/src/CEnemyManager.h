#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H
#include "CEnemy.h"

//エネミーの管理クラス
class CEnemyManager
{
public:
	//CEnemyManagerのインスタンスを取得
	static CEnemyManager* Instance();
	//コンストラクタ
	CEnemyManager();
	//デストラクタ
	~CEnemyManager();

	//エネミーをリストに追加
	void Add(CEnemy* enemy);
	//エネミーをリストから取り除く
	void Remove(CEnemy* enemy);

	//エネミーのリストを取得
	const std::vector<CEnemy*>& GetEnemyList() const;

private:
	//CEnemyManagerのインスタンス
	static CEnemyManager* mpInstance;
	//エネミーのリスト
	std::vector<CEnemy*> mEnemyList;
};

#endif