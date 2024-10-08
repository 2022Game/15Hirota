using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InventoryAnimation : MonoBehaviour
{
    public float maxPerFrameOpen = 0.3f;
    public float maxPerFrameClose = 0.3f;

    private Vector3 prevPos;
    private int frame = 0;

    // Start is called before the first frame update
    void Start()
    {
        prevPos = transform.position += new Vector3(0, -300);
    }

    // 開くアニメーション
    public bool Open()
    {
        return Move(prevPos + new Vector3(0, 300), maxPerFrameOpen);
    }

    // 閉じるアニメーション
    public bool Close()
    {
        return Move(prevPos + new Vector3(0, -300), maxPerFrameClose);
    }

    // 補間で計算してアニメーションさせる
    private bool Move(Vector3 p2, float maxPreFrame)
    {
        frame += 1;
        float c = maxPreFrame / Time.deltaTime;
        float t = frame / c;
        transform.position = prevPos + (p2 - prevPos) * t;
        if (c <= frame)
        {
            frame = 0;
            transform.position = p2;
            prevPos = p2;
            return true;
        }
        return false;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
