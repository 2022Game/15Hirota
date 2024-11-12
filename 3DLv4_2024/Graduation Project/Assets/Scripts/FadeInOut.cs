using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeInOut : MonoBehaviour
{
    public float maxPerFrame = 0.0005f;
    private float complementFrame;
    private bool isFadeOut = false;
    private Image image;
    public Text text;

    // Start is called before the first frame update
    void Start()
    {
        complementFrame = maxPerFrame / Time.deltaTime;
        image = GetComponent<Image>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!isFadeOut && image.color.a <= 0) return;
        if (isFadeOut && image.color.a >= 1.0f) return;
        if (isFadeOut) FadeOut();
        if (!isFadeOut) FadeIn();
    }

    // フェードさせる
    public bool Fade(bool isFadeOut, string str = "")
    {
        if (!isFadeOut && image.color.a <= 0) return true;
        if (isFadeOut && image.color.a >= 1.0f) return true;
        if (this.isFadeOut != isFadeOut)
        {
            this.isFadeOut = isFadeOut;
            text.text = str;
        }
        return false;
    }

    // フェードアウト
    private void FadeOut()
    {
        float alpha = image.color.a + complementFrame;
        if (alpha > 1.0f) alpha = 1.0f;
        image.color = new Color(image.color.r, image.color.g, image.color.b, alpha);
    }

    // フェードイン
    private void FadeIn()
    {
        float alpha = image.color.a - complementFrame;
        if (alpha < 0) alpha = 0;
        image.color = new Color(image.color.r, image.color.g, image.color.b, alpha);
    }
}
