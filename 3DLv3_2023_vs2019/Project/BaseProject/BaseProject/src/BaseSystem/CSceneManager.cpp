#include "CSceneManager.h"
#include "CTitleScene.h"
#include "CGameScene.h"

// �V�[���}�l�[�W���̃C���X�^���X
CSceneManager* CSceneManager::mpInstance = nullptr;

// �C���X�^���X���擾
CSceneManager* CSceneManager::Instance()
{
	// �C���X�^���X�����݂��Ȃ��ꍇ�͐V������������
	if (mpInstance == nullptr)
	{
		mpInstance = new CSceneManager();
	}
	return mpInstance;
}

// �C���X�^���X��j��
void CSceneManager::ClearInstance()
{
	delete mpInstance;
	mpInstance = nullptr;
}

// �R���X�g���N�^
CSceneManager::CSceneManager()
	: mpScene(nullptr)
{
}

// �f�X�g���N�^
CSceneManager::~CSceneManager()
{
	// �ǂݍ���ł���V�[��������΁A�j������
	UnloadScene();
}

//�V�[���ǂݍ���
void CSceneManager::LoadScene(EScene scene)
{
	//���ɃV�[�����ǂݍ��܂�Ă�����A
	//���̃V�[����j��
	UnloadScene();

	//�ǂݍ��ރV�[���̎�ނɍ��킹��
	//��������V�[���̃N���X��ύX����
	switch (scene)
	{
		//�^�C�g���V�[��
	case EScene::eTitle:   mpScene = new CTitleScene();   break;
		//�Q�[���V�[��
	case EScene::eGame:    mpScene = new CGameScene();    break;
	}

	//�V�[����V���������ł�����A
	//�V�[���ǂݍ��݊J�n
	if (mpScene != nullptr)
	{
		mpScene->Load();
	}
}

// �ǂݍ���ł���V�[����j��
void CSceneManager::UnloadScene()
{
	delete mpScene;
	mpScene = nullptr;
}

// ���ݓǂݍ���ł���V�[���̎�ނ��擾
EScene CSceneManager::GetCurrentScene() const
{
	if (mpScene == nullptr) return EScene::eNone;
	return mpScene->GetSceneType();
}

//�ǂݍ���ł���V�[���̍X�V����
void CSceneManager::Update()
{
	//�V�[�����ǂݍ��܂�Ă��Ȃ��ꍇ�́A�������Ȃ�
	if (mpScene == nullptr) return;
	//�V�[���X�V
	mpScene->Update();
}
