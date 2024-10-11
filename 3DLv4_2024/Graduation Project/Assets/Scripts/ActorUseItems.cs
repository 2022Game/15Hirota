using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActorUseItems : MonoBehaviour
{
    public ActorMovement move;
    public ActorParamsController param;
    public Inventory inventory;

    public delegate bool UseItem(Item it);

    // もしアイテムがあれば廣ってインベントリに加える
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

    // 文字列に対応するデリゲートを返す
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

    // 引数で渡されたアイテムを使う
    public bool Use(Item it)
    {
        Message.Add(5, param.actorName, it.name);
        inventory.Remove(it);
        return true;
    }

    // 引数で渡されたアイテムを置く
    public bool Put(Item it)
    {
        return true;
    }

    // 引数で渡されたアイテムを投げる
    public bool Throw(Item it)
    {
        return true;
    }

    // 何もしない
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
