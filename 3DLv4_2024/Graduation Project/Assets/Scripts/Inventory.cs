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
            itemList[i] = items[i].Get();
        }
        return itemList;
    }

    // �C���x���g���̒��g��S�ē���ւ���
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

    // �C���x���g������w�肵���A�C�e�����폜����
    public bool Remove(Item it)
    {
        if (it != null)
        {
            return items.Remove(it);
        }
        return false;
    }

    // ��������Α����ɂ���A�C�e����Ԃ�
    public Item GetFootItem()
    {
        Pos2D grid = GetComponent<ActorMovement>().grid;
        GameObject obj = GetComponentInParent<Field>().GetExistItem(grid.x, grid.z);
        if (obj == null) return null;
        return obj.GetComponent<ItemParamsController>().parameter;
    }

    // �C���x���g���������ς����ǂ���
    public bool IsFull() => items.Count >= itemNumMax;
}
