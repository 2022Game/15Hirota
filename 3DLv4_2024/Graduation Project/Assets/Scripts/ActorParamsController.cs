using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActorParamsController : MonoBehaviour
{
    public Params parameter;

    // パラメーターのコピーを返す
    public Params GetParameter()
    {
        Params p = new Params();
        p.id = parameter.id;
        p.lv = parameter.lv;
        p.hp = parameter.hp;
        p.hpmax = parameter.hpmax;
        p.str = parameter.str;
        p.exp = parameter.exp;
        p.xp = parameter.xp;
        return p;
    }

    // パラメーターを纏めて設定する
    public void SetParameter(Params p)
    {
        parameter.id = p.id;
        parameter.lv = p.lv;
        parameter.hp = p.hp;
        parameter.hpmax = p.hpmax;
        parameter.str = p.str;
        parameter.exp = p.exp;
        parameter.xp = p.xp;
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
