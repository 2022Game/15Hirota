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
        if (items.Count <itemNumMax)
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
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
