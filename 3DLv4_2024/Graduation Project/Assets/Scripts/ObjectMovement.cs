using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class ObjectMovement : ObjectPosition
{
    //public Pos2D grid = new Pos2D();
    public Pos2D newGrid = null;
    //public EDir direction = EDir.Up;
    public float maxPerFrame = 1.67f;

    private float compementFrame;
    private int currentFrame = 0;

    // Start is called before the first frame update
    void Start()
    {
        compementFrame = maxPerFrame / Time.deltaTime;
        newGrid = grid;
    }

    // �C���X�y�N�^�[�̒l���ς�������ɌĂяo�����
    //private void OnValidate()
    //{
    //    if (grid.x != Field.ToGridX(transform.position.x) || grid.z != Field.ToGridZ(transform.position.z))
    //    {
    //        transform.position = new Vector3(Field.ToWorldX(grid.x), 0, Field.ToWorldZ(grid.z));
    //    }
    //    if (direction != DirUtil.RotationToDir(transform.rotation))
    //    {
    //        transform.rotation = DirUtil.DirToRotation(direction);
    //    }
    //}

    // �ړ��J�n
    public bool Move()
    {
        if (currentFrame > 0) return false;
        grid = Move(grid, newGrid, ref currentFrame);
        return true;
    }

    // �ړ���
    public EAct Moving()
    {
        if (grid.Equals(newGrid) && currentFrame == 0)
        {
            return EAct.MoveEnd;
        }
        grid = Move(grid, newGrid, ref currentFrame);
        return EAct.Move;
    }

    // �⊮�Ōv�Z���Đi��
    private Pos2D Move(Pos2D currentPos, Pos2D newPos, ref int frame)
    {
        float px1 = Field.ToWorldX(currentPos.x);
        float pz1 = Field.ToWorldZ(currentPos.z);
        float px2 = Field.ToWorldX(newPos.x);
        float pz2 = Field.ToWorldZ(newPos.z);
        frame += 1;
        float t = frame / compementFrame;
        float newX = px1 + (px2 - px1) * t;
        float newZ = pz1 + (pz2 - pz1) * t;
        transform.position = new Vector3(newX, 0, newZ);
        if (compementFrame <= frame)
        {
            frame = 0;
            transform.position = new Vector3(px2, 0, pz2);
            return newPos;
        }
        return currentPos;
    }

    // �w�肵���O���b�h���W�ɍ��킹�Ĉʒu��ύX����
    //public void SetPosition(int xgrid, int zgrid)
    //{
    //    grid.x = xgrid;
    //    grid.z = zgrid;
    //    transform.position = new Vector3(Field.ToWorldX(xgrid), 0, Field.ToWorldZ(zgrid));
    //    newGrid = grid;
    //}

    // �w�肵�������ɍ��킹�ĉ�]�x�N�g�����ύX����
    //public void SetDirection(EDir d)
    //{
    //    direction = d;
    //    transform.rotation = DirUtil.DirToRotation(d);
    //}

    // Update is called once per frame
    void Update()
    {
        
    }
}
