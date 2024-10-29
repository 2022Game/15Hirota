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
    public ActorParamsController actorParamsController;

    private EAct action = EAct.KeyInput;
    private EffectManager_Original effect;

    private void Start()
    {
        effect = GetComponentInParent<EffectManager_Original>();
    }

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
        action = actorOperation.Operate(actorMovement, actorParamsController);
        bool isParalysis = actorParamsController.IsParalysis();
        if (isParalysis && action != EAct.KeyInput)
            effect.Play(EffectManager_Original.EType.Paralysis, gameObject);
        bool isSleep = actorParamsController.IsSleep();
        if (isSleep && action != EAct.KeyInput)
            effect.Play(EffectManager_Original.EType.Sleep, gameObject);
        bool isConfusion = actorParamsController.IsConfusion();
        if (isConfusion && action != EAct.KeyInput)
            effect.Play(EffectManager_Original.EType.Confusion, gameObject);
        if (action == EAct.TurnEnd) action = EAct.KeyInput;
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
