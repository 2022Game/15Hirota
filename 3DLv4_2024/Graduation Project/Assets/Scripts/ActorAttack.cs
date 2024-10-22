using UnityEngine;

public class ActorAttack : MonoBehaviour
{
    public Animator animator;
    public float animationLength = 1.0f;

    private readonly int hashAttackPara = Animator.StringToHash("Attack");
    private float time = 0.0f;

    /**
    * 攻撃アニメーション開始
    */
    public void Attack()
    {
        //Message.Add("Attack");
        animator.SetTrigger(hashAttackPara);
    }

    /**
    * 攻撃中
    */
    public EAct Attacking()
    {
        AnimatorStateInfo stateInfo = animator.GetCurrentAnimatorStateInfo(0);
        time += Time.deltaTime;
        if (time > animationLength)
        {
            time = 0.0f;
            return EAct.ActEnd;
        }
        return EAct.Act;
    }

    // 指定した相手がnullでなければダメージを与える
    public void DamageOpponent(GameObject actor)
    {
        if (actor == null) return;
        EDir d = DirUtil.ReverseDirection(GetComponent<ActorMovement>().direction);
        actor.GetComponent<ActorMovement>().SetDirection(d);
        ActorParamsController param = GetComponent<ActorParamsController>();
        int str = param.parameter.str + param.equipment.GetAllAtk();
        actor.GetComponent<ActorParamsController>().Damaged(str);
    }
}