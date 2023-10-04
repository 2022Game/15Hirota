#include "CImage.h"

//�R���X�g���N�^
CImage::CImage()
	: mpTexture(nullptr)
	, mPosition(0.0f, 0.0f)
	, mSize(128.0f, 128.0f)
	, mUV(0.0f, 0.0f, 1.0f, 1.0f)
	, mColor(1.0f, 1.0f, 1.0f, 1.0f)
{
}

//�R���X�g���N�^�i�e�N�X�`���w��Łj
CImage::CImage(const char* path)
	: CImage()
{
	Load(path);
}

//�f�X�g���N�^
CImage::~CImage()
{
	//�e�N�X�`����ǂݍ���ł�����j��
	if (mpTexture != nullptr)
	{
		delete mpTexture;
	}
}

//�e�N�X�`���̓ǂݍ���
void CImage::Load(const char* path)
{
	mpTexture = new CTexture();
	bool success = mpTexture->Load(path);
	//�ǂݍ��ݐ���
	if (success)
	{
		//�\���T�C�Y���e�N�X�`���̃T�C�Y�ŏ�����
		const STgamHeader& header = mpTexture->Header();
		SetSize(header.width, header.height);
	}
	//�ǂݍ��ݎ��s
	else
	{
		//�e�N�X�`����j��
		delete mpTexture;
		mpTexture = nullptr;
	}
}

//�\�����W��ݒ�iCVector2�Łj
void CImage::SetPos(const CVector2& pos)
{
	mPosition = pos;
}

//�\�����W��ݒ�
void CImage::SetPos(const float& x, const float& y)
{
	SetPos(CVector2(x, y));
}

//�\�����W���擾
const CVector2& CImage::GetPos() const
{
	return mPosition;
}

//�\���T�C�Y��ݒ�iCVector2�Łj
void CImage::SetSize(const CVector2& size)
{
	mSize = size;
}

//�\���T�C�Y��ݒ�
void CImage::SetSize(const float& x, const float& y)
{
	SetSize(CVector2(x, y));
}

//�\���T�C�Y���擾
const CVector2& CImage::GetSize() const
{
	return mSize;
}

//�\������͈͂�ݒ�iCVector4�Łj
void CImage::SetUV(const CVector4& uv)
{
	mUV = uv;
}

//�\������͈͂�ݒ�
void CImage::SetUV(const float& left, const float& top, const float& right, const float& bottom)
{
	SetUV(CVector4(left, top, right, bottom));
}

//�\������͈͂��擾
const CVector4& CImage::GetUV() const
{
	return mUV;
}

//�\���J���[��ݒ�iCVector4�Łj
void CImage::SetColor(const CVector4& color)
{
	mColor = color;
}

//�\���J���[��ݒ�iCVector�Łj
void CImage::SetColor(const CVector& color)
{
	mColor = color;
}

//�\���J���[��ݒ�i�A���t�@�l�L��Łj
void CImage::SetColor(const float& r, const float& g, const float& b, const float& a)
{
	mColor.Set(r, g, b, a);
}

//�\���J���[��ݒ�
void CImage::SetColor(const float& r, const float& g, const float& b)
{
	mColor.Set(r, g, b);
}

//�\���J���[���擾
const CVector4& CImage::GetColor() const
{
	return mColor;
}

//�A���t�@�l��ݒ�
void CImage::SetAlpha(const float& alpha)
{
	mColor.W(alpha);
}

//�A���t�@�l���擾
const float& CImage::GetAlpha() const
{
	return mColor.W();
}

//�`��
void CImage::Render()
{
	//�e�N�X�`�����ǂݍ��܂�ĂȂ���΁A�`�揈���͍s��Ȃ�
	if (mpTexture == nullptr) return;

	glPushMatrix();

	glLoadIdentity();

	//�e�N�X�`����L���ɂ���
	glEnable(GL_TEXTURE_2D);
	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//�e�N�X�`�����w��
	glBindTexture(GL_TEXTURE_2D, mpTexture->Id());

	glBegin(GL_TRIANGLES);
	// �\���J���[��ݒ�
	glColor4fv((GLfloat*)&mColor);

	float uvLeft = mUV.X();
	float uvTop = mUV.Y();
	float uvRight = mUV.Z();
	float uvBottom = mUV.W();

	float vtxLeft = mPosition.X();
	float vtxRight = vtxLeft + mSize.X();
	//OpenGL�͍������_�Ȃ̂ŁA���オ���_�ɂȂ�悤����
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

	//�e�N�X�`�������
	glBindTexture(GL_TEXTURE_2D, 0);
	//�A���t�@�u�����h�𖳌�
	glDisable(GL_BLEND);
	//�e�N�X�`���𖳌�
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
