using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class ActorAction : MonoBehaviour
{
    public ActorMovement actorMovement;
    public ActorOperation actorOperation;
    public ActorAttack actorAttack;
    public ActorUseItems actorUseItems;

    private EAct action = EAct.KeyInput;

    // �Ǝ��̍X�V���\�b�h
    public void Proc()
    {
        switch (action)
        {
            case EAct.KeyInput: KeyInput(); break;
            case EAct.ActBegin: ActBegin(); break;
            case EAct.Act: Act(); break;
            case EAct.ActEnd: ActEnd(); break;
            case EAct.MoveBegin: MoveBegin(); break;
            case EAct.Move: Move(); break;
            case EAct.MoveEnd: MoveEnd(); break;
            case EAct.TurnEnd: TurnEnd(); break;
        }
    }

    // ���݂̍s����Ԃ�Ԃ�
    public EAct GetAction() => action;

    // �ҋ@��
    private void KeyInput()
    {
        action = actorOperation.Operate(actorMovement);
        if (action != EAct.MoveBegin) actorMovement.Stop();
    }

    // �A�N�V�������n�߂�
    private void ActBegin()
    {
        actorAttack.Attack();
        action = EAct.Act;
    }

    // �A�N�V������
    private void Act()
    {
        action = actorAttack.Attacking();
        if (action == EAct.ActEnd)
        {
            Pos2D grid = DirUtil.GetNewGrid(actorMovement.grid, actorMovement.direction);
            actorAttack.DamageOpponent(GetComponentInParent<Field>().GetExistActor(grid.x, grid.z));
        }
    }

    // �A�N�V�������I�����
    private void ActEnd()
    {
        action = EAct.TurnEnd;
    }

    // �ړ����n�߂�
    private void MoveBegin()
    {
        actorMovement.Walk();
        action = EAct.Move;
    }

    // �ړ���
    private void Move()
    {
        action = actorMovement.Walking();
        if (action == EAct.MoveEnd) actorUseItems.PickUp();
    }

    // �ړ����I�����
    private void MoveEnd()
    {
        action = EAct.TurnEnd;
    }

    // �^�[�����I�����
    private void TurnEnd()
    {
        action = EAct.KeyInput;
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // ���s�A�j���[�V�������X�g�b�v������
    public void StopWalkingAnimation()
    {
        actorMovement.Stop();
    }
}
