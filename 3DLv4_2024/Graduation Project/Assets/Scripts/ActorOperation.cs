using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class ActorOperation : MonoBehaviour
{
    // ���ɍs���\��̍s����Ԃ�Ԃ�
    public abstract EAct Operate(ActorMovement actorMovement);
}
