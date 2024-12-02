using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using UnityEngine;

[ExcelAsset]
public class ExcelActorData : ScriptableObject
{
	//public List<EntityType> Data; // Replace 'EntityType' to an actual type that is serializable.
	//public List<EntityType> Player; // Replace 'EntityType' to an actual type that is serializable.
	//public List<EntityType> Enemy1; // Replace 'EntityType' to an actual type that is serializable.
	public List<ActorData> Data;
	public List<Params> Player;
	public List<Params> Enemy1;

    // パラメーターを返す
    public List<Params> GetParamsData(string status)
    {
        Type type = GetType();
        FieldInfo field = type.GetField(status);
        return (List<Params>)field.GetValue(this);
    }

    [System.Serializable]
    public class ActorData
    {
        public EActor id;
        public string name;
        public string prefab;
        public string status;
    }
}
