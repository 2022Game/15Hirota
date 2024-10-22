using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemParamsController : MonoBehaviour
{
    public Item parameter;

    // アイテムのパラメーターを返す
    public Item GetParams()
    {
        return parameter.Get();
    }

    // アイテムパラメータを設定する
    public void SetParams(Item it)
    {
        parameter = it.Get();
    }
}
