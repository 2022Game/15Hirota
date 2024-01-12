#include "CEnemyManager.h"


int CEnemyManager::enemyCount = 0;

void CEnemyManager::IncrementEnemyCount()
{
    enemyCount++;
}

void CEnemyManager::DecrementEnemyCount()
{
    enemyCount--;
}

int CEnemyManager::GetEnemyCount()
{
    return enemyCount;
}