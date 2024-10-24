using System.Runtime.InteropServices.WindowsRuntime;
using UnityEngine;

public class ItemMovement : ObjectMovement
{
    private bool isThrowing = false;
    //private GameObject effect = null;
    private EffectManager_Original effect;
    private bool isPlayingEffect = false;

    // 投擲する位置の設定
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

    // 投擲中
    public bool Throwing(EDir d, ActorParamsController tParam)
    {
        if (effect == null) effect = GetComponentInParent<EffectManager_Original>();
        if (!isThrowing && !effect.IsPlaying())
        {
            SetThrowPosition(d);
            isThrowing = true;
        }
        //if (isPlayingEffect && !effect.IsPlaying())
        //{
        //    Destroy(gameObject);
        //    isPlayingEffect = false;
        //    return true;
        //}
        if (isPlayingEffect && !effect.IsPlaying())
        {
            Field field = GetComponentInParent<Field>();
            HitActor(tParam, field.GetExistActor(grid.x, grid.z));
            if (!gameObject.Equals(field.GetExistItem(grid.x, grid.z)))
                //Destroy(gameObject);
            DestroyImmediate(gameObject);
            Debug.Log("Destroying item: " + gameObject.name);
            isPlayingEffect = false;
            return true;
        }
        if (!effect.IsPlaying() && Moving() == EAct.MoveEnd)
        {
            HitEffect(GetComponentInParent<Field>().GetExistActor(grid.x, grid.z));
            isThrowing = false;
            if (!(isPlayingEffect = effect.IsPlaying())) return true;
        }
        return false;
    }

    // 落下できる場所を返す
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

    // もしキャラクターにぶつかったらアイテム効果を発生させる
    private void HitActor(ActorParamsController tParam, UnityEngine.GameObject actor)
    {
        Item param = GetComponent<ItemParamsController>().parameter;
        if (actor == null) Message.Add(10, param.name);
        else
        {
            if (param.dmg > 0)
            {
                int str = tParam.parameter.str + param.dmg;
                actor.GetComponent<ActorParamsController>().Damaged(str);
                if ((int)param.id > 1000)
                {
                    Message.Add(13, param.name);
                    Destroy(gameObject);
                }
                else actor.GetComponent<ActorUseItems>().PickUp(param);
            }
            else if (param.hp > 0)
            {
                effect.Play(EffectManager_Original.EType.Recovery, actor);
                actor.GetComponent<ActorParamsController>().RecoveryHp(param.hp);
            }
            Message.Add(19, param.name);
        }
    }

    // エフェクトを発生させる
    private void HitEffect(GameObject actor)
    {
        Item param = GetComponent<ItemParamsController>().parameter;
        if (actor == null) effect.Play(EffectManager_Original.EType.HitItem, gameObject);
        else
        {
            if (param.dmg > 0)
                effect.Play(EffectManager_Original.EType.HitItem, actor);
            else if (param.hp > 0)
                effect.Play(EffectManager_Original.EType.Recovery, actor);
        }
    }
}