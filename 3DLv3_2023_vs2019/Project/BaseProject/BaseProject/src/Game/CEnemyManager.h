#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H

// �G�̐��̃N���X
class CEnemyManager
{
public:
    // �\���W���[�̐��𑝂₷
    static void IncrementSoldierCount();
    // �\���W���[�̐������炷
    static void DecrementSoldierCount();
    // �\���W���[�̐����擾
    static int GetSoldierCount();

private:
    // �G�̐�
    static int enemyCount;
};
#endif