#include "CEnemyManager.h"

int CEnemyManager::enemyCount = 0;
int CEnemyManager::VanguardCount = 0;

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

// ���@���K�[�h�̐��𑝂₷
void CEnemyManager::IncrementVanguardCount()
{
    VanguardCount++;
}

// ���@���K�[�h�̐������炷
void CEnemyManager::DecrementVanguardCount()
{
    VanguardCount--;
}

// ���@���K�[�h�̐����擾
int CEnemyManager::GetVanguardCount()
{
    return VanguardCount;
}