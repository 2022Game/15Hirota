using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ItemSlotDisplay : MonoBehaviour
{
    public Inventory inventory;
    public GameObject content;

    private ScrollView view;
    private int prevViewSelectItemIndex;
    private int selectItemIndex;
    private int leadShowItemIndex = 0;
    private int maxShowItemNum;

    // Start is called before the first frame update
    void Start()
    {
        view = GetComponentInChildren<ScrollView>();
        selectItemIndex = prevViewSelectItemIndex = view.GetSelectItemIndex();
    }

    // Update is called once per frame
    void Update()
    {
        if (!gameObject.activeInHierarchy) return;
        int viewSelectItemIndex = view.GetSelectItemIndex();
        if (viewSelectItemIndex == prevViewSelectItemIndex) return;
        ScrollItem[] contents = content.GetComponentsInChildren<ScrollItem>();
        if (viewSelectItemIndex == prevViewSelectItemIndex + 1)
        {
            if (viewSelectItemIndex == maxShowItemNum - 1 && selectItemIndex < inventory.itemNumMax - 2)
            {
                contents[0].transform.SetParent(null);
                contents[0].transform.SetParent(content.transform);
                leadShowItemIndex++;
                Vector3 moveDistance = contents[viewSelectItemIndex].GetBackDistance(true);
                view.MoveContentPosition(moveDistance);
                ShowItemInfo();
            }
        }
        if (prevViewSelectItemIndex == maxShowItemNum - 1 && viewSelectItemIndex == 0)
        {
            leadShowItemIndex = 0;
            ShowItemInfo();
        }
        if (viewSelectItemIndex == prevViewSelectItemIndex - 1)
        {
            if (viewSelectItemIndex == 0 && selectItemIndex > 1)
            {
                for (int i = 0; i < maxShowItemNum - 1; i++)
                    contents[i].transform.SetParent(null);
                for (int i = 0; i < maxShowItemNum - 1; i++)
                    contents[i].transform.SetParent(content.transform);
                leadShowItemIndex--;
                Vector3 moveDistance = contents[viewSelectItemIndex].GetBackDistance(false);
                view.MoveContentPosition(moveDistance);
                ShowItemInfo();
            }
        }
        if (prevViewSelectItemIndex == 0 && viewSelectItemIndex == maxShowItemNum - 1)
        {
            leadShowItemIndex = inventory.itemNumMax - maxShowItemNum;
            ShowItemInfo();
        }
        selectItemIndex = leadShowItemIndex + viewSelectItemIndex;
        prevViewSelectItemIndex = viewSelectItemIndex;
    }

    /**
    * インベントリを参照し、アイテムスロットを表示する
    */
    public void Show()
    {
        maxShowItemNum = content.transform.childCount;
        for (int i = inventory.itemNumMax; i < maxShowItemNum; i++)
            content.transform.GetChild(i).gameObject.SetActive(false);
        maxShowItemNum = maxShowItemNum > inventory.itemNumMax ? inventory.itemNumMax : maxShowItemNum;
        ShowItemInfo();
    }

    /**
    * アイテムスロットに情報を付け足す
    */
    private void ShowItemInfo()
    {
        for (int i = 0; i < maxShowItemNum; i++)
        {
            Transform slot = content.transform.GetChild(i);
            slot.gameObject.SetActive(true);
            Item it = inventory.Get(i + leadShowItemIndex);
            if (it == null)
            {
                slot.GetComponentInChildren<Text>().text = "";
                slot.GetChild(0).gameObject.SetActive(false);
            }
            else
            {
                slot.GetComponentInChildren<Text>().text = it.name;
                slot.GetChild(0).gameObject.SetActive(true);
                slot.GetComponentsInChildren<Image>()[1].sprite = Resources.Load<Sprite>("Sprites/" + it.sprite);
            }
        }
    }

    // 現在選択しているアイテムスロットのアイテムを返す
    public Item GetSelectItem() => inventory.Get(selectItemIndex);
}
