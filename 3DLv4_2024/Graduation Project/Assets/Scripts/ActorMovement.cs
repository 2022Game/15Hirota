using System.Collections;
using System.Collections.Generic;
using UnityEditor.VersionControl;
using UnityEngine;
using UnityEngine.UIElements;

public class ActorMovement : MonoBehaviour
{
    public Animator animator;
    public EDir direction = EDir.Up;
    public float speed = 0.9f;
    public float speedDampTime = 0.1f;

    public Pos2D grid = new Pos2D();
    //public int maxFrame = 100;

    private int currentFrame = 0;
    public Pos2D newGrid = null;

    public float maxPerFrame = 1.67f;
    private float complementFrame;

    // readonly : �ǂݍ��ݐ�p
    private readonly int hashSpeedPara = Animator.StringToHash("Speed");

    // Start is called before the first frame update
    void Start()
    {
        complementFrame = maxPerFrame / Time.deltaTime;
        newGrid = grid;
    }

    // ��ԂŌv�Z���Đi��
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

    // �C���X�y�N�^�[�̒l���ς�������ɌĂяo�����
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
    * �w�肵���O���b�h���W�ɍ��킹�Ĉʒu��ύX����
    */
    public void SetPosition(int xgrid, int zgrid)
    {
        grid.x = xgrid;
        grid.z = zgrid;
        transform.position = new Vector3(Field.ToWorldX(xgrid), 0, Field.ToWorldZ(zgrid));
        newGrid = grid;
    }

    // �w�肵�������ɍ��킹�ĉ�]�x�N�g�����ύX����
    public void SetDirection(EDir d)
    {
        direction = d;
        transform.rotation = DirUtil.DirToRotation(d);
    }

    // �ړ��J�n�ł��邩�ǂ���
    public bool IsMoveBegin()
    {
        newGrid = DirUtil.Move(GetComponentInParent<Field>(), grid, direction);
        if (grid.Equals(newGrid)) return false;
        return true;
    }

    // ���s�A�j���[�V�����J�n
    public void Walk()
    {
        if (currentFrame > 0) return;
        //Message.Add(direction.ToString());
        //newGrid = DirUtil.Move(GetComponentInParent<Field>(), grid, direction);
        grid = Move(grid, newGrid, ref currentFrame);
    }

    // ���s��
    public EAct Walking()
    {
        if (grid.Equals(newGrid) && currentFrame == 0)
        {
            animator.SetFloat(hashSpeedPara, 0.0f, speedDampTime, Time.deltaTime);
            return EAct.MoveEnd;
        }
        grid = Move(grid, newGrid, ref currentFrame);
        return EAct.Move;
    }

    // ��~
    public void Stop()
    {
        if (animator.GetFloat(hashSpeedPara) > 0.0f)
        {
            animator.SetFloat(hashSpeedPara, 0.0f, speedDampTime, Time.deltaTime);
        }
    }
}