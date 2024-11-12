using UnityEngine;
using System.Xml.Linq;
using static ExcelActorData;
using NUnit.Framework;
using System.Collections.Generic;

public class LoadFieldMap : MonoBehaviour
{
    public string mapName;
    public Field field;
    //List<ActorData> actorDatas = new List<ActorData>();
    // �����Ă���Ƃ͎v������X��肪�o���璼��prefabs����f�[�^���擾������j�ɂ���
    private List<ActorData> actorDatas = new List<ActorData>();

    // Start is called before the first frame update
    void Start()
    {
        //Application.targetFrameRate = 100;
        //field.Reset();
        //Array2D mapdata = ReadMapFile(mapName);
        //if (mapdata != null)
        //{
        //    field.Create(mapdata);
        //}
        Load();
    }

    // �}�b�v��ǂݍ���
    public void Load()
    {
        field.Reset();
        Array2D mapdata = ReadMapFile(mapName);
        if (mapdata != null)
        {
            field.Create(mapdata);
        }
    }

    /**
    * TMX�t�@�C������}�b�v�f�[�^���擾����
    */
    private Array2D ReadMapFile(string path)
    {
        try
        {
            XDocument xml = XDocument.Load(path);
            XElement map = xml.Element("map");
            Array2D data = null;
            int w = 0, h = 0;
            foreach (var layer in map.Elements("layer"))
            {
                switch (layer.Attribute("id").Value)
                {
                    case "1":
                        string[] sdata = (layer.Element("data").Value).Split(',');
                        w = int.Parse(layer.Attribute("width").Value);
                        h = int.Parse(layer.Attribute("height").Value);
                        data = new Array2D(w, h);
                        for (int z = 0; z < h; z++)
                        {
                            for (int x = 0; x < w; x++)
                            {
                                data.Set(x, z, int.Parse(sdata[ToMirrorX(x, w) + z * w]) - 1);
                            }
                        }
                        break;
                }
            }
            // �����̏����͖{����DataActor�Ŏ擾�ł��邪�G���[����������̂�
            // ���̂܂܃v���n�u����擾���Ă���
            //ExcelActorData actorDatabase = Resources.Load<ExcelActorData>("Datas/ExcelActorData");
            //ExcelActorData.ActorData[] actorDatas = actorDatabase.Data.ToArray();
            //ExcelItemData itemDatabase = Resources.Load<ExcelItemData>("Datas/ExcelItemData");
            foreach (var objgp in map.Elements("objectgroup"))
            {
                switch (objgp.Attribute("id").Value)
                {
                    case "2":
                        foreach (var obj in objgp.Elements("object"))
                        {
                            int x = int.Parse(obj.Attribute("x").Value);
                            int z = int.Parse(obj.Attribute("y").Value);
                            int pw = int.Parse(obj.Attribute("width").Value);
                            int ph = int.Parse(obj.Attribute("height").Value);
                            string name = obj.Attribute("name").Value;
                            string type = "";
                            foreach (var prop in obj.Element("properties").Elements("property"))
                            {
                                switch (prop.Attribute("name").Value)
                                {
                                    case "Type":
                                        type = prop.Attribute("value").Value;
                                        break;
                                }
                            }
                            field.SetObject(name, type, ToMirrorX(x / pw, w), z / ph);
                        }
                        break;
                }
            }
            return data;
        }
        catch (System.Exception i_exception)
        {
            Debug.LogErrorFormat("{0}", i_exception);
        }
        return null;
    }

    /**
    * Z���ɑ΂��Ĕ��΂̒l��Ԃ�
    */
    private int ToMirrorX(int xgrid, int mapWidth)
    {
        return mapWidth - xgrid - 1;
    }
}