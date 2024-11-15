#include "CEnemyManager.h"

int CEnemyManager::enemyCount = 0;
int CEnemyManager::VanguardCount = 0;

// �G�l�~�[�}�l�W���[�̃C���X�^���X
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

CEnemyManager::CEnemyManager()
{
    // �C���X�^���X�̐ݒ�
    spInstance = this;
}

CEnemyManager::~CEnemyManager()
{
    spInstance = nullptr;
}
