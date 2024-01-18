#include "CEnemyManager.h"

int CEnemyManager::enemyCount = 0;

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