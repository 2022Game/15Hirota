using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EffectManager_Original : MonoBehaviour
{
    public enum EType
    {
        Recovery,
        HitItem,
        Magic
    };
    public GameObject recovery;
    public GameObject hititem;
    public GameObject magic;

    private GameObject playingEffect;

    // 再生中かどうか
    public bool IsPlaying()
    {
        if (playingEffect == null) return false;

        ParticleSystem particleSystem = playingEffect.GetComponentInChildren<ParticleSystem>();
        if (particleSystem == null || particleSystem.isStopped)
        {
            Destroy(playingEffect);
            playingEffect = null;
            return false;
        }
        return true;

        //if (playingEffect == null) return false;
        //if (playingEffect.GetComponentInChildren<ParticleSystem>().isStopped)
        //{
        //    Destroy(playingEffect);
        //    playingEffect = null;
        //    return false;
        //}
        //return true;
    }

    // 指定したエフェクトを再生する
    public void Play(EType type, GameObject target)
    {
        if (playingEffect != null) return;
        switch (type)
        {
            case EType.Recovery:
                playingEffect = Instantiate<GameObject>(recovery, target.transform);
                break;
            case EType.HitItem:
                playingEffect = Instantiate<GameObject>(hititem, target.transform);
                break;
            case EType.Magic:
                playingEffect = Instantiate<GameObject>(magic, target.transform);
                break;
        }
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
