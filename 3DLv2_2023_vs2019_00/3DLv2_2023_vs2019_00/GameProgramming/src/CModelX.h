#ifndef CMODELX_H	//�C���N���[�h
#define CMODELX_H

#define MODEL_FILE "res\\sample.blend.x"	//���̓t�@�C����

//���Ȉ�J�����}�N����
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a;a = nullptr;}
/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
public:
	CModelX();
	//�t�@�C���ǂݍ���
	void Load(char* file);
private:
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
};
#endif