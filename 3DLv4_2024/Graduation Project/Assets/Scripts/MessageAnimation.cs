using UnityEngine;

public class MessageAnimation : MonoBehaviour
{
    public float waitTime = 8.0f;
    public float maxPerFrameD = 1.0f;

    private bool isMoving = false;
    private bool isDeleting = false;
    private Vector3 prevPos = Vector3.zero; // 初期化
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
    * 補完で計算してアニメーションさせる
    */
    public bool MoveMessage(Vector3 p2, float maxPerFrame)
    {
        // 移動中かどうかのフラグ
        isMoving = !isDeleting;

        // 各フレームでカウントを進める
        frame += 1;

        // c: 必要なフレーム数の計算
        float c = maxPerFrame / Time.deltaTime;

        // 移動の進行割合 (0.0～1.0) を計算
        float t = frame / c;

        // Mathf.SmoothStepで補間して滑らかに移動
        t = Mathf.SmoothStep(0.0f, 1.0f, t);

        // 位置の更新（線形補間の代わりにSmoothStepを利用）
        transform.position = Vector3.Lerp(prevPos, p2, t);

        // 移動が完了した場合
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
    * 削除アニメーション中ではないか
    */
    public bool IsDeleting() => isDeleting;

    /**
    * 削除アニメーション
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
