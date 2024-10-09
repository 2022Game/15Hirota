using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScrollItem : MonoBehaviour
{
    public Color[] color;
    public float paddingX = 20;
    private bool isSelected = false;

    // ���̃X�N���v�g���A�^�b�`����Ă���I�u�W�F�N�g���B��Ă���ꍇ��
    // �ړ�����ׂ��ʒu�܂ł̋�����Ԃ�
    public Vector3 GetMoveDistance(RectTransform viewport)
    {
        RectTransform transform = GetComponent<RectTransform>();
        float x1 = transform.rect.x + transform.position.x;
        float x2 = x1 + transform.rect.width;
        float vx1 = viewport.rect.x + viewport.position.x;
        float vx2 = vx1 + viewport.rect.width;
        if (x1 < vx2) return new Vector3(vx1 - x1 + paddingX, 0);
        if (x2 < vx2) return new Vector3(vx2 - x2 + paddingX, 0);
        return new Vector3(0, 0);
    }

    // �I����Ԃ�Ԃ�
    public bool GetSelected() => isSelected;

    // �I����Ԃ�ݒ肷��
    public void SetSelected(bool s, bool isForce = false)
    {
        if (s)
        {
            foreach (var item in transform.parent.GetComponentsInChildren<ScrollItem>())
                item.SetSelected(false, true);
            isSelected = true;
            GetComponent<Image>().color = color[1];
        }
        else if (isForce)
        {
            isSelected = false;
            GetComponent<Image>().color = color[0];
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
