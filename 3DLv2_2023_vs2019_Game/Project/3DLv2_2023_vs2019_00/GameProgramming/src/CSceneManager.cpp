#include "CSceneManager.h"
#include "CTitleScene.h"
#include "CGameScene.h"

CSceneManager* CSceneManager::mpInstance = nullptr;

//�C���X�^���X���擾
CSceneManager* CSceneManager::Instance()
{
	//�C���X�^���X�����݂��Ȃ��ꍇ�͐V������������
	if (mpInstance == nullptr)
	{
		mpInstance = new CSceneManager();
	}
	return mpInstance;
}

//�C���X�^���X��j��
void CSceneManager::ClearInstance()
{
	delete mpInstance;
	mpInstance = nullptr;
}

//�R���X�g���N�^
CSceneManager::CSceneManager()
	:mpScene(nullptr)
	,mNextScene(EScene::eNone)
{
}

//�f�X�g���N�^
CSceneManager::~CSceneManager()
{
	//�ǂݍ���ł���V�[��������΁A�j������
	UnloadScene();
}

//�V�[���ǂݍ���
void CSceneManager::LoadScene(EScene scene)
{
	//���ɓǂݍ��ރV�[����ݒ�
	mNextScene = scene;

	////���łɃV�[�����ǂݍ��܂�Ă�����A
	////���̃V�[����j��
	//UnloadScene();

	////�ǂݍ��ރV�[���̎�ނɍ��킹��
	////��������V�[���̃N���X��ύX����
	//switch (scene)
	//{
	//	//�^�C�g���V�[��
	//case EScene::eTitle:	mpScene = new CTitleScene();	break;
	//	//�Q�[���V�[��
	//case EScene::eGame:		mpScene = new CGameScene();		break;
	//}

	////�V�[����V��������������ǂݍ���
	////�V�[���ǂݍ��݊J�n
	//if (mpScene != nullptr)
	//{
	//	mpScene->Load();
	//}
}

//�ǂݍ���ł���V�[����j��
void CSceneManager::UnloadScene()
{
	delete mpScene;
	mpScene = nullptr;
}

void CSceneManager::LoadNextScene()
{
	//���łɃV�[�����ǂݍ��܂�Ă�����
	//���̃V�[����j��
	UnloadScene();

	//�ǂݍ��ރV�[���̎�ނɍ��킹��
	//��������V�[���̃N���X��ύX����
	switch (mNextScene)
	{
		//�^�C�g���V�[��
	case EScene::eTitle:	mpScene = new CTitleScene(); break;
		//�Q�[���̃V�[��
	case EScene::eGame:		mpScene = new CGameScene();  break;
	}

	//�V�[����V��������������ǂݍ���
	//�V�[���ǂݍ��݊J�n
	if (mpScene != nullptr)
	{
		mpScene->Load();
	}
	//���̃V�[���̓ǂݍ��݂��I������̂�
	//���̃V�[���̃^�C�v�͏�����
	mNextScene = EScene::eNone;
}

//�ǂݍ���ł���V�[���̍X�V����
void CSceneManager::Update()
{
	//�V�[�����ǂݍ��܂�Ă�����A�V�[���X�V
	if (mpScene != nullptr)
	{
		mpScene->Update();
	}

	//���̃V�[�����ݒ肳��Ă�����A���̃V�[���ǂݍ���
	if (mNextScene != EScene::eNone)
	{
		LoadNextScene();
	}
	////�V�[�����ǂݍ��܂�Ă��Ȃ��ꍇ�́A�������Ȃ�
	//if (mpScene == nullptr) return;
	////�V�[���X�V
	//mpScene->Update();
}