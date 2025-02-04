#include "CTaskManager.h"
#include "CCamera.h"
#include "CDebugCamera.h"
#include "CBillBoard.h"
#include "CShadowMap.h"

//#define TEXWIDTH  1192  //テクスチャ幅
//#define TEXHEIGHT  1144  //テクスチャ高さ
#define TEXWIDTH  8192  //テクスチャ幅
#define TEXHEIGHT  6144  //テクスチャ高さ

//タスクマネージャのインスタンス
CTaskManager* CTaskManager::mpInstance = nullptr;

CShadowMap mShadowMap;

// インスタンスを取得
CTaskManager* CTaskManager::Instance()
{
	// インスタンスが無ければ、新しく生成する
	if (mpInstance == nullptr)
	{
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}

// インスタンスの破棄
void CTaskManager::ClearInstance()
{
	delete mpInstance;
	mpInstance = nullptr;
}

// 描画用関数
void RenderShadow()
{
	CTaskManager::Instance()->Render3D();
}

// コンストラクタ
CTaskManager::CTaskManager()
	: mPauseBit(0)

{
	// シャドウマップ
	//float shadowColor[] = { 0.3f, 0.3f, 0.3f, 0.15f };  //影の色
	//float lightPos[] = { 600.0f, 2000, 0.0f };  //光源の位置 :2000.0f
	//mShadowMap.Init(TEXWIDTH, TEXHEIGHT, RenderShadow,
	//	shadowColor, lightPos);
}

// デストラクタ
CTaskManager::~CTaskManager()
{
	for (int i = 0; i < 2; i++)
	{
		std::list<CTask*>& list = i == 0 ? m3dTasks : m2dTasks;
		// 先頭から最後まで繰り返し
		auto itr = list.begin();
		auto end = list.end();
		while (itr != end)
		{
			// 削除タスクを記憶しておく
			CTask* del = *itr;
			itr = list.erase(itr);
			delete del;
		}
	}
	m3dTasks.clear();
	m2dTasks.clear();
}

// 指定したタスクをリストに追加
void CTaskManager::Add(CTask* task, bool isSort)
{
	if (!task->mAddTaskList) return;

	// 追加するタスクが3Dタスクかどうか
	bool is3dTask = task->mPriority < ETaskPriority::Start2d;
	// 3Dタスクか2Dタスクかで追加するリスト切り替える
	std::list<CTask*>& list = is3dTask ? m3dTasks : m2dTasks;

	// リストの先頭から順番に調べる
	auto itr = list.begin();
	auto end = list.end();
	while (itr != end)
	{
		CTask* current = *itr;
		// 追加するタスクと検索中のタスクの優先度が同じ場合
		if (task->mPriority == current->mPriority)
		{
			// 並び替え順の番号が小さい順に並べる
			if (task->mSortOrder < current->mSortOrder)
			{
				list.insert(itr, task);
				return;
			}
		}
		// 追加するタスクの優先度が
		// 検索中のタスクの優先度より小さい場合は、
		// 検索中のタスクの前に挿入
		else if (task->mPriority < current->mPriority)
		{
			list.insert(itr, task);
			return;
		}
		// 次へ
		itr++;
	}
	// ここまで調べてタスクを差し込む場所がなかった場合は、
	// リストの最後尾に追加
	list.push_back(task);
}

// 指定したタスクをリストから取り除く
void CTaskManager::Remove(CTask* task, bool isSort)
{
	if (!task->mAddTaskList) return;

	// 取り除くタスクが3Dタスクかどうか
	bool is3dTask = task->mPriority < ETaskPriority::Start2d;
	// 3Dタスクか2Dタスクかでリストを切り替える
	std::list<CTask*>& list = is3dTask ? m3dTasks : m2dTasks;

	// リスト内に取り除くタスクが存在するかどうか
	auto find = std::find(list.begin(), list.end(), task);
	if (find == list.end()) return;

	// 存在した場合は、リストからタスクを取り除く
	list.erase(find);
}

// 削除フラグが立っているタスクを全て削除
void CTaskManager::Delete()
{
	// 3Dタスクリスト内を精査
	Delete(m3dTasks);
	// 2Dタスクリスト内を精査
	Delete(m2dTasks);
}

// 指定されたリスト内で
// 削除フラグが立っているタスクを全て削除
void CTaskManager::Delete(std::list<CTask*>&list)
{
	// 先頭から最後まで繰り返し
	auto itr = list.begin();
	auto end = list.end();
	while (itr != end)
	{
		// 削除タスクを記憶しておく
		CTask* del = *itr;
		// 削除フラグが立っていたら、削除して次へ
		if (del->IsKill())
		{
			itr = list.erase(itr);
			delete del;
		}
		// 削除フラグが立っていなければ、そのまま次へ
		else
		{
			itr++;
		}
	}
}

// 指定したシーンに所属するタスクを全て削除
void CTaskManager::DeleteInScene(EScene scene)
{
	// 3Dタスクリストを精査
	for (CTask* task : m3dTasks)
	{
		// 所属するシーンが一致したら、
		// 削除フラグを立てる
		if (task->GetSceneType() == scene)
		{
			task->Kill();
		}
	}
	// 2Dタスクリストを精査
	for (CTask* task : m2dTasks)
	{
		// 所属するシーンが一致したら、
		// 削除フラグを立てる
		if (task->GetSceneType() == scene)
		{
			task->Kill();
		}
	}
}

// タスクの並び替え
void CTaskManager::Sort()
{
	// タスクリストに追加しなおすタスクのリスト
	std::list<CTask*> addTasks;

	// 3Dタスクリスト内で並び替えるタスクを検索
	auto itr = m3dTasks.begin();
	auto end = m3dTasks.end();
	while (itr != end)
	{
		CTask* task = *itr;
		itr++;

		// 並び替えフラグが立っていたら、
		if (task->mIsSort)
		{
			Remove(task, true);
			task->mIsSort = false;
			addTasks.push_back(task);
		}
	}
	// 2Dタスクリスト内で並び替えるタスクを検索
	itr = m2dTasks.begin();
	end = m2dTasks.end();
	while (itr != end)
	{
		CTask* task = *itr;
		itr++;

		// 並び替えフラグが立っていたら、
		if (task->mIsSort)
		{
			Remove(task, true);
			task->mIsSort = false;
			addTasks.push_back(task);
		}
	}

	// タスクリストから取り除いたタスクを、
	// タスクリストに追加しなおす
	for (CTask* task : addTasks)
	{
		Add(task, true);
	}
}

// 3Dタスクのリストを取得
const std::list<CTask*>& CTaskManager::Get3dTasks() const
{
	return m3dTasks;
}

// 2Dタスクのリストを取得
const std::list<CTask*>& CTaskManager::Get2dTasks() const
{
	return m2dTasks;
}

// ポーズする
void CTaskManager::Pause(int pauseBit)
{
	mPauseBit |= pauseBit;
}

// ポーズを解除する
void CTaskManager::UnPause(int pauseBit)
{
	mPauseBit &= ~pauseBit;
}

// ポーズ中かどうか
bool CTaskManager::IsPaused(int pauseBit) const
{
	if (pauseBit == 0) pauseBit = ~pauseBit;
	return (mPauseBit & pauseBit) != 0;
}

// 更新するかどうか
bool CTaskManager::IsUpdate(CTask* task) const
{
	if (task == nullptr) return false;

	// ポーズ中のタスクならば、更新しない
	ETaskPauseType pause = task->GetPauseType();
	if (pause != ETaskPauseType::eNone && (mPauseBit & (int)pause) != 0) return false;

	// 有効フラグがオフならば、更新しない
	if (!task->IsEnable()) return false;

	return true;
}

// 更新
void CTaskManager::Update()
{
	// タスクの更新前にタスクの並び替えを行う
	Sort();

	// 3Dタスクリスト内のタスクを順番に更新
	for (CTask* task : m3dTasks)
	{
		// 更新するタスクであれば、タスクを更新
		if (IsUpdate(task))
		{
			task->Update();
		}
	}
	// 2Dタスクリスト内のタスクを順番に更新
	for (CTask* task : m2dTasks)
	{
		// 更新するタスクであれば、タスクを更新
		if (IsUpdate(task))
		{
			task->Update();
		}
	}
}

// 描画
void CTaskManager::Render()
{
	// 現在のカメラが存在すれば
	CCamera* current = CCamera::CurrentCamera();
	if (current != nullptr)
	{
		// 現在のカメラを反映
		current->Apply();
		mShadowMap.Render();

		// 3D関連の描画
		for (CTask* task : m3dTasks)
		{
			// 表示フラグがオンならば、
			if (task->IsShow())
			{
				// タスクを描画
				task->Render();
			}
		}
	}

	// 2D描画用のカメラに切り替える
	CCamera::Start2DCamera();
	// 2D関連の描画
	for (CTask* task : m2dTasks)
	{
		// 表示フラグがオンならば、
		if (task->IsShow())
		{
			// タスクを描画
			task->Render();
		}
	}
	// 3D描画用のカメラへ戻す
	CCamera::End2DCamera();
}

void CTaskManager::Render3D()
{
	// 3D関連の描画
	for (CTask* task : m3dTasks)
	{
		// 表示フラグがオンならば
		if (task->IsShow())
		{
			// タスクを描画
			task->Render();
		}
	}
}