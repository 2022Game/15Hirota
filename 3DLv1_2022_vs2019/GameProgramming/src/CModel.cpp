#include "CModel.h"
//�W�����͂̃C���N���[�h
#include <stdio.h>

//���f���t�@�C���̓���
//Load(���f���t�@�C�����A�}�e���A���t�@�C����)
void CModel::Load(char* obj, char* mtl) {
	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp;
	//�t�@�C������f�[�^�����
	//���̓G���A���쐬����
	char buf[256];

		//�t�@�C���̃I�[�v�� "mtl"
		//fopen(�t�@�C�����A���[�h)
		//�I�[�v���ł��Ȃ��Ƃ���NULL��Ԃ�
		fp = fopen(mtl, "r");
	//�t�@�C���I�[�v���G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[�o�͂��Ė߂�
		printf("%s file open error\n", mtl);
		return;
	}
	//�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//���͂����l���R���\�[���ɏo�͂���
		printf("%s", buf);
	}
	//�t�@�C���̃N���[�Y
	fclose(fp);

	//	�t�@�C���̃I�[�v�� "obj"
	//fopen(�t�@�C�����A���[�h)
	//�I�[�v���ł��Ȃ��Ƃ���NULL��Ԃ�
	fp = fopen(obj, "r");
	//�t�@�C���I�[�v���G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[���o�͂��Ė߂�
		printf("%s file open error\n", obj);
		return;
	}
	//�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//���͂����l���R���\�[���ɏo�͂���
		printf("%s", buf);
	}
	//�t�@�C���̃N���[�Y
	fclose(fp);

}
