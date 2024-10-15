using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class ActorUseItems : MonoBehaviour
{
    public ActorMovement move;
    public ActorParamsController param;
    public Inventory inventory;

    public delegate bool UseItem(Item it);

    private GameObject usingItem = null;

    // ������ɑΉ�����f���Q�[�g��Ԃ�
    public UseItem GetDelegate(string method)
    {
        switch (method)
        {
            case "Use": return new UseItem(Use);
            case "Put": return new UseItem(Put);
            case "Throw": return new UseItem(Throw);
            case "PickUp": return new UseItem(PickUp);
            case "PickUpUse": return new UseItem(PickUpUse);
            case "Replace": return new UseItem(Replace);
            case "PickUpThrow": return new UseItem(PickUpThrow);
        }
        return new UseItem(DoNothing);
    }

    // �����œn���ꂽ�A�C�e�����g��
    public bool Use(Item it)
    {
        Message.Add(5, param.actorName, it.name);
        inventory.Remove(it);
        return true;
    }

    // �����œn���ꂽ�A�C�e����u��
    public bool Put(Item it)
    {
        Message.Add(11, it.name);
        GameObject item = GetComponentInParent<Field>().GetExistItem(move.grid.x, move.grid.z);
        if (item != null) Destroy(item);
        GameObject items = GetComponentInParent<Field>().items;
        GameObject itemObj = (GameObject)Resources.Load("Prefabs/" + it.prefab);
        item = Instantiate(itemObj, items.transform);
        item.GetComponent<ItemMovement>().SetPosition(move.grid.x, move.grid.z);
        item.GetComponent<ItemParamsController>().SetParams(it);
        inventory.Remove(it);
        return true;
    }

    // �����œn���ꂽ�A�C�e���𓊂���
    public bool Throw(Item it)
    {
        if (usingItem == null)
        {
            Message.Add(13, it.name);
            GameObject items = GetComponentInParent<Field>().items;
            GameObject itemObj = (GameObject)Resources.Load("Prefabs/" + it.prefab);
            usingItem = Instantiate(itemObj, items.transform);
            usingItem.GetComponent<ItemMovement>().SetPosition(move.grid.x, move.grid.z);
            usingItem.GetComponent<ItemParamsController>().SetParams(it);
            inventory.Remove(it);
            return false;
        }
        if (usingItem.GetComponent<ItemMovement>().Throwing(move.direction))
        {
            usingItem = null;
            return true;
        }
        return false;
    }

    // �����A�C�e��������ΏE���ăC���x���g���ɉ�����
    public void PickUp()
    {
        GameObject item = GetComponentInParent<Field>().GetExistItem(move.grid.x, move.grid.z);
        if (item == null) return;
        Item it = item.GetComponent<ItemParamsController>().parameter;
        if (inventory.Add(it))
        {
            Destroy(item);
            Message.Add(8, param.actorName, it.name);
        }
        else
        {
            if (param.parameter.id == 0) Message.Add(9);
            Message.Add(10, param.actorName, it.name);
        }
    }

    // �����œn���ꂽ�A�C�e�����E���ăC���x���g���ɉ�����
    public bool PickUp(Item it)
    {
        inventory.Add(it);
        GameObject item = GetComponentInParent<Field>().GetExistItem(move.grid.x, move.grid.z);
        if (item != null) Destroy(item);
        Message.Add(8, param.actorName, it.name);
        return true;
    }

    // �����œn���ꂽ�A�C�e�����E���Ďg��
    public bool PickUpUse(Item it)
    {
        Message.Add(5, param.actorName, it.name);
        GameObject item = GetComponentInParent<Field>().GetExistItem(move.grid.x, move.grid.z);
        if (item == null) return true;
        Destroy(item);
        return true;
    }

    // �����œn���ꂽ�A�C�e����n�ʂ̃A�C�e�����ƌ�������
    public bool Replace(Item it)
    {
        Message.Add(11, it.name);
        GameObject item = GetComponentInParent<Field>().GetExistItem(move.grid.x, move.grid.z);
        GameObject items = GetComponentInParent<Field>().items;
        GameObject itemObj = (GameObject)Resources.Load("Prefabs/" + it.prefab);
        GameObject item2 = Instantiate(itemObj, items.transform);
        item2.GetComponent<ItemMovement>().SetPosition(move.grid.x, move.grid.z);
        item2.GetComponent<ItemParamsController>().SetParams(it);
        inventory.Remove(it);
        if (item != null)
        {
            it = item.GetComponent<ItemParamsController>().parameter;
            Message.Add(8, param.actorName, it.name);
            inventory.Add(it);
            Destroy(item);
        }
        return true;
    }

    // �����œn���ꂽ�A�C�e�����E���ē�����
    public bool PickUpThrow(Item it)
    {
        return true;
    }

    // �������Ȃ�
    public bool DoNothing(Item it)
    {
        return true;
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
