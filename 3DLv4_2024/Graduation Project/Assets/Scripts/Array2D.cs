[System.Serializable]
public class Array2D
{
    public int width;
    public int height;
    [UnityEngine.SerializeField] private int[] data;
    //private int[,] data;

    public Array2D(int w, int h)
    {
        width = w; height = h;
        data = new int[width*height];
    }

    // X/Z座標にある値を取得する
    public int Get(int x, int z)
    {
        if (x >= 0 && z >= 0 && x < width && z < height)
        {
            return data[x + z * width];
        }
        return -1;
    }

    // X/Z座標に値(v)を設定する
    public int Set(int x, int z, int v)
    {
        if (x >= 0 && z >= 0 && x < width && z < height)
        {
            data[x + z * width] = v;
            return v;
        }
        return -1;
    }
}