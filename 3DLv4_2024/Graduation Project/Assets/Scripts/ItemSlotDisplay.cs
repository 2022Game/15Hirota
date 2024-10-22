using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ItemSlotDisplay : MonoBehaviour
{
    public Inventory inventory;
    public GameObject detail;
    //public List<Item> footItem = new List<Item>();
    public Item footItem;
    public GameObject content;
    
    private ScrollView view;
    private int prevViewSelectItemIndex;
    private int selectItemIndex;
    private int leadShowItemIndex = 0;
    private int maxShowItemNum;
    private int inventoryNum;

    // Start is called before the first frame update
    void Start()
    {
        view = GetComponentInChildren<ScrollView>();
        selectItemIndex = prevViewSelectItemIndex = view.GetSelectItemIndex();
    }

    // EDir���󂯎���āA���̕����ɃJ�[�\���𓮂���
    public bool MoveSelect(EDir d)
    {
        if (!view.MoveSelect(d)) return false;
        int viewSelectItemIndex = view.GetSelectItemIndex();
        ScrollItem[] contents = content.GetComponentsInChildren<ScrollItem>();
        if (viewSelectItemIndex == prevViewSelectItemIndex + 1)
        {
            if (viewSelectItemIndex > maxShowItemNum - 2 && selectItemIndex < inventoryNum - 2)
            {
                contents[0].transform.SetParent(null);
                contents[0].transform.SetParent(content.transform);
                leadShowItemIndex++;
                Vector3 moveDistance = contents[viewSelectItemIndex].GetBackDistance(true);
                view.MoveContentPosition(moveDistance);
                viewSelectItemIndex--;
                ShowItemInfo();
                ShowItemDetail();
            }
        }
        if (prevViewSelectItemIndex == maxShowItemNum - 1 && viewSelectItemIndex == 0)
        {
            leadShowItemIndex = 0;
            ShowItemInfo();
            ShowItemDetail();
        }
        if (viewSelectItemIndex == prevViewSelectItemIndex - 1)
        {
            if (viewSelectItemIndex < 1 && selectItemIndex > 1)
            {
                for (int i = 0; i < maxShowItemNum - 1; i++)
                    contents[i].transform.SetParent(null);
                for (int i = 0; i < maxShowItemNum - 1; i++)
                    contents[i].transform.SetParent(content.transform);
                leadShowItemIndex--;
                Vector3 moveDistance = contents[viewSelectItemIndex].GetBackDistance(false);
                view.MoveContentPosition(moveDistance);
                viewSelectItemIndex++;
                ShowItemInfo();
                ShowItemDetail();
            }
        }
        if (prevViewSelectItemIndex == 0 && viewSelectItemIndex == maxShowItemNum - 1)
        {
            leadShowItemIndex = inventoryNum - maxShowItemNum;
            ShowItemInfo();
            ShowItemDetail();
        }
        selectItemIndex = leadShowItemIndex + viewSelectItemIndex;
        prevViewSelectItemIndex = viewSelectItemIndex;
        ShowItemDetail();
        return true;
    }

    // Update is called once per frame
    //void Update()
    //{
    //    if (!gameObject.activeInHierarchy) return;
    //    int viewSelectItemIndex = view.GetSelectItemIndex();
    //    if (viewSelectItemIndex == prevViewSelectItemIndex) return;
    //    ScrollItem[] contents = content.GetComponentsInChildren<ScrollItem>();
    //    if (viewSelectItemIndex == prevViewSelectItemIndex + 1)
    //    {
    //        if (viewSelectItemIndex == maxShowItemNum - 1 && selectItemIndex < inventory.itemNumMax - 2)
    //        {
    //            contents[0].transform.SetParent(null);
    //            contents[0].transform.SetParent(content.transform);
    //            leadShowItemIndex++;
    //            Vector3 moveDistance = contents[viewSelectItemIndex].GetBackDistance(true);
    //            view.MoveContentPosition(moveDistance);
    //            ShowItemInfo();
    //        }
    //    }
    //    if (prevViewSelectItemIndex == maxShowItemNum - 1 && viewSelectItemIndex == 0)
    //    {
    //        leadShowItemIndex = 0;
    //        ShowItemInfo();
    //    }
    //    if (viewSelectItemIndex == prevViewSelectItemIndex - 1)
    //    {
    //        if (viewSelectItemIndex == 0 && selectItemIndex > 1)
    //        {
    //            for (int i = 0; i < maxShowItemNum - 1; i++)
    //                contents[i].transform.SetParent(null);
    //            for (int i = 0; i < maxShowItemNum - 1; i++)
    //                contents[i].transform.SetParent(content.transform);
    //            leadShowItemIndex--;
    //            Vector3 moveDistance = contents[viewSelectItemIndex].GetBackDistance(false);
    //            view.MoveContentPosition(moveDistance);
    //            ShowItemInfo();
    //        }
    //    }
    //    if (prevViewSelectItemIndex == 0 && viewSelectItemIndex == maxShowItemNum - 1)
    //    {
    //        leadShowItemIndex = inventory.itemNumMax - maxShowItemNum;
    //        ShowItemInfo();
    //    }
    //    selectItemIndex = leadShowItemIndex + viewSelectItemIndex;
    //    prevViewSelectItemIndex = viewSelectItemIndex;
    //}

    /**
    * �C���x���g�����Q�Ƃ��A�A�C�e���X���b�g��\������
    */
    public void Show()
    {
        maxShowItemNum = content.transform.childCount;
        for (int i = inventory.itemNumMax; i < maxShowItemNum; i++)
            content.transform.GetChild(i).gameObject.SetActive(false);
        footItem = inventory.GetFootItem();
        if (selectItemIndex == inventory.itemNumMax && footItem == null)
        {
            while (!MoveSelect(EDir.Right)) ;
            while (!MoveSelect(EDir.Left)) ;
        }
        inventoryNum = (footItem == null ? 0 : 1) + inventory.itemNumMax;
        maxShowItemNum = maxShowItemNum > inventoryNum ? inventoryNum : maxShowItemNum;
        ShowItemInfo();
        ShowItemDetail();
    }

    /**
    * �A�C�e���X���b�g�ɏ���t������
    */
    private void ShowItemInfo()
    {
        for (int i = 0; i < maxShowItemNum; i++)
        {
            Transform slot = content.transform.GetChild(i);
            slot.gameObject.SetActive(true);
            int idx = i + leadShowItemIndex;
            Item it = idx == inventory.itemNumMax ? footItem : inventory.Get(idx);
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

    // �A�C�e���̏ڍׂ�\������
    private void ShowItemDetail()
    {
        int idx = prevViewSelectItemIndex + leadShowItemIndex;
        Item it = idx == inventory.itemNumMax ? footItem : inventory.Get(idx);
        if (it == null) detail.GetComponentInChildren<Text>().text = "";
        else detail.GetComponentInChildren<Text>().text = it.detail;
        for (int i = 0; i < maxShowItemNum; i++)
        {
            Transform slot = content.transform.GetChild(i);
            slot.GetChild(2).gameObject.SetActive(false);
        }
        Transform currentSlot = content.transform.GetChild(prevViewSelectItemIndex);
        currentSlot.GetChild(2).gameObject.SetActive(true);
    }

    // ���ݑI�����Ă���A�C�e���X���b�g�̃A�C�e����Ԃ�
    public Item GetSelectItem() => inventory.Get(selectItemIndex);

    // ���ݒn�ʂɂ���A�C�e�����I������Ă��鎞�́A���̃A�C�e����Ԃ�
    public Item GetSelectFootItem() => selectItemIndex == inventory.itemNumMax ? footItem : null;
}
