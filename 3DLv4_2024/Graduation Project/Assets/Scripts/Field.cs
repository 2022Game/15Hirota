using System.Collections.Generic;
using UnityEngine;
using static ExcelActorData;

public class Field : MonoBehaviour
{
    public GameObject floor;
    public GameObject wall;
    public GameObject line;
    public ActorMovement playerMovement;
    public GameObject enemies;
    public GameObject items;
    public ExcelItemData itemDatabase;
    public GameObject stairs;
    public string startStairs = "Down";
    public static int floorNum = 1;
    public ExcelActorData actorDatabase;
    public ExcelAppearData appearDatabase;

    private Array2D map;
    private const float oneTile = 1.0f;
    private const float floorSize = 10.0f / oneTile;

    // グリッド座標をワールド座標に変換
    public static float ToWorldX(int xgrid)
    {
        return xgrid * oneTile;
    }

    // ワールド座標をグリッド座標に変換
    public static float ToWorldZ(int zgrid)
    {
        return zgrid * oneTile;
    }

    // ワールド座標をグリッド座標に変換
    // FloorToInt : 小数点以下の値を切り捨てる関数
    public static float ToGridX(float xworld)
    {
        return Mathf.FloorToInt(xworld / oneTile);
    }

    // ワールド座標をグリッド座標に変換
    public static float ToGridZ(float zworld)
    {
        return Mathf.FloorToInt(zworld / oneTile);
    }

    /**
    * マップデータの生成
    */
    public void Create(Array2D mapdata)
    {
        map = mapdata;
        float floorw = map.width / floorSize;
        float floorh = map.height / floorSize;
        floor.transform.localScale = new Vector3(floorw, 1, floorh);
        float floorx = (map.width - 1) / 2.0f * oneTile;
        float floorz = (map.height - 1) / 2.0f * oneTile;
        floor.transform.position = new Vector3(floorx, 0, floorz);
        for (int z = 0; z < map.height; z++)
        {
            for (int x = 0; x < map.width; x++)
            {
                if (map.Get(x, z) > 0)
                {
                    GameObject block = Instantiate(wall);
                    float xblock = ToWorldX(x);
                    float zblock = ToWorldZ(z);
                    block.transform.localScale = new Vector3(oneTile, 2, oneTile);
                    block.transform.position = new Vector3(xblock, 1, zblock);
                    block.transform.SetParent(floor.transform.GetChild(0));
                }
            }
        }
        ShowGridEffects();
    }

    /**
    * 生成したマップのリセット
    */
    public void Reset()
    {
        for (int i = 0; i < items.transform.childCount; i++)
            Destroy(items.transform.GetChild(i).gameObject);
        for (int i = 0; i < enemies.transform.childCount; i++)
            Destroy(enemies.transform.GetChild(i).gameObject);
        for (int i = 0; i < floor.transform.childCount; i++)
        {
            Transform child = floor.transform.GetChild(i);
            for (int j = 0; j < child.childCount; j++)
                Destroy(child.GetChild(j).gameObject);
        }
    }

    /**
    * 指定の座標が壁かどうかをチェック
    */
    public bool IsCollide(int xgrid, int zgrid)
    {
        return map.Get(xgrid, zgrid) != 0;
    }

    // 指定の座標にキャラクターが居たらそのゲームオブジェクトを返す
    // いなければnullを返す
    public GameObject GetExistActor(int xgrid, int zgrid)
    {
        if (xgrid == playerMovement.newGrid.x && zgrid == playerMovement.newGrid.z)
            return playerMovement.gameObject;
        foreach (var enemyMovement in enemies.GetComponentsInChildren<ActorMovement>())
        {
            if (xgrid == enemyMovement.newGrid.x && zgrid == enemyMovement.newGrid.z)
                return enemyMovement.gameObject;
        }
        return null;
    }

    // 升目のエフェクトを表示する
    private void ShowGridEffects()
    {
        for (int x = 1; x < map.width; x++)
        {
            GameObject obj = Instantiate(line, floor.transform.GetChild(1));
            obj.transform.position = new Vector3(x * oneTile - oneTile / 2, 0.1f, -oneTile / 2);
            obj.transform.localScale = new Vector3(1, 1, floorSize * oneTile);
        }
        for (int z = 1; z < map.height; z++)
        {
            GameObject obj = Instantiate(line, floor.transform.GetChild(1));
            obj.transform.position = new Vector3(-oneTile / 2, 0.1f, z * oneTile - oneTile / 2);
            obj.transform.rotation = Quaternion.Euler(0, 90, 0);
            obj.transform.localScale = new Vector3(1, 1, floorSize * oneTile);
        }
    }

