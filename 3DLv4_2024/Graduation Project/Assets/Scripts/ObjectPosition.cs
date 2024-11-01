using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPosition : MonoBehaviour
{
    public Pos2D grid = new Pos2D();
    public EDir direction = EDir.Up;

    // インスペクターの値が変わった時に呼び出される
    private void OnValidate()
    {
        if (grid.x != Field.ToGridX(transform.position.x) || grid.z != Field.ToGridZ(transform.position.z))
            transform.position = new Vector3(Field.ToWorldX(grid.x), 0, Field.ToWorldZ(grid.z));
        if (direction != DirUtil.RotationToDir(transform.rotation))
            transform.rotation = DirUtil.DirToRotation(direction);
    }

    // 指定したグリッド座標に合わせて位置を変更する
    public void SetPosition(int xgrid, int zgrid)
    {
        grid.x = xgrid;
        grid.z = zgrid;
        transform.position = new Vector3(Field.ToWorldX(xgrid), 0, Field.ToWorldZ(zgrid));
    }

    // 指定した向きに合わせて回転ベクトルも変更する
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
