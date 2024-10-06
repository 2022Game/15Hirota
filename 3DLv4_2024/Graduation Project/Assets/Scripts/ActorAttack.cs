using UnityEngine;

public class ActorAttack : MonoBehaviour
{
    public Animator animator;
    public float animationLength = 1.0f;

    private readonly int hashAttackPara = Animator.StringToHash("Attack");
    private float time = 0.0f;

    /**
    * �U���A�j���[�V�����J�n
    */
    public void Attack()
    {
        Message.Add("Attack");
        animator.SetTrigger(hashAttackPara);
    }

    /**
    * �U����
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