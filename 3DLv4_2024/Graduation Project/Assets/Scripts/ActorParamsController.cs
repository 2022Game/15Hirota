using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActorParamsController : MonoBehaviour
{
    public Params parameter;

    // �p�����[�^�[�̃R�s�[��Ԃ�
    public Params GetParameter()
    {
        Params p = new Params();
        p.id = parameter.id;
        p.lv = parameter.lv;
        p.hp = parameter.hp;
        p.hpmax = parameter.hpmax;
        p.str = parameter.str;
        p.def = parameter.def;
        p.exp = parameter.exp;
        p.xp = parameter.xp;
        return p;
    }

    // �p�����[�^�[��Z�߂Đݒ肷��
    public void SetParameter(Params p)
    {
        parameter.id = p.id;
        parameter.lv = p.lv;
        parameter.hp = p.hp;
        parameter.hpmax = p.hpmax;
        parameter.str = p.str;
        parameter.def = p.def;
        parameter.exp = p.exp;
        parameter.xp = p.xp;
    }

    // �_���[�W���󂯂�
    public void Damaged(int str)
    {
        parameter.hp -= CalcDamage(str, parameter.def);
    }

    // �_���[�W���v�Z����
    private static int CalcDamage(int str, int def)
    {
        return Mathf.CeilToInt(str * Mathf.Pow(0.9375f, def));
    }
}
