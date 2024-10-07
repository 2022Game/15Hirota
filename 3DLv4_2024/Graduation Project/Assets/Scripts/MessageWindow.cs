using UnityEngine;
using UnityEngine.UI;

public class MessageWindow : MonoBehaviour
{
    public Text text;
    public float maxPerFrameH = 0.5f;
    public float maxPerFrameV = 1.0f;
    private bool isAdding = false;
    private bool isFalling = false;

    // Start is called before the first frame update
    void Start()
    {
        Message.LoadData();
    }

    // Update is called once per frame
    void Update()
    {
        if (isAdding)
        {
            MessageAnimation anim;
            if (!isFalling)
            {
                anim = transform.GetChild(transform.childCount - 1).GetComponent<MessageAnimation>();
                isAdding = !anim.MoveMessage(transform.position + new Vector3(0, 0, 0), maxPerFrameH);
                return;
            }

            for (int i = 0; i < transform.childCount - 1; i++)
            {
                anim = transform.GetChild(i).GetComponent<MessageAnimation>();
                if (anim.IsDeleting()) continue;
                isFalling = !anim.MoveMessage(transform.position + new Vector3(0, -130 * (transform.childCount - i - 1), 0), maxPerFrameV);
            }
        }
        else ShowMessage();
    }

    /**
    * メッセージを追加(表示)する
    */
    private void ShowMessage()
    {
        if (Message.GetCount() > 0)
        {
            isAdding = true;
            isFalling = transform.childCount > 0;
            Message.Data m = Message.Get();
            Text msg = Instantiate(text, transform);
            msg.transform.position = transform.position + new Vector3(-1000, 0, 0);
            msg.color = m.GetColor();
            msg.text = m.str;
        }
    }

}