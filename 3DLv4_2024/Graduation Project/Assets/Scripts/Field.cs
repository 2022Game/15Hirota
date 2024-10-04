using UnityEngine;
using UnityEngine.Rendering;

public class Field : MonoBehaviour
{
    public GameObject floor;
    public GameObject wall;

    private Array2D map;
    private const float oneTile = 2.0f;
    private const float floorSize = 10.0f / oneTile;

    // �O���b�h���W�����[���h���W�ɕϊ�
    public static float ToWorldX(int xgrid)
    {
        return xgrid * oneTile;
    }

    // ���[���h���W���O���b�h���W�ɕϊ�
    public static float ToWorldZ(int zgrid)
    {
        return zgrid * oneTile;
    }

    // ���[���h���W���O���b�h���W�ɕϊ�
    // FloorToInt : �����_�ȉ��̒l��؂�̂Ă�֐�
    public static float ToGridX(float xworld)
    {
        return Mathf.FloorToInt(xworld / oneTile);
    }

    // ���[���h���W���O���b�h���W�ɕϊ�
    public static float ToGridZ(float zworld)
    {
        return Mathf.FloorToInt(zworld / oneTile);
    }

    // �}�b�v�f�[�^�̐���
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
                if (map.Get(x,z) > 0)
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
    }

    // ���������}�b�v�̃��Z�b�g
    public void Reset()
    {
        Transform walls = floor.transform.GetChild(0);
        for (int i = 0; i < walls.childCount; i++)
        {
            Destroy(walls.GetChild(i).gameObject);
        }
    }

    // �w��̍��W���ǂ������`�F�b�N
    public bool IsCollide(int xgrid, int zgrid)
    {
        return map.Get(xgrid, zgrid) != 0;
    }

    void Start()
    {
        Array2D mapdata = new Array2D(10, 10);
        mapdata.Set(1, 1, 1);
        Create(mapdata);
    }
}