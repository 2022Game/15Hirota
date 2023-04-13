#ifndef CMODELX_H	//インクルード
#define CMODELX_H

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
class CModelX {
public:
	CModelX();
	//ファイル読み込み
	void Load(char* file);
private:
	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域t
	//単語の取り出し
	char* GetToken();
	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);
};
#endif
