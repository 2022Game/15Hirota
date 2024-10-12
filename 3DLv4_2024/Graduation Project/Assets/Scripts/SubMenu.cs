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

    // EDirを受け取って、その方向にカーソルを動かす
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

    // 選択されている項目が使用するメソッド名を返す
    public string GetSelectItemMethod() => choiceMethods[choiceIndexes[selectItemIndex]];

    // サブメニューを開く
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

    // サブメニューを閉じる
    public void Hide()
    {
        gameObject.SetActive(false);
    }

    // メソッドの文字列から選択肢の順番を変える
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
