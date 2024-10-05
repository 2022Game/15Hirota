using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerOperation : MonoBehaviour
{
    public ActorMovement actorMovement;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    private void Update()
    {
        EDir d = DirUtil.KeyToDir();
        if (d != EDir.Pause)
        {
            actorMovement.SetDirection(d);
            actorMovement.Walk();
        }
    }
}
