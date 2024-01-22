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

    // ���@���K�[�h�̐��𑝂₷
    static void IncrementVanguardCount();
    // ���@���K�[�h�̐������炷
    static void DecrementVanguardCount();
    // ���@���K�[�h�̐����擾
    static int GetVanguardCount();

private:
    // �\���W���[�̐�
    static int enemyCount;
    // ���@���K�[�h�̐�
    static int VanguardCount;
};
#endif