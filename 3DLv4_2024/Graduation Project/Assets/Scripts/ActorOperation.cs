using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class ActorOperation : MonoBehaviour
{
    // 次に行う予定の行動状態を返す
    public abstract EAct Operate(ActorMovement actorMovement, ActorParamsController actorParam);
}
