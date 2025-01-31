using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem;

public class SaveDataManager : MonoBehaviour
{
    public Field field;
    public GameObject player;
    public GameObject enemies;
    public GameObject items;
    public GameObject stairs;
    private SaveData saveData;
    private const string saveKey = "GameData";

    // Start is called before the first frame update
    void Start()
    {
        saveData = new SaveData();    
    }

    // アクターデータを作成、返す
    private ActorSaveData MakeActorData(Transform actor)
    {
        ActorMovement move = actor.GetComponent<ActorMovement>();
        ActorSaveData actorSaveData = new ActorSaveData();
        actorSaveData.grid = new Pos2D();
        actorSaveData.grid.x = move.grid.x;
        actorSaveData.grid.z = move.grid.z;
        actorSaveData.direction = move.direction;
        actorSaveData.parameter = actor.GetComponent<ActorParamsController>().GetParameter();
        ActorParamsController param = actor.GetComponent<ActorParamsController>();
        actorSaveData.parameter = param.GetParameter();
        actorSaveData.conditions = param.GetConditions();
        actorSaveData.clearConditionRates = param.GetClearConditionRates();
        actorSaveData.inventory = MakeInventoryData(actor);
        return actorSaveData;
    }

    // アクターデータをアクターに反映する
    private void LoadActorData(ActorSaveData data, Transform actor)
    {
        ActorMovement move = actor.GetComponent<ActorMovement>();
        ActorParamsController param = actor.GetComponent<ActorParamsController>();
        param.SetParameter(data.parameter);
        param.SetConditions(data.conditions);
        move.SetPosition(data.grid.x, data.grid.z);
        move.SetDirection(data.direction);
        actor.GetComponent<ActorParamsController>().SetParameter(data.parameter);
        param.SetClearConditionRates(data.clearConditionRates);
        LoadInventoryData(data.inventory, actor);
    }

    // プレイヤーデータを作成、返す
    private ActorSaveData MakePlayerData()
    {
        return MakeActorData(player.transform);
    }

    // プレイヤーデータを反映する
    private void LoadPlayerData(SaveData saveData)
    {
        LoadActorData(saveData.playerData, player.transform);
    }

    // 敵データを作成、返す
    private ActorSaveData[] MakeEnemyDatas()
    {
        int enemyCount = enemies.transform.childCount;
        ActorSaveData[] enemySaveDatas = new ActorSaveData[enemyCount];
        for (int i = 0; i < enemyCount; i++)
        {
            Transform enemy = enemies.transform.GetChild(i);
            enemySaveDatas[i] = MakeActorData(enemy);
        }
        return enemySaveDatas;
    }

    // 敵データを反映するminotaur1
    private void LoadEnemyDatas(SaveData saveData)
    {
        foreach (var data in saveData.enemyDatas)
        {
            ExcelActorData database = Resources.Load<ExcelActorData>("Datas/ExcelActorData");
            ExcelActorData.ActorData actorData =
                database.Data.Find(n => n.id == data.parameter.id);
            GameObject enemyObj = (GameObject)Resources.Load("Prefabs/" + actorData.prefab);
            GameObject enemy = Instantiate(enemyObj, enemies.transform);
            LoadActorData(data, enemy.transform);
            enemy.GetComponent<EnemyOperation>().target = player.GetComponent<ActorMovement>();
        }
    }

    // アイテムデータを作成、返す
    private ItemSaveData[] MakeItemDatas()
    {
        int itemCount = items.transform.childCount;
        ItemSaveData[] itemSaveDatas = new ItemSaveData[itemCount];
        for (int i = 0; i < itemCount; i++)
        {
            Transform it = items.transform.GetChild(i);
            ItemMovement move = it.GetComponent<ItemMovement>();
            ItemSaveData itemSaveData = new ItemSaveData();
            itemSaveData.grid = new Pos2D();
            itemSaveData.grid.x = move.grid.x;
            itemSaveData.grid.z = move.grid.z;
            itemSaveData.parameter = it.GetComponent<ItemParamsController>().GetParams();
            itemSaveDatas[i] = itemSaveData;
        }
        return itemSaveDatas;
    }


    // アイテムデータをマップ上に反映する
    private void LoadItemData(SaveData saveData)
    {
        foreach (var data in saveData.itemDatas)
        {
            GameObject itemObj = (GameObject)Resources.Load("Prefabs/" + data.parameter.prefab);
            GameObject it = Instantiate(itemObj, items.transform);
            ItemMovement move = it.GetComponent<ItemMovement>();
            move.SetPosition(data.grid.x, data.grid.z);
            it.GetComponent<ItemParamsController>().SetParams(data.parameter);
        }
    }

    // インベントリデータを作成、返す
    private InventorySaveData MakeInventoryData(Transform actor)
    {
        Inventory inventory = actor.GetComponent<Inventory>();
        InventorySaveData inventorySaveData = new InventorySaveData();
        inventorySaveData.items = inventory.GetAllItem();
        inventorySaveData.maxItemNum = inventory.itemNumMax;
        return inventorySaveData;
    }

    // インベントリデータをアクターに反映する
    private void LoadInventoryData(InventorySaveData data, Transform actor)
    {
        Inventory inventory = actor.GetComponent<Inventory>();
        inventory.SetAllItem(data.items, data.maxItemNum);
    }

    // マップデータを作成、返す
    private MapSaveData MakeMapData()
    {
        MapSaveData mapSaveData = new MapSaveData();
        Pos2D[] stairsPos = new Pos2D[2];
        for (int i = 0; i < 2; i++)
        {
            ObjectPosition objPos = stairs.transform.GetChild(i).GetComponent<ObjectPosition>();
            Pos2D pos = new Pos2D();
            pos.x = objPos.grid.x;
            pos.z = objPos.grid.z;
            stairsPos[i] = pos;
        }
        mapSaveData.stairs = stairsPos;
        mapSaveData.map = field.GetMapData();
        return mapSaveData;
    }

    // マップデータを反映する
    private void LoadMapData(SaveData saveData)
    {
        field.Reset();
        field.Create(saveData.mapData.map);
        for (int i = 0; i < 2; i++)
        {
            ObjectPosition objPos = stairs.transform.GetChild(i).GetComponent<ObjectPosition>();
            objPos.SetPosition(saveData.mapData.stairs[i].x, saveData.mapData.stairs[i].z);
        }
    }

    // データを保存する
    private void Save()
    {
        saveData.playerData = MakePlayerData();
        saveData.enemyDatas = MakeEnemyDatas();
        saveData.mapData = MakeMapData();
        saveData.itemDatas = MakeItemDatas();
        PlayerPrefs.SetString(saveKey, JsonUtility.ToJson(saveData));
    }

    // データを読み込む
    private void Load()
    {
        if (PlayerPrefs.HasKey(saveKey))
        {
            var data = PlayerPrefs.GetString(saveKey);
            JsonUtility.FromJsonOverwrite(data, saveData);
            LoadMapData(saveData);
            LoadEnemyDatas(saveData);
            LoadPlayerData(saveData);
            LoadItemData(saveData);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.anyKeyDown)
        {
            if (Input.GetKeyDown(KeyCode.K))
            {
                Save();
                Message.Add("セーブしました！");
            }
            if (Input.GetKeyDown(KeyCode.L))
            {
                Load();
                Message.Add("ロードしました！");
            }
        }
    }
}
