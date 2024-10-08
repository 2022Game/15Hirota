using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class InventoryAction : MonoBehaviour
{
    public InventoryAnimation anim;

    private EAct action = EAct.KeyInput;
    private bool isOpen = false;

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

    /**
    * 現在の行動状態を返す
    */
    public EAct GetAction() => action;

    /**
    * 待機中
    */
    private void KeyInput()
    {
        if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.E))
        {
            action = EAct.MoveBegin;
        }
    }

    /**
    * アクションを始める
    */
    private void ActBegin()
    {
        KeyInput();
    }

    /**
    * アクション中
    */
    private void Act()
    {

    }

    /**
    * アクションが終わった
    */
    private void ActEnd()
    {
        action = EAct.TurnEnd;
    }

    /**
    * 移動を始める
    */
    private void MoveBegin()
    {
        isOpen = !isOpen;
        if (isOpen) gameObject.SetActive(true);
        action = EAct.Move;
    }

    /**
    * 移動中
    */
    private void Move()
    {
        if (isOpen)
        {
            if (anim.Open())
            {
                action = EAct.MoveEnd;
                return;
            }
        }
        else
        {
            if (anim.Close())
            {
                action = EAct.MoveEnd;
                return;
            }
        }
        action = EAct.Move;
    }

    /**
    * 移動が終わった
    */
    private void MoveEnd()
    {
        if (isOpen) action = EAct.ActBegin;
        else
        {
            gameObject.SetActive(false);
            action = EAct.TurnEnd;
        }
    }

    /**
    * ターンが終わった
    */
    private void TurnEnd()
    {
        action = EAct.KeyInput;
    }
}
