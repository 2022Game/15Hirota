using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Message
{
    private static Queue<Data> texts = new Queue<Data>();
    private static List<Data> data;

    [System.Serializable]
    public class Data
    { 
        public enum EColor
        {
            White,
            Yellow,
            Orange,
            Cyan
        };
        public int id;
        public string str;
        public EColor color;

        // EColorの値をColorに変換して返す
        public Color GetColor()
        {
            Color newColor;
            switch (color)
            {
                case EColor.White:
                    return Color.white;
                case EColor.Yellow:
                    return Color.yellow;
                case EColor.Orange:
                    ColorUtility.TryParseHtmlString("#FFA500", out newColor);
                    return newColor;
                case EColor.Cyan:
                    return Color.cyan;
            }
            return Color.cyan;
        }
    }

    // メッセージデータを読み込む
    public static void LoadData()
    {
        data = Resources.Load<ExcelMessageData>("Datas/ExcelMessageData").Data;
    }

    // IDからメッセージデータを読みだしたキューに加える
    public static void Add(int id, params string[] vals)
    {
        if (id < 1 && id > data.Count) return;
        Data textData = new Data();
        Data baseData = data.Find(n => n.id == id);
        textData.id = id;
        textData.str = baseData.str;
        for (int i = 0; i < vals.Length; i++)
        {
            if (!textData.str.Contains("<val" + (i + 1) + ">")) break;
            textData.str = textData.str.Replace("<val" + (i + 1) + ">", vals[i]);
        }
        textData.color = baseData.color;
        texts.Enqueue(textData);
    }

    /**
    * 文字列をキューに加える
    */
    public static void Add(string m, Data.EColor color = Data.EColor.White)
    {
        Data textData = new Data();
        textData.id = 0;
        textData.str = m;
        textData.color = color;
        texts.Enqueue(textData);
    }

    /**
    * キューから文字列を取り出す
    */
    public static Data Get()
    {
        if (texts.Count > 0)
        {
            return texts.Dequeue();
        }
        return null;
    }

    /**
     * キューに格納されている文字列の数を返す
     */
    public static int GetCount()
    {
        return texts.Count;
    }
}