public class ItemMovement : ObjectMovement
{
    private bool IsThrowing = false;

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
    }

    // ìäù±íÜ
    public bool Throwing(EDir d)
    {
        if (!IsThrowing)
        {
            SetThrowPosition(d);
            IsThrowing = true;
        }
        if (Moving() == EAct.MoveEnd)
        {
            IsThrowing = false;
            return true;
        }
        return false;
    }
}