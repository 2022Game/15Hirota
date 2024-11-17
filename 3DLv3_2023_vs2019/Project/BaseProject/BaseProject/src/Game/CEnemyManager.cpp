#include "CEnemyManager.h"

int CEnemyManager::enemyCount = 0;
int CEnemyManager::VanguardCount = 0;

// エネミーマネジャーのインスタンス
CEnemyManager* CEnemyManager::spInstance = nullptr;

CEnemyManager* CEnemyManager::Instance()
{
    if (spInstance == nullptr)
    {
        spInstance = new CEnemyManager();
    }
    return spInstance;
}

std::vector<CXCharacter*> CEnemyManager::GetEnemies()
{
    return enemies;
}

void CEnemyManager::AddEnemy(CXCharacter* enemy)
{
    if (enemy != nullptr)
    {
        enemies.push_back(enemy);
    }
}

void CEnemyManager::RemoveEnemy(CXCharacter* enemy)
{
    if (enemy == nullptr)
        return;

    // enemies 配列内で、指定された enemy を探して削除
    auto it = std::find(enemies.begin(), enemies.end(), enemy);
    if (it != enemies.end())
    {
        enemies.erase(it);  // 見つかった場合、配列から削除
    }
}

// ソルジャーの数を増やす
void CEnemyManager::IncrementSoldierCount()
{
    enemyCount++;
}

// ソルジャーの数を減らす
void CEnemyManager::DecrementSoldierCount()
{
    enemyCount--;
}

// ソルジャーの数を取得
int CEnemyManager::GetSoldierCount()
{
    return enemyCount;
}

// ヴァンガードの数を増やす
void CEnemyManager::IncrementVanguardCount()
{
    VanguardCount++;
}

// ヴァンガードの数を減らす
void CEnemyManager::DecrementVanguardCount()
{
    VanguardCount--;
}

// ヴァンガードの数を取得
int CEnemyManager::GetVanguardCount()
{
    return VanguardCount;
}

CEnemyManager::CEnemyManager()
{
    // インスタンスの設定
    spInstance = this;
}

CEnemyManager::~CEnemyManager()
{
    spInstance = nullptr;
}
