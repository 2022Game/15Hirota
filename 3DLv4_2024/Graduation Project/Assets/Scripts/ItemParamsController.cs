using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemParamsController : MonoBehaviour
{
    public Item parameter;

    // �A�C�e���̃p�����[�^�[��Ԃ�
    public Item GetParams()
    {
        return parameter.Get();
    }

    // �A�C�e���p�����[�^��ݒ肷��
    public void SetParams(Item it)
    {
        parameter = it.Get();
    }
}
