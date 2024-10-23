using System.Runtime.InteropServices.WindowsRuntime;
using UnityEngine;

public class ItemMovement : ObjectMovement
{
    private bool isThrowing = false;
    private GameObject effect = null;

    // ��������ʒu�̐ݒ�
    public void SetThrowPosition(EDir d)
    {
        Field field = GetComponentInParent<Field>();
        Pos2D pos = DirUtil.Move(field, grid, d);
        while (!newGrid.Equals(pos))
        {
            newGrid = pos;
            pos = DirUtil.Move(field, newGrid, d);
        }
        pos = DirUtil.Move(field, newGrid, d, false);
        pos = GetFallPosition(pos);
        if (pos != null) newGrid = pos;
    }

    // ������
    public bool Throwing(EDir d, ActorParamsController tParam)
    {
        if (!isThrowing && effect == null)
        {
            SetThrowPosition(d);
            isThrowing = true;
        }
        if (!isThrowing && effect != null)
        {
            if (effect.GetComponentInChildren<ParticleSystem>().isStopped)
            {
                Destroy(effect);
                Destroy(gameObject);
                return true;
            }
            return false;
        }
        if (Moving() == EAct.MoveEnd)
        {
            Field field = GetComponentInParent<Field>();
            HitActor(tParam, field.GetExistActor(grid.x, grid.z));
            if (!gameObject.Equals(field.GetExistItem(grid.x, grid.z)))
                Destroy(gameObject);
            isThrowing = false;
            if (effect == null) return true;
        }
        return false;
    }

    // �����ł���ꏊ��Ԃ�
    private Pos2D GetFallPosition(Pos2D pos)
    {
        Field field = GetComponentInParent<Field>();
        if (field.GetExistActor(pos.x, pos.z) != null) return pos;
        if (field.GetExistItem(pos.x, pos.z) == null) return pos;
        foreach (EDir d in System.Enum.GetValues(typeof(EDir)))
        {
            if (d == EDir.Pause) continue;
            Pos2D newP = DirUtil.Move(field, pos, d, false);
            if (newP.Equals(pos)) continue;
            if (field.GetExistActor(newP.x, newP.z) != null) return newP;
            if (field.GetExistItem(newP.x, newP.z) == null) return newP;
        }
        return null;
    }

    // �����L�����N�^�[�ɂԂ�������A�C�e�����ʂ𔭐�������
    private void HitActor(ActorParamsController tParam, UnityEngine.GameObject actor)
    {
        Item param = GetComponent<ItemParamsController>().parameter;
        if (actor == null) Message.Add(20, param.name);
        else
        {
            if (param.dmg > 0)
            {
                GameObject effectObj = Resources.Load<GameObject>("Prefabs/HitItemEffect");
                effect = Instantiate(effectObj, actor.transform);
                int str = tParam.parameter.str + param.dmg;
                actor.GetComponent<ActorParamsController>().Damaged(str);
            }
            else if (param.hp > 0)
            {
                GameObject effectObj = Resources.Load<GameObject>("Prefabs/RecoveryEffect");
                effect = Instantiate(effectObj, actor.transform);
                actor.GetComponent<ActorParamsController>().RecoveryHp(param.hp);
            }
            Message.Add(19, param.name);
        }
    }
}