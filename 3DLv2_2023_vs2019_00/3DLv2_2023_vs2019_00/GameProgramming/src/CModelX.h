#ifndef CMODELX_H	//インクルード
#define CMODELX_H

#include <vector>		//ベクトルクラスのインクルード(動的配列)
#include "CMatrix.h"	//マトリクスクラスのインクルード

//宣言
class CModelX;
class CModelXFrame;
class CMesh;
class CVector;
class CMaterial;	//マテリアル宣言
class CSkinWeights;	//スキンウェイトクラス
class CAnimationSet;	//アニメーションセットクラス
class CAnimation;		//アニメーションクラス
class CAnimationKey;	//アニメーションキークラス

#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))

/*
IsDelimiter(c)
cが\t \r \n スペースなどの空白文字
または,;などの文字であれば
区切り文字としてtrueを返す
*/

#define MODEL_FILE "res\\sample.blend.x"	//入力ファイル名

//了以域開放をマクロ化
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a;a = nullptr;}
/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで認識する
*/



//CModelXFrameの定義
class CModelXFrame {
	friend CModelX;
	friend CAnimation;
public:
	//コンストラクタ
	CModelXFrame(CModelX* model);
	//デストラクタ
	~CModelXFrame();
	void Render();
	bool Index();
private:
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;			//変換行列
	char* mpName;						//フレーム名前
	int mIndex;							//フレーム番号
	CMesh* mpMesh;						//Meshデータ
};

class CModelX {
	friend CModelXFrame;
	friend CSkinWeights;
	friend CAnimationSet;
	friend CAnimation;
public:
	~CModelX();
	//ノードの読み飛ばし
	void SkipNode();
	CModelX();
	//ファイル読み込み
	void Load(char* file);
	void Render();
	//単語の取り出し
	char* GetToken();
	char* Token();
	bool EOT();	//トークンが無くなったらture
	//フレーム名に該当するフレームのアドレスを返す
	CModelXFrame* FindFrame(char* name);
private:
	std::vector<CModelXFrame*> mFrame;	//フレームの配列
	std::vector<CAnimationSet*> mAnimationSet;	//アニメーションセットの配列
	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域t
	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);
};

//CMeshクラスの定義を追加する
class CMesh {
	friend CModelX;
	friend CModelXFrame;
public:
	//コンストラクタ
	CMesh();
	//デストラクタ
	~CMesh();
	//読み込み処理
	void Init(CModelX* model);
	void Render();
private:
	int mVertexNum;		//頂点数
	CVector* mpVertex;	//頂点データ
	int mFaceNum;		//面数
	int* mpVertexIndex;	//面を構成する頂点インデックス
	int mNormalNum;		//法線
	CVector* mpNormal;	//法線ベクトル
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;	//マテリアル番号数(面数)
	int* mpMaterialIndex;	//マテリアル番号

	std::vector<CMaterial*> mMaterial;	//マテリアルデータ
	std::vector<CSkinWeights*>mSkinWeights;	//スキンウェイト
};

/*
CSkinWeights
スキンウェイトクラス
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights();
	const int& FrameIndex();
	const CMatrix& Offset();
private:
	char* mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mIndexNum;		//頂点番号数
	int* mpIndex;		//頂点番号配列
	float* mpWeight;	//頂点ウェイト配列
	CMatrix mOffset;	//オフセットマトリックス
};

/*
CAnimationSet
アニメーションセット
*/
class CAnimationSet {
public:
	CAnimationSet(CModelX* model);
	~CAnimationSet();
private:
	//アニメーションセット名
	char* mpName;
	std::vector<CAnimation*> mAnimation;
};

/*
CAnimation
アニメーションクラス
*/
class CAnimation {
	friend CAnimationSet;
public:
	CAnimation(CModelX* model);
	~CAnimation();
private:
	char *mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mKeyNum;	//キー数(時間数)
	CAnimationKey* mpKey;	//キーの配列
};

/*
CAnimationKey
アニメーションキークラス
*/
class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
private:
	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
};

#endif