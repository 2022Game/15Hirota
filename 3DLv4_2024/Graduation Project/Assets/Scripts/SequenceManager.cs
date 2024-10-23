using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using UnityEngine;

public class SequenceManager : MonoBehaviour
{
    public ActorAction playerAction;
    public GameObject enemies;
    public InventoryAction inventoryAction;

    private List<ActorAction> actEnemies = new List<ActorAction>();
    private List<ActorAction> moveEnemies = new List<ActorAction>();
    private List<ActorAction> operatedEnemies = new List<ActorAction>();
    private bool isEnemyDeterminedBehaviour = false;

    // Update is called once per frame
    void Update()
    {
        EAct iAct = inventoryAction.GetAction();
        if (iAct != EAct.KeyInput && iAct != EAct.ActEnd && iAct != EAct.TurnEnd)
        {
            inventoryAction.Proc();
            return;
        }
        EAct pAct = (iAct == EAct.ActEnd || iAct == EAct.TurnEnd) ? iAct : playerAction.GetAction();
        if (pAct == EAct.KeyInput || pAct == EAct.ActBegin || pAct == EAct.Act)
        {
            inventoryAction.Proc();
            if (iAct != EAct.KeyInput) return;
            playerAction.Proc();
            AllEnemyStopWalkingAnimation();
            return;
        }
        if (pAct == EAct.TurnEnd)
        {
            AllOperatedProc(iAct == EAct.TurnEnd);
            isEnemyDeterminedBehaviour = false;
            operatedEnemies.Clear();
            DecreaseFood();
            return;
        }
        if (pAct == EAct.ActEnd && !isEnemyDeterminedBehaviour)
        {
            AllEnemyDetermineBehaviour();
            return;
        }
        if (actEnemies.Count < 1 && moveEnemies.Count < 1 && (pAct == EAct.ActEnd || pAct == EAct.MoveEnd))
        {
            AllOperatedProc(iAct == EAct.ActEnd);
            return;
        }
        if (pAct == EAct.MoveBegin)
        {
            playerAction.Proc();
            AllEnemyDetermineBehaviour();
            isEnemyDeterminedBehaviour = true;
            return;
        }
        if (pAct == EAct.ActEnd && actEnemies.Count < 1)
        {
            OperatedEnemyProc(moveEnemies, EAct.MoveEnd);
            return;
        }
        if (pAct == EAct.ActEnd && isEnemyDeterminedBehaviour)
        {
            EnemyAct();
            return;
        }
        if (pAct == EAct.MoveEnd && moveEnemies.Count < 1)
        {
            EnemyAct();
            return;
        }
        if (isEnemyDeterminedBehaviour)
        {
            if (pAct == EAct.Move)
            {
                playerAction.Proc();
            }
            OperatedEnemyProc(moveEnemies, EAct.MoveEnd);
            return;
        }
    }

    // 動作したキャラクター全員の更新メソッドを呼び出す
    private void AllOperatedProc(bool isUseItem)
    {
        if (isUseItem) inventoryAction.Proc();
        else playerAction.Proc();
        foreach (var enemyAction in operatedEnemies)
        {
            enemyAction.Proc();
        }
    }

    // 全敵の動作決定
    private void AllEnemyDetermineBehaviour()
    {
        ActorAction[] src = this.enemies.GetComponentsInChildren<ActorAction>();
        List<ActorAction> enemies = new List<ActorAction>();
        enemies.AddRange(src);
        Pos2D pgrid = playerAction.GetComponent<ActorMovement>().grid;
        System.Comparison<ActorAction> p = (a, b) =>
        {
            Pos2D agrid = a.GetComponent<ActorMovement>().grid;
            Pos2D bgrid = b.GetComponent<ActorMovement>().grid;
            int p_a = Mathf.Abs(agrid.x - pgrid.x) + Mathf.Abs(agrid.z - pgrid.z);
            int p_b = Mathf.Abs(bgrid.x - pgrid.x) + Mathf.Abs(bgrid.z - pgrid.z);
            return p_a - p_b;
        };
        enemies.Sort(p);
        foreach (var enemyAction in enemies)
        {
            enemyAction.Proc();
            EAct eAct = enemyAction.GetAction();
            if (eAct == EAct.ActBegin)
            {
                actEnemies.Add(enemyAction);
                operatedEnemies.Add(enemyAction);
            }
            else if ( eAct == EAct.MoveBegin)
            {
                moveEnemies.Add(enemyAction);
                operatedEnemies.Add(enemyAction);
                enemyAction.Proc();
            }
        }
        actEnemies.Reverse();
        moveEnemies.Reverse();
        isEnemyDeterminedBehaviour = true;
    }

    // 敵を動作させる
    private void OperatedEnemyProc(List<ActorAction> enemies, EAct targetAct, bool isAll = true)
    {
        for (int i = enemies.Count - 1; i >= 0; i--)
        {
            enemies[i].Proc();
            EAct eAct = enemies[i].GetAction();
            if (eAct == targetAct)
            {
                enemies.RemoveAt(i);
                continue;
            }
            if (!isAll) break;
        }
    }

    // 前敵の歩行アニメーションを止める
    private void AllEnemyStopWalkingAnimation()
    {
        foreach (var enemyAction in enemies.GetComponentsInChildren<ActorAction>())
        {
            enemyAction.StopWalkingAnimation();
        }
    }

    // 敵が行動する
    private void EnemyAct()
    {
        OperatedEnemyProc(actEnemies, EAct.ActEnd, false);
        playerAction.StopWalkingAnimation();
        AllEnemyStopWalkingAnimation();
    }

    /**
    * 全敵を行動させる
    */
    private void AllEnemyProc()
    {
        foreach (var enemyAction in enemies.GetComponentsInChildren<ActorAction>())
        {
            enemyAction.Proc();
        }
    }

    // 満腹度を減少させる
    private void DecreaseFood()
    {
        playerAction.GetComponent<ActorParamsController>().DecreaseFood();
    }
}
