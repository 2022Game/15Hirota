[System.Serializable]
public class Item
{
    public bool isEquip;

    public EItem id;

    public EItemType type;
    public string name;
    public string sprite;
    public string prefab;
    public int atk;
    public int def;
    public int hp;
    public int food;
    public int dmg;
    public ECondition condition;
    public string extra;
    public EItem shot;
    public string detail;

    public Item Get()
    {
        Item p = new Item();
        p.id = id;        
        p.type = type;
        p.name = name;
        p.prefab = prefab;
        p.sprite = sprite;
        p.isEquip = isEquip;
        p.atk = atk;
        p.def = def;
        p.hp = hp;
        p.food = food;
        p.dmg = dmg;
        p.condition = condition;
        p.extra = extra;
        p.shot = shot;
        p.detail = detail;
        return p;
    }
}