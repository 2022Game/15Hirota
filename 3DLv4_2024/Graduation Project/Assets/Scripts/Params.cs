// キャラクターパラメーター
[System.Serializable]
public class Params
{
    public EActor id;      // ユニークID
    public int lv;      // レベル
    public int lvmax;   // レベル最大値
    public float hp;      // HP
    public float hpmax;   // 最大HP
    public float food;    // 満腹度
    public float foodmax; // 満腹度最大値
    public int str;     // 攻撃力
    public int def;     // 防御力
    public int exp;     // 獲得した経験値
    public int xp;      // 倒したときに得られる経験値
}
