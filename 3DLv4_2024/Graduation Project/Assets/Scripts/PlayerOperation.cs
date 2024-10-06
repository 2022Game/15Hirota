using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerOperation : ActorOperation
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Ÿ‚És‚¤—\’è‚Ìs“®ó‘Ô‚ğ•Ô‚·
    public override EAct Operate(ActorMovement actorMovement)
    {
        if (!Input.anyKey) return EAct.KeyInput;
        if (Input.GetKey(KeyCode.Space)) return EAct.ActBegin;
        EDir d = DirUtil.KeyToDir();
        if (d != EDir.Pause)
        {
            actorMovement.SetDirection(d);
            if (actorMovement.IsMoveBegin()) return EAct.MoveBegin;
        }
        return EAct.KeyInput;
    }
}
