using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScrollView : MonoBehaviour
{
    public GameObject viewPort;
    public GameObject content;
    public float inputHoldDelay = 0.5f;
    public float maxPerFrameScroll = 0.3f;

    private int selectItemIndex = 0;
    private float time = 0;
    private float prevPosX;
    private float nextPosX;
    private int frame = 0;

    // Start is called before the first frame update
    void Start()
    {
        ScrollItem[] contents = content.GetComponentsInChildren<ScrollItem>();
        if (contents.Length > 0)
            contents[selectItemIndex].SetSelected(true);
        nextPosX = prevPosX = content.transform.position.x;
    }

    // Update is called once per frame
    void Update()
    {
        if (!transform.parent.gameObject.activeInHierarchy) return;
        ScrollItem[] contents = content.GetComponentsInChildren<ScrollItem>();
        if (contents.Length < 1) return;
        if (frame > 0) Move(nextPosX, maxPerFrameScroll);
        Vector3 moveDistance;
        if (Input.anyKeyDown)
        {
            if (Input.GetKeyDown(KeyCode.RightArrow))
            {
                selectItemIndex = (selectItemIndex + 1) % contents.Length;
            }
            if (Input.GetKeyDown(KeyCode.LeftArrow))
            {
                selectItemIndex = (selectItemIndex + contents.Length - 1) % contents.Length;
            }
            moveDistance = contents[selectItemIndex].GetMoveDistance(viewPort.GetComponent<RectTransform>());
            nextPosX = content.transform.position.x + moveDistance.x;
            Move(nextPosX, maxPerFrameScroll);
            contents[selectItemIndex].SetSelected(true);
            time = 0;
            return;
        }
        time += Time.deltaTime;
        if (time < inputHoldDelay) return;
        if (!Input.anyKey) return;
        if (Input.GetKey(KeyCode.RightArrow))
        {
            selectItemIndex = (selectItemIndex + 1) % contents.Length;
        }
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            selectItemIndex = (selectItemIndex + contents.Length - 1) % contents.Length;
        }
        moveDistance = contents[selectItemIndex].GetMoveDistance(viewPort.GetComponent<RectTransform>());
        nextPosX = content.transform.position.x + moveDistance.x;
        Move(nextPosX, maxPerFrameScroll);
        contents[selectItemIndex].SetSelected(true);
        time = 0;
    }

    // 選択されているアイテムのインデックスを返す
    public int GetSelectItemIndex() => selectItemIndex;

    // 補間で計算してアニメーションさせる
    private bool Move(float p2x, float maxPerFrame)
    {
        frame += 1;
        float c = maxPerFrame / Time.deltaTime;
        float t = frame / c;
        content.transform.position = new Vector3(prevPosX + (p2x - prevPosX) * t, content.transform.position.y);
        if (c <= frame)
        {
            frame = 0;
            content.transform.position = new Vector3(p2x, content.transform.position.y);
            prevPosX = p2x;
            return true;
        }
        return false;
    }
}
