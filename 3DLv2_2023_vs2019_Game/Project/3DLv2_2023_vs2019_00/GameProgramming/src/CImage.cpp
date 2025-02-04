#include "CImage.h"
#include "main.h"

//コンストラクタ
CImage::CImage()
	: mpTexture(nullptr)
	, mPosition(0.0f, 0.0f)
	, mSize(128.0f, 128.0f)
	, mUV(0.0f, 0.0f, 1.0f, 1.0f)
	, mColor(1.0f, 1.0f, 1.0f, 1.0f)
{
}

//コンストラクタ（テクスチャ指定版）
CImage::CImage(const char* path)
	: CImage()
{
	Load(path);
}

//デストラクタ
CImage::~CImage()
{
	//テクスチャを読み込んでいたら破棄
	if (mpTexture != nullptr)
	{
		delete mpTexture;
	}
}

//テクスチャの読み込み
void CImage::Load(const char* path)
{
	mpTexture = new CTexture();
	bool success = mpTexture->Load(path);
	//読み込み成功
	if (success)
	{
		//表示サイズをテクスチャのサイズで初期化
		const STgamHeader& header = mpTexture->Header();
		SetSize(header.width, header.height);
	}
	//読み込み失敗
	else
	{
		//テクスチャを破棄
		delete mpTexture;
		mpTexture = nullptr;
	}
}

//表示座標を設定（CVector2版）
void CImage::SetPos(const CVector2& pos)
{
	mPosition = pos;
}

//表示座標を設定
void CImage::SetPos(const float& x, const float& y)
{
	SetPos(CVector2(x, y));
}

//表示座標を取得
const CVector2& CImage::GetPos() const
{
	return mPosition;
}

//表示サイズを設定（CVector2版）
void CImage::SetSize(const CVector2& size)
{
	mSize = size;
}

//表示サイズを設定
void CImage::SetSize(const float& x, const float& y)
{
	SetSize(CVector2(x, y));
}

//表示サイズを取得
const CVector2& CImage::GetSize() const
{
	return mSize;
}

//表示する範囲を設定（CVector4版）
void CImage::SetUV(const CVector4& uv)
{
	mUV = uv;
}

//表示する範囲を設定
void CImage::SetUV(const float& left, const float& top, const float& right, const float& bottom)
{
	SetUV(CVector4(left, top, right, bottom));
}

//表示する範囲を取得
const CVector4& CImage::GetUV() const
{
	return mUV;
}

//表示カラーを設定（CVector4版）
void CImage::SetColor(const CVector4& color)
{
	mColor = color;
}

//表示カラーを設定（CVector版）
void CImage::SetColor(const CVector& color)
{
	mColor = color;
}

//表示カラーを設定（アルファ値有り版）
void CImage::SetColor(const float& r, const float& g, const float& b, const float& a)
{
	mColor.Set(r, g, b, a);
}

//表示カラーを設定
void CImage::SetColor(const float& r, const float& g, const float& b)
{
	mColor.Set(r, g, b);
}

//表示カラーを取得
const CVector4& CImage::GetColor() const
{
	return mColor;
}

//アルファ値を設定
void CImage::SetAlpha(const float& alpha)
{
	mColor.W(alpha);
}

//アルファ値を取得
const float& CImage::GetAlpha() const
{
	return mColor.W();
}

//描画
void CImage::Render()
{
	//テクスチャが読み込まれてなければ、描画処理は行わない
	if (mpTexture == nullptr) return;

	//2D描画用のプロジェクション行列を設定
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);

	//モデルビュー行列を初期化
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//カリング無効
	glDisable(GL_CULL_FACE);
	//ライティング無効
	glDisable(GL_LIGHTING);
	//デプステスト無効
	glDisable(GL_DEPTH_TEST);
	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//テクスチャを指定
	glBindTexture(GL_TEXTURE_2D, mpTexture->Id());

	glBegin(GL_TRIANGLES);
	// 表示カラーを設定
	glColor4fv((GLfloat*)&mColor);

	float uvLeft = mUV.X();
	float uvTop = mUV.Y();
	float uvRight = mUV.Z();
	float uvBottom = mUV.W();

	float vtxLeft = mPosition.X();
	float vtxRight = vtxLeft + mSize.X();
	//OpenGLは左下原点なので、左上が原点になるよう調整
	float vtxBottom = WINDOW_HEIGHT - mPosition.Y();
	float vtxTop = vtxBottom - mSize.Y();

	glTexCoord2f(uvLeft, uvTop);
	glVertex2d(vtxLeft, vtxTop);

	glTexCoord2f(uvLeft, uvBottom);
	glVertex2d(vtxLeft, vtxBottom);

	glTexCoord2f(uvRight, uvBottom);
	glVertex2d(vtxRight, vtxBottom);

	glTexCoord2f(uvLeft, uvTop);
	glVertex2d(vtxLeft, vtxTop);

	glTexCoord2f(uvRight, uvBottom);
	glVertex2d(vtxRight, vtxBottom);

	glTexCoord2f(uvRight, uvTop);
	glVertex2d(vtxRight, vtxTop);

	glEnd();

	//テクスチャを解放
	glBindTexture(GL_TEXTURE_2D, 0);
	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャを無効
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	//Popして元の行列に戻す（モデルビュー行列）
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);

	//Popして元の行列に戻す（プロジェクション行列）
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}