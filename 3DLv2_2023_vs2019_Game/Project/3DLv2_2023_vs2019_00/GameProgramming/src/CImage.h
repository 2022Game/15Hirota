#ifndef CIMAGE_H
#define CIMAGE_H
#include "CVector.h"
#include "CTexture.h"

//2D�C���[�W�`��p�N���X
//�ǂݍ���CTexture��2D�\������
class CImage
{
private:
	CTexture* mpTexture;	//�\������C���[�W�̃e�N�X�`��
	CVector2 mPosition;		//�\�����W
	CVector2 mSize;			//�\���T�C�Y
	CVector4 mUV;			//�\������e�N�X�`����͈̔́iUV�j
	CVector4 mColor;		//�\���J���[

public:
	//�R���X�g���N�^
	CImage();
	//�R���X�g���N�^�i�e�N�X�`���w��Łj
	CImage(const char* path);
	//�f�X�g���N�^
	~CImage();

	//�e�N�X�`���̓ǂݍ���
	void Load(const char* path);

	//�\�����W��ݒ�iCVector2�Łj
	void SetPos(const CVector2& pos);
	//�\�����W��ݒ�
	void SetPos(const float& x, const float& y);
	//�\�����W���擾
	const CVector2& GetPos() const;

	//�\���T�C�Y��ݒ�iCVector2�Łj
	void SetSize(const CVector2& size);
	//�\���T�C�Y��ݒ�
	void SetSize(const float& x, const float& y);
	//�\���T�C�Y���擾
	const CVector2& GetSize() const;

	//�\������͈͂�ݒ�iCVector4�Łj
	void SetUV(const CVector4& uv);
	//�\������͈͂�ݒ�
	void SetUV(const float& left, const float& top, const float& right, const float& bottom);
	//�\������͈͂��擾
	const CVector4& GetUV() const;

	//�\���J���[��ݒ�iCVector4�Łj
	void SetColor(const CVector4& color);
	//�\���J���[��ݒ�iCVector�Łj
	void SetColor(const CVector& color);
	//�\���J���[��ݒ�i�A���t�@�l�L��Łj
	void SetColor(const float& r, const float& g, const float& b, const float& a);
	//�\���J���[��ݒ�
	void SetColor(const float& r, const float& g, const float& b);
	//�\���J���[���擾
	const CVector4& GetColor() const;

	//�A���t�@�l��ݒ�
	void SetAlpha(const float& alpha);
	//�A���t�@�l���擾
	const float& GetAlpha() const;

	//�`��
	void Render();
};

#endif