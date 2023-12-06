#pragma once
class CResourceManager;

// リソース管理するクラスのベースクラス
class CResource
{
	friend CResourceManager;

public:
	// 参照カウント加算
	void Referenced();
	// リソース解放
	virtual void Release();

protected:
	// コンストラクタ
	CResource();
	// デストラクタ
	virtual ~CResource();
	// リソース読み込み
	virtual bool Load(std::string path) = 0;

	int mReferenceCount;	// 参照カウント
};