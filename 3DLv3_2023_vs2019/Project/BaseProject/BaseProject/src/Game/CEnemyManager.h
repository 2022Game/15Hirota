#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H

class CEnemyManager
{
public:
    // �\���W���[�̐��𑝂₷
    static void IncrementEnemyCount();
    // �\���W���[�̐������炷
    static void DecrementEnemyCount();
    // �\���W���[�̐����擾
    static int GetEnemyCount();

private:
    static int enemyCount;
};
#endif