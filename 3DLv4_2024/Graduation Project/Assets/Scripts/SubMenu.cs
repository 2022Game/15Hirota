using System.Collections;
using System.Collections.Generic;
using System.Net.Mime;
using System;
using UnityEngine;
using UnityEngine.UI;

public class SubMenu : MonoBehaviour
{
    public string[] choiceNames;
    public string[] choiceMethods;
    private int[] choiceIndexes;

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
    public string GetSelectItemMethod() => choiceMethods[choiceIndexes[selectItemIndex]];

    // �T�u���j���[���J��
    public void Show()
    {
        int i = 0;
        foreach (var text in GetComponentsInChildren<Text>())
        {
            text.text = choiceNames[choiceIndexes[i]];
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

    // ���\�b�h�̕����񂩂�I�����̏��Ԃ�ς���
    public void SetChoices(string choiceOrder)
    {
        string[] choiceOrderList = choiceOrder.Replace(" ", "").Split(',');
        int maxItemNum = transform.childCount;
        for (int i = 0; i < maxItemNum; i++) transform.GetChild(i).gameObject.SetActive(false);
        maxItemNum = maxItemNum < choiceOrderList.Length ? maxItemNum : choiceOrderList.Length;
        choiceIndexes = new int[maxItemNum];
        int j = 0;
        for (int i = 0; i < maxItemNum; i++)
        {
            int idx = Array.IndexOf(choiceMethods, choiceOrderList[i]);
            if (idx < 0) continue;
            choiceIndexes[j] = idx;
            transform.GetChild(i).gameObject.SetActive(true);
            j++;
        }
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
