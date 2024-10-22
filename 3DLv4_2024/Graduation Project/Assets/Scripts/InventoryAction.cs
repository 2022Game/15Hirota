using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class InventoryAction : MonoBehaviour
{
    public InventoryAnimation anim;
    public ItemSlotDisplay display;
    public SubMenu subMenu;
    private Item selectItem = null;
    public float inputHoldDelay = 0.3f;
    private float inputTime = 0;
    private bool isCursorMoving = false;

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
        if (isCursorMoving)
        {
            isCursorMoving = !MoveSelectItem();
            return;
        }
        if (selectItem == null)
        {
            isCursorMoving = !MoveSelectItem();
            if (isCursorMoving) return;
            KeyInput();
            SelectItem();
        }
        else
        {
            MoveSelectSubMenuItem();
            SelectSubMenuItem();
            UnSelectItem();
        }
    }

    /**
    * アクション中
    */
    private void Act()
    {
        action = EAct.MoveBegin;
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
        if (isOpen)
        {
            display.Show();
            gameObject.SetActive(true);
        }
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
            if (selectItem == null)
            {
                action = EAct.KeyInput;
                return;
            }
            ActorUseItems actorUse = display.inventory.GetComponentInParent<ActorUseItems>();
            ActorUseItems.UseItem use = actorUse.GetDelegate(subMenu.GetSelectItemMethod());
            if (use(selectItem))
            {
                selectItem = null;
                action = EAct.ActEnd;
            }
        }
    }

    /**
    * ターンが終わった
    */
    private void TurnEnd()
    {
        action = EAct.KeyInput;
    }

    // アイテムを選択
    private void SelectItem()
    {
        if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.Space))
        {
            string choiceOrder = "";
            selectItem = display.GetSelectItem();
            if (selectItem != null)
            {
                if (selectItem.isEquip) choiceOrder = "Remove";
                else
                {
                    if (display.inventory.GetFootItem() == null) choiceOrder = "Use, Put, Throw";
                    else choiceOrder = "Use, Replace, Throw";
                    if ((int)selectItem.id < 1001) choiceOrder = choiceOrder.Replace("Use", "Equip");
                }
                subMenu.SetChoices(choiceOrder);
                subMenu.Show();
            }
        }
    }

    // アイテムの選択を解除
    private void UnSelectItem()
    {
        if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.E))
        {
            selectItem = null;
            subMenu.Hide();
        }
    }

    // 選択スロットを変更する
    private bool MoveSelectItem()
    {
        if (isCursorMoving) return display.MoveSelect(EDir.Pause);
        if (Input.anyKeyDown)
        {
            inputTime = 0;
            if (Input.GetKeyDown(KeyCode.LeftArrow)) return display.MoveSelect(EDir.Left);
            if (Input.GetKeyDown(KeyCode.RightArrow)) return display.MoveSelect(EDir.Right);
        }
        inputTime += Time.deltaTime;
        if (inputTime < inputHoldDelay) return true;
        if (!Input.anyKey) return true;
        inputTime = 0;
        if (Input.GetKey(KeyCode.LeftArrow)) return display.MoveSelect(EDir.Left);
        if (Input.GetKey(KeyCode.RightArrow)) return display.MoveSelect(EDir.Right);
        return true;
    }

    // 選択するサブメニューの項目を変更する
    private bool MoveSelectSubMenuItem()
    {
        if (Input.anyKeyDown)
        {
            inputTime = 0;
            if (Input.GetKeyDown(KeyCode.UpArrow)) return subMenu.MoveSelect(EDir.Up);
            if (Input.GetKeyDown(KeyCode.DownArrow)) return subMenu.MoveSelect(EDir.Down);
        }
        inputTime += Time.deltaTime;
        if (inputTime < inputHoldDelay) return true;
        if (!Input.anyKey) return true;
        inputTime = 0;
        if (Input.GetKey(KeyCode.UpArrow)) return subMenu.MoveSelect(EDir.Up);
        if (Input.GetKey(KeyCode.DownArrow)) return subMenu.MoveSelect(EDir.Down);
        return true;
    }

    // サブメニューの項目を選択
    private void SelectSubMenuItem()
    {
        if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.Space))
        {
            action = EAct.Act;
            subMenu.Hide();
        }
    }
}