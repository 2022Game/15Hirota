// 行動状態
// 以下の記事を参考
// https://qiita.com/2dgames_jp/items/1730e7c4822091c3c320#actor%E3%81%AB%E5%BF%85%E8%A6%81%E3%81%AA%E8%A1%8C%E5%8B%95%E7%8A%B6%E6%85%8B
public enum EAct
{
    KeyInput,   // キー入力待ち。もしくは待機中
    
    // アクション
    ActBegin,   // 開始
    Act,        // 実行中
    ActEnd,     // 終了

    // 移動
    MoveBegin,  // 開始
    Move,       // 移動中
    MoveEnd,    // 完了

    TurnEnd,    // ターン終了
}