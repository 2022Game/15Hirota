using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActorUseItems : MonoBehaviour
{
    public ActorMovement move;
    public ActorParamsController param;
    public Inventory inventory;

    public delegate bool UseItem(Item it);

    // �����A�C�e��������ΜA���ăC���x���g���ɉ�����
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

    // ������ɑΉ�����f���Q�[�g��Ԃ�
    public UseItem GetDelegate(string method)
    {
        switch (method)
        {
            case "Use": return new UseItem(Use);
            case "Put": return new UseItem(Put);
            case "Throw": return new UseItem(Throw);
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
        return true;
    }

    // �����œn���ꂽ�A�C�e���𓊂���
    public bool Throw(Item it)
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
