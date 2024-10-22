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

    /**
    * ���݂̍s����Ԃ�Ԃ�
    */
    public EAct GetAction() => action;

    /**
    * �ҋ@��
    */
    private void KeyInput()
    {
        if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.E))
        {
            action = EAct.MoveBegin;
        }
    }

    /**
    * �A�N�V�������n�߂�
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
    * �A�N�V������
    */
    private void Act()
    {
        action = EAct.MoveBegin;
    }

    /**
    * �A�N�V�������I�����
    */
    private void ActEnd()
    {
        action = EAct.TurnEnd;
    }

    /**
    * �ړ����n�߂�
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
    * �ړ���
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
    * �ړ����I�����
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
    * �^�[�����I�����
    */
    private void TurnEnd()
    {
        action = EAct.KeyInput;
    }

    // �A�C�e����I��
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

    // �A�C�e���̑I��������
    private void UnSelectItem()
    {
        if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.E))
        {
            selectItem = null;
            subMenu.Hide();
        }
    }

    // �I���X���b�g��ύX����
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

    // �I������T�u���j���[�̍��ڂ�ύX����
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

    // �T�u���j���[�̍��ڂ�I��
    private void SelectSubMenuItem()
    {
        if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.Space))
        {
            action = EAct.Act;
            subMenu.Hide();
        }
    }
}