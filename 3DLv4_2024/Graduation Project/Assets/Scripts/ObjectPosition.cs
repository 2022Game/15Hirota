using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPosition : MonoBehaviour
{
    public Pos2D grid = new Pos2D();
    public EDir direction = EDir.Up;

    // �C���X�y�N�^�[�̒l���ς�������ɌĂяo�����
    private void OnValidate()
    {
        if (grid.x != Field.ToGridX(transform.position.x) || grid.z != Field.ToGridZ(transform.position.z))
            transform.position = new Vector3(Field.ToWorldX(grid.x), 0, Field.ToWorldZ(grid.z));
        if (direction != DirUtil.RotationToDir(transform.rotation))
            transform.rotation = DirUtil.DirToRotation(direction);
    }

    // �w�肵���O���b�h���W�ɍ��킹�Ĉʒu��ύX����
    public void SetPosition(int xgrid, int zgrid)
    {
        grid.x = xgrid;
        grid.z = zgrid;
        transform.position = new Vector3(Field.ToWorldX(xgrid), 0, Field.ToWorldZ(zgrid));
    }

    // �w�肵�������ɍ��킹�ĉ�]�x�N�g�����ύX����
    public void SetDirection(EDir d)
    {
        direction = d;
        transform.rotation = DirUtil.DirToRotation(d);
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
