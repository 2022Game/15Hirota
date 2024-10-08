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

    // readonly : �ǂݍ��ݐ�p
    private readonly int hashSpeedPara = Animator.StringToHash("Speed");

    // �ړ��J�n�ł��邩�ǂ���
    public bool IsMoveBegin()
    {
        newGrid = DirUtil.Move(GetComponentInParent<Field>(), grid, direction);
        return !grid.Equals(newGrid);
    }

    // ���s�J�n
    public void Walk()
    {
        if (Move()) animator.SetFloat(hashSpeedPara, speed, speedDampTime, Time.deltaTime);
    }

    // ���s��
    public EAct Walking()
    {
        animator.SetFloat(hashSpeedPara, speed, speedDampTime, Time.deltaTime);
        return Moving();
    }

    // ��~
    public void Stop()
    {
        if (animator.GetFloat(hashSpeedPara) > 0.0f)
        {
            animator.SetFloat(hashSpeedPara, 0.0f, speedDampTime, Time.deltaTime);
        }
    }
}