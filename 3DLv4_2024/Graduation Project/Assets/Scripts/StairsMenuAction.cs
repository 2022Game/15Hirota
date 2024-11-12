using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StairsMenuAction : MonoBehaviour
{
    public SubMenu subMenu;
    public float inputHoldDelay = 0.3f;
    public Field field;
    public LoadFieldMap loadFieldMap;
    public FadeInOut fade;

    private EAct action = EAct.KeyInput;
    private float inputTime = 0;


    // �Ǝ��̍X�V���\�b�h
    public void Proc()
    {
        switch (action)
        {
            case EAct.KeyInput: KeyInput(); break;
            case EAct.ActBegin: ActBegin(); break;
            case EAct.Act: Act(); break;
            case EAct.ActEnd: ActEnd(); break;
            case EAct.TurnEnd: TurnEnd(); break;
        }
    }

    // ���݂̍s����Ԃ�Ԃ�
    public EAct GetAction() => action;

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
            Hide();
            string method = subMenu.GetSelectItemMethod();
            if (method.Equals("Remain")) action = EAct.ActEnd;
            else
            {
                string str = (Field.floorNum + (method.Contains("Down") ? -1 : 1)) + "F";
                fade.Fade(true, str);
                action = EAct.Act;
            }
        }
    }

    // ���j���[���J��
    private void Show(int isOnStairs)
    {
        if (isOnStairs < 0) return;
        string choiceOrder = "Remain";
        if (isOnStairs == 0) choiceOrder += ", UpStairs";
        else choiceOrder += ", DownStairs";
        subMenu.SetChoices(choiceOrder);
        subMenu.Show();
        gameObject.SetActive(true);
        action = EAct.ActBegin;
    }

    // ���j���[�����
    private void Hide()
    {
        gameObject.SetActive(false);
    }

    // �ҋ@��
    private void KeyInput()
    {
        Show(field.PlayerOnStairs());
    }

    // �A�N�V�������n�߂�
    private void ActBegin()
    {
        MoveSelectSubMenuItem();
        SelectSubMenuItem();
    }

    // �A�N�V������
    private void Act()
    {
        if (fade.Fade(true))
        {
            if (Input.anyKeyDown && Input.GetKeyDown(KeyCode.Space))
            {
                string method = subMenu.GetSelectItemMethod();
                ChangeFloor(method);
                fade.Fade(false);
                action = EAct.ActEnd;
            }
        }
    }

    // �K��ύX
    private void ChangeFloor(string stairs)
    {
        if (stairs.Contains("Down"))
        {
            stairs = "Up";
            Field.floorNum--;
        }
        else
        {
            stairs = "Down";
            Field.floorNum++;
        }
        field.startStairs = stairs;
        loadFieldMap.Load();
    }

    // �A�N�V�������I�����
    private void ActEnd()
    {
        if (Input.GetKeyUp(KeyCode.Space)) action = EAct.TurnEnd;
    }

    // �^�[�����I�����
    private void TurnEnd()
    {
        if (fade.Fade(false)) action = EAct.KeyInput;
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
