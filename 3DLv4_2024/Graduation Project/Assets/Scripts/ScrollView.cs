using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScrollView : MonoBehaviour
{
    public GameObject viewPort;
    public GameObject content;
    public float inputHoldDelay = 0.5f;

    private int selectItemIndex = 0;
    private float time = 0;

    // Start is called before the first frame update
    void Start()
    {
        ScrollItem[] contents = content.GetComponentsInChildren<ScrollItem>();
        if (contents.Length < 1) return;
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
            content.transform.position += moveDistance;
            contents[selectItemIndex].SetSelected(true);
            time = 0;
            return;
        }

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
