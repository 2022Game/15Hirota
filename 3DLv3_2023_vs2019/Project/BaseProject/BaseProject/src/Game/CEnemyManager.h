#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H

class CEnemyManager
{
public:
    // ソルジャーの数を増やす
    static void IncrementEnemyCount();
    // ソルジャーの数を減らす
    static void DecrementEnemyCount();
    // ソルジャーの数を取得
    static int GetEnemyCount();

private:
    static int enemyCount;
};
#endif