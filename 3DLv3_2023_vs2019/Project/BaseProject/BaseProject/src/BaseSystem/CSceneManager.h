#pragma once
#include "CSceneBase.h"
#include "SceneType.h"

class CSceneManager
{
public:
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static CSceneManager* Instance();
	// �C���X�^���X��j��
	static void ClearInstance();

	// �V�[���ǂݍ���
	void LoadScene(EScene scene);
	// �ǂݍ���ł���V�[����j��
	void UnloadScene();

	/// <summary>
	/// ���ݓǂݍ���ł���V�[���̎�ނ��擾
	/// </summary>
	/// <returns>�V�[���̎�ށieNone�̏ꍇ�̓V�[�����ǂݍ��܂�Ă��Ȃ��j</returns>
	EScene GetCurrentScene() const;

	// �ǂݍ���ł���V�[���̍X�V����
	void Update();

private:
	// �R���X�g���N�^
	CSceneManager();
	// �f�X�g���N�^
	~CSceneManager();

	// �V�[���}�l�[�W���̃C���X�^���X
	static CSceneManager* mpInstance;
	// ���ݓǂݍ���ł���V�[��
	CSceneBase* mpScene;
};