using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem;

public class SaveDataManager : MonoBehaviour
{
    public Field field;
    public GameObject player;
    private SaveData saveData;
    private const string saveKey = "GameData";

    // Start is called before the first frame update
    void Start()
    {
        saveData = new SaveData();    
    }

    // データを保存する
    private void Save()
    {
        ActorMovement playermove = player.GetComponent<ActorMovement>();
        ActorSaveData playerSaveData = new ActorSaveData();
        playerSaveData.grid = new Pos2D();
        playerSaveData.grid.x = playermove.grid.x;
        playerSaveData.grid.z = playermove.grid.z;
        playerSaveData.direction = playermove.direction;
        saveData.playerData = playerSaveData;
        MapSaveData mapSaveData = new MapSaveData();
        mapSaveData.map = field.GetMapData();
        saveData.mapData = mapSaveData;
        PlayerPrefs.SetString(saveKey, JsonUtility.ToJson(saveData));
    }

    // データを読み込む
    private void Load()
    {
       if (PlayerPrefs.HasKey(saveKey))
        {
            var data = PlayerPrefs.GetString(saveKey);
            JsonUtility.FromJsonOverwrite(data,saveData);
            field.Reset();
            field.Create(saveData.mapData.map);
            ActorMovement playermove = player.GetComponent<ActorMovement>();
            playermove.SetPosition(saveData.playerData.grid.x,saveData.playerData.grid.z);
            playermove.SetDirection(saveData.playerData.direction);
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
