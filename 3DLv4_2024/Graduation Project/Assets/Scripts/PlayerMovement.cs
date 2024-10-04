using System.Collections;
using System.Collections.Generic;
using UnityEditor.VersionControl;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    public Animator animator;
    public EDir direction = EDir.Up;
    public float speed = 0.9f;
    public float speedDampTime = 0.1f;

    public Pos2D grid = new Pos2D();
    //public int maxFrame = 100;

    private int currentFrame = 0;
    private Pos2D newGrid = null;

    public float maxPerFrame = 1.67f;
    private float complementFrame;

    // readonly : 読み込み専用
    private readonly int hashSpeedPara = Animator.StringToHash("Speed");

    // Start is called before the first frame update
    void Start()
    {
        complementFrame = maxPerFrame / Time.deltaTime;
    }

    // 補間で計算して進む
    private Pos2D Move(Pos2D currentPos,Pos2D newPos,ref int frame)
    {
        float px1 = Field.ToWorldX(currentPos.x);
        float pz1 = Field.ToWorldX(currentPos.z);
        float px2 = Field.ToWorldX(newPos.x);
        float pz2 = Field.ToWorldZ(newPos.z);
        frame += 1;
        float t = frame / complementFrame;
        float newX = px1 + (px2 - px1) * t;
        float newZ = pz1 + (pz2 - pz1) * t;
        transform.position = new Vector3(newX, 0, newZ);
        animator.SetFloat(hashSpeedPara,speed,speedDampTime,Time.deltaTime);
        if (complementFrame <= frame)
        {
            frame = 0;
            transform.position = new Vector3(px2, 0, pz2);
            return newPos;
        }
        return currentPos;
    }

    // Update is called once per frame
    private void Update()
    {
        if (currentFrame == 0)
        {
            EDir d = DirUtil.KeyToDir();
            if (d == EDir.Pause)
                animator.SetFloat(hashSpeedPara, 0.0f, speedDampTime, Time.deltaTime);
            else
            {
                direction = d;
                Message.add(direction.ToString());
                transform.rotation = DirUtil.DirToRotation(direction);
                //newGrid = DirUtil.GetNewGrid(grid, direction);
                newGrid = DirUtil.Move(GetComponentInParent<Field>(), grid, direction);
                grid = Move(grid, newGrid, ref currentFrame);
            }
        }
        else grid = Move(grid, newGrid, ref currentFrame);
    }

    // インスペクターの値が変わった時に呼び出される
    void OnValidate()
    {
        if (grid.x != Field.ToGridX(transform.position.x) || grid.z != Field.ToGridZ(transform.position.z))
        {
            transform.position = new Vector3(Field.ToWorldX(grid.x),0, Field.ToWorldZ(grid.z));
        }
        if (direction != DirUtil.RotationToDir(transform.rotation))
        {
            transform.rotation = DirUtil.DirToRotation(direction);
        }
    }

    /**
    * 指定したグリッド座標に合わせて位置を変更する
    */
    public void SetPosition(int xgrid, int zgrid)
    {
        grid.x = xgrid;
        grid.z = zgrid;
        transform.position = new Vector3(Field.ToWorldX(xgrid), 0, Field.ToWorldZ(zgrid));
    }
}