using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScrollView : MonoBehaviour
{
    public GameObject viewPort;
    public GameObject content;
    //public float inputHoldDelay = 0.5f;
    public float maxPerFrameScroll = 0.3f;

    private int selectItemIndex = 0;
    //private float time = 0;
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

    // EDirを受け取って、その方向にカーソルを動かす
    public bool MoveSelect(EDir d)
    {
        ScrollItem[] contents = content.GetComponentsInChildren<ScrollItem>();
        if (contents.Length < 1) return true;
        if (frame > 0) return Move(nextPosX, maxPerFrameScroll);
        selectItemIndex = GetSelectItemIndexFor(contents);
        if (d == EDir.Right)
        {
            selectItemIndex = (selectItemIndex + 1) % contents.Length;
        }
        if (d == EDir.Left)
        {
            selectItemIndex = (selectItemIndex + contents.Length - 1) % contents.Length;
        }
        Vector3 moveDistance = contents[selectItemIndex].GetMoveDistance(viewPort.GetComponent<RectTransform>());
        nextPosX = content.transform.position.x + moveDistance.x;
        contents[selectItemIndex].SetSelected(true);
        return Move(nextPosX, maxPerFrameScroll);
    }

    // Update is called once per frame
    //void Update()
    //{
    //    if (!transform.parent.gameObject.activeInHierarchy) return;
    //    ScrollItem[] contents = content.GetComponentsInChildren<ScrollItem>();
    //    if (contents.Length < 1) return;
    //    if (frame > 0) Move(nextPosX, maxPerFrameScroll);
    //    selectItemIndex = GetSelectItemIndexFor(contents);
    //    Vector3 moveDistance;
    //    if (Input.anyKeyDown)
    //    {
    //        if (Input.GetKeyDown(KeyCode.RightArrow))
    //        {
    //            selectItemIndex = (selectItemIndex + 1) % contents.Length;
    //        }
    //        if (Input.GetKeyDown(KeyCode.LeftArrow))
    //        {
    //            selectItemIndex = (selectItemIndex + contents.Length - 1) % contents.Length;
    //        }
    //        moveDistance = contents[selectItemIndex].GetMoveDistance(viewPort.GetComponent<RectTransform>());
    //        nextPosX = content.transform.position.x + moveDistance.x;
    //        Move(nextPosX, maxPerFrameScroll);
    //        contents[selectItemIndex].SetSelected(true);
    //        time = 0;
    //        return;
    //    }
    //    time += Time.deltaTime;
    //    if (time < inputHoldDelay) return;
    //    if (!Input.anyKey) return;
    //    if (Input.GetKey(KeyCode.RightArrow))
    //    {
    //        selectItemIndex = (selectItemIndex + 1) % contents.Length;
    //    }
    //    if (Input.GetKey(KeyCode.LeftArrow))
    //    {
    //        selectItemIndex = (selectItemIndex + contents.Length - 1) % contents.Length;
    //    }
    //    moveDistance = contents[selectItemIndex].GetMoveDistance(viewPort.GetComponent<RectTransform>());
    //    nextPosX = content.transform.position.x + moveDistance.x;
    //    Move(nextPosX, maxPerFrameScroll);
    //    contents[selectItemIndex].SetSelected(true);
    //    time = 0;
    //}

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

    // 配列から選択されているアイテムのインデックスを返す
    private int GetSelectItemIndexFor(ScrollItem[] contents)
    {
        for (int i = 0; i < contents.Length; i++)
        {
            if (contents[i].GetSelected()) return i;
        }
        return 0;
    }

    // コンテンツオブジェクトの位置を移動する
    public void MoveContentPosition(Vector3 p)
    {
        content.transform.position += p;
        prevPosX += p.x;
        nextPosX += p.x;
    }
}
