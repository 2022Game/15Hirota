#include "CEnemyManager.h"

int CEnemyManager::enemyCount = 0;

// �\���W���[�̐��𑝂₷
void CEnemyManager::IncrementSoldierCount()
{
    enemyCount++;
}

// �\���W���[�̐������炷
void CEnemyManager::DecrementSoldierCount()
{
    enemyCount--;
}

// �\���W���[�̐����擾
int CEnemyManager::GetSoldierCount()
{
    return enemyCount;
}