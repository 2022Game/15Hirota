using UnityEngine;

public static class DirUtil
{
    // 入力されたキーに対応する向きを返す
    public static EDir KeyToDir()
    {
        // GetKey : 押している間ずっと関数が呼び出される
        if (!Input.anyKey)
        {
            return EDir.Pause;
        }

        // ここで具体的なキーに応じた方向処理を追加
        // 例:
        if (Input.GetKey(KeyCode.W))
        {
            return EDir.Up;
        }
        else if (Input.GetKey(KeyCode.S))
        {
            return EDir.Down;
        }
        else if (Input.GetKey(KeyCode.A))
        {
            return EDir.Left;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            return EDir.Right;
        }

        return EDir.Pause; // デフォルト
    }

    // 引数で与えられた向きに対応する回転のベクトルを返す
    public static Quaternion DirToRotation(EDir d)
    {
        Quaternion r = Quaternion.Euler(0, 0, 0);
        switch (d)
        {
            case EDir.Up:
                r = Quaternion.Euler(0, 0, 0); break;
            case EDir.Left:
                r = Quaternion.Euler(0, 270, 0); break;
            case EDir.Down:
                r = Quaternion.Euler(0, 180, 0); break;
            case EDir.Right:
                r = Quaternion.Euler(0, 90, 0); break;
        }
        return r;
    }

    // ランダムな向きを返す
    public static EDir RandomDirection()
    {
        int dirnum = UnityEngine.Random.Range(0, 4);
        switch (dirnum)
        {
            case 0:
                return EDir.Up;
            case 1:
                return EDir.Left;
            case 2:
                return EDir.Down;
            case 3:
                return EDir.Right;
        }
        return EDir.Down;
    }

    // 引数で与えられた回転のベクトルに対応する向きを返す
    public static EDir RotationToDir(Quaternion r)
    {
        float y = r.eulerAngles.y;

        if (y < 45)
        {
            return EDir.Up;
        }
        else if (y < 135)
        {
            return EDir.Right;
        }
        else if (y < 225)
        {
            return EDir.Down;
        }
        else if (y < 315)
        {
            return EDir.Left;
        }

        return EDir.Up; // デフォルトの向きを返す
    }

    // 現在の座標(position)と移動したい方向(d)を渡すと
    // 移動先の座標を取得
    public static Pos2D GetNewGrid(Pos2D position, EDir d)
    {
        Pos2D newP = new Pos2D();
        newP.x = position.x;
        newP.z = position.z;
        switch (d)
        {
            case EDir.Up:
                newP.z += 1; break;
            case EDir.Left:
                newP.x -= 1; break;
            case EDir.Down:
                newP.z -= 1; break;
            case EDir.Right:
                newP.x += 1; break;
        }
        return newP;
    }

    // マップのデータ(map)と現在の座標(position)と移動したい方向(d)を渡すと
    // (もし移動できるならば)移動先の座標を取得
    public static Pos2D Move(Field field, Pos2D position, EDir d)
    {
        Pos2D newP = GetNewGrid(position, d);
        if (field.IsCollide(newP.x, newP.z) || field.GetExistActor(newP.x, newP.z) != null)
            return position;
        return newP;
    }
}