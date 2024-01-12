#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H

class CEnemyManager
{
public:
    static void IncrementEnemyCount();
    static void DecrementEnemyCount();
    static int GetEnemyCount();
    static void EnemyKilled();

private:
    static int enemyCount;
};
#endif