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
    public string GetSelectItemMethod() => choiceMethods[selectItemIndex];

    // サブメニューを開く
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

    // サブメニューを閉じる
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
