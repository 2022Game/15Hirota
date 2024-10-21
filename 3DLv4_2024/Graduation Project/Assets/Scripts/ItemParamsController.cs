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

        p.type = it.type;
        p.atk = it.atk;
        p.def = it.def;
        p.hp = it.hp;
        p.food = it.food;
        p.dmg = it.dmg;
        p.detail = it.detail;
        parameter = p;
    }
}
