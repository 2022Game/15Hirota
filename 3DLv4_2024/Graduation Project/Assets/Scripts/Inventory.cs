using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoBehaviour
{
    public int itemNumMax = 10;
    public List<Item> items = new List<Item>();
   
    // Start is called before the first frame update
    void Start()
    {
       
    }

    // Update is called once per frame
    void Update()
    {

    }

    // もし所持可能数を超えていなければ、アイテムをインベントリに加える
    public bool Add(Item it)
    {
        if (items.Count < itemNumMax)
        {
            items.Add(it);
            return true;
        }
        return false;
    }

    // インベントリから指定したインデックスのアイテムを返す
    public Item Get(int i)
    {
        if (items.Count > i && i >= 0) return items[i];
        return null;
    }

    // インベントリに入っている全てのアイテムの配列を返す
    public Item[] GetAllItem()
    {
        Item[] itemList = new Item[items.Count];
        for (int i = 0; i < items.Count; i++)
        {
            itemList[i] = items[i].Get();
        }
        return itemList;
    }

    // インベントリの中身を全て入れ替える
    public void SetAllItem(Item[] itemList, int maxNum)
    {
        List<Item> items = new List<Item>();
        ActorParamsController.Equipment equipment = new ActorParamsController.Equipment();
        int itemCnt = itemList.Length < maxNum ? itemList.Length : maxNum;
        for (int i = 0; i < itemCnt; i++)
        {
            items.Add(itemList[i].Get());
            if (items[i].isEquip)
            {
                if (items[i].type == EItemType.Weapon)
                {
                    if (equipment.weapon == null) equipment.weapon = items[i];
                    else items[i].isEquip = false;
                }
                if (items[i].type == EItemType.Armor)
                {
                    if (equipment.armor == null) equipment.armor = items[i];
                    else items[i].isEquip = false;
                }
            }
        }
        itemNumMax = maxNum;
        this.items = items;
        GetComponent<ActorParamsController>().equipment = equipment;
    }

    // インベントリから指定したアイテムを削除する
    public bool Remove(Item it)
    {
        if (it != null)
        {
            return items.Remove(it);
        }
        return false;
    }

    // もしあれば足下にあるアイテムを返す
    public Item GetFootItem()
    {
        Pos2D grid = GetComponent<ActorMovement>().grid;
        GameObject obj = GetComponentInParent<Field>().GetExistItem(grid.x, grid.z);
        if (obj == null) return null;
        return obj.GetComponent<ItemParamsController>().parameter;
    }

    // インベントリがいっぱいかどうか
    public bool IsFull() => items.Count >= itemNumMax;
}
