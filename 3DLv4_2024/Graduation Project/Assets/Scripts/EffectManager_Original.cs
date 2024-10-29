using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EffectManager_Original : MonoBehaviour
{
    private List<GameObject> playingEffects = new List<GameObject>();

    public enum EType
    {
        Recovery,
        HitItem,
        Magic,
        Poison,
        Confusion,
        Paralysis,
        Sleep,
    };
    public GameObject recovery;
    public GameObject hititem;
    public GameObject magic;
    public GameObject poison;
    public GameObject confusion;
    public GameObject paralysis;
    public GameObject sleep;

    //private GameObject playingEffect;

    // 再生中かどうか
    public bool IsPlaying()
    {
        if (playingEffects.Count < 1) return false;
        return true;

        //ParticleSystem particleSystem = playingEffect.GetComponentInChildren<ParticleSystem>();
        //if (particleSystem == null || particleSystem.isStopped)
        //{
        //    Destroy(playingEffect);
        //    playingEffect = null;
        //    return false;
        //}
        //return true;

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
        switch (type)
        {
            case EType.Recovery:
                playingEffects.Add(Instantiate<GameObject>(recovery, target.transform));
                break;
            case EType.HitItem:
                playingEffects.Add(Instantiate<GameObject>(hititem, target.transform));
                break;
            case EType.Magic:
                playingEffects.Add(Instantiate<GameObject>(magic, target.transform));
                break;
            case EType.Poison:
                playingEffects.Add(Instantiate<GameObject>(poison, target.transform));
                break;
            case EType.Confusion:
                playingEffects.Add(Instantiate<GameObject>(confusion, target.transform));
                break;
            case EType.Paralysis:
                playingEffects.Add(Instantiate<GameObject>(paralysis, target.transform));
                break;
            case EType.Sleep:
                playingEffects.Add(Instantiate<GameObject>(sleep, target.transform));
                break;

        }
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    private void Update()
    {
        if (playingEffects.Count < 1) return;
        List<GameObject> tempEffects = new List<GameObject>();
        foreach (var effect in playingEffects)
        {
            tempEffects.Add(effect);
        }
        foreach (var effect in tempEffects)
        {
            if (effect.GetComponentInChildren<ParticleSystem>().isStopped)
            {
                Destroy(effect);
                playingEffects.Remove(effect);
            }
        }

        // スプライトのアニメーション画像を使う際には
        // 下記の処理に変更

        //if (playingEffects.Count < 1) return;
        //List<GameObject> tempEffects = new List<GameObject>();
        //foreach (var effect in playingEffects)
        //{
        //    tempEffects.Add(effect);
        //}
        //foreach (var effect in tempEffects)
        //{
        //    ParticleSystem particle = effect.GetComponentInChildren<ParticleSystem>();
        //    if (particle != null && particle.isStopped)
        //    {
        //        Destroy(effect);
        //        playingEffects.Remove(effect);
        //        return;
        //    }
        //    Animator animator = effect.GetComponentInChildren<Animator>();
        //    if (animator != null && animator.GetCurrentAnimatorStateInfo(0).normalizedTime >= 1)
        //    {
        //        Destroy(effect);
        //        playingEffects.Remove(effect);
        //        return;
        //    }
        //}
    }
}
