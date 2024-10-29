using System.Collections;
using System.Collections.Generic;
using UnityEditor.VersionControl;
using UnityEngine;
using UnityEngine.UIElements;

public class ActorMovement : ObjectMovement
{
    public Animator animator;
    public float speed = 0.9f;
    public float speedDampTime = 0.1f;

    // readonly : 読み込み専用
    private readonly int hashSpeedPara = Animator.StringToHash("Speed");

    // 移動開始できるかどうか
    public bool IsMoveBegin(EDir direction = EDir.Pause)
    {
        if (direction == EDir.Pause) direction = this.direction;
        newGrid = grid;
        newGrid = DirUtil.Move(GetComponentInParent<Field>(), grid, direction);
        return !grid.Equals(newGrid);
    }

    // 歩行開始
    public void Walk()
    {
        if (Move()) animator.SetFloat(hashSpeedPara, speed, speedDampTime, Time.deltaTime);
    }

    // 歩行中
    public EAct Walking()
    {
        animator.SetFloat(hashSpeedPara, speed, speedDampTime, Time.deltaTime);
        return Moving();
    }

    // 停止
    public void Stop()
    {
        if (animator.GetFloat(hashSpeedPara) > 0.0f)
        {
            animator.SetFloat(hashSpeedPara, 0.0f, speedDampTime, Time.deltaTime);
        }
    }

    // 引数で渡された方へ振り向く
    public void TurnAround(EDir d)
    {
        bool isParalysis = GetComponent<ActorParamsController>().CantAction();
        if (isParalysis) return;
        SetDirection(DirUtil.ReverseDirection(d));
    }
}