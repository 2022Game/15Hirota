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

    // 独自の更新メソッド
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

    // 現在の行動状態を返す
    public EAct GetAction() => action;

    // 待機中
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

    // アクションを始める
    private void ActBegin()
    {
        actorAttack.Attack();
        action = EAct.Act;
    }

    // アクション中
    private void Act()
    {
        action = actorAttack.Attacking();
        if (action == EAct.ActEnd)
        {
            Pos2D grid = DirUtil.GetNewGrid(actorMovement.grid, actorMovement.direction);
            actorAttack.DamageOpponent(GetComponentInParent<Field>().GetExistActor(grid.x, grid.z));
        }
    }

    // アクションが終わった
    private void ActEnd()
    {
        action = EAct.TurnEnd;
    }

    // 移動を始める
    private void MoveBegin()
    {
        actorMovement.Walk();
        action = EAct.Move;
    }

    // 移動中
    private void Move()
    {
        action = actorMovement.Walking();
        if (action == EAct.MoveEnd) actorUseItems.PickUp();
    }

    // 移動が終わった
    private void MoveEnd()
    {
        action = EAct.TurnEnd;
    }

    // ターンが終わった
    private void TurnEnd()
    {
        action = EAct.KeyInput;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // 歩行アニメーションをストップさせる
    public void StopWalkingAnimation()
    {
        actorMovement.Stop();
    }
}
