using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class InventoryAction : MonoBehaviour
{
    public InventoryAnimation anim;
    public ItemSlotDisplay display;
    public GameObject subMenu;
    private Item selectItem = null;

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
        if (selectItem == null)
        {
            KeyInput();
            SelectItem();
        }
        else UnSelectItem();
    }

    /**
    * �A�N�V������
    */
    private void Act()
    {

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
            action = EAct.TurnEnd;
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
            selectItem = display.GetSelectItem();
            if (selectItem != null) subMenu.SetActive(true);
        }
    }

    // �A�C�e���̑I��������
    private void UnSelectItem()
    {
        if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.E))
        {
            selectItem = null;
            subMenu.SetActive(false);
        }
    }
}