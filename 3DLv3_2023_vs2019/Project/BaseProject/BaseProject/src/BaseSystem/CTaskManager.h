#pragma once
#include "CTask.h"

/// <summary>
/// �^�X�N�Ǘ��N���X
/// </summary>
class CTaskManager
{
public:
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static CTaskManager* Instance();
	// �C���X�^���X��j��
	static void ClearInstance();

	/// <summary>
	/// �w�肵���^�X�N�����X�g�ɒǉ�
	/// </summary>
	/// <param name="task">�ǉ�����^�X�N</param>
	void Add(CTask* task);
	/// <summary>
	/// �w�肵���^�X�N�����X�g�����菜��
	/// </summary>
	/// <param name="task">��菜���^�X�N</param>
	void Remove(CTask* task);

	// �폜�t���O�������Ă���^�X�N��S�č폜
	void Delete();
	/// <summary>
	/// �w�肵���V�[���ɏ�������^�X�N��S�č폜
	/// </summary>
	/// <param name="scene">�폜����V�[���̎��</param>
	void DeleteInScene(EScene scene);

	// �X�V
	void Update();
	// �`��
	void Render();

	void Collision();

private:
	// �R���X�g���N�^
	CTaskManager();
	// �f�X�g���N�^
	~CTaskManager();

	// �^�X�N�}�l�[�W���̃C���X�^���X
	static CTaskManager* mpInstance;

	// ������
	void Initialize();

	CTask* mpHead;	// �擪�^�X�N
	CTask* mpTail;	// �ŏI�^�X�N
};
