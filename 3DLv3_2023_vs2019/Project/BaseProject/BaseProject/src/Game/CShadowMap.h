#ifndef CSHADOWMAP_H
#define CSHADOWMAP_H

/// <summary>
/// �Q�l�L�� : https://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20050926
/// </summary>

class CShadowMap
{
	// �����̈ʒu
	GLfloat mLightPos[3];
	// �e�̐F
	GLfloat mShadowCol[4];
	// �f�v�X�e�N�X�`���̕�
	int mTextureWidth;
	// �f�v�X�e�N�X�`���̍���
	int mTextureHeight;
	// GLuint : �����Ȃ������^
	// �f�v�X�e�N�X�`��ID
	GLuint mDepthTextureID;
	// �t���[���o�b�t�@���ʎq
	GLuint mFb;
	// Render�֐��̃|�C���^
	void(*mpRender)();
	// ����������
	void Init();
public:
	// �R���X�g���N�^
	CShadowMap();
	// �f�X�g���N�^
	~CShadowMap();
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="width">�f�v�X�e�N�X�`���̕�</param>
	/// <param name="height">�f�v�X�e�N�X�`���̍���</param>
	/// <param name="funcRender">�`��֐��̃|�C���^</param>
	/// <param name="shadowCol">�e�̐F</param>
	/// <param name="lightPos">�����̈ʒu</param>
	void Init(int width, int height, void (*funcRender)(), float shadowCol[], float lightPos[]);
	// �`�揈��
	void Render();
};
#endif