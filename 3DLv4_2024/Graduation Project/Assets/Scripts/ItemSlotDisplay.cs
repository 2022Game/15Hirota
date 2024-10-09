using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ItemSlotDisplay : MonoBehaviour
{
    public Inventory inventory;
    public GameObject content;
    public GameObject itemSlot;


    // インベントリを参照し、アイテムスロットを表示する
    public void Show()
    {
        for (int i = inventory.itemNumMax; i < content.transform.childCount; i++)
            content.transform.GetChild(i).gameObject.SetActive(false);
        for (int i = content.transform.childCount; i < inventory.itemNumMax; i++)
            Instantiate(itemSlot, content.transform);
        for (int i = 0; i < inventory.itemNumMax; i++)
        {
            Transform slot = content.transform.GetChild(i);
            slot.gameObject.SetActive(true);
            Item it = inventory.Get(i);
            if (it != null) slot.GetComponentInChildren<Text>().text = it.name;
        }
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
