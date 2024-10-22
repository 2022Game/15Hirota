using UnityEngine;
using UnityEditor;
using UnityEditorInternal;

[CustomEditor(typeof(Inventory))]
[CanEditMultipleObjects]
public class InventoryEditor : Editor
{
    private ReorderableList list;
    private Inventory inventory;
    private EItem id;

    void OnEnable()
    {
        inventory = (Inventory)target;
        list = new ReorderableList(
            inventory.items,
            typeof(Item)
        );
        list.drawElementCallback += DrawElement;
        list.onCanAddCallback += CanAdd;
        list.drawHeaderCallback += DrawHeader;
    }

    public override void OnInspectorGUI()
    {
        serializedObject.Update();
        inventory.itemNumMax = Mathf.Max(0, EditorGUILayout.IntField("�����\��", inventory.itemNumMax));
        list.DoLayoutList();
        id = (EItem)EditorGUILayout.EnumPopup("�A�C�e��ID", id);
        serializedObject.ApplyModifiedProperties();
    }

    private void DrawElement(Rect rect, int index, bool isActive, bool isFocused)
    {
        if (isFocused)
        {
            ExcelItemData database = Resources.Load<ExcelItemData>("Datas/ExcelItemData");
            Item item;
            if ((int)id > 1000) item = database.Goods.Find(n => n.id == id);
            else item = database.Equipments.Find(n => n.id == id);
            if (item != null)
            {
                SetItem(item, ref item);
                inventory.items[index] = item;
            }
        }
        EditorGUI.LabelField(rect, inventory.items[index].name);
    }

    private bool CanAdd(ReorderableList list)
    {
        return inventory.items.Count < inventory.itemNumMax;
    }

    private void DrawHeader(Rect rect)
    {
        EditorGUI.LabelField(rect, "�����A�C�e��");
    }

    private void SetItem(Item it, ref Item parameter)
    {
        parameter = it.Get();
    }
}