    // マップデータを返す
    public Array2D GetMapData()
    {
        Array2D mapdata = new Array2D(map.width,map.height);
        for (int z = 0; z < map.height; z++)
        {
            for (int x = 0; x < map.width; x++)
            {
                mapdata.Set(x,z,map.Get(x,z));
            }
        }
        return mapdata;
    }

    // 指定の座標にアイテムがあったらそのゲームオブジェクトを返す
    // 無ければnull
    public GameObject GetExistItem(int xgrid, int zgrid)
    {
        foreach (var itemMovement in items.GetComponentsInChildren<ItemMovement>())
        {
            if (xgrid == itemMovement.grid.x && zgrid == itemMovement.grid.z)
                return itemMovement.gameObject;
        }
        return null;
    }

    // フィールドにオブジェクトを配置する
    public void SetObject(string name, string type, int xgrid, int zgrid)
    {
        switch (type)
        {
            case "Stairs":
                if (name.Contains("Down"))
                    stairs.GetComponentsInChildren<ObjectPosition>()[1].SetPosition(xgrid, zgrid);
                else
                    stairs.GetComponentsInChildren<ObjectPosition>()[0].SetPosition(xgrid, zgrid);
                if (name.Contains(startStairs)) playerMovement.SetPosition(xgrid, zgrid);
                break;
            case "Enemy":
                EActor actorId;
                if (!System.Enum.TryParse(name, out actorId)) return;
                ExcelActorData.ActorData actorData = actorDatabase.Data.Find(n => n.id == actorId);
                if (actorData == null) break;
                GameObject enemyObj = (GameObject)Resources.Load("Prefabs/" + actorData.prefab);
                GameObject enemy = Instantiate(enemyObj, enemies.transform);
                enemy.GetComponent<ActorMovement>().SetPosition(xgrid, zgrid);
                enemy.GetComponent<EnemyOperation>().target = playerMovement;
                break;
            case "Item":
                SetItem(name, xgrid, zgrid);
                break;
                //Item itemData;
                //EItem itemId;
                //if (!System.Enum.TryParse(name, out itemId)) return;
                //if ((int)itemId > 1000) itemData = itemDatabase.Goods.Find(n => n.id == itemId);
                //else itemData = itemDatabase.Equipments.Find(n => n.id == itemId);
                //if (itemData == null) break;
                //GameObject itemObj = (GameObject)Resources.Load("Prefabs/" + itemData.prefab);
                //GameObject item = Instantiate(itemObj, items.transform);
                //item.GetComponent<ItemMovement>().SetPosition(xgrid, zgrid);
                //item.GetComponent<ItemParamsController>().SetParams(itemData);
        }
    }

    // フィールドにアイテムを設置する
    // nameに「Random」が指定されていた場合はその場所にランダムなアイテムを設置する
    private void SetItem(string name, int xgrid, int zgrid)
    {
        Item itemData;
        EItem itemId = EItem.NONE;
        if (name.Equals("Random"))
        {
            List<ExcelAppearData.ItemAppearData> cItems =
                appearDatabase.ItemAppear.FindAll(n => !n.shoponly && n.start <= floorNum && n.end >= floorNum);
            int maxRate = 0;
            foreach (var cItem in cItems) maxRate += cItem.rate;
            int p = Random.Range(1, maxRate + 1);
            foreach (var cItem in cItems)
            {
                Debug.Log(p);
                p -= cItem.rate;
                if (p <= 0)
                {
                    itemId = cItem.id;
                    break;
                }
            }
        }
        else if (!System.Enum.TryParse(name, out itemId)) return;
        if ((int)itemId > 1000) itemData = itemDatabase.Goods.Find(n => n.id == itemId);
        else itemData = itemDatabase.Equipments.Find(n => n.id == itemId);
        
        return;
    }

    // 階段とプレイヤーが重なっているかどうか
    // 登り階段(ゴール地点)なら0、下り階段(スタート地点)なら1
    // 階段と重なっていなければ-1を返す
    public int PlayerOnStairs()
    {
        Pos2D pPos = playerMovement.grid;
        for (int i = 0; i < 2; i++)
        {
            Pos2D sPos = stairs.GetComponentsInChildren<ObjectPosition>()[i].grid;
            if (pPos.x == sPos.x && pPos.z == sPos.z) return i;
        }
        return -1;
    }
}