using System.Collections.Generic;
using UnityEngine;

[ExcelAsset]
public class ExcelAppearData : ScriptableObject
{
    public List<EnemyAppearData> EnemyAppear;
    public List<ItemAppearData> ItemAppear;

    [System.Serializable]
    public class EnemyAppearData
    {
        public int floor;
        public EActor id1;
        public int lvmin1;
        public int lvmax1;
        public int rate1;
    }

    [System.Serializable]
    public class ItemAppearData
    {
        public EItem id;
        public int start;
        public int end;
        public int rate;
        public bool shoponly;
    }
}