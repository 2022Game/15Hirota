using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExcelAsset]
public class ExcelMessageData : ScriptableObject
{
    //public List<EntityType> Data; // Replace 'EntityType' to an actual type that is serializable.
    public List<Message.Data> Data;
}