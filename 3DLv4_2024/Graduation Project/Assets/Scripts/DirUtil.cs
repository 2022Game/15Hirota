using UnityEngine;

public static class DirUtil
{
    // ���͂��ꂽ�L�[�ɑΉ����������Ԃ�
    public static EDir KeyToDir()
    {
        // GetKey : �����Ă���Ԃ����Ɗ֐����Ăяo�����
        if (!Input.anyKey)
        {
            return EDir.Pause;
        }

        // �����ŋ�̓I�ȃL�[�ɉ���������������ǉ�
        // ��:
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

        return EDir.Pause; // �f�t�H���g
    }

    // �����ŗ^����ꂽ�����ɑΉ������]�̃x�N�g����Ԃ�
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

    // �����_���Ȍ�����Ԃ�
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

    // �����ŗ^����ꂽ��]�̃x�N�g���ɑΉ����������Ԃ�
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

        return EDir.Up; // �f�t�H���g�̌�����Ԃ�
    }

    // ���݂̍��W(position)�ƈړ�����������(d)��n����
    // �ړ���̍��W���擾
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

    // �}�b�v�̃f�[�^(map)�ƌ��݂̍��W(position)�ƈړ�����������(d)��n����
    // (�����ړ��ł���Ȃ��)�ړ���̍��W���擾
    public static Pos2D Move(Field field, Pos2D position, EDir d)
    {
        Pos2D newP = GetNewGrid(position, d);
        if (field.IsCollide(newP.x, newP.z) || field.GetExistActor(newP.x, newP.z) != null)
            return position;
        return newP;
    }
}