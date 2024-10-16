using System.Runtime.InteropServices.WindowsRuntime;

public class ItemMovement : ObjectMovement
{
    private bool isThrowing = false;

    // ìäù±Ç∑ÇÈà íuÇÃê›íË
    public void SetThrowPosition(EDir d)
    {
        Field field = GetComponentInParent<Field>();
        Pos2D pos = DirUtil.Move(field, grid, d);
        while (!newGrid.Equals(pos))
        {
            newGrid = pos;
            pos = DirUtil.Move(field, newGrid, d);
        }
        pos = DirUtil.Move(field, newGrid, d, false);
        pos = GetFallPosition(pos);
        if (pos != null) newGrid = pos;
    }

    // ìäù±íÜ
    public bool Throwing(EDir d)
    {
        if (!isThrowing)
        {
            SetThrowPosition(d);
            isThrowing = true;
        }
        if (Moving() == EAct.MoveEnd)
        {
            Field field = GetComponentInParent<Field>();
            if (field.GetExistActor(grid.x, grid.z) != null)
                Destroy(gameObject);
            if (!gameObject.Equals(GetComponentInParent<Field>().GetExistItem(grid.x, grid.z)))
                Destroy(gameObject);
            isThrowing = false;
            return true;
        }
        return false;
    }

    // óéâ∫Ç≈Ç´ÇÈèÍèäÇï‘Ç∑
    private Pos2D GetFallPosition(Pos2D pos)
    {
        Field field = GetComponentInParent<Field>();
        if (field.GetExistActor(pos.x, pos.z) != null) return pos;
        if (field.GetExistItem(pos.x, pos.z) == null) return pos;
        foreach (EDir d in System.Enum.GetValues(typeof(EDir)))
        {
            if (d == EDir.Pause) continue;
            Pos2D newP = DirUtil.Move(field, pos, d, false);
            if (newP.Equals(pos)) continue;
            if (field.GetExistActor(newP.x, newP.z) != null) return newP;
            if (field.GetExistItem(newP.x, newP.z) == null) return newP;
        }
        return null;
    }
}