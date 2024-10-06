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
        Message.Add("Attack");
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
}