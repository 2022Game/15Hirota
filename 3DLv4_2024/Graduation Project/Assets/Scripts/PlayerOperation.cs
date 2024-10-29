using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerOperation : ActorOperation
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // éüÇ…çsÇ§ó\íËÇÃçsìÆèÛë‘Çï‘Ç∑
    public override EAct Operate(ActorMovement actorMovement, ActorParamsController actorParam)
    {
        if (!Input.anyKey) return EAct.KeyInput;
        bool isConfusion = actorParam.IsConfusion();
        bool isParalysis = actorParam.CantAction();
        if (Input.GetKey(KeyCode.Space))
        {
            if (isParalysis) return EAct.ActEnd;
            if (isConfusion) actorMovement.SetDirection(DirUtil.RandomDirection());
            return EAct.ActBegin;
        }
        EDir d = DirUtil.KeyToDir();
        if (d != EDir.Pause)
        {
            if (isParalysis) return EAct.ActEnd;
            if (!actorMovement.IsMoveBegin(d))
            {
                actorMovement.SetDirection(d);
                return EAct.KeyInput;
            }
            if (isConfusion)
            {
                EDir d2 = DirUtil.RandomDirection();
                if (actorMovement.IsMoveBegin(d2))
                {
                    actorMovement.SetDirection(d2);
                    return EAct.MoveBegin;
                }
            }
            else
            {
                actorMovement.SetDirection(d);
                return EAct.MoveBegin;
            }
        }
        return EAct.KeyInput;
    }
}
