using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoBehaviour
{
    public int itemNumMax = 10;
    public List<Item> items = new List<Item>();


    // ���������\���𒴂��Ă��Ȃ���΁A�A�C�e�����C���x���g���ɉ�����
    public bool Add(Item it)
    {
        if (items.Count < itemNumMax)
        {
            items.Add(it);
            return true;
        }
        return false;
    }

    // �C���x���g������w�肵���C���f�b�N�X�̃A�C�e����Ԃ�
    public Item Get(int i)
    {
        if (items.Count > i && i >= 0) return items[i];
        return null;
    }

    // �C���x���g���ɓ����Ă���S�ẴA�C�e���̔z���Ԃ�
    public Item[] GetAllItem()
    {
        Item[] itemList = new Item[items.Count];
        for (int i = 0; i < items.Count; i++)
        {
            Item it = new Item();
            it.id = items[i].id;
            it.name = items[i].name;
            it.sprite = items[i].sprite;
            itemList[i] = it;
        }
        return itemList;
    }

    // �C���x���g���̒��g��S�ē���ւ���
    public void SetAllItem(Item[] itemList, int maxNum)
    {
        List<Item> items = new List<Item>();
        int itemCnt = itemList.Length < maxNum ? itemList.Length : maxNum;
        for (int i = 0; i < itemCnt; i++)
        {
            Item it = new Item();
            it.id = itemList[i].id;
            it.name = itemList[i].name;
            it.sprite = itemList[i].sprite;
            items.Add(it);
        }
        itemNumMax = maxNum;
        this.items = items;
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