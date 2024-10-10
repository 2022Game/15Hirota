using System.Collections;
using System.Collections.Generic;
using System.Net.Mime;
using UnityEngine;
using UnityEngine.UI;

public class SubMenu : MonoBehaviour
{
    public string[] choiceNames;
    public string[] choiceMethods;

    private int selectItemIndex = 0;

    // EDir���󂯎���āA���̕����ɃJ�[�\���𓮂���
    public bool MoveSelect(EDir d)
    {
        ScrollItem[] contents = GetComponentsInChildren<ScrollItem>();
        if (contents.Length < 1) return true;
        if (d == EDir.Down)
        {
            selectItemIndex = (selectItemIndex + 1) % contents.Length;
        }
        if (d == EDir.Up)
        {
            selectItemIndex = (selectItemIndex + contents.Length - 1) % contents.Length;
        }
        contents[selectItemIndex].SetSelected(true);
        gameObject.SetActive(true);
        return true;
    }

    // �I������Ă��鍀�ڂ��g�p���郁�\�b�h����Ԃ�
    public string GetSelectItemMethod() => choiceMethods[selectItemIndex];

    // �T�u���j���[���J��
    public void Show()
    {
        int i = 0;
        foreach (var text in GetComponentsInChildren<Text>())
        {
            text.text = choiceNames[i];
            i++;
        }
        selectItemIndex = 0;
        GetComponentInChildren<ScrollItem>().SetSelected(true);
        gameObject.SetActive(true);
    }

    // �T�u���j���[�����
    public void Hide()
    {
        gameObject.SetActive(false);
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
