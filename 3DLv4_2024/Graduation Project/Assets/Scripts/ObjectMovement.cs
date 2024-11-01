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

    // インスペクターの値が変わった時に呼び出される
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

    // 移動開始
    public bool Move()
    {
        if (currentFrame > 0) return false;
        grid = Move(grid, newGrid, ref currentFrame);
        return true;
    }

    // 移動中
    public EAct Moving()
    {
        if (grid.Equals(newGrid) && currentFrame == 0)
        {
            return EAct.MoveEnd;
        }
        grid = Move(grid, newGrid, ref currentFrame);
        return EAct.Move;
    }

    // 補完で計算して進む
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

    // 指定したグリッド座標に合わせて位置を変更する
    //public void SetPosition(int xgrid, int zgrid)
    //{
    //    grid.x = xgrid;
    //    grid.z = zgrid;
    //    transform.position = new Vector3(Field.ToWorldX(xgrid), 0, Field.ToWorldZ(zgrid));
    //    newGrid = grid;
    //}

    // 指定した向きに合わせて回転ベクトルも変更する
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
