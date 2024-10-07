using UnityEngine;

public class MessageAnimation : MonoBehaviour
{
    public float waitTime = 8.0f;
    public float maxPerFrameD = 1.0f;

    private bool isMoving = false;
    private bool isDeleting = false;
    private Vector3 prevPos = Vector3.zero; // ������
    private int frame = 0;

    // Start is called before the first frame update
    void Start()
    {
        prevPos = transform.position;
        //Application.targetFrameRate = 150;
    }

    // Update is called once per frame
    void Update()
    {
        Invoke("DeleteMessage", waitTime);
    }

    /**
    * �⊮�Ōv�Z���ăA�j���[�V����������
    */
    public bool MoveMessage(Vector3 p2, float maxPerFrame)
    {
        // �ړ������ǂ����̃t���O
        isMoving = !isDeleting;

        // �e�t���[���ŃJ�E���g��i�߂�
        frame += 1;

        // c: �K�v�ȃt���[�����̌v�Z
        float c = maxPerFrame / Time.deltaTime;

        // �ړ��̐i�s���� (0.0�`1.0) ���v�Z
        float t = frame / c;

        // Mathf.SmoothStep�ŕ�Ԃ��Ċ��炩�Ɉړ�
        t = Mathf.SmoothStep(0.0f, 1.0f, t);

        // �ʒu�̍X�V�i���`��Ԃ̑����SmoothStep�𗘗p�j
        transform.position = Vector3.Lerp(prevPos, p2, t);

        // �ړ������������ꍇ
        if (t >= 1.0f)
        {
            frame = 0;
            transform.position = p2;
            prevPos = p2;
            isMoving = false;
            return true;
        }

        return false;
    }

    /**
    * �폜�A�j���[�V�������ł͂Ȃ���
    */
    public bool IsDeleting() => isDeleting;

    /**
    * �폜�A�j���[�V����
    */
    private void DeleteMessage()
    {
        if (isMoving) return;
        isDeleting = true;
        MoveMessage(prevPos + new Vector3(0, -1000, 0), maxPerFrameD);
        if (transform.position.y < -100.0f)
        {
            Destroy(gameObject);
        }
    }
}
