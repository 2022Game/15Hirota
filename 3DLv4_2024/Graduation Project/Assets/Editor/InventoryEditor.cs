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
        inventory.itemNumMax = Mathf.Max(0, EditorGUILayout.IntField("所持可能数", inventory.itemNumMax));
        list.DoLayoutList();
        id = (EItem)EditorGUILayout.EnumPopup("アイテムID", id);
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
        EditorGUI.LabelField(rect, "所持アイテム");
    }

    private void SetItem(Item it, ref Item parameter)
    {
        Item p = new Item();
        p.id = it.id;
        p.name = it.name;
        p.type = it.type;
        p.sprite = it.sprite;
        p.prefab = it.prefab;
        p.atk = it.atk;
        p.def = it.def;
        p.hp = it.hp;
        p.food = it.food;
        p.dmg = it.dmg;
        p.detail = it.detail;
        parameter = p;
    }
}