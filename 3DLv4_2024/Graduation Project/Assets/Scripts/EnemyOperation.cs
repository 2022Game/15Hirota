using System.Collections;
using System.Linq;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices.WindowsRuntime;

public class EnemyOperation : ActorOperation
{
    public ActorMovement target;

    private class Node
    {
        public Pos2D grid;
        public EDir direction;
        public int actualCost = 0;
        public int estimatedCost = 0;
        public Node parentNode = null;


        // A*アルゴリズムにて算出した方向を返す
        public EDir GetAstarNextDirection(Pos2D pos, Pos2D target, Field field)
        {
            grid = new Pos2D();
            grid.x = pos.x;
            grid.z = pos.z;
            Array2D nodeMap = field.GetMapData();
            nodeMap.Set(grid.x, grid.z, 1);
            Node node = Astar(target, field, new List<Node>(), nodeMap);
            if (node.parentNode == null) return EDir.Pause;
            while (node.parentNode.parentNode != null) node = node.parentNode;
            return node.direction;
        }

        // 再帰的にA*アルゴリズムを計算し、結果を返す
        private Node Astar(Pos2D target, Field field, List<Node> openList, Array2D nodeMap)
        {
            foreach (EDir d in System.Enum.GetValues(typeof(EDir)))
            {
                if (d == EDir.Pause) continue;
                Pos2D newGrid = DirUtil.GetNewGrid(grid, d);
                if (target.x == newGrid.x && target.z == newGrid.z) return this;
                if (nodeMap.Get(newGrid.x, newGrid.z) > 0) continue;
                Node node = new Node();
                node.grid = newGrid;
                node.direction = d;
                node.parentNode = this;
                node.actualCost = node.parentNode.actualCost + 1;
                node.actualCost += field.GetExistActor(node.grid.x, node.grid.z) == null ? 0 : field.enemies.transform.childCount * 2;
                node.estimatedCost = Mathf.Abs(target.x - node.grid.x) + Mathf.Abs(target.z - node.grid.z);
                openList.Add(node);
                nodeMap.Set(node.grid.x, node.grid.z, 1);
            }
            if (openList.Count < 1) return this;
            openList = openList.OrderBy(n => (n.actualCost + n.estimatedCost)).ThenBy(n => n.actualCost).ToList();
            Node baseNode = openList[0];
            openList.RemoveAt(0);
            return baseNode.Astar(target, field, openList, nodeMap);
        }
    }

    // 次に行う予定の行動状態を返す
    public override EAct Operate(ActorMovement actorMovement, ActorParamsController actorParam)
    {
        if (actorParam.CantAction()) return EAct.TurnEnd;
        if (actorParam.IsConfusion()) return ConfusionActionAI(actorMovement);
        return AstarActionAI(actorMovement);
    }

    // A*アルゴリズムを用いた行動AI
    private EAct AstarActionAI(ActorMovement actorMovement)
    {
        EDir d = GetPlayerDirection(actorMovement);
        if (d == EDir.Pause)
        {
            d = AstarMovementAI(actorMovement);
            actorMovement.SetDirection(d);
            if (actorMovement.IsMoveBegin()) return EAct.MoveBegin;
            return EAct.KeyInput;
        }
        actorMovement.SetDirection(d);
        return EAct.ActBegin;
    }


    // A*アルゴリズム
    private EDir AstarMovementAI(ActorMovement actorMovement)
    {
        Node node = new Node();
        return node.GetAstarNextDirection(actorMovement.grid, target.newGrid, GetComponentInParent<Field>());
    }

    // 周囲のプレイヤーがいる方向を返す
    private EDir GetPlayerDirection(ActorMovement actorMovement)
    {
        Field field = GetComponentInParent<Field>();
        Pos2D grid;
        foreach (EDir d in System.Enum.GetValues(typeof(EDir)))
        {
            if (d == EDir.Pause) continue;
            grid = DirUtil.GetNewGrid(actorMovement.grid, d);
            GameObject actor = field.GetExistActor(grid.x, grid.z);
            if (actor == null) continue;
            EActor id = actor.GetComponent<ActorParamsController>().parameter.id;
            if (id == EActor.PLAYER) return d;
        }
        return EDir.Pause;
    }

    // 混乱状態の行動AI
    private EAct ConfusionActionAI(ActorMovement actorMovement)
    {
        EDir d = GetPlayerDirection(actorMovement);
        actorMovement.SetDirection(DirUtil.RandomDirection());
        if (d == EDir.Pause && actorMovement.IsMoveBegin())
            return EAct.MoveBegin;
        return EAct.ActBegin;
    }
}
