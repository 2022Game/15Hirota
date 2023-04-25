#ifndef CMODELX_H	//インクルード
#define CMODELX_H

#include <vector>		//ベクトルクラスのインクルード(動的配列)
#include "CMatrix.h"	//マトリクスクラスのインクルード

//宣言
class CModelX;
class CModelXFrame;
class CMesh;
class CVector;

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
public:
	//コンストラクタ
	CModelXFrame(CModelX* model);
	//デストラクタ
	~CModelXFrame();
private:
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;			//変換行列
	char* mpName;						//フレーム名前
	int mIndex;							//フレーム番号
	CMesh* mpMesh;						//Meshデータ
};

class CModelX {
	friend CModelXFrame;
public:
	~CModelX();
	//ノードの読み飛ばし
	void SkipNode();
	CModelX();
	//ファイル読み込み
	void Load(char* file);
	//単語の取り出し
	char* GetToken();
	char* Token();
private:
	std::vector<CModelXFrame*> mFrame;	//フレームの配列	
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
private:
	int mVertexNum;		//頂点数
	CVector* mpVertex;	//頂点データ
	int mFaceNum;		//面数
	int* mpVertexIndex;	//面を構成する頂点インデックス
	
};
#endif
