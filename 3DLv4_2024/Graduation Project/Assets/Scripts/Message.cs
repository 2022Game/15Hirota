using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Message
{
    private static Queue<string> texts = new Queue<string>();

    /**
    * 文字列をキューに加える
    */
    public static void Add(string m)
    {
        texts.Enqueue(m);
    }

    /**
    * キューから文字列を取り出す
    */
    public static string Get()
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