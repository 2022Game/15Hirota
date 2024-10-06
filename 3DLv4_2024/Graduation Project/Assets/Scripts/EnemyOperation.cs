using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyOperation : ActorOperation
{
    // ���ɍs���\��̍s����Ԃ�Ԃ�
    public override EAct Operate(ActorMovement actorMovement)
    {
        return RandomActionAI(actorMovement);
    }

    // �����_���ȍs��AI
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
