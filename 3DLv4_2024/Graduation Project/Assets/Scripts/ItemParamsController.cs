using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemParamsController : MonoBehaviour
{
    public Item parameter;

    // アイテムパラメータを設定する
    public void SetParams(Item it)
    {
        Item p = new Item();
        p.id = it.id;
        p.name = it.name;
        p.prefab = it.prefab;
        p.sprite = it.sprite;
        parameter = p;
    }
}
