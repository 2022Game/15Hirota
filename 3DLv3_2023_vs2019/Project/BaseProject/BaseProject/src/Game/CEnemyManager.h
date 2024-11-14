#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H
#include "CXCharacter.h"

class CPicoChan;

// �G�̐��̃N���X
class CEnemyManager
{
public:
    //�C���X�^���X�̃|�C���^�̎擾
    static CEnemyManager* Instance();
    // �G�L�����N�^�[���i�[���郊�X�g
    std::vector<CPicoChan*> enemies;
    // �G�L�����N�^�[�̃��X�g���擾����
    std::vector<CPicoChan*> GetEnemies();
    void AddEnemy(CPicoChan* enemy);

    // �\���W���[�̐��𑝂₷
    static void IncrementSoldierCount();
    // �\���W���[�̐������炷
    static void DecrementSoldierCount();
    // �\���W���[�̐����擾
    static int GetSoldierCount();

    // ���@���K�[�h�̐��𑝂₷
    static void IncrementVanguardCount();
    // ���@���K�[�h�̐������炷
    static void DecrementVanguardCount();
    // ���@���K�[�h�̐����擾
    static int GetVanguardCount();

    CEnemyManager();
    ~CEnemyManager();

private:
    // �v���C���[�̃C���X�^���X
    static CEnemyManager* spInstance;

    // �\���W���[�̐�
    static int enemyCount;
    // ���@���K�[�h�̐�
    static int VanguardCount;
};
#endif