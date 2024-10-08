using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoBehaviour
{
    public int itemNumMax = 10;
    public List<Item> items = new List<Item>();


    // もし所持可能数を超えていなければ、アイテムをインベントリに加える
    public bool Add(Item it)
    {
        if (items.Count <itemNumMax)
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
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
