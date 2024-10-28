using Mono.Cecil;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActorParamsController : MonoBehaviour
{
    public Params parameter;
    public Equipment equipment;

    private List<Params> paramsData;
    private int prevLv = 0;
    public float decFoodPt = 0.25f;

    public string actorName;

    void Reset()
    {
        ExcelActorData database = Resources.Load<ExcelActorData>("Datas/ExcelActorData");
        ExcelActorData.ActorData actorData =
            database.Data.Find(n => n.prefab == gameObject.name.Replace("(Clone)", ""));
        paramsData = database.GetParamsData(actorData.status);
        parameter.id = actorData.id;
        parameter.lvmax = paramsData[0].lvmax;
        actorName = actorData.name;
    }

    private void OnValidate()
    {
        if (prevLv != parameter.lv)
        {
            if (parameter.lv < 1) parameter.lv = 1;
            if (parameter.lv > parameter.lvmax) parameter.lv = parameter.lvmax;
            Reset();
            parameter = GetParameterFromLv(parameter.lv);
            prevLv = parameter.lv;
        }
    }


    // ���x������Q�Ƃ����p�����[�^�[��Ԃ�
    private Params GetParameterFromLv(int lv)
    {
        Params p = new Params();
        p.id = parameter.id;
        p.lv = lv;
        p.lvmax = parameter.lvmax;
        for (int i = 0; i < lv; i++)
        {
            p.hp += paramsData[i].hp;
            p.hpmax += paramsData[i].hpmax;
            p.food += paramsData[i].food;
            p.foodmax += paramsData[i].foodmax;
            p.str += paramsData[i].str;
            p.def += paramsData[i].def;
            p.exp += paramsData[i].exp;
            p.xp += paramsData[i].xp;
        }
        return p;
    }

    // �p�����[�^�[�̃R�s�[��Ԃ�
    public Params GetParameter()
    {
        Params p = new Params();
        p.id = parameter.id;
        p.lv = parameter.lv;
        p.lvmax = parameter.lvmax;
        p.hp = parameter.hp;
        p.hpmax = parameter.hpmax;
        p.food = parameter.food;
        p.foodmax = parameter.foodmax;
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
        parameter.lvmax = p.lvmax;
        parameter.hp = p.hp;
        parameter.hpmax = p.hpmax;
        parameter.food = p.food;
        parameter.foodmax = p.foodmax;
        parameter.str = p.str;
        parameter.def = p.def;
        parameter.exp = p.exp;
        parameter.xp = p.xp;
    }

    // �A�C�e���𑕔�����
    public void EquipItem(Item it)
    {
        RemoveEquipment(it);
        if (it.type == EItemType.Weapon)
        {
            Message.Add(6, it.name);
            equipment.weapon = it;
            it.isEquip = true;
        }
        else if (it.type == EItemType.Armor)
        {
            Message.Add(6, it.name);
            equipment.armor = it;
            it.isEquip = true;
        }
    }

    // �����A�C�e�����O��
    public void RemoveEquipment(Item it)
    {
        if (it.type == EItemType.Weapon && equipment.weapon != null && equipment.weapon.isEquip)
        {
            Message.Add(7, equipment.weapon.name);
            equipment.weapon.isEquip = false;
            equipment.weapon = null;
        }
        else if (it.type == EItemType.Armor && equipment.armor != null && equipment.armor.isEquip)
        {
            Message.Add(7, equipment.armor.name);
            equipment.armor.isEquip = false;
            equipment.armor = null;
        }
    }

    // �_���[�W���󂯂�
    public void Damaged(int str)
    {
        int d = CalcDamage(str, parameter.def + equipment.GetAllDef());
        parameter.hp -= d;
        if (parameter.id < 1) Message.Add(1, actorName, d.ToString());
        else Message.Add(2, actorName, d.ToString());
    }

    // �_���[�W���v�Z����
    private static int CalcDamage(int str, int def)
    {
        return Mathf.CeilToInt(str * Mathf.Pow(0.9375f, def));
    }

    // �����x������������
    public void DecreaseFood()
    {
        if (parameter.food > 0)
        {
            parameter.food -= decFoodPt;
            if (parameter.food < 0) parameter.food = 0;
        }
        else parameter.hp--;
    }

    // �����x���񕜂���
    public void RecoveryFood(int food)
    {
        parameter.food += food;
        if (parameter.food > parameter.foodmax)
        {
            parameter.food = parameter.foodmax;
            Message.Add(17);
            return;
        }
        Message.Add(18);
    }

    // �̗͂��񕜂���
    public void RecoveryHp(int p)
    {
        int hp = parameter.hpmax - parameter.hp;
        hp = p < hp ? p : hp;
        Message.Add(15, actorName, hp.ToString());
        parameter.hp += hp;
    }

    [System.Serializable]
    public class Equipment
    {
        public Item weapon;
        public Item armor;

        // �S�Ă̐g�ɒ����Ă��鑕���i�̍U���͂̍��Z�l��Ԃ�
        public int GetAllAtk()
        {
            return (weapon == null ? 0 : weapon.atk) + (armor == null ? 0 : armor.atk);
        }

        // �S�Ă̐g�ɒ����Ă��鑕���i�̖h��͂̍��Z�l��Ԃ�
        public int GetAllDef()
        {
            return (weapon == null ? 0 : weapon.def) + (armor == null ? 0 : armor.def);
        }
    }
}
