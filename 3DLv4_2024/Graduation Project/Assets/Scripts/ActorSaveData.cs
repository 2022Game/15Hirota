[System.Serializable]
public class ActorSaveData
{
    public Pos2D grid;
    public EDir direction;
    public Params parameter;
    public InventorySaveData inventory;
    public ECondition[] conditions;
    public int[] clearConditionRates;
}