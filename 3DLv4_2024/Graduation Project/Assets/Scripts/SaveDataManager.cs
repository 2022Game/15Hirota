using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem;

public class SaveDataManager : MonoBehaviour
{
    public Field field;
    public GameObject player;
    public GameObject enemies;
    private SaveData saveData;
    private const string saveKey = "GameData";

    // Start is called before the first frame update
    void Start()
    {
        saveData = new SaveData();    
    }

    // �A�N�^�[�f�[�^���쐬�A�Ԃ�
    private ActorSaveData MakeActorData(Transform actor)
    {
        ActorMovement move = actor.GetComponent<ActorMovement>();
        ActorSaveData actorSaveData = new ActorSaveData();
        actorSaveData.grid = new Pos2D();
        actorSaveData.grid.x = move.grid.x;
        actorSaveData.grid.z = move.grid.z;
        actorSaveData.direction = move.direction;
        actorSaveData.parameter = actor.GetComponent<ActorParamsController>().GetParameter();
        return actorSaveData;
    }

    // �A�N�^�[�f�[�^���A�N�^�[�ɔ��f����
    private void LoadActorData(ActorSaveData data, Transform actor)
    {
        ActorMovement move = actor.GetComponent<ActorMovement>();
        move.SetPosition(data.grid.x, data.grid.z);
        move.SetDirection(data.direction);
        actor.GetComponent<ActorParamsController>().SetParameter(data.parameter);
    }

    // �v���C���[�f�[�^���쐬�A�Ԃ�
    private ActorSaveData MakePlayerData()
    {
        return MakeActorData(player.transform);
    }

    // �v���C���[�f�[�^�𔽉f����
    private void LoadPlayerData(SaveData saveData)
    {
        LoadActorData(saveData.playerData, player.transform);
    }

    // �G�f�[�^���쐬�A�Ԃ�
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

    // �G�f�[�^�𔽉f����minotaur1
    private void LoadEnemyDatas(SaveData saveData)
    {
        GameObject enemyObj = (GameObject)Resources.Load("Prefabs/minotaur1");
        foreach (var data in saveData.enemyDatas)
        {
            GameObject enemy = Instantiate(enemyObj, enemies.transform);
            LoadActorData(data, enemy.transform);
        }
    }

    // �}�b�v�f�[�^���쐬�A�Ԃ�
    private MapSaveData MakeMapData()
    {
        MapSaveData mapSaveData = new MapSaveData();
        mapSaveData.map = field.GetMapData();
        return mapSaveData;
    }

    // �}�b�v�f�[�^�𔽉f����
    private void LoadMapData(SaveData saveData)
    {
        field.Reset();
        field.Create(saveData.mapData.map);
    }

    // �f�[�^��ۑ�����
    private void Save()
    {
        saveData.playerData = MakePlayerData();
        saveData.enemyDatas = MakeEnemyDatas();
        saveData.mapData = MakeMapData();
        PlayerPrefs.SetString(saveKey, JsonUtility.ToJson(saveData));
    }

    // �f�[�^��ǂݍ���
    private void Load()
    {
        if (PlayerPrefs.HasKey(saveKey))
        {
            var data = PlayerPrefs.GetString(saveKey);
            JsonUtility.FromJsonOverwrite(data, saveData);
            LoadMapData(saveData);
            LoadEnemyDatas(saveData);
            LoadPlayerData(saveData);
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
                Message.Add("�Z�[�u���܂����I");
            }
            if (Input.GetKeyDown(KeyCode.L))
            {
                Load();
                Message.Add("���[�h���܂����I");
            }
        }
    }
}
