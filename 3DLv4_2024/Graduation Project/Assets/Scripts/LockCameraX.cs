using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using UnityEngine;

[ExecuteInEditMode]
[SaveDuringPlay]
[AddComponentMenu("")]
public class LockCameraX : CinemachineExtension
{
    [Tooltip("カメラのX座標を固定する値")]
    public float m_XPosition = 10;

    protected override void PostPipelineStageCallback(
        CinemachineVirtualCameraBase vcam,
        CinemachineCore.Stage stage,
        ref CameraState state,
        float deltaTime)
    {
        if (stage == CinemachineCore.Stage.Body)
        {
            var pos = state.RawPosition;
            pos.x = m_XPosition;
            state.RawPosition = pos;
        }
    }
}
