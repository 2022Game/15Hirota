#ifndef CSCENEMANAGER_H
#define CSCENEMANAGER_H

#include "CSceneBase.h"
#include "SceneType.h"

//�V�[�����Ǘ�����N���X
class CSceneManager
{
public:
	//�C���X�^���X���擾
	static CSceneManager* Instance();
	//�C���X�^���X��j��
	static void ClearInstance();
	//�V�[���ǂݍ���
	void LoadScene(EScene scene);
	//�ǂݍ���ł���V�[����j��
	void UnloadScene();
	//�ǂݍ���ł���V�[���̍X�V����
	void Update();

private:
	//�R���X�g���N�^
	CSceneManager();
	//�f�X�g���N�^
	~CSceneManager();

	//���̃V�[����ǂݍ���
	void LoadNextScene();

	//CSceneManager�̃C���X�^���X
	static CSceneManager* mpInstance;
	//���ݓǂݍ���ł���V�[��
	CSceneBase* mpScene;
	//���ɓǂݍ��ރV�[��
	EScene mNextScene;
};
#endif