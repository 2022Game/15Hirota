#include "CEnemyManager.h"

int CEnemyManager::enemyCount = 0;
int CEnemyManager::VanguardCount = 0;

// �G�l�~�[�}�l�W���[�̃C���X�^���X
CEnemyManager* CEnemyManager::spInstance = nullptr;

//�C���X�^���X�̃|�C���^�̎擾
CEnemyManager* CEnemyManager::Instance()
{
    if (spInstance == nullptr)
    {
        spInstance = new CEnemyManager();
    }
    return spInstance;
}

// �G�L�����N�^�[�̃��X�g���擾����
const std::vector<CXCharacter*>& CEnemyManager::GetEnemies() const
{
    return enemies;
}

// �G�����X�g�ɒǉ�����
void CEnemyManager::AddEnemy(CXCharacter* enemy)
{
    if (enemy != nullptr)
    {
        enemies.push_back(enemy);
    }
}

// �G�����X�g���珜�O����
void CEnemyManager::RemoveEnemy(CXCharacter* enemy)
{
    if (enemy == nullptr)
        return;

    // enemies �z����ŁA�w�肳�ꂽ enemy ��T���č폜
    auto it = std::find(enemies.begin(), enemies.end(), enemy);
    if (it != enemies.end())
    {
        // ���������ꍇ�A�z�񂩂�폜
        enemies.erase(it);
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
