using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyOperation : ActorOperation
{
    // 次に行う予定の行動状態を返す
    public override EAct Operate(ActorMovement actorMovement)
    {
        return RandomActionAI(actorMovement);
    }

    // ランダムな行動AI
    private EAct RandomActionAI(ActorMovement actorMovement)
    {
        actorMovement.SetDirection(DirUtil.RandomDirection());
        if (Random.Range(0, 2) > 0)
        {
            actorMovement.IsMoveBegin();
            return EAct.MoveBegin;
        }
        return EAct.ActBegin;
    }
}